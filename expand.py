import sys
import os
import re

# Set of included files to prevent cycles and duplicates (implementing pragma once behavior)
included_files = set()

def expand_file(filepath, output_lines):
    # Resolve absolute path
    abs_path = os.path.abspath(filepath)
    if abs_path in included_files:
        return
    included_files.add(abs_path)
    
    if not os.path.exists(abs_path):
        print(f"Error: File not found: {abs_path}")
        return

    with open(abs_path, 'r') as f:
        lines = f.readlines()
    
    # Check for #pragma once (simple check)
    # If we relying on manual include guards, we might need more complex logic.
    # But since we track 'included_files' manually, we effectively enforce #pragma once for everything expanded.
    
    for line in lines:
        # Match #include "..."
        # We assume local includes use quotes. System includes use brackets.
        # Regex to capture content in quotes
        match = re.match(r'^\s*#include\s*"([^"]+)"', line)
        if match:
            include_path = match.group(1)
            # Determine full path. Relative to current file directory.
            # But the user might run this script from root.
            # We assume include paths are either relative to the file or relative to project root.
            # In CP templates, usually "cf-lib/..." is relative to project root.
            # If the file is included as "cp_template.h" inside "cf-lib/", it refers to "cf-lib/cp_template.h".
            
            current_dir = os.path.dirname(abs_path)
            candidate_path_rel = os.path.join(current_dir, include_path)
            candidate_path_root = os.path.join(os.getcwd(), include_path)
            
            if os.path.exists(candidate_path_rel):
                expand_file(candidate_path_rel, output_lines)
            elif os.path.exists(candidate_path_root):
                expand_file(candidate_path_root, output_lines)
            else:
                # Fallback: keep the line as is if file not found (maybe it's a specific local header not meant to be expanded?)
                # Or print error.
                print(f"Warning: Could not resolve include: {include_path} in {abs_path}")
                output_lines.append(line)
        else:
            # Check for #pragma once. If found, ignore it, since we handle it logic side.
            if re.match(r'^\s*#pragma\s+once', line):
                continue
            output_lines.append(line)

def main():
    if len(sys.argv) > 1:
        input_file = sys.argv[1]
    else:
        input_file = "main.cpp"
    
    if len(sys.argv) > 2:
        output_file = sys.argv[2]
    else:
        # Default to outputs/output.cpp
        output_dir = "outputs"
        if not os.path.exists(output_dir):
            os.makedirs(output_dir)
        output_file = os.path.join(output_dir, "output.cpp")
    
    output_lines = []
    # Clear included_files for fresh run (though script runs once)
    included_files.clear()
    
    # We want to process the input file, but NOT ignore it if we see it again? 
    # Actually, the input file is the root.
    # We shouldn't add input_file to included_files immediately if we want to allow it to be self-contained, 
    # but normally we just expand it.
    
    # However, 'expand_file' checks included_files first. 
    # So we call expand_file on input_file.
    
    expand_file(input_file, output_lines)
    
    content = "".join(output_lines)
    
    if output_file:
        with open(output_file, 'w') as f:
            f.write(content)
        print(f"Generated {output_file}")
    else:
        print(content)

if __name__ == "__main__":
    main()
