//
// Created by yiran on 2021/12/24.
//

#ifndef CF_BASE_2SAT_H
#define CF_BASE_2SAT_H

// 2SAT with n clauses, clause i true -> node 2*i, clause i false -> node 2*i+1
// care: MAXN >= 2*n+10 should hold


template <typename edgeT, typename graphT>
class TwoSATSolver {
public:

    int n,ans[MAXN*2], scc_vis[MAXN*2];
    graphT G;

    explicit TwoSATSolver(int _n, graphT &G_): n(_n), G(G_) {}

    bool solve() {
        TarjanSCC<edgeT, graphT> scc_solver(2*n+1, G);
        scc_solver.solve();
        bool valid_flag=true;
        repin(i,1,n) {
            if(scc_solver.scc[2*i] == scc_solver.scc[2*i+1]) valid_flag=false;
        }
        if(!valid_flag) return false;

        my_fill_n(scc_vis, scc_solver.nsc, 0);
        repin(i,1,n) {
            int true_scc = scc_solver.scc[2*i], false_scc = scc_solver.scc[2*i+1];
            if(scc_vis[true_scc]) {
                ans[i] = 1;
                continue;
            }
            if(scc_vis[false_scc]) {
                ans[i] = 0;
                continue;
            }
            if(true_scc<false_scc) {
                scc_vis[true_scc] = 1;
                ans[i] = 1;
            }
            else {
                scc_vis[false_scc] = 1;
                ans[i] = 0;
            }
        }
        return true;
    }
};

#endif //CF_BASE_2SAT_H
