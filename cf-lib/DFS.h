//
// Created by yiran on 2021/12/24.
//

#ifndef CF_BASE_DFS_H
#define CF_BASE_DFS_H

#include "../template/cp_template.h"

template <typename graphT>
class GraphDFS {
public:
    const graphT &G;
    vector<int> father;
    
    explicit GraphDFS(const graphT &_G): G(_G) {
        father.resize(G.n + 1);
    }

    void dfs(int p, int fa) {
        father[p] = fa;
        for(auto& edge : G.G[p]) {
            int v = edge.v; // Assuming edge has .v member
            if(v == fa) continue;
            dfs(v, p);
        }
    }
};

#endif //CF_BASE_DFS_H
