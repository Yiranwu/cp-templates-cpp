#pragma GCC optimize ("-Ofast")
#pragma GCC target("sse,sse2,sse3,ssse3,sse4,popcnt,abm,mmx,avx,avx2,tune=native")
#pragma GCC optimize ("unroll-loops")
#include<cstdio>
#include<iostream>
#include<cstring>
#include<vector>
#include<list>
#include<algorithm>
#include<vector>
#include<map>
#include<unordered_map>
#include<set>
#include<unordered_set>
#include<queue>
#include<stack>
#include<numeric>
#include<cassert>
#include<cmath>
#include<memory>
#include<iterator>
#include<random>
#include<chrono>
#include<bit>
using namespace std;

#define forn(i, n) for (int i = 0; i < int(n); i++)


const int MOD = 998244353;

int main() {
#ifdef LOCAL
    freopen("/Users/yiran/CLionProjects/codeforces/input.txt", "r", stdin);
#endif
    int t;
    scanf("%d", &t);
    forn(_, t){
        int n, m, k, q;
        scanf("%d%d%d%d", &n, &m, &k, &q);
        vector<int> xs(q), ys(q);
        forn(i, q) scanf("%d%d", &xs[i], &ys[i]);
        int ans = 1;
        set<int> ux, uy;
        for (int i = q - 1; i >= 0; --i){
            bool fl = false;
            if (!ux.count(xs[i])){
                ux.insert(xs[i]);
                fl = true;
            }
            if (!uy.count(ys[i])){
                uy.insert(ys[i]);
                fl = true;
            }
            if (fl){
                ans = ans * 1ll * k % MOD;
            }
            if (int(ux.size()) == n || int(uy.size()) == m){
                break;
            }
        }
        printf("%d\n", ans);
    }
    return 0;
}