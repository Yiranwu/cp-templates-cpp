import sys
import os
import re
import json
from collections import deque

# Configuration
DEFAULT_OUTPUT_DIR = "outputs"
DEFAULT_CACHE_FILE = os.path.join(DEFAULT_OUTPUT_DIR, ".dependencies.json")

class DependencyManager:
    def __init__(self, cache_file):
        self.cache_file = cache_file
        self.adj = {} # file -> list of included files (absolute paths)
        self.files = set()
        self.timestamps = {} # filepath -> mtime

    def scan_directory(self, root_dir):
        """Scans a directory for .h and .cpp files and parses includes."""
        root_dir = os.path.abspath(root_dir)
        for dirpath, _, filenames in os.walk(root_dir):
            for filename in filenames:
                if filename.endswith(('.h', '.cpp', '.hpp')):
                    filepath = os.path.join(dirpath, filename)
                    self.parse_file(filepath)

    def parse_file(self, filepath):
        """Parses a single file for includes and updates the graph."""
        filepath = os.path.abspath(filepath)
        self.files.add(filepath)
        
        if not os.path.exists(filepath):
            return

        try:
            self.timestamps[filepath] = os.path.getmtime(filepath)
        except OSError:
            return

        if filepath not in self.adj:
            self.adj[filepath] = []
            
        with open(filepath, 'r') as f:
            try:
                content = f.read()
            except UnicodeDecodeError:
                return # Skip binary files if any

        # Regex to match #include "..."
        # We rely on the convention that library includes use quotes.
        matches = re.findall(r'^\s*#include\s*"([^"]+)"', content, re.MULTILINE)
        
        current_dir = os.path.dirname(filepath)
        
        # Reset dependencies for this file as we are re-parsing
        self.adj[filepath] = []

        for include_path in matches:
            # Resolve path
            # Strategy: 
            # 1. Relative to current file
            # 2. Relative to project root (common in CP, e.g. "cf-lib/...")
            
            candidates = [
                os.path.join(current_dir, include_path),
                os.path.abspath(include_path) # Assumes include_path is relative to CWD (project root)
            ]
            
            resolved = None
            for cand in candidates:
                cand = os.path.abspath(cand)
                if os.path.exists(cand):
                    resolved = cand
                    break
            
            if resolved:
                # Add edge: filepath depends on resolved
                if resolved not in self.adj[filepath]:
                    self.adj[filepath].append(resolved)

    def save_cache(self):
        # Create output dir if needed
        cache_dir = os.path.dirname(self.cache_file)
        if cache_dir and not os.path.exists(cache_dir):
            os.makedirs(cache_dir, exist_ok=True)
            
        with open(self.cache_file, 'w') as f:
            json.dump({
                'adj': self.adj,
                'timestamps': self.timestamps
            }, f, indent=2)
        print(f"Dependencies saved to {self.cache_file}")

    def load_cache(self):
        if not os.path.exists(self.cache_file):
            return False
        try:
            with open(self.cache_file, 'r') as f:
                data = json.load(f)
                self.adj = data.get('adj', {})
                self.timestamps = data.get('timestamps', {})
            
            # Check for staleness
            # We iterate over a copy of keys because we might modify graph
            for filepath in list(self.adj.keys()):
                if not os.path.exists(filepath):
                    # File deleted, remove from graph logic could be complex, 
                    # but for now we just verify existence.
                    continue
                
                try:
                    current_mtime = os.path.getmtime(filepath)
                    cached_mtime = self.timestamps.get(filepath, 0)
                    if current_mtime != cached_mtime:
                        print(f"File changed, re-scanning: {filepath}")
                        self.parse_file(filepath)
                except OSError:
                    pass
                    
            return True
        except Exception as e:
            print(f"Failed to load cache: {e}")
            return False

    def get_dependencies(self, root_files):
        """Returns a topologically sorted list of files required by root_files."""
        # BFS/DFS to find all reachable nodes
        visited = set()
        queue = deque(root_files)
        subgraph_nodes = set()
        
        while queue:
            node = queue.popleft()
            node = os.path.abspath(node)
            if node in visited:
                continue
            visited.add(node)
            subgraph_nodes.add(node)
            
            # If node is in our graph, add its children
            if node in self.adj:
                for child in self.adj[node]:
                    queue.append(child)
            else:
                # Lazy parse if encountered but not in graph
                if os.path.exists(node):
                    self.parse_file(node)
                    if node in self.adj:
                         for child in self.adj[node]:
                            queue.append(child)

        # Topological Sort on subgraph
        # Graph: A includes B => A->B
        # Limit processing to subgraph_nodes
        
        # Calculate in-degrees (number of files including me)
        # Wait, if A includes B, we need B before A.
        # So in output order: B, then A.
        # This is reverse topological sort if Edge is A->B.
        # Or standard topo sort if Edge is Dependency->Dependent (B->A).
        # Our adj is A->B (A includes B).
        # So we want post-order DFS (visit children, then self).
        
        result = []
        visited_sort = set()
        temp_mark = set() # for cycle detection

        def visit(n):
            if n in visited_sort:
                return
            if n in temp_mark:
                # Cycle detected
                # In CP headers, #ifndef guards prevent infinite recursion, 
                # but for hoisting, cycle is ambiguous. We just proceed.
                return
            
            temp_mark.add(n)
            
            if n in self.adj:
                for child in self.adj[n]:
                    if child in subgraph_nodes:
                        visit(child)
            
            temp_mark.remove(n)
            visited_sort.add(n)
            result.append(n)

        for node in root_files:
            visit(os.path.abspath(node))
            
        return result


def process_file_content(filepath):
    """Reads file and returns content with local includes stripped."""
    with open(filepath, 'r') as f:
        lines = f.readlines()
    
    result = []
    # Strip includes that use quotes #include "..."
    # Keep others.
    # Also strip #pragma once if present
    
    for line in lines:
        if re.match(r'^\s*#pragma\s+once', line):
            continue
        if re.match(r'^\s*#include\s*"[^"]+"', line):
            # We assume these are the bundled libraries.
            # Ideally we should check if they are in our dependency graph, 
            # but stripping all quoted includes is a safe heuristic for CP templates 
            # where all such includes are being bundled.
            continue
        result.append(line)
        
    return "".join(result)


def main():
    import argparse
    parser = argparse.ArgumentParser(description='Bundle C++ files with dependency management.')
    parser.add_argument('input_file', nargs='?', default='main.cpp', help='Input file (default: main.cpp)')
    parser.add_argument('output_file', nargs='?', help='Output file')
    parser.add_argument('--scan', action='store_true', help='Force re-scan of dependencies')
    parser.add_argument('--deps-file', default=DEFAULT_CACHE_FILE, help='Path to dependency cache file')
    
    args = parser.parse_args()
    
    input_file = os.path.abspath(args.input_file)
    
    if args.output_file:
        output_file = args.output_file
    else:
        if not os.path.exists(DEFAULT_OUTPUT_DIR):
            os.makedirs(DEFAULT_OUTPUT_DIR)
        output_file = os.path.join(DEFAULT_OUTPUT_DIR, "output.cpp")

    manager = DependencyManager(args.deps_file)

    # Step 1: Cache Loading / Scanning
    if args.scan or not manager.load_cache():
        print("Scanning dependencies...")
        manager.scan_directory("cf-lib")
        manager.scan_directory("template")
        manager.save_cache()
    
    # Step 2: Parse Main File Ad-hoc (to find roots)
    # We must scan main.cpp to see what it includes. But we don't save main.cpp to cache usually.
    manager.parse_file(input_file)
    
    # Step 3: Compute Order
    # We want everything main.cpp depends on, ordered.
    # The list returned by get_dependencies(X) ends with X.
    # So dependencies come first.
    
    files_to_bundle = manager.get_dependencies([input_file])
    
    # Step 4: Generate Output
    with open(output_file, 'w') as out:
        # Add a header
        out.write(f"// Bundled from {os.path.basename(input_file)}\n")
        out.write("// Auto-generated by expand.py\n\n")
        
        for filepath in files_to_bundle:
            out.write(f"// Start of {os.path.basename(filepath)}\n")
            out.write(process_file_content(filepath))
            out.write(f"\n// End of {os.path.basename(filepath)}\n\n")
            
    print(f"Generated {output_file}")


if __name__ == "__main__":
    main()
