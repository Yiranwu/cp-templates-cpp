//
// Created by yiran on 2021/11/22.
//

#ifndef CF_BASE_HASHING_H
#define CF_BASE_HASHING_H


template<class T>
class PairHash {
public:
    ll operator()(const T& x) const {return modM(x.x + x.y * H);}
};
template <typename T>
class PowHasher {
public:
    vl powH;
    explicit PowHasher(int len): powH(len) {
        powH[0]=1;
        rep(i,1,len) powH[i]=modM(powH[i-1] * H);
    }
    ll hash(T *a, int n) {
        ll hash=0;
        rep0(i,n) hash = modM(hash + powH[i]*ll(a[i]));
        return hash;
    }
    ll updateHash(const ll &hash, ll v, ll pow) {
        return modM(hash+v*powH[pow]);
    }
    ll updateHash(ll &hash, ll v, ll pow) {
        hash = modM(hash+v*powH[pow]);
        return hash;
    }
};

#endif //CF_BASE_HASHING_H
