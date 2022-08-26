//
// Created by yiran on 2021/8/20.
//

#ifndef CF_BASE_DSU_H
#define CF_BASE_DSU_H

class DSU {
public:
    vector<int> f;
    explicit DSU(int size) {
        f.clear();
        f.reserve(size+1);
        repin(i,0,size) f.pb(i);
    }
    int father(int idx) {
        if(f[idx]==idx) return idx;
        return f[idx]=father(f[idx]);
    }
    int joinSelf(int i1, int i2) {
        return f[i1]=i2;
    }
    int joinFather(int i1, int i2){
        if(!inSameSet(i1,i2)) return joinSelf(f[i1],f[i2]);
        return -1;
    }
    bool inSameSet(int i1, int i2) {
        return father(i1)==father(i2);
    }
};

class DSUWithMember {
public:
    vector<int> f;
    vector<vector<int>> members;
    vector<vector<int>*> p;
    explicit DSUWithMember(int size) {
        f.clear(); members.clear(); p.clear();
        f.reserve(size+1); members.reserve(size+1); p.reserve(size+1);
        repin(i,0,n) f.pb(i), members.pb({i}), p.pb(&members[i]);
    }
    int father(int idx) {
        if(f[idx]==idx) return idx;
        return f[idx]=father(f[idx]);
    }
    int joinSelf(int i1, int i2) {
        f[i1]=i2;
        int i_fa = p[i1]->size()>p[i2]->size()?i1:i2, i_son=i_fa^i1^i2;
        p[i_fa]->insert(p[i_fa]->end(), p[i_son]->begin(), p[i_son]->end());
        p[i2] = p[i_fa];
        return i2;
    }
    int joinFather(int i1, int i2) {
        if(!inSameSet(i1,i2)) return joinSelf(f[i1],f[i2]);
        return -1;
    }
    bool inSameSet(int i1, int i2) {
        return father(i1)==father(i2);
    }
};

#endif //CF_BASE_DSU_H
