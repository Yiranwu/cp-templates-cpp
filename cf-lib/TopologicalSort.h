//
// Created by yiran on 2022/3/26.
//

#ifndef CF_BASE_TOPOLOGICALSORT_H
#define CF_BASE_TOPOLOGICALSORT_H

// sort vertices of directed graph topologically
// Sort() returns false if their is loop
template <typename graphT>
class TopologicalSort {
public:
    int n;
    const graphT& G;
    vector<bool> visited;
    vector<int> ranks, sorted;
    // ranks is used to store indeg before it becomes 0-indeg, and rank after that.

    explicit TopologicalSort(const graphT& G_): G(G_), n(G_.n) {
        visited.resize(n);
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
            if(!ranks[i]) Q.push(i);
        }
        int cnt=0;
        while(!Q.empty()) {
            int x=Q.front(); Q.pop();
            sorted.pb(x);

            ranks[x] = cnt++;
            for(auto &[id, j]: G[x]) {
                --ranks[j];
                if(!ranks[j]) Q.push(j);
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
