//
// Created by Andrew Wu on 7/25/24.
//

#ifndef CARTESIANTREE_H
#define CARTESIANTREE_H

#include "../../template/cp_template.h"


// Reference: https://codeforces.com/blog/entry/112664
// Index is 1..n because we use 0 as soldier to prevent accessing nonexistent node
class CartesianTree {
public:
    int n, vSize, root;
    vector<int> src, fa, l, r, subtree_size;
    vector<ll> subtree_ans, ans;

    explicit CartesianTree(vector<int> &&_src) {
        n = _src.size();
        vSize = n+1;

        // pad 0 to vector to align with soldier position
        src.pb(0);
        std::copy(all(_src), std::back_inserter(src));
        _src.clear();
        root = 0;
        fa.resize(vSize);
        l.resize(vSize);
        r.resize(vSize);

        stack<int> S;
        for(int i=1;i<=n;++i) {
            while(!S.empty() && src[S.top()] > src[i]) S.pop();
            if(S.empty()) {
                l[i] = root;
                fa[root] = i;
                root=i;
            }
            else {
                int cur_fa=S.top();
                l[i] = r[cur_fa];
                r[cur_fa] = i;
                fa[i] = cur_fa;
            }
            S.push(i);
        }

        subtree_ans.resize(vSize);
        subtree_size.resize(vSize);
        ans.resize(vSize);
        dfs(root);
    }

    void dfs(int node) {
        int lson = l[node], rson = r[node];
        if(lson) dfs(lson);
        if(rson) dfs(rson);
        int lsize = subtree_size[lson], rsize = subtree_size[rson];
        subtree_size[node] = 1 + lsize + rsize;
        subtree_ans[node] = subtree_ans[lson] + subtree_ans[rson];
        subtree_ans[node] += ll(src[node]) * (lsize+1) * (rsize+1);
    }

    void get_delete_x_ans(int x, ll delta) {
        int lson = l[x], rson = r[x];
        ll LTsize = subtree_size[lson], RTsize = subtree_size[rson];
        if(lson)
            get_delete_x_ans(lson, delta + ll(src[x]) * (1 + RTsize));
        if(rson)
            get_delete_x_ans(rson, delta + ll(src[x]) * (1 + LTsize));
        queue<int> Lchain, Rchain;
        while(lson) Lchain.push(lson), lson=r[lson];
        while(rson) Rchain.push(rson), rson=l[rson];

        ll cur_ans = subtree_ans[root] - subtree_ans[x] - delta;

        while(!Lchain.empty() || !Rchain.empty()) {
            bool Lflag = Rchain.empty() || !Lchain.empty() && src[Lchain.front()] < src[Rchain.front()];
            if(Lflag) {
                int cur_root = Lchain.front();
                LTsize -= subtree_size[l[cur_root]] + 1;
                Lchain.pop();
                ll lsize = subtree_size[l[cur_root]];
                ll rsize = subtree_size[r[cur_root]] + RTsize;
                cur_ans += ll(src[cur_root]) * (lsize+1) * (rsize+1) + subtree_ans[l[cur_root]];
            }
            else {
                int cur_root = Rchain.front();
                RTsize -= subtree_size[r[cur_root]] + 1;
                Rchain.pop();
                ll lsize = subtree_size[l[cur_root]] + LTsize;
                ll rsize = subtree_size[r[cur_root]];
                cur_ans += ll(src[cur_root]) * (lsize+1) * (rsize+1) + subtree_ans[r[cur_root]];
            }
        }
        ans[x] = cur_ans;
    }
};


#endif //CARTESIANTREE_H
