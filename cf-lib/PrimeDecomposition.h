//
// Created by yiran on 2022/3/20.
//

#ifndef CF_BASE_PRIMEDECOMPOSITION_H
#define CF_BASE_PRIMEDECOMPOSITION_H

// remember to set sieve attribute with:
// PrimeDcmpRational<intT>::sieve = xx
template <typename intT>
class PrimeDcmpRational {
public:
    typedef PrimeDcmpRational<intT> pdT;
    static SieveOfEuler *sieve;
    unordered_map<int,int> factors;

    explicit PrimeDcmpRational(intT numerator=1, intT denominator=1) {
        (*this) *= numerator;
        (*this) /= denominator;
    }

    explicit PrimeDcmpRational(pdT numerator, pdT denominator) {

        (*this) *= numerator;
        (*this) /= denominator;
    }

    pdT& operator *= (const pdT& mul) {
        unordered_set<int> toErase;
        for (auto &kv : mul.factors) {
            int fac=kv.x;
            if(!factors.contains(fac)) factors[fac] = 0;
            int &pow = factors[fac];
            pow += kv.y;
            if(!pow) toErase.insert(fac);
        }
        for(auto k: toErase) {
            if(factors.contains(k) && !factors[k]) factors.erase(k);
        }
        return *this;
    };

    pdT& operator *= (intT mul) {
        unordered_set<int> toErase;
        while(mul>1) {
            int p = sieve->fac[mul];
            if(!factors.contains(p)) factors[p]=0;
            int &pow = factors[p];
            ++pow;
            if(!pow) toErase.insert(p);
            mul/=p;
        }
        for(auto k: toErase) {
            if(factors.contains(k) && !factors[k]) factors.erase(k);
        }
        return *this;
    };

    pdT& operator /= (const pdT& mul) {
        unordered_set<int> toErase;
        for (auto &kv : mul.factors) {
            int fac=kv.x;
            if(!factors.contains(fac)) factors[fac] = 0;
            int &pow = factors[fac];
            pow -= kv.y;
            if(!pow) toErase.insert(fac);
        }
        for(auto k: toErase) {
            if(factors.contains(k) && !factors[k]) factors.erase(k);
        }
        return *this;
    };

    pdT& operator /= (intT mul) {
        unordered_set<int> toErase;
        while(mul>1) {
            int p = sieve->fac[mul];
            if(!factors.contains(p)) factors[p]=0;
            int &pow = factors[p];
            --pow;
            if(!pow) toErase.insert(p);
            mul/=p;
        }
        for(auto k: toErase) {
            if(factors.contains(k) && !factors[k]) factors.erase(k);
        }
        return *this;
    };
};

template <typename intT>
SieveOfEuler* PrimeDcmpRational<intT>::sieve = &eulerSieve;

typedef PrimeDcmpRational<ll> pdT;
#endif //CF_BASE_PRIMEDECOMPOSITION_H
