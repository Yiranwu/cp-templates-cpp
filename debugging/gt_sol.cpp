#pragma GCC optimize ("-Ofast")

// There is a bug in codeforces machine that prevents compilation to some targets,
// if we put this include after target definition.
// It's fixed in gcc but not yet ported to codeforces.
// This include works with the following targets only: sse,sse2,mmx,avx,tune=native
// Source: https://codeforces.com/blog/entry/126772
#include<iterator>

#ifndef LOCAL
#pragma GCC target("sse,sse2,sse3,ssse3,sse4,popcnt,abm,mmx,avx,avx2,tune=native")
#endif

#pragma GCC optimize ("unroll-loops")
#include<cstdio>
#include<iostream>
#include<iomanip>
#include<cstring>
#include<utility>
#include<vector>
#include<list>
#include<algorithm>
#include<vector>
#include<tuple>
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
#include<random>
#include<chrono>
#include<climits>
#include<type_traits>
#include<stdexcept>
#include<any>

// clang does not support some of c++20 features officially
// need compiler option -fexperimental-library
#include<format>
#include<ranges>
#include<bit>
#include<bitset>
#include <complex>

using namespace std;
#define mp make_pair
#define pb push_back
#define eb emplace_back
#define x first
#define y second
#define rep(i,l,r) for(int i=l;i<r;++i)
#define repin(i,l,r) for(int i=l;i<=r;++i)
#define rrep(i,r,l) for(int i=r;i>l;--i)
#define rrepin(i,r,l) for(int i=r;i>=l;--i)
#define modM(a) (((a)%M+M)%M)
#define addM(a,b) ((modM(a) + modM(b))%M)
#define subM(a,b) (modM(modM(a) - modM(b)))
#define multM(a,b) (modM(modM(a) * modM(b)))
#define divM(a,b) (multM(a, Qinv(b,M)))
#define QinvM(a) (Qinv(a,M))
#define QpowM(a,b) (Qpow(a,b,M))
#define my_all(data) (data).begin(), (data).end()
#define println() printf("\n")
#define endlCh '\n'
#define usafe_at(arr, i, val) ((i)>=(arr).size()? (val) : ((arr)[i]))
#define usafe_index(arr, i, ub, val) ((i)>=(ub)? (val) : ((arr)[i]))
#define lsafe_at(arr, i, val) ((i)<0? (val) : ((arr)[i]))
#define lsafe_index(arr, i, lb, val) ((i)<(lb)? (val) : ((arr)[i]))
#define yesno_string(flag) ((flag) ? "YES" : "NO")
#define DEBUGLOG(mark) (cout << std::format("Passing function {} at mark {}", __FUNCTION__, mark))
using ll = long long;
using ull = unsigned long long;
template<typename valueT>
using pair_t = pair<valueT,valueT>;
using pii = pair<int,int>;
using vi = vector<int>;
template <typename valueT>
using vv_t = vector<vector<valueT>>;
using mii = map<int,int>;

// io utils

// template <typename T>
// void readint(T &first, int i) {
//     x=0;int f=1;char c;
//     for(c=getchar();!isdigit(c);c=getchar())if(c=='-')f=-1;
//     for(;isdigit(c);c=getchar())x=x*10+(c-'0');
//     x*=f;
// }
template <typename T> void read(T &x) {cin >> x;}
template <typename T, typename... Ts> void read(T &x, Ts&... xs) {read(x); read(xs...);}
template <typename T> void readint(T pbegin, T pend)  {for(auto p=pbegin;p!=pend;++p) cin>>*p;}
template <typename T> void readint_n(T *a, int n) {for(int i=0;i<n;++i) cin>>a[i];}
template <typename T> void readint_n(vector<T> &a, int n) {T tmp; a.pb(T()); for(int i=0;i<n;++i) cin>>tmp, a.pb(tmp);}
template <typename T> void readint_n_with_n(T *a, int &n) {cin>>n; readint_n(a, n);}
template <typename T> void readint_n_with_n(vector<T> &a, int &n) {cin>>n; readint_n(a, n);}
template <typename T> void printint(T pbegin, T pend, char *format)  {for(auto p=pbegin;p!=pend;++p) printf(format, *p); printf("\n");}
template <typename T> void printint(T pbegin, T pend)  {for(auto p=pbegin;p!=pend;++p) cout<<*p<<' '; cout<<'\n';}

// Shortcuts or named popular ops
template <typename T> void chkmax(T &x,T y){x<y?x=y:T();}
template <typename T> void chkmin(T &x,T y){y<x?x=y:T();}
template <typename T> bool inRange(T x, pair<T,T> range) {return range.x<=x && x<=range.y;}
template <typename T> T parity(T x) {return x&1LL;}
template <typename T> bool is_odd(T x) {return parity(x)==1;}
template <typename T> bool is_even(T x) {return parity(x)==0;}
template <typename T> auto arrayToVector(T* pbegin, T* pend) {return vector<T>(pbegin, pend);}

// Bit ops
template<typename T> int log2i(T x) {return x;}//{return std::bit_width(x) - 1;}
ll pow2(ll x){return 1LL<<x;}
ll digitAt(ll x, int pow) {return x&pow2(pow);}
bool digitIsOn(ll x, int pow) {return (x&pow2(pow))>0;}
ll fullBitmask(ll n) {return pow2(n)-1;}
ll rangeBitmask(ll pow_lb, ll pow_ub) {return fullBitmask(pow_ub) - fullBitmask(pow_lb);}
ll extractBitRange(ll x, ll pow_lb, ll pow_ub) {return x & rangeBitmask(pow_lb, pow_ub);}
ll lowbit(ll i) {return i & -i;}
ll highbit(ll x) {while(x!=lowbit(x)) {x-=lowbit(x);} return x;}
ll lowpow(ll x) {return log2i(lowbit(x));}
ll highpow(ll x) {return log2i(highbit(x));}
template <typename T>
int popCount(T x) {std::make_unsigned_t<T> ux(x); return __builtin_popcount(ux);}

//math ops
template <typename T> T sqr(T x) {return x*x;}
inline ll Qpow(ll a,ll b){ll s=1;while(b){if(b&1){s=s*a;}a=a*a;b>>=1;}return s;}
inline ll Qpow(ll a,ll b,ll M){ll s=1;while(b){if(b&1){s=(s*a)%M;}a=a*a%M;b>>=1;}return s;}
inline ll Qinv(ll a, ll M){return QpowM(a,M-2);}
template <typename T> T _divceil_pos(T x, T y) {return x/y + (x%y>0);}
template <typename T> T divceil(T x, T y) {return x>0?_divceil_pos(x,y):x/y;}
template <typename T> T _divfloor_neg(T x, T y) {return x/y - (x%y<0);}
template <typename T> T divfloor(T x, T y) {return x<0?_divfloor_neg(x,y):x/y;}
template <typename T>
T gcd(T a,T b) {
    if(a==0) return b;
    return gcd(b%a,a);
}

// Misc

template <typename T>
inline T selectOther(const T &x, const T &y, const T &z) {
    return z == x ? y : x;
}
// Only trust this with array-like STL containers.
// For map, set, etc, this might not work due to the use of std::back_inserter
template <typename T> void mergeContainerInPlace(T& c1, const T& c2) {
    T *t1=c1, *t2=c2;
    if(t1->size() < t2->size()) std::swap(t1,t2);
    std::copy(t2->begin(), t2->end(), std::back_inserter(*t1));
}
template <typename T> T mergeContainer(const T& c1, const T& c2) {
    T ret;
    ret.reserve(c1.size()+c2.size());
    std::copy(my_all(c1), std::back_inserter(ret));
    std::copy(my_all(c2), std::back_inserter(ret));
    return ret;
}
template <typename T> auto toBlockRepresentation(T pbegin, T pend) {
    // Need remove_reference, otherwise valueT becomes a reference type.
    // Cannot use itT::value_type because it doesn't work for c-style arrays (e.g. T=int*).
    using valueT = std::remove_reference_t<decltype(*pbegin)>;
    vector<pair<valueT, int>> V;
    if(pbegin == pend) return V;
    valueT cur_value=*pbegin;
    int cur_cnt=0;
    for(auto p=pbegin; p!=pend; ++p) {
        if(*p != cur_value) {
            V.pb(mp(cur_value, cur_cnt));
            cur_cnt=0;
            cur_value = *p;
        }
        ++cur_cnt;
    }
    V.pb(mp(cur_value, cur_cnt));
    return V;
}
template <typename T> auto toUnorderedValueAndCount(T pbegin, T pend) {
    using valueT = typename T::value_type;
    unordered_map<valueT, int> M;
    for(auto p=pbegin; p!=pend; ++p) {
        ++M[*p];
    }
    return vector<pair<valueT, int>> (M.begin(), M.end());
}
template <typename vT, typename checkT> ll binsearchFirstFalse(ll L, ll R, checkT check) {
    //assert(check(L));
    //assert(!check(R));
    return *ranges::partition_point(views::iota(L, R), check);
}
mt19937 rng(chrono::steady_clock::now().time_since_epoch().count()+1);

/*
class solver {
public:
    int t=0;
    int n=0;
    int a[MAXN];

    explicit solver() {
    }

    void solve() {
        cin >> t;
        while(t--) {
            cin >> n;
            readint_n(a+1, n);
        }
    }
};
 */

const int H=23333;
//const ll M=998244353;
const ll M = 1000000007;

const int MAXN = 500005;

class solver {
public:
    int t=0;
    int n=0,m=0;
    vv_t<pii> G={};
    bool visit[MAXN], ban[MAXN];
    bool backtrack=false;
    vv_t<int> ans;
    int root=0;
    vector<pii> forest;
    stack<int> vstack;

    explicit solver() {
    }

    int dfs(int x, int fa, int mfa) {
        visit[x]=true;
        vstack.push(x);
        int some_son=-1;
        vi visit_son;
        for(auto [y, mid]: G[x]) {
            if(ban[mid]) continue;
            if(visit[y]) {
                if(y==fa) continue;
                root=y;
                backtrack=true;
                ban[mid]=true;
            }
            if(!backtrack) dfs(y, x, mid);
            if(backtrack) {
                if(x==root) {
                    backtrack=false;
                    while(vstack.top()!=root) {
                        visit[vstack.top()]=false;
                        vstack.pop();
                    }
                }
                else {
                    //visit[x]=false;
                    ban[mfa]=true;
                    if(fa!=root) ans.pb({root, x,fa});
                    //for(auto [y2, mid2]: G[x]) visit[y2]=false;
                    return -1;
                }
            }
            some_son=y;
        }
        return some_son;
    }

    void answer() {
        cout << ans.size() << endl;
        for(auto &v: ans) {
            cout << v[0] << ' ' << v[1] << ' ' << v[2] << endl;
        }
    }

    void solve() {
        cin >> t;
        while(t--) {
            cin >> n >> m;
            fill(visit, visit+n+1, false);
            fill(ban, ban+m+1, false);
            G = vv_t<pii>(n+1, vector<pii>());
            forest = vector<pii>();
            ans = vv_t<int>();
            vstack = stack<int>();
            repin(i,1,m) {
                int x,y;
                cin >> x >> y;
                G[x].pb({y, i});
                G[y].pb({x, i});
            }
            repin(i,1,n) {
                backtrack=false;
                if(!visit[i]) {
                    int some_son = dfs(i,0,0);
                    forest.pb({i, some_son});
                }
            }
            if(forest.size()==1 || forest.size()==n) answer();
            else {
                pii merge_root={-1,-1};
                for(auto f: forest) {
                    if(f.y!=-1) merge_root=f;
                }
                assert(merge_root.x !=-1);
                int skip_root = merge_root.x;

                for(auto f: forest) {
                    if(f.x==skip_root) continue;
                    ans.pb({merge_root.x, merge_root.y, f.x});
                    merge_root = {f.x, merge_root.x};
                }
                answer();
            }
        }
    }
};

int main()
{
    ios::sync_with_stdio(false); cin.tie(nullptr);
#ifdef LOCAL
    freopen("/Users/andrewwu/CLionProjects/cp-templates-cpp/input.txt", "r", stdin);
#endif
    //freopen("/Users/andrewwu/CLionProjects/cp-templates-cpp/output.txt", "w", stdout);

    auto mysolver = solver();
    mysolver.solve();
    return 0;
}