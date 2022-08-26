//
// Created by yiran on 2022/1/8.
//


#ifndef CF_BASE_RANDOMUTILS_H
#define CF_BASE_RANDOMUTILS_H

#include<vector>

int randInt(int lb, int ub) {return rand()%(ub-lb+1)+lb;}

std::pair<int,int> randInterval(int l,int r) {
    int x=randInt(l,r), y=randInt(l,r);
    return std::make_pair(std::min(x,y), std::max(x,y));
}

void printRandInterval(int l,int r) {
    auto interval = randInterval(l,r);
    printf("%d %d\n", interval.first, interval.second);
}

std::vector<std::vector<int>> generateCombination(int n, int k)
{
    std::vector<int> bitmask(k, 1); // k leading 1's
    bitmask.resize(n, 0); // n-k trailing 0's
    std::vector<std::vector<int>> combs;

    // print integers and permute bitmask
    do {
        std::vector<int> cur_comb;
        for (int i = 0; i < n; ++i) // [0..n-1] integers
        {
            if (bitmask[i]) cur_comb.push_back(i+1);
        }
        combs.push_back(cur_comb);
    } while (std::prev_permutation(bitmask.begin(), bitmask.end()));
    return combs;
}

#endif //CF_BASE_RANDOMUTILS_H
