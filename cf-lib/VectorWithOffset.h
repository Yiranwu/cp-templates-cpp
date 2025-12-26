//
// Created by yiran on 2022/3/31.
//

#ifndef CF_BASE_VECTORWITHOFFSET_H
#define CF_BASE_VECTORWITHOFFSET_H

#include "../template/cp_template.h"
template <typename dataT>
class vectorWithOffset {
public:
    using vecT = vector<dataT>;
    vector<dataT> vec;
    int offset;
    explicit vectorWithOffset(const vector<dataT>& _vec, int _offset=1): vec(_vec), offset(_offset) {}
    explicit vectorWithOffset(vector<dataT>&& _vec, int _offset=1): vec(_vec), offset(_offset) {}
    size_t size() {return vec.size();}
    decltype(vec.begin()) begin() {return vec.begin();}
    decltype(vec.end()) end() {return vec.end();}
    decltype(vec.rbegin()) rbegin() {return vec.rbegin();}
    decltype(vec.rend()) rend() {return vec.rend();}

    void push_back(dataT data) {vec.push_back(data);}
    dataT& operator[] (int index) {return vec[index-offset];}
    void clear() {vec.clear();}
};

#endif //CF_BASE_VECTORWITHOFFSET_H
