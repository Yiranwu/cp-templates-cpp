//
// Created by yiran on 2021/7/12.
//
#include "GCD.h"
#ifndef CF_BASE_COMBINATORIALNUMBER_H



class CnkCalculator {
public:
    int n;
    ll fac[MAXN], facinv[MAXN];

    CnkCalculator(int _n): n(_n) {
        fac[0]=facinv[0]=1;
        repin(i,1,n) {
            fac[i] = modM(fac[i-1]*i);
            facinv[i] = Qinv(fac[i], M);
        }
    }

    ll Cnk(ll n, ll k) {
        if(k>n) return 0;
        return modM(modM(fac[n]*facinv[k])*facinv[n-k]);
    }
};

ll Cnk(ll n, ll k) {
    if(k>n) return 0;
    if(k==n) return 1;
    if(k==0) return 1;
    ll ans=1;
    for(int i=1;i<=k;++i) {
        ans = ans * (n+1-i) % M * Qinv(i,M) % M;
    }
    return ans;
}

ll Lucas(ll n, ll k)
{
    if(k == 0) return 1;
    return Cnk(n % p, k % p) * Lucas(n / p, k / p) % p;
}
#define CF_BASE_COMBINATORIALNUMBER_H

#endif //CF_BASE_COMBINATORIALNUMBER_H
