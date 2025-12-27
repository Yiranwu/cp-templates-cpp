#include "template/cp_template.h"

class solver {
public:
    int t=0;
    int n=0,m;
    ll a[MAXN];
    // string s;
    vvi G;

    explicit solver() {
    }

    void solve() {
        cin >> t;
        while(t--) {
            cin >> n;
            read_range(a+1,a+n+1);
        }
    }
};


int main()
{
    ios::sync_with_stdio(false); cin.tie(nullptr);
#ifdef LOCAL
    //freopen("/Users/yiranwu1997/CLionProjects/cp-templates-cpp/outputs/input.txt", "r", stdin);
#endif
    //freopen("/Users/yiranwu1997/CLionProjects/cp-templates-cpp/outputs/output.txt", "w", stdout);

    auto mysolver = solver();
    mysolver.solve();

}
