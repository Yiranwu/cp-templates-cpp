import sys
import os
import subprocess
import argparse
import time

# ANSI color codes
GREEN = '\033[92m'
RED = '\033[91m'
YELLOW = '\033[93m'
RESET = '\033[0m'
BOLD = '\033[1m'


def run_solution(exec_file, input_file, output_file):
    with open(input_file, 'r') as fin, open(output_file, 'w') as fout:
        try:
            # Timeout set to 2 seconds to catch TLE
            subprocess.run([exec_file], stdin=fin, stdout=fout, stderr=subprocess.PIPE, check=True, timeout=2.0)
            return True
        except subprocess.TimeoutExpired:
            print(f"{RED}Time Limit Exceeded (2.0s){RESET}")
            return False
        except subprocess.CalledProcessError as e:
            print(f"{RED}Runtime Error (Exit code: {e.returncode}){RESET}")
            return False

def main():
    parser = argparse.ArgumentParser(description="Stress test your CP solution.")
    parser.add_argument("--gen", default="./debugging/generate_test_case.cpp", help="Path to generator C++ file")
    parser.add_argument("--sol", default="./main.cpp", help="Path to your solution C++ file")
    parser.add_argument("--gt", default="./debugging/gt_sol.cpp", help="Path to ground truth C++ file")
    parser.add_argument("--iter", type=int, default=1000, help="Number of iterations")
    args = parser.parse_args()

    # Expand paths
    gen_src = os.path.abspath(args.gen)
    sol_src = os.path.abspath(args.sol)
    gt_src = os.path.abspath(args.gt)
    
    # Check if files exist
    for f in [gen_src, sol_src, gt_src]:
        if not os.path.exists(f):
            print(f"{RED}Error: File not found: {f}{RESET}")
            sys.exit(1)

    # Executable names
    gen_exec = "./gen.exe"
    sol_exec = "./sol.exe"
    gt_exec = "./gt.exe"
    
    # Input/Output files
    files = ["input.txt", "my_out.txt", "gt_out.txt"]
    
    # Compilation Command Construction
    # default fallback
    default_cmd = ["g++", "-O2", "-std=c++20", "{src}", "-o", "{exe}", "-DLOCAL"]
    
    # Try to find compile_commands.json
    compile_db_paths = [
        "compile_commands.json",
        "build/compile_commands.json",
        "cmake-build-debug/compile_commands.json",
        "cmake-build-release/compile_commands.json"
    ]
    
    found_cmd = None
    for db_path in compile_db_paths:
        if os.path.exists(db_path):
            print(f"{GREEN}Found compile database at {db_path}{RESET}")
            try:
                import json
                with open(db_path, 'r') as f:
                    data = json.load(f)
                    # Find command for the solution file
                    # We look for an entry where 'file' ends with the solution filename
                    sol_abs = os.path.abspath(args.sol)
                    entry = next((e for e in data if os.path.abspath(e['file']) == sol_abs), None)
                    
                    if not entry and len(data) > 0:
                        # Fallback: try to find ANY cpp file's flags if exact match fail
                        entry = next((e for e in data if e['file'].endswith(".cpp")), None)
                        if entry:
                             print(f"{YELLOW}Exact match for {args.sol} not found in DB, using flags from {entry['file']}{RESET}")

                    if entry:
                        # Extract command
                        # "command": "/usr/bin/c++ ... -o CMakeFiles/Target.dir/main.cpp.o -c /path/to/main.cpp"
                        # We need to strip the input file, the output object, and '-c'
                        raw_parts = entry['command'].split()
                        
                        # Reconstruct command
                        # 1. Compiler is first arg
                        # 2. Filter out -o <obj>, -c <src>, and the src execution
                        # 3. Add -DLOCAL if not present? (Usually Cmake has it)
                        
                        clean_cmd = []
                        skip_next = False
                        for part in raw_parts:
                            if skip_next:
                                skip_next = False
                                continue
                            if part == "-o":
                                skip_next = True
                                continue
                            if part == "-c":
                                continue
                            if os.path.abspath(part) == os.path.abspath(entry['file']):
                                continue
                            clean_cmd.append(part)
                            
                        # Now we have [compiler, flags...]
                        # Add {src} to {exe} template
                        clean_cmd.extend(["{src}", "-o", "{exe}"])
                        found_cmd = clean_cmd
                        print(f"{GREEN}Auto-detected flags: {' '.join(found_cmd)}{RESET}")
                        break
            except Exception as e:
                print(f"{RED}Failed to parse compile_commands.json: {e}{RESET}")

    if found_cmd:
        compile_template = found_cmd
    else:
        # If user provided a manual command string (TODO: Add argument for this if needed), use that
        # otherwise default
        compile_template = default_cmd
        print(f"{YELLOW}Using default compilation command: {' '.join(default_cmd)}{RESET}")


    import shutil

    try:
        # Helper to compile a specific file
        # We might need to move the file to the same directory as the solution
        # to ensure relative includes work as if it were the solution file.
        def compile_target(src_path, output_exec, use_sol_dir=False):
            target_src = src_path
            temp_src = None
            
            # If we need to mimic being in the solution dir
            if use_sol_dir:
                sol_dir = os.path.dirname(os.path.abspath(args.sol))
                src_dir = os.path.dirname(os.path.abspath(src_path))
                
                # If the file is not already in the solution dir, copy it there
                if sol_dir != src_dir:
                    basename = os.path.basename(src_path)
                    # Add a prefix to avoid collision
                    temp_src = os.path.join(sol_dir, f"_temp_stress_{basename}")
                    print(f"{YELLOW}Copying {src_path} to {temp_src} for compilation context...{RESET}")
                    shutil.copy(src_path, temp_src)
                    target_src = temp_src

            try:
                # Substitute {src} and {exe}
                # Note: compile_template is a list if defaults, or from JSON split
                cmd_list = [arg.replace("{src}", target_src).replace("{exe}", output_exec) for arg in compile_template]
                
                print(f"Compiling {target_src}...")
                res = subprocess.run(cmd_list, capture_output=True, text=True)
                if res.returncode != 0:
                     print(f"{RED}Compilation failed for {target_src}:{RESET}")
                     print(res.stderr)
                     sys.exit(1)
                print(f"{GREEN}Compiled {target_src} successfully.{RESET}")
            finally:
                # Clean up temp file
                if temp_src and os.path.exists(temp_src):
                    os.remove(temp_src)

        # Compile Generator (usually doesn't need strict context, but safe to use)
        compile_target(gen_src, gen_exec, use_sol_dir=True)
        
        # Compile Solution (already in place)
        compile_target(sol_src, sol_exec, use_sol_dir=False)
        
        # Compile Ground Truth (NEEDS to be in place)
        compile_target(gt_src, gt_exec, use_sol_dir=True)
        
        print(f"\n{BOLD}Starting stress test for {args.iter} iterations...{RESET}\n")

        for i in range(1, args.iter + 1):
            print(f"Iteration {i}...", end="\r")
            
            # Generate Input
            # We pass iteration number as seed to generator if it accepts args, 
            # but simplest is generator handles randomness itself.
            # Capturing stdout of generator to write to input.txt
            with open("input.txt", "w") as fgen:
                subprocess.run([gen_exec, str(i)], stdout=fgen, check=True)
            
            # Run My Solution
            if not run_solution(sol_exec, "input.txt", "my_out.txt"):
                 print(f"\n{RED}My Solution failed at iteration {i}{RESET}")
                 print(f"\n{BOLD}Input:{RESET}")
                 with open("input.txt", "r") as f: print(f.read())
                 break

            # Run Ground Truth
            if not run_solution(gt_exec, "input.txt", "gt_out.txt"):
                 print(f"\n{RED}Ground Truth failed at iteration {i}{RESET}")
                 print(f"\n{BOLD}Input:{RESET}")
                 with open("input.txt", "r") as f: print(f.read())
                 break

            # Compare
            diff = subprocess.run(["diff", "-w", "-B", "my_out.txt", "gt_out.txt"], capture_output=True, text=True)
            
            if diff.returncode != 0:
                print(f"\n{RED}Mismatch found at iteration {i}!{RESET}")
                
                print(f"\n{BOLD}Input:{RESET}")
                with open("input.txt", "r") as f: print(f.read())
                
                print(f"\n{BOLD}Diff (My Output vs Ground Truth):{RESET}")
                print(diff.stdout)
                
                # Save the failing case
                subprocess.run(["cp", "input.txt", "wa_input.txt"])
                print(f"{BOLD}Failing input saved to 'wa_input.txt'{RESET}")
                break
        else:
            print(f"\n\n{GREEN}Passed all {args.iter} iterations!{RESET}")

    except KeyboardInterrupt:
        print(f"\n{BOLD}Stress test interrupted.{RESET}")
    finally:
        print(f"\n{YELLOW}Cleaning up executables...{RESET}")
        for f in [gen_exec, sol_exec, gt_exec]:
            if os.path.exists(f):
                os.remove(f)
        # We keep input.txt/my_out.txt/gt_out.txt as they might be useful for inspecting the last run

if __name__ == "__main__":
    main()
