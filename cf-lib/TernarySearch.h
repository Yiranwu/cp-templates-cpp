//
// Created by Yiran Wu on 1/22/25.
//

#ifndef TERNARYSEARCH_H
#define TERNARYSEARCH_H

#include "../template/cp_template.h"

template <typename vT>
vT ternary_search_int_maximize(std::function<vT(int)> fn, int L, int R) {

    double EPS=1e-6;

    while (R-L>=3) {
        double delta = (R-L)/3;
        int p1 = floor(L+delta+EPS), p2 = ceil(R-delta-EPS);
        if (p1==L || p2==R) assert(false);
        vT v1 = fn(p1), v2 = fn(p2);
        if (v1>v2) R=p2;
        else L=p1;
    }
    vT maxf=std::numeric_limits<vT>::min();
    repin(i,L,R) {
        chkmax(maxf, fn(i));
    }
    return maxf;
}

#endif //TERNARYSEARCH_H
