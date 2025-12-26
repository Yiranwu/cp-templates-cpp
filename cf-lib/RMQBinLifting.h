//
// Created by Andrew Wu on 5/30/24.
//

#ifndef CF_BASE_RMQBINLIFTING_H
#define CF_BASE_RMQBINLIFTING_H

#include "../template/cp_template.h"

// RMQ with binary lifting
// template<dataT, iterT>
// Init (n, begin_iter, end_iter)
// n: number of elements, index start from 0
// getRangeMax(lb,ub): range max of interval [lb, ub)
template<typename dataT, typename iterT>
class RMQBinLifting {
public:
    int n, maxp;
    vector<dataT> V;
    vector<vector<dataT>> rangeMax;

    RMQBinLifting(iterT pbegin, iterT pend): n(pend-pbegin), V(pbegin, pend) {
        maxp = log2i(highbit(n));
        rangeMax.resize(n);
        repin(i,0,n-1) {
            rangeMax[i].resize(maxp+1);
            rangeMax[i][0] = V[i];
        }
        repin(p,1,maxp) {
            repin(i,0,n-pow2(p)) {
                rangeMax[i][p] = max(rangeMax[i][p-1], rangeMax[i+pow2(p-1)][p-1]);
            }
        }
    }

    dataT getRangeMax(int lb, int ub) {
        int p = log2i(highbit(ub-lb));
        return max(rangeMax[lb][p], rangeMax[ub-pow2(p)][p]);
    }
};


#endif //CF_BASE_RMQBINLIFTING_H
