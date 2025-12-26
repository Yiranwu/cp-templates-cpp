//
// Created by yiran on 2021/9/7.
//

#ifndef CF_BASE_BINLIFTING_H
#define CF_BASE_BINLIFTING_H

#include "../template/cp_template.h"

#include "VectorWithOffset.h"
#include "GCD.h"


template <typename dataT>
class GCDStats {
public:
    dataT v;

    explicit GCDStats(): v(1) {}
    explicit GCDStats(dataT _v): v(_v) {}

    GCDStats operator + (GCDStats& other) {return GCDStats<dataT>(gcd(v, other.v)); }
};

template <typename dataT>
class ArgmaxStats {
public:
    dataT v;

    explicit ArgmaxStats(dataT _v): v(_v) {}

    dataT at(int i) {
        // get element @ i
    }

    ArgmaxStats operator + (ArgmaxStats& other) {
        dataT argm;
        if (at(v) > at(other.v))
            argm = v;
        else if(at(v) == at(other.v))
            argm = min(v, other.v);
        else argm = other.v;

        return ArgmaxStats<dataT>(argm);
    }
};

template <typename dataT, typename statsT>
class SparseTable {
public:
    int n,m;
    vectorWithOffset<vector<statsT>> stats;

    explicit SparseTable(const vector<dataT> &_data, int _offset=1): n(_data.size()), m(log2i(n)),
                                                                     stats(vector<vector<statsT>>(n), _offset) {

        for(int i=0;i<n;++i) {
            stats.vec[i].resize(m+1);
            stats.vec[i][0] = statsT(_data[i]);
        }

        for(int p=1; p<=m; ++p)
            for(int i=0;i<=n-pow2(p);++i) {
                stats.vec[i][p] = stats.vec[i][p-1] + stats.vec[i + pow2(p-1)][p-1];
            }
    }

    statsT rangeQuery(int l, int r) {
        int p = log2i(r-l);
        return stats[l][p] + stats[r-pow2(p)][p];
    }

    /*
    T walk() {
        int pow2=0;
        while(f[i][pow2+1]>1) ++pow2;
        ll cur_pos=i, cur_gcd=f[i][pow2];
        rrepin(j,pow2,0) {
            //if(cur_pos>=n) break;
            if(ll next_gcd=gcd(cur_gcd, f[cur_pos][j]); next_gcd>1) {
                cur_pos+=1<<j;
                cur_gcd = next_gcd;
            }
        }
    }
     */
};


#endif //CF_BASE_BINLIFTING_H
