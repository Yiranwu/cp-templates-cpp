# Automated Fail Case Finding

This directory contains tools to automatically find test cases where your solution fails (Wrong Answer or Runtime Error).

## Files
- `stress.py`: The main runner script.
- `generate_test_case.cpp`: Template for generating random test cases.
- `gt_sol.cpp`: Place for the Ground Truth solution (brute force or correct logic).
- `debug.sh`: (Deprecated) Old bash script.

## How to Usage

1.  **Prepare your solution**: Ensure your main solution is in `../main.cpp` (or specify path).
2.  **Prepare Ground Truth**: Write a correct (possibly slow) solution in `gt_sol.cpp`.
3.  **Prepare Generator**: Edit `generate_test_case.cpp` to output random valid inputs to `stdout`.

## Running the Stress Test

Run the python script from the root of the project (or anywhere, adjusting paths):

```bash
python3 debugging/stress.py
```

### Options
- `--iter N`: Run N iterations (default: 1000).
- `--gen PATH`: Path to generator file (default: `./debugging/generate_test_case.cpp`).
- `--sol PATH`: Path to your solution (default: `./main.cpp`).
- `--gt PATH`: Path to ground truth solution (default: `./debugging/gt_sol.cpp`).

Example:
```bash
python3 debugging/stress.py --iter 5000 --sol ./contest/A.cpp
```

## Output
- If a mismatch is found:
    - The script prints **Mismatch found at iteration X!**.
    - It prints the **Input** case.
    - It prints the **Diff** between your output and ground truth.
    - It saves the bad input to `wa_input.txt` for further debugging.

## Troubleshooting
- **Compilation Error**: The script checks compilation before running. Fix errors shown.
- **Runtime Error**: If your code or GT crashes, it stops and reports the error.
