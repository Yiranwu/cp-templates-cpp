//
// Created by yiran on 2022/1/8.
//


#ifndef CF_BASE_RANDOMUTILS_H
#define CF_BASE_RANDOMUTILS_H

#include "../../template/cp_template.h"
#include <numeric>

#include<vector>

// srand((unsigned) time(0));

int randInt(int lb, int ub) {return rand()%(ub-lb)+lb;}

std::pair<int,int> randInterval(int l,int r) {
    int x=randInt(l,r), y=randInt(l,r);
    return std::make_pair(std::min(x,y), std::max(x,y));
}

void printRandInterval(int l,int r) {
    auto interval = randInterval(l,r);
    printf("%d %d\n", interval.first, interval.second);
}

std::vector<int> randCombination(int n, int k) {
    std::vector<int> nums(n);
    std::iota(all(nums), 0);
    for(int i=0;i<n;++i) {
        swap(nums[i], nums[i+ rand()%(n-i)]);
    }
    return {nums.begin(), nums.begin() + k};
}

#endif //CF_BASE_RANDOMUTILS_H
