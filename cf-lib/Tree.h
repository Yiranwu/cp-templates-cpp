//
// Created by Andrew Wu on 8/14/24.
//

#ifndef TREE_H
#define TREE_H

#include "../template/cp_template.h"

// Node id start with 1
class GeneralTree {
public:
    int n;
    vvi G;
    static constexpr int MAXPOW=20;
    vi d,f,sz;
    vvi fs;
    // Sometimes array style declaration is needed for faster execution
    // int d[MAXN], f[MAXN], fs[MAXN][MAXPOW+1], sz[MAXN];


    explicit GeneralTree(int n): n(n) {
        G = vvi(n+1, vi());
        d = vi(n+1);
        f = vi(n+1);
        sz = vi(n+1);
        fs = vvi(n+1, vi(MAXPOW+2));
        assert(false);
        // Choose a reading method:
        //readByAncestor();
        //readByEdge();
    }

    void readByAncestor() {
        int x;
        repin(i,2,n) {
            cin >> x;
            G[x].pb(i);
        }
    }

    void readByEdge() {
        int x,y;
        repin(i,1,n-1) {
            cin >> x >> y;
            G[x].pb(y);
            G[y].pb(x);
        }
    }

    void dfs(int root, int fa, int depth) {
        f[root]=fa;
        sz[root]=1;
        fs[root][0]=fa;
        repin(i,1,MAXPOW) {
            int midf = fs[root][i-1];
            fs[root][i] = midf==0 ? 1 : fs[midf][i-1];
        }
        d[root]=depth;
        for(auto &son: this->G[root]) {
            if(son == fa) continue;
            dfs(son, root, depth+1);
            sz[root] += sz[son];
        }
    }

    vi getPath(int a, int b) {
        // assuming a is deeper or equal depth than b
        if(d[a]<d[b]) {
            auto rev_path = getPath(b,a);
            std::reverse(rev_path.begin(), rev_path.end());
            return rev_path;
        }
        vi pa, pb;
        pa.pb(a);
        while(d[a]>d[b]) {
            a = f[a];
            pa.pb(a);
        }
        pb.pb(b);
        while(a!=b) {
            a=f[a];
            b=f[b];
            pa.pb(a);
            pb.pb(b);
        }
        pb.pop_back();
        std::reverse(pb.begin(), pb.end());
        pa.insert(pa.end(), pb.begin(), pb.end());
        return pa;
    }

    int lca(int x, int y) {
        if(d[x]<d[y]) swap(x,y);
        // assume x is deeper or eq
        if(d[x] != d[y]) {
            rrepin(i, MAXPOW, 0) {
                if(d[x]-d[y] >= pow2(i)) x=fs[x][i];
            }
        }
        assert(d[x]==d[y]);
        if(x==y) return x;

        int i=MAXPOW;
        while(fs[x][i] == fs[y][i]) --i;
        rrepin(j,i,0) {
            if(fs[x][j]!=fs[y][j]) x=fs[x][j], y=fs[y][j];
        }
        return fs[x][0];
    }
};


#endif //TREE_H
