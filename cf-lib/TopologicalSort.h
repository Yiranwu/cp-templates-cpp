//
// Created by yiran on 2022/3/26.
//

#ifndef CF_BASE_TOPOLOGICALSORT_H
#define CF_BASE_TOPOLOGICALSORT_H

#include "../template/cp_template.h"
#include "Graph.h"

// Sort vertices of directed graph topologically

// this.Sort() returns false if their is loop
// this.G:        graph represented as adjacency list. Each edge is (edge_id, next_vertex)
// this.visited:  whether it's processed by the sort. If =false, means it's in a loop.
// this.ranks:     Used to store degree of vertex during sort, and for ranks after sorting.
// this.sorted:   Sorted vertex indices.
template <typename graphT>
class TopologicalSort {
public:
    int n;
    const graphT& G;
    vector<bool> visited;
    vector<int> ranks, sorted;
    // ranks is used to store indeg before it becomes 0-indeg, and rank after that.

    explicit TopologicalSort(const graphT& G_): n(G_.n), G(G_) {
        visited.resize(n); fill(all(visited), false);
        ranks.resize(n);
        sorted.reserve(n);
    }

    bool Sort() {
        ll ans=0;
        queue<int> Q;
        for(int i=0;i<n;++i) {
            for(auto &[id, j]: G[i]) ++ranks[j];
        }
        for(int i=0;i<n;++i) {
            if(!ranks[i]) {
                Q.push(i);
                visited[i] = true;
            }
        }
        int cnt=0;
        while(!Q.empty()) {
            int x=Q.front(); Q.pop();
            sorted.pb(x);

            ranks[x] = cnt++;
            for(auto &[id, j]: G[x]) {
                --ranks[j];
                if(!ranks[j]) visited[j] = true, Q.push(j);
            }
        }
        return cnt==n;
    }

    int GetRank(int x) {
        return ranks[x];
    }

    int operator[] (int x) {
        return ranks[x];
    }
};

#endif //CF_BASE_TOPOLOGICALSORT_H
