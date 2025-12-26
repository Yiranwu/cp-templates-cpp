//
// Created by Andrew Wu on 3/31/24.
//

#ifndef CF_BASE_LONGLONGWITHMOD_H
#define CF_BASE_LONGLONGWITHMOD_H

class llM {
public:
    ll v;

    llM(): v(0) {}
    llM(ll _v): v(_v) {}
    llM(const llM&) = default;

    inline llM& operator += (llM x) {v = (v+x.v)%M; return *this;}
    inline llM& operator -= (llM x) {v = (v-x.v+M)%M; return *this;}
    inline llM& operator *= (llM x) {v = (v * x.v) % M; return *this;}
    inline llM& operator /= (llM x) {v = (v * QinvM(x.v)) % M; return *this;}
    inline llM& Qpow(llM x, ll p) {return Qpow(x.v, p);}
    inline llM& Qinv(llM x) {return Qinv(x.v);}

    ll get() const {return v;}
};

inline llM operator + (const llM& x1, const llM& x2) {llM t(x1); return t+=x2;}
inline llM operator - (const llM& x1, const llM& x2) {llM t(x1); return t-=x2;}
inline llM operator * (const llM& x1, const llM& x2) {llM t(x1); return t*=x2;}
inline llM operator / (const llM& x1, const llM& x2) {llM t(x1); return t/=x2;}

#endif //CF_BASE_LONGLONGWITHMOD_H
