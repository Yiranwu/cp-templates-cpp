//
// Created by yiran on 2021/7/11.
//

#ifndef CF_BASE_SIEVEOFEULER_H

// Sieve of Euler: mark each composite x as not prime with its least prime factor
// Suppose x=pq, will mark x when finding multiples of q, and considering prime factor p.
class SieveOfEuler {
public:
    // const static int NP=80000, MAXN=1000000;
    int n;
    vector<int> p, fac;
    vector<bool> flag;

    explicit SieveOfEuler(int _n, bool withFactor=false) : n(_n) {
        flag.resize(n+1, false);
        if(!withFactor) findPrime();
        else findPrimeAndFactor();
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


#define CF_BASE_SIEVEOFEULER_H

#endif //CF_BASE_SIEVEOFEULER_H
