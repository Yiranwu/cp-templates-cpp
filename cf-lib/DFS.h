//
// Created by yiran on 2021/12/24.
//

#ifndef CF_BASE_DFS_H
#define CF_BASE_DFS_H

void dfs(int p,int fa) {
    father[p] = fa;
    for(edgeT s:T[p]) {
        int v=s.v;
        if(v==fa) continue;
        dfs(v, p);
    }
}

#endif //CF_BASE_DFS_H
