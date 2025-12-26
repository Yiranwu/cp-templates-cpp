# Thinking Phase

## General Guideline

1. Read the description, reason about the problem.
2. If no immediate thoughts, go through the sample or try some examples.
3. If can't find a solution that satisfies time constraints, think of a more brute-force solution and then try to optimize by identifying how to reuse computation.
4. After having a coarse solution, always formalize it to look for missed aspects, and also to prepare for coding phase.

## Tips

1. For decision problem / combinatorial games, try parity.
2. For ~1000 constructive problem, try to think about upper/lower bounds, and then construct a solution that meets the bound
3. For problems where you need to handle both modification and questions to some underlying data, try to break the quantity of interest into a joint of multiple individual predicates, so that one modification only impacts very few of them.

# Coding Phase

## General Guideline

1. First things first, plan about how to structure the code, including how many sections we need, function of each section, what data structure to hold the data, etc.  
2. Implement reads, estimate and adjust MAXN according to problem description.
3. Better decide what array / STLs we need beforehand, and write statements to reset them at the start of every testcase.

## Tips

1. Try to not have duplicate code, because if you make mistake, you will forget to correct every occurrence.
2. When copy-pasting code for similar usages, be very careful to check whether every word is adapted to the new use case.

# Debugging Phase

## General Guideline

1. First check:
   1. Need larger MAXN?
   2. Whether data is cleared before next case.
   3. Arithmetic overflow
   4. Array out-of-bound errors
2. Eye-checking code to find mistakes in implementation.
   1. Boundary cases, soldier, range validity, one-pass-the-end
   2. Confusing variable X for Y, reusing loop variable, etc
3. If still WA, it's usually due to the following:
   1. Logical error in implementation
   2. Missing cases when analyzing the problem
   3. Incorrect solution
   4. Misunderstanding the problem

## Tips

1. When debugging, don't rely on step-to-step debugging heavily. You will quickly lose focus and forget about what you are doing. Think of several intermediate state to check before start debugging, this will give you some hint about what to find. Don't try to step debugging and verify every step, because it's very likely that you will fail to identify mistake.
