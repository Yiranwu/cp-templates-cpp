//
// Created by yiran on 2022/3/23.
//

#ifndef CF_BASE_MODINTEGER_H
#define CF_BASE_MODINTEGER_H

template <typename intT>
class ModInteger {
public:
    static intT M;
    intT value;
    typedef ModInteger<intT> modT;

    explicit ModInteger(intT _value=0) : value(_value % M) {}

    modT operator + (const modT& other) {return modT((value + other.value) % M);}
    modT operator + (const intT other) {return modT((value + other%M) % M);}
    modT& operator += (const modT& other) {value = (value + other.value) %M; return *this;}
    modT& operator += (const intT other) {value = (value + other%M) %M; return *this;}
    modT operator - (const modT& other) {return modT((value - other.value + M) % M);}
    modT operator - (const intT other) {return modT((value - other%M + M) % M);}
    modT& operator -= (const modT& other) {value = (value - other.value + M) %M; return *this;}
    modT& operator -= (const intT other) {value = (value - other%M + M) %M; return *this;}
    modT operator * (const modT& other) {return modT((value * other.value) % M);}
    modT operator * (const intT other) {return modT((value * (other%M)) % M);}
    modT& operator *= (const modT& other) {value = (value * other.value) %M; return *this;}
    modT& operator *= (const intT other) {value = (value * (other%M)) %M; return *this;}
    modT operator / (const modT& other) {return modT((value * Qinv(other.value,M)) % M);}
    modT operator / (const intT other) {return modT((value * Qinv(other%M,M)) % M);}
    modT& operator /= (const modT& other) {value = (value * Qinv(other.value,M)) %M; return *this;}
    modT& operator /= (const intT other) {value = (value * Qinv(other%M,M)) %M; return *this;}
};

template <typename intT>
intT ModInteger<intT>::M = 998244353;

typedef ModInteger<ll> mintT;

#endif //CF_BASE_MODINTEGER_H
