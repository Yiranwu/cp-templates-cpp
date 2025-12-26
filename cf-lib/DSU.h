//
// Created by yiran on 2021/8/20.
//

#ifndef CF_BASE_DSU_H
#define CF_BASE_DSU_H

#include "../template/cp_template.h"

class DSU {
public:
    vector<int> f;
    explicit DSU(int size) {
        f.clear();
        f.reserve(size+1);
        repin(i,0,size) f.pb(i);
    }
    int find(int idx) {
        if(f[idx]==idx) return idx;
        return f[idx]=find(f[idx]);
    }
    int mergeSelf(int i1, int i2) {
        return f[i1]=i2;
    }
    int merge(int i1, int i2){
        if(!equal(i1,i2)) return mergeSelf(f[i1],f[i2]);
        return -1;
    }
    bool equal(int i1, int i2) {
        return find(i1)==find(i2);
    }
};

class DSUElementMembershipState {
    vector<int> members;

    DSUElementMembershipState(): members() {}
    explicit DSUElementMembershipState(int x): members{x} {}

    void addMember(int member) {
        members.pb(member);
    }

    // merge sx into sy
    static void merge(DSUElementMembershipState &sx, DSUElementMembershipState &sy, int w) {
        if(sx.members.size() > sy.members.size()) swap(sx,sy);
        sy.members.insert(sy.members.end(), sx.members.begin(), sx.members.end());
    }
};

// DSUWithState
// init(n)
//   n: number of elements assuming element starts from 1
// find(x): find representative element of set having x
// merge(x, y): merge set of x into set of y
template<class stateT>
class DSUWithState {
public:
    vector<int> f;
    vector<stateT> states;
    int n;

    explicit DSUWithState(int _n): n(_n), f(), states() {
        f.reserve(n+1); states.reserve(n+1);
        repin(i,0,n) f.pb(i), states.pb(stateT());
    }
    int find(int idx) {
        if(f[idx]==idx) return idx;
        return f[idx]=find(f[idx]);
    }
    int mergeSelf(int i1, int i2, int w) {
        f[i1]=i2;
        stateT::merge(states[i1], states[i2], w);
        return i2;
    }
    int merge(int i1, int i2, int w) {
        if(!equal(i1,i2)) return mergeSelf(f[i1],f[i2], w);
        return -1;
    }
    bool equal(int i1, int i2) {
        return find(i1)==find(i2);
    }
};

using DSUStateT = DSUElementMembershipState;
using DSUWithStateT = DSUWithState<DSUStateT>;

#endif //CF_BASE_DSU_H
