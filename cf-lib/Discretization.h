//
// Created by yiran on 2021/11/22.
//

#ifndef CF_BASE_DISCRETIZATION_H
#define CF_BASE_DISCRETIZATION_H

#include "../template/cp_template.h"

template <typename T> unordered_map<T, int> getDiscretizationMap(T it_begin, T it_end, int start_index=1) {
    unordered_map<T, int> M;
    int cnt=start_index;
    for(T it = it_begin;it!=it_end;++it) {
        using valueT = typename std::iterator_traits<T>::value_type;
        if(M.find((valueT)*it)==M.end()) M[*it] = cnt++;
    }
    return M;
}
template <typename T> void discretize(T *a, int n) {
    auto M= getDiscretizationMap(a, a+n);
    rep(i,0,n) a[i] = M[a[i]];
}
template <typename iterT> vector<int> applyDiscretizationMap(iterT it_begin, iterT it_end, unordered_map<typename std::iterator_traits<iterT>::value_type, int> &M, int start_index=1) {
    vector<int> ret;
    for(iterT it = it_begin;it!=it_end;++it) {
        ret.push_back(M[*it]);
    }
    return ret;
}

template <typename T>
class RankDiscretizer{
public:
    map<T, int> M;
    int n;
    vector<T> data;

    RankDiscretizer(T* begin, T* end): n(end-begin) {
        data.reserve(n);
        copy(begin, end, back_inserter(data));
        initMap();
    }

    RankDiscretizer(vector<T> _data): n(_data.size()), data(_data) {
        initMap();
    }

    void initMap() {
        sort(data.begin(), data.end());
        for(int i=0;i<n;++i) M[data[i]] = i;
    }

    int toIndex(T x) {return M[x];}

    T toData(int x) {return data[x];}
};

#endif //CF_BASE_DISCRETIZATION_H
