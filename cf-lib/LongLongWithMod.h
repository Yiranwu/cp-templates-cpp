//
// Created by Andrew Wu on 3/31/24.
//

#ifndef CF_BASE_LONGLONGWITHMOD_H
#define CF_BASE_LONGLONGWITHMOD_H

#include "../template/cp_template.h"

class llM {
public:
    ll v;

    llM(): v(0) {}
    llM(ll _v): v(_v) {}
    llM(const llM&) = default;

    inline llM& operator += (llM x) {v = (v+x.v)%M; return *this;}
    inline llM& operator -= (llM x) {v = (v-x.v+M)%M; return *this;}
    inline llM& operator *= (llM x) {v = (v * x.v) % M; return *this;}
    inline llM& operator /= (llM x) {v = (v * ::Qinv(x.v, M)) % M; return *this;}
    inline llM& operator += (ll x) {v = (v+x%M)%M; return *this;}
    inline llM& operator -= (ll x) {v = (v-x%M+M)%M; return *this;}
    inline llM& operator *= (ll x) {v = (v * (x%M)) % M; return *this;}
    inline llM& operator /= (ll x) {v = (v * ::Qinv(x%M, M)) % M; return *this;}
    
    inline llM Qpow(llM x, ll p) {return ::Qpow(x.v, p, M);}
    inline llM Qinv(llM x) {return ::Qinv(x.v, M);}
    inline llM inv() const {return ::Qinv(v, M);}

    ll get() const {return v;}
    
    bool operator == (const llM& other) const {return v == other.v;}
    bool operator != (const llM& other) const {return v != other.v;}
};

inline llM operator + (const llM& x1, const llM& x2) {llM t(x1); return t+=x2;}
inline llM operator - (const llM& x1, const llM& x2) {llM t(x1); return t-=x2;}
inline llM operator * (const llM& x1, const llM& x2) {llM t(x1); return t*=x2;}
inline llM operator / (const llM& x1, const llM& x2) {llM t(x1); return t/=x2;}

inline llM operator + (const llM& x1, const ll& x2) {llM t(x1); return t+=x2;}
inline llM operator - (const llM& x1, const ll& x2) {llM t(x1); return t-=x2;}
inline llM operator * (const llM& x1, const ll& x2) {llM t(x1); return t*=x2;}
inline llM operator / (const llM& x1, const ll& x2) {llM t(x1); return t/=x2;}

inline std::istream& operator >> (std::istream& is, llM& x) {ll t; is>>t; x=llM(t); return is;}
inline std::ostream& operator << (std::ostream& os, const llM& x) {os<<x.v; return os;}

#endif //CF_BASE_LONGLONGWITHMOD_H
