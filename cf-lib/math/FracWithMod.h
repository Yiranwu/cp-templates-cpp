//
// Created by Andrew Wu on 7/7/24.
//

#ifndef FRACWITHMOD_H
#define FRACWITHMOD_H

#include "../../template/cp_template.h"
#include "LongLongWithMod.h"


// One caveat: if frac = u*M / v*M, cannot directly add.
// This can happen e.g., 1/2 + 3/M - 3/M = M / 2M.
// Need to be cafeful if denominator can have factor M.
class FracM {
public:
    llM numerator, denominator;

    FracM(): numerator(0), denominator(1) {}
    FracM(ll v): numerator(v), denominator(1) {}
    FracM(ll nume, ll denom): numerator(nume), denominator(denom) {}
    FracM(llM nume, llM denom): numerator(nume.get()), denominator(denom.get()) {}

    // Define in place add, and use += to define +.
    // Because if we use the other way around, we need to write += which returns a reference.
    // Since we cannot return reference of a temp var, the only reference eligible for return is *this.
    // But that requires to have a in place add that modifies *this.
    inline FracM& addInPlace(const FracM &x) {
        llM new_denom = denominator * x.denominator;
        llM new_nume = numerator * x.denominator + x.numerator * denominator;
        numerator = new_nume, denominator = new_denom;
        return *this;
    }
    // += (ll x) relies on auto conversion from ll to llM.
    inline FracM& operator += (const FracM& x) {return this->addInPlace(x);}
    inline FracM operator + (const FracM& x) const {FracM t(*this); return t+=x;}

    inline FracM& subInPlace(const FracM &x) {
        llM new_denom = denominator * x.denominator;
        llM new_nume = numerator * x.denominator - x.numerator * denominator;
        numerator = new_nume, denominator = new_denom;
        return *this;
    }
    inline FracM& operator -= (const FracM& x) {return this->subInPlace(x);}
    inline FracM operator - (const FracM& x) const {FracM t(*this); return t-=x;}

    inline FracM& multInPlace(const FracM &x) {
        llM new_denom = denominator * x.denominator;
        llM new_nume = numerator * x.numerator;
        numerator = new_nume, denominator = new_denom;
        return *this;
    }
    inline FracM& operator *= (const FracM& x) {return this->multInPlace(x);}
    inline FracM operator * (const FracM& x) const {FracM t(*this); return t*=x;}

    inline FracM& divInPlace(const FracM &x) {
        llM new_denom = denominator * x.numerator;
        llM new_nume = numerator * x.denominator;
        numerator = new_nume, denominator = new_denom;
        return *this;
    }
    inline FracM& operator /= (const FracM& x) {return this->divInPlace(x);}
    inline FracM operator / (const FracM& x) const {FracM t(*this); return t/=x;}

    inline ll toLL() {
        return (numerator * denominator.inv()).get();
    }
};

#endif //FRACWITHMOD_H
