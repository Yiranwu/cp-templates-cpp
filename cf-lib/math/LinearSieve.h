#ifndef CF_BASE_SIEVEOFEULER_H
#define CF_BASE_SIEVEOFEULER_H

#include "../../template/cp_template.h"

// LinearSieve: mark each composite x as not prime with its least prime factor
// Suppose x=pq, will mark x when finding multiples of q, and considering prime factor p.
class LinearSieve {
public:
    // const static int NP=80000, MAXN=1000000;
    int n;
    vector<int> p, fac;
    vector<bool> flag;
    vector<int> euler;

    explicit LinearSieve(int _n, bool withFactor=false, bool findFunction=false) : n(_n) {
        flag.resize(n+1, false);
        if(withFactor) findPrimeAndFactor();
        else if(findFunction) {
            euler.resize(n+1, 0);
            findPrimeAndFunction();
        }
        else findPrime();
    }

    void findPrime() {
        for(int i=2;i<=n;++i) {
            if(!flag[i]) {
                p.pb(i);
            }
            for(auto &pj : p) {
                if(i * pj>n) break;
                flag[i*pj]=true;
                if(i%pj==0) break;
            }
        }
    }

    void findPrimeAndFunction() {
        euler[1]=1;
        for(int i=2;i<=n;++i) {
            if(!flag[i]) {
                p.pb(i);
                euler[i] = i-1;
            }
            for(auto &pj : p) {
                if(i * pj>n) break;
                flag[i*pj]=true;
                euler[i*pj] = i%pj==0? euler[i] * pj : euler[i] * (pj-1);
                if(i%pj==0) break;
            }
        }
    }

    // Also find least prime factor fac[i] for composite i
    void findPrimeAndFactor() {
        fac.resize(n+1);
        for(int i=2;i<=n;++i) {
            if(!flag[i]) {
                p.pb(i);
                fac[i]=i;
            }
            for(auto &pj : p) {
                if(i * pj>n) break;
                flag[i*pj]=true;
                fac[i*pj] = pj;
                if(i%pj==0) break;
            }
        }
    }

    // Handles factorization of v
    // v range: n^2
    mii factorize(ll v) {
        mii ret;
        for(auto &prime: p) {
            if(v%prime!=0) continue;
            while(v%prime==0) {
                ++ret[prime];
                v/=prime;
            }
        }
        if(v>1) ++ret[v];
        return ret;
    }
};

#endif //CF_BASE_SIEVEOFEULER_H
