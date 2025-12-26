//
// Created by yiran on 2021/12/20.
//

#ifndef CF_BASE_SCC_H
#define CF_BASE_SCC_H

#include "../../template/cp_template.h"
#include "Graph.h"

// solve scc
// scc[x]: the scc id of x
// S[y]: all element of scc y

template <typename graphT>
class TarjanSCC{
public:
    vi dfn, low, sta, in_stack, scc, sz;
    int n_scc, dfncnt, sta_ptr;
    graphT G, G_scc;
    vvi SCC_set;
    int n;

    TarjanSCC(graphT& G_): G(G_), n(G_.n), G_scc() {
        dfn.resize(n); low.resize(n); sz.resize(n);
        scc.resize(n); in_stack.resize(n);
        sta.resize(n+1);
        n_scc=0; dfncnt=0; sta_ptr=0;
        SCC_set = vvi();
    }

    void Tarjan(int u) {
        low[u] = dfn[u] = ++dfncnt, sta[++sta_ptr] = u, in_stack[u] = 1;
        for (auto &[id, v]: G[u]) {
            if (!dfn[v]) {
                Tarjan(v);
                low[u] = min(low[u], low[v]);
            } else if (in_stack[v]) {
                low[u] = min(low[u], dfn[v]);
            }
        }
        if (dfn[u] == low[u]) {
            int cur_scc = n_scc++;
            SCC_set.pb(vi());
            while (sta[sta_ptr] != u) {
                scc[sta[sta_ptr]] = cur_scc;
                SCC_set.back().pb(sta[sta_ptr]);
                sz[cur_scc]++;
                in_stack[sta[sta_ptr]] = 0;
                --sta_ptr;
            }
            scc[sta[sta_ptr]] = cur_scc;
            SCC_set.back().pb(sta[sta_ptr]);
            sz[cur_scc]++;
            in_stack[sta[sta_ptr]] = 0;
            --sta_ptr;
        }
    }

    void SolveSCC() {
        for(int i=0;i<n;++i)
            if(!dfn[i]) Tarjan(i);
    }

    void BuildSccGraph() {
        G_scc=graphT(n_scc);
        for(int u=0;u<n;++u) {
            for(auto &[id,v] : G[u]) {
                if(scc[v] == scc[u]) continue;
                G_scc.AddEdgeDirectional(scc[u], scc[v]);
            }
        }
    }
};

typedef TarjanSCC<graphDummyT> sccT;

#endif //CF_BASE_SCC_H
