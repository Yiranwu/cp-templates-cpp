#ifndef CF_BASE_COMBINATORIALNUMBER_H
#define CF_BASE_COMBINATORIALNUMBER_H

#include "../template/cp_template.h"
#include "GCD.h"

inline ll QinvM(ll a) {return Qinv(a, M);}
inline ll divM(ll a, ll b) {return a * QinvM(b) % M;}

class CnkSolverWithFactorial {
public:
    int maxN;
    vl facM, facInvM;

    explicit CnkSolverWithFactorial(int _maxN): maxN(_maxN)  {
        facM.reserve(maxN+1);
        facInvM.reserve(maxN+1);
        facM.pb(1); facInvM.pb(1);
        repin(i,1,maxN) {
            facM.pb(facM.back() * i % M);
            facInvM.pb(QinvM(facM.back()));
        }
    }

    ll get(int n, int k) {
        return divM(divM(facM[n], facM[k]), facM[n-k]);
    }
};

ll Cnk(ll n, ll k) {
    if(k>n) return 0;
    if(k<0) throw std::invalid_argument("Cnk with negative k");
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
    return Cnk(n % M, k % M) * Lucas(n / M, k / M) % M;
}


std::vector<std::vector<int>> getAllCombination(int n, int k)
{
    std::vector<int> bitmask(k, 1); // k leading 1's
    bitmask.resize(n, 0); // n-k trailing 0's
    std::vector<std::vector<int>> combs;

    // print integers and permute bitmask
    do {
        std::vector<int> cur_comb;
        for (int i = 0; i < n; ++i) // [0..n-1] integers
        {
            if (bitmask[i]) cur_comb.push_back(i+1);
        }
        combs.push_back(cur_comb);
    } while (std::prev_permutation(bitmask.begin(), bitmask.end()));
    return combs;
}

#endif //CF_BASE_COMBINATORIALNUMBER_H
