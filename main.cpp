#include "template/cp_template.h"

class solver {
public:
    int t=0;
    int n=0,m;
    ll a[MAXN];
    string s;
    vvi G;

    explicit solver() {
    }

    void solve() {
        vector<int> V;
        V.push_back(1);
        V.push_back(2);
        map<int,int> M;
        M[1]=2;
        M[2]=4;
    }
};


int main()
{
    ios::sync_with_stdio(false); cin.tie(nullptr);
#ifdef LOCAL
    freopen("/Users/yiranwu1997/CLionProjects/cp-templates-cpp/input.txt", "r", stdin);
#endif
    //freopen("/Users/yiranwu1997/CLionProjects/cp-templates-cpp/output.txt", "w", stdout);

    auto mysolver = solver();
    mysolver.solve();

}
