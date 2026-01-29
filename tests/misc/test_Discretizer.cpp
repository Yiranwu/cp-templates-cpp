
#include <gtest/gtest.h>
#include <vector>
#include <string>
#include "cf-lib/misc/Discretization.h"

// --- HashMode Tests ---

TEST(DiscretizerTest, HashMode_BasicIntegers) {
    std::vector<int> data = {10, 20, 10, 30, 20};
    Discretizer<int, HashMode> d; // default start_index=0
    d.fromRange(data);

    // Order of appearance: 10(0), 20(1), 30(2)
    EXPECT_EQ(d.get(10), 0);
    EXPECT_EQ(d.get(20), 1);
    EXPECT_EQ(d.get(30), 2);
    
    EXPECT_EQ(d.inverse(0), 10);
    EXPECT_EQ(d.inverse(1), 20);
    EXPECT_EQ(d.inverse(2), 30);
    
    EXPECT_EQ(d.size(), 3);
}

TEST(DiscretizerTest, HashMode_CustomStartIndex) {
    std::vector<int> data = {5, 1, 5};
    Discretizer<int, HashMode> d(10); // start at 10
    d.fromRange(data);
    
    // 5 -> 10, 1 -> 11
    EXPECT_EQ(d.get(5), 10);
    EXPECT_EQ(d.get(1), 11);
    
    EXPECT_EQ(d.inverse(10), 5);
    EXPECT_EQ(d.inverse(11), 1);

    EXPECT_EQ(d.size(), 2);
}

TEST(DiscretizerTest, HashMode_ApplyRange) {
    std::vector<std::string> data = {"apple", "banana", "apple"};
    Discretizer<std::string, HashMode> d;
    d.fromRange(data);
    
    std::vector<std::string> query = {"banana", "apple", "banana"};
    auto res = d.applyRange(query);
    
    // apple->0, banana->1
    std::vector<int> expected = {1, 0, 1};
    EXPECT_EQ(res, expected);
}

TEST(DiscretizerTest, HashMode_Exceptions) {
    Discretizer<int, HashMode> d;
    d.put(100);
    EXPECT_EQ(d.get(100), 0);
    EXPECT_THROW(d.get(999), std::out_of_range);
}

// --- RankMode Tests ---

TEST(DiscretizerTest, RankMode_Basic) {
    std::vector<int> data = {10, 20, 10, 5, 20, 30};
    Discretizer<int, RankMode> d;
    d.fromRange(data);
    
    // Sorted Unique: 5, 10, 20, 30
    // Ranks: 5->0, 10->1, 20->2, 30->3
    
    EXPECT_EQ(d.getRank(5), 0);
    EXPECT_EQ(d.getRank(10), 1);
    EXPECT_EQ(d.getRank(20), 2);
    EXPECT_EQ(d.getRank(30), 3);
    
    EXPECT_EQ(d.inverse(0), 5);
    EXPECT_EQ(d.inverse(3), 30);
    
    EXPECT_EQ(d.size(), 4);
}

TEST(DiscretizerTest, RankMode_NotFound) {
    std::vector<int> data = {10, 20, 30};
    Discretizer<int, RankMode> d;
    d.fromRange(data);
    
    EXPECT_THROW(d.getRank(15), std::out_of_range); // Between 10 and 20
    EXPECT_THROW(d.getRank(5), std::out_of_range);  // Unseen smaller
    EXPECT_THROW(d.getRank(35), std::out_of_range); // Unseen larger
}

TEST(DiscretizerTest, RankMode_ApplyRange) {
    std::vector<int> data = {10, 5, 20};
    Discretizer<int, RankMode> d;
    d.fromRange(data);
    // 5->0, 10->1, 20->2
    
    std::vector<int> query = {20, 5, 10, 20};
    auto res = d.applyRange(query);
    std::vector<int> expected = {2, 0, 1, 2};
    EXPECT_EQ(res, expected);
}


