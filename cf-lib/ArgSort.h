//
// Created by Andrew Wu on 12/3/23.
//

#ifndef CF_BASE_ARGSORT_H
#define CF_BASE_ARGSORT_H

// Argsort
// vec: vector to sort
// index_starts_with: the index of the first element of vector
template <typename dataT> std::vector<int> argSort(vector<dataT> vec, int index_starts_with=0, bool decreasing=false) {
    std::vector<int> indices(vec.size());
    std::iota(indices.begin(), indices.end(), index_starts_with);
    if(!decreasing) {
        std::sort(
                indices.begin(), indices.end(),
                [&](int a, int b)->bool { return vec[a-index_starts_with] < vec[b-index_starts_with]; }
        );
    }
    else {
        std::sort(
                indices.begin(), indices.end(),
                [&](int a, int b)->bool { return vec[a-index_starts_with] > vec[b-index_starts_with]; }
        );

    }
    return indices;
}


// Argsort with iterator arguments
// Haven't checked
template <typename iteratorT> std::vector<int> argSort(iteratorT it_begin, iteratorT it_end, int index_starts_with=0) {
    return argSort(vector<typename iteratorT::value_type>(it_begin, it_end), index_starts_with);
}


// Get rank of elements
// Haven't checked
template <typename dataT> std::vector<int> getRank(vector<dataT> V, int index_starts_with=0) {
    auto argV = argSort(V);
    vi rank(V.size());
    for(size_t i=0;i<V.size();++i) {
        rank[argV[i]]=i+index_starts_with;
    }
    return rank;
}


// Rearrange V based on increasing order of Vindex.
// e.g., if Vindex = {1,0,2}, return = {V[1], V[0], V[2]}
// If index is already 0..n-1, set indexToRank = false.
template <typename dataT, typename indexT>
vector<dataT> rearrangeByIndexRank(vector<dataT> V, vector<indexT> Vindex, bool indexToRank=false) {
    assert(V.size() == Vindex.size());

    auto& rank = indexToRank ? getRank(Vindex) : Vindex;
    vector<dataT> ret(V.size());
    // change to views::enumerate later
    // clang do not support enumerate as of now
    for(auto i: views::iota(0, V.size())) {
        ret[rank[i]] = V[i];
    }
    return ret;
}

#endif //CF_BASE_ARGSORT_H
