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

    inline llM& addInPlace(const llM &x) {v = addM(v, x.v); return *this;}
    inline llM operator + (llM x) const {llM t(*this); return t+=x;}
    inline llM& operator += (llM x) {return this->addInPlace(x);}

    inline llM& subInPlace(const llM &x) {v = subM(v, x.v); return *this;}
    inline llM operator - (llM x) const {llM t(*this); return t-=x;}
    inline llM& operator -= (llM x) {return this->subInPlace(x);}

    inline llM& multInPlace(const llM &x) {v = multM(v, x.v); return *this;}
    inline llM operator * (llM x) const {llM t(*this); return t*=x;}
    inline llM& operator *= (llM x) {return this->subInPlace(x);}

    inline llM& divInPlace(const llM &x) {v = divM(v, x.v); return *this;}
    inline llM operator / (llM x) const {llM t(*this); return t/=x;}
    inline llM& operator /= (llM x) {return this->divInPlace(x);}

    inline llM inv() const {return QinvM(v);}
    ll get() {return v;}
};

#endif //CF_BASE_LONGLONGWITHMOD_H
