//
// Generator Template
//
#include <iostream>
#include <vector>
#include <random>
#include <algorithm>
#include <chrono>

using namespace std;

// Random number generator
mt19937 rng(chrono::steady_clock::now().time_since_epoch().count());

// Helper functions
int rand_int(int l, int r) {
    return uniform_int_distribution<int>(l, r)(rng);
}

// Helper to print a vector
template<typename T>
void print_vec(const vector<T>& v) {
    for (int i = 0; i < v.size(); ++i) {
        cout << v[i] << (i == v.size() - 1 ? "" : " ");
    }
    cout << endl;
}

int main(int argc, char* argv[]) {
    // Optional: Allow passing seed as argument for reproducibility
    if (argc > 1) {
        rng.seed(atoi(argv[1]));
    }
    
    // ==========================================
    // TODO: Write your test case generator here
    // ==========================================
    
    // Example: Generate N (1..10) and an array of N integers (1..100)
    int n = rand_int(1, 10);
    cout << n << endl;
    
    vector<int> a(n);
    for (int i = 0; i < n; ++i) {
        a[i] = rand_int(1, 100);
    }
    print_vec(a);

    return 0;
}