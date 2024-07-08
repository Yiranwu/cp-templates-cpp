//
// Created by yiran on 2021/7/23.
//

#ifndef CF_BASE_BIT_H
#define CF_BASE_BIT_H

// FenwickTree(int n)
// Construct bit on index 0..n-1
// Point modification, range query

// rangeSum(lb,ub): get sum of range [lb, ub)
// add(pos, delta): add delta to position pos
// set(pos, x): set position pos to x
template <typename T>
class FenwickTree {
public:
    explicit FenwickTree(int _n): n(_n), A(n) {}
    int n;
    vector<T> A;

    int LSB(int i) {return i & -i;}
    T prefixSum(int i)
    {
        if(i<0) return T();
        if(i>=n) i=n;
        T sum = A[0];
        for (; i != 0; i -= LSB(i))
            sum = sum + A[i];
        return sum;
    }
    T rangeSum(int lb, int ub) {
        if(ub<=lb) return T();
        return prefixSum(min(ub,n)-1) - prefixSum(max(lb,0)-1);
    }
    void add(int i, T delta)
    {
        if (i == 0){
            A[0] += delta;
            return;
        }
        if(i==n) return;
        for (; i < n; i+= LSB(i))
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
template<typename T>
struct FenwickTreeDiff {
    FenwickTree<T> bit_diff;
    int n;
    explicit FenwickTreeDiff(int _n): n(_n), bit_diff(_n) {}
    void rangeAdd(int lb, int ub, T op) {
        if(ub<=lb) return;
        bit_diff.add(max(lb,0), op);
        bit_diff.add(min(ub,n), -op);
    }
    T operator [] (int index) {
        return bit_diff.prefixSum(index);
    }
};

#endif //CF_BASE_BIT_H
