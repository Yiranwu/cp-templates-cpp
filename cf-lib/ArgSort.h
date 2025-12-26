//
// Created by Andrew Wu on 12/3/23.
//

#ifndef CF_BASE_ARGSORT_H
#define CF_BASE_ARGSORT_H

#include <ranges>
#include <numeric>
#include "../template/cp_template.h"

// Argsort
// index_starts_with: output index start with this number
template <typename iteratorT> auto argSort(iteratorT it_begin, iteratorT it_end, auto cmp=std::less<decltype(*it_begin)>(), int index_starts_with=0, bool decreasing=false) {
    std::vector<int> indices(it_end - it_begin);
    std::iota(indices.begin(), indices.end(), index_starts_with);
    std::sort(
            indices.begin(), indices.end(),
            [&it_begin, &cmp, index_starts_with](int a, int b)->bool { return cmp(*(it_begin+b-index_starts_with), *(it_begin+a-index_starts_with)); }
    );
    return indices;
}


// Get rank of elements
template <typename iterT> std::vector<int> getRank(iterT it_begin, iterT it_end, int index_starts_with=0, bool decreasing=false) {
    auto argV = argSort(it_begin, it_end, index_starts_with, decreasing);
    vi rank(it_end - it_begin);
    for(size_t i=0;i<rank.size();++i) {
        rank[argV[i]-index_starts_with]=i+index_starts_with;
    }
    return rank;
}




// Rearrange V based on a permutation of index.
// e.g., if perm = {1,0,2}, return = {V[1], V[0], V[2]}
// If index is already 0..n-1, set indexToRank = false.
template <typename dataT, typename indexT>
vector<dataT> rearrangeWithPerm(vector<dataT> V, vector<indexT> perm) {
    assert(V.size() == perm.size());

    vector<dataT> ret(V.size());
    // change to views::enumerate later
    // clang do not support enumerate as of now
    for(auto i: views::iota(0, V.size())) {
        ret[i] = V[perm[i]];
    }
    return ret;
}

#endif //CF_BASE_ARGSORT_H
