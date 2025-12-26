SIGTRAP: usually caused by missing return value in functions.
all(__INITIALIZE_VECTOR__) will not work because all is a macro and two vectors will be created after substitution.

When deciding whether clearing result from last test cases is needed, keep in mind that there can be edge cases if n_new < n_old.
Then it will be problematic if you just undo first n_old entry, but in the new iteration can refer to entries larger than n_new.


// Sometimes unordered containers can be extremely slow
// https://codeforces.com/blog/entry/22947?locale=ru
// https://codeforces.com/blog/entry/132929
// A potential fix: R.max_load_factor(0.25);R.reserve(512);
// Also, prevent using clear() to reset, always create a new object.