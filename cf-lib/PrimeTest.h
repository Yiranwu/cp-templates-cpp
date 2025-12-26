//
// Created by Andrew Wu on 12/3/23.
//

#ifndef CF_BASE_PRIMETEST_H
#define CF_BASE_PRIMETEST_H

#include "../template/cp_template.h"

template <typename T> bool is_prime(T x) {
    assert(x>=0); if(x<=1) return false;
    for(T i=2;i<=T(sqrt(x)+1e-7);++i) if(x%i==0) return false;
    return true;
}
template <typename T> bool is_composite(T x) {
    assert(x>=0); if(x<=1) return false;
    return !is_prime(x);
}

#endif //CF_BASE_PRIMETEST_H
