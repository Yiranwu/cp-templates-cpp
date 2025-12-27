#include <gtest/gtest.h>
#include <random>
#include <vector>
#include <numeric>
#include "cf-lib/ds/BIT.h"

// Test fixture
class BITTest : public ::testing::Test {
protected:
    void SetUp() override {}
    void TearDown() override {}
};

TEST_F(BITTest, PrefixSum) {
    FenwickTree<long long> bit(10);
    bit.add(1, 5);
    bit.add(3, 2);
    bit.add(5, 10);

    // [0, 1] sum is 5
    EXPECT_EQ(bit.prefixSum(1), 5);
    // [0, 2] sum is 5
    EXPECT_EQ(bit.prefixSum(2), 5);
    // [0, 3] sum is 5+2=7
    EXPECT_EQ(bit.prefixSum(3), 7);
    // [0, 5] sum is 5+2+10=17
    EXPECT_EQ(bit.prefixSum(5), 17);
}

TEST_F(BITTest, RangeSum) {
    FenwickTree<int> bit(5);
    bit.add(0, 1);
    bit.add(1, 2);
    bit.add(2, 3);
    
    // [0, 1) -> sum of index 0 -> 1
    EXPECT_EQ(bit.rangeSum(0, 1), 1);
    
    // [1, 3) -> sum of index 1, 2 -> 2+3=5
    EXPECT_EQ(bit.rangeSum(1, 3), 5);
    
    // [0, 3) -> 1+2+3 = 6
    EXPECT_EQ(bit.rangeSum(0, 3), 6);
}

TEST_F(BITTest, UpperBound) {
    FenwickTree<int> bit(10);
    // Works only for non-negative
    bit.add(1, 2);
    bit.add(2, 2);
    bit.add(3, 2);
    // prefix sums:
    // 0: 0
    // 1: 2
    // 2: 4
    // 3: 6
    // 4: 6
    
    EXPECT_EQ(bit.upper_bound(1), 1);
    EXPECT_EQ(bit.upper_bound(3), 2);
    EXPECT_EQ(bit.upper_bound(7), 11); // n+1
}

TEST_F(BITTest, BoundaryCases) {
    // 1. Smallest valid size logic
    FenwickTree<int> bit0(0);
    EXPECT_EQ(bit0.prefixSum(0), 0);
    bit0.add(0, 5);
    EXPECT_EQ(bit0.prefixSum(0), 5);
    EXPECT_EQ(bit0.prefixSum(-1), 0);
    EXPECT_EQ(bit0.prefixSum(1), 5); // n=0, i>n -> i=n=0

    // 2. Add at boundaries
    int n = 5;
    FenwickTree<int> bit(n);
    bit.add(0, 10);
    EXPECT_EQ(bit.prefixSum(0), 10);
    EXPECT_EQ(bit.rangeSum(0, 1), 10);
    
    bit.add(n, 20);
    EXPECT_EQ(bit.prefixSum(n), 30); // 10 + 20
    EXPECT_EQ(bit.prefixSum(n-1), 10);
    
    // 3. Out of bounds queries
    EXPECT_EQ(bit.prefixSum(-5), 0);
    EXPECT_EQ(bit.prefixSum(n+5), 30); // Same as prefixSum(n)
    
    // 4. Empty range
    EXPECT_EQ(bit.rangeSum(2, 2), 0);
    EXPECT_EQ(bit.rangeSum(3, 2), 0); // lb > ub
}

TEST_F(BITTest, LargeRandomData) {
    // Stress test against naive vector implementation
    int n = 5000;
    int num_ops = 5000;
    FenwickTree<long long> bit(n);
    std::vector<long long> naive(n + 1, 0);

    // Using fixed seed for reproducibility
    std::mt19937 rng(42); 
    std::uniform_int_distribution<int> idx_dist(0, n);
    std::uniform_int_distribution<int> val_dist(-1000, 1000);
    std::uniform_int_distribution<int> op_dist(0, 2); // 0: add, 1: prefixSum, 2: rangeSum

    for (int i = 0; i < num_ops; ++i) {
        int op = op_dist(rng);
        if (op == 0) { // add
            int idx = idx_dist(rng);
            int val = val_dist(rng);
            bit.add(idx, val);
            naive[idx] += val;
        } else if (op == 1) { // prefixSum
            int idx = idx_dist(rng);
            long long expected = 0;
            // Handle out of bounds logic for naive same as BIT
            int effective_idx = std::min(idx, n);
            if (effective_idx < 0) effective_idx = -1;
            
            for (int k = 0; k <= effective_idx; ++k) {
                expected += naive[k];
            }
            long long actual = bit.prefixSum(idx);
            ASSERT_EQ(actual, expected) << "Mismatch at op " << i << " prefixSum(" << idx << ")";
        } else { // rangeSum
            int lb = idx_dist(rng);
            int ub = idx_dist(rng);
            // BIT rangeSum(lb, ub) is [lb, ub)
            long long expected = 0;
            if (ub > lb) {
                 // Naive calc
                 // Handle bounds? BIT uses prefixSum internally which handles bounds.
                 // Let's rely on naive implementation of prefixSum logic
                 long long sum_ub = 0;
                 int effective_ub = std::min(ub-1, n); // prefixSum(ub-1)
                 for(int k=0; k<=effective_ub; ++k) sum_ub += naive[k];
                 
                 long long sum_lb = 0;
                 int effective_lb = std::min(lb-1, n); // prefixSum(lb-1)
                 for(int k=0; k<=effective_lb; ++k) sum_lb += naive[k];
                 
                 expected = sum_ub - sum_lb;
            }
            
            long long actual = bit.rangeSum(lb, ub);
            ASSERT_EQ(actual, expected) << "Mismatch at op " << i << " rangeSum(" << lb << ", " << ub << ")";
        }
    }
}
