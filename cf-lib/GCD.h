
#ifndef CF_BASE_GCD_H
#define CF_BASE_GCD_H

#include "../template/cp_template.h"

// Quick fact on number of divisors: The number is 1344 for integers up to 10^9 and 103680 for integers up to 10^18.
// We can use O(n^(1/3)) as bound in general.
// Source: https://codeforces.com/blog/entry/14463



template <typename T>
T exgcd(T a, T b, T &x, T &y)
{
    if (a == 0)
    {
        x = 0, y = 1;
        return b;
    }
    T x1, y1;
    T gcd = exgcd(b % a, a, x1, y1);

    x = y1 - (b / a) * x1;
    y = x1;

    return gcd;
}

template <typename T>
T ModInvCoPrime(T a,T p) {
    T x,y,g;
    exgcd(a, p,x,y);
    if(x<0)
        return x+((-x-1)/p+1)*p;
    else
        return x%p;
}
#endif //CF_BASE_GCD_H
