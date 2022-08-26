//
// Created by yiran on 2022/3/26.
//

#ifndef CF_BASE_GRAPHCOLORING_H
#define CF_BASE_GRAPHCOLORING_H

template <typename graphT>
class GraphBiColoring {
public:
    const graphT& G;
    vector<bool> visited, colors;
    explicit GraphBiColoring(const graphT& _G): G(_G) {
        visited.resize(G.n);
        colors.resize(G.n);
    }

    bool dfs(int x, bool color) {
        if(visited[x]) return colors[x]==color;
        visited[x]=true; colors[x] = color;
        bool ret_flag=true;
        for(auto &[id, y]: G.G[x])
            ret_flag &= dfs(y, !color);
        return ret_flag;
    }

    bool Color() {
        bool ret_flag=true;
        for(int i=0;i<G.n;++i) {
            if(!visited[i]) ret_flag &= dfs(i, 0);
        }
        return ret_flag;
    }

    bool GetColor(int x) {
        return colors[x-G.index_offset];
    }

    bool operator[] (int x) {
        return colors[x-G.index_offset];
    }
};


#endif //CF_BASE_GRAPHCOLORING_H
