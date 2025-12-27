//
// Created by yiran on 2021/7/23.
//

#ifndef CF_BASE_BIT_H
#define CF_BASE_BIT_H

#include "../../template/cp_template.h"

// FenwickTree(int n)
// Construct BIT on index 0..n
// Point modification, range query

// prefixSum(i): get sum of range [0, i]
// rangeSum(lb,ub): get sum of range [lb, ub)
// add(pos, delta): add delta to position pos
// set(pos, x): set position pos to x
// operator[pos]: get value at position pos
// upper_bound(v): like std::upper_bound, only works if all elements are nonnegative

template <typename T>
class FenwickTree {
public:
    explicit FenwickTree(int _n): n(_n), A(n+1) {}
    int n;
    vector<T> A;

    int LSB(int i) {return i & -i;}
    T prefixSum(int i)
    {
        if(i<0) return T();
        if(i>n) i=n;
        T sum = A[0];
        for (; i != 0; i -= LSB(i))
            sum = sum + A[i];
        return sum;
    }
    T rangeSum(int lb, int ub) {
        if(ub<=lb) return T();
        return prefixSum(ub-1) - prefixSum(lb-1);
    }
    // Only makes sense when elements are nonnegative
    // Assumes 0 is soldier position, A[0]=0
    // Returns 0 if v is negative
    // Returns n+1 if v cannot be achieved by any prefix
    T upper_bound(int v) {
        if(v<0) return 0;

        T total = prefixSum(n);

        if(v>total) return n+1;

        int p=0, max_pw=0;
        T sum=0;
        while(pow2(max_pw+1)<=n && A[pow2(max_pw+1)]<v) ++max_pw;
        rrepin(pw, max_pw,0) {
            int nxt_p = p+pow2(pw);
            if(nxt_p <= n) {
                int nxt_sum = sum + A[nxt_p];
                if(nxt_sum < v) {
                    sum = nxt_sum;
                    p=nxt_p;
                }
            }
        }
        return p+1;
    }

    void add(int i, T delta)
    {
        if (i == 0){
            A[0] += delta;
            return;
        }
        if(i>n) return;
        for (; i <= n; i+= LSB(i))
            A[i] += delta;
    }
    void set(int i, T delta) {
        add(i, delta-(*this)[i]);
    }

    T operator [] (int index) {
        return rangeSum(index, index+1);
    }
};

// Range add, point query

// diff[i] = a[i] - a[i-1]
// diff index valid 1..n
template<typename T>
struct FenwickTreeDiff {
    FenwickTree<T> bit_diff;
    int n;
    explicit FenwickTreeDiff(int _n): n(_n), bit_diff(_n) {}
    void rangeAdd(int lb, int ub, T op) {
        if(ub<=lb) return;
        bit_diff.add(max(lb,0), op);
        bit_diff.add(min(ub,n+1), -op);
    }
    T operator [] (int index) {
        return bit_diff.prefixSum(index);
    }
};

#endif //CF_BASE_BIT_H
