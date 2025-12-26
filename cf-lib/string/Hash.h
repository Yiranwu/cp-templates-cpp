//
// Created by yiran on 2021/11/22.
//

#ifndef CF_BASE_HASHING_H
#define CF_BASE_HASHING_H

#include "../../template/cp_template.h"
#include "../math/LongLongWithMod.h"


template<class T>
class PairHash {
public:
    ll operator()(const T& x) const {return modM(x.x + x.y * H);}
};

template<typename T>
class SequenceHasherPreprocessed {
public:
    T s;
    int n;
    vector<llM> prefixHash, pows, invs;

    explicit SequenceHasherPreprocessed(const T &_s): s(_s), n(_s.size()) {
        prefixHash.resize(n+1);
        prefixHash[0] = 0;
        repin(i,0,n-1) {
            prefixHash[i+1] = prefixHash[i] * H + llM(s[i]);
        }

        pows.resize(n+1); invs.resize(n+1);
        pows[0]=1; invs[0]=1;
        llM invh = Qinv(H,M);
        repin(i,1,n) pows[i] = pows[i-1] * H;
        repin(i,1,n) invs[i] = invs[i-1] * invh;
    }

    llM getHash(int begin, int end) {
        llM endHash = prefixHash[end], beginHash = prefixHash[begin] * pows[end-begin];
        return endHash - beginHash;
    }

    llM getAppendedHash(llM hashL, llM hashR, int lenL) {
        return hashL * pows[lenL] + hashR;
    }
};
using StringHasher = SequenceHasherPreprocessed<string>;

#endif //CF_BASE_HASHING_H
