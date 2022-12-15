
#ifndef CF_BASE_GCD_H
#define CF_BASE_GCD_H

template <typename T>
T gcd(T a,T b) {
    if(a==0)
        return b;
    return gcd(b%a,a);
}

template <typename T>
T exgcd(T a, T b, T &x, T &y)
{
    if (a == 0)
    {
        x = 0, y = 1;
        return b;
    }
    T x1, y1;
    T gcd = gcdExtended(b % a, a, x1, y1);

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
