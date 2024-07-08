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

// clang does not support some of c++20 features officially
// need compiler option -fexperimental-library
#include<format>
#include<ranges>
#include<bit>

using namespace std;
#define mp make_pair
#define pb push_back
#define x first
#define y second
#define rep0(i,n) for(int i=0;i<n;++i)
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
#define my_fill_n(arr, cnt, v) fill_n(arr, (cnt)+1, v)
#define all(data) (data).begin(), (data).end()
#define println() printf("\n")
#define selectOther(x,y,z) ((z)==(x)?(y):(x))
#define endlCh '\n'
#define log2int(x) (int(log2(x)))
#define usafe_at(arr, i, val) ((i)>=(arr).size()? (val) : ((arr)[i]))
#define usafe_index(arr, i, ub, val) ((i)>=(ub)? (val) : ((arr)[i]))
#define lsafe_at(arr, i, val) ((i)<0? (val) : ((arr)[i]))
#define lsafe_index(arr, i, lb, val) ((i)<(lb)? (val) : ((arr)[i]))
#define DEBUGLOG(mark) (cout << std::format("Passing function {} at mark {}", __FUNCTION__, mark))
typedef long long ll;
typedef unsigned long long ull;
typedef pair<int,int> pii;
typedef pair<ll,ll> pll;
typedef vector<int> vi;
typedef vector<ll> vl;
typedef vector<vector<int>> vvi;
typedef vector<vector<ll>> vvl;
typedef vector<pii> vpii;
typedef vector<pll> vpll;
typedef vector<vector<pair<int,int>>> vvpii;
typedef vector<vector<pair<int,int>>> vvpll;
typedef map<int,int> mii;
template <typename T> T sqr(T x) {return x*x;}
template <typename T> void chkmax(T &x,T y){x<y?x=y:T();}
template <typename T> void chkmin(T &x,T y){y<x?x=y:T();}
template <typename T> T parity(T x) {return x&1LL;}
template <typename T> bool is_odd(T x) {return parity(x)==1;}
template <typename T> bool is_even(T x) {return parity(x)==0;}
template <typename T> T mod(T a, T x) {return (((a)%x+x)%x);}
ll pow2(ll x){return 1LL<<x;}
ll digitAt(ll x, int pow) {return x&pow2(pow);}
bool digitIsOn(ll x, int pow) {return (x&pow2(pow))>0;}
ll fullBitmask(ll n) {return pow2(n)-1;}
ll rangeBitmask(ll pow_lb, ll pow_ub) {return fullBitmask(pow_ub) - fullBitmask(pow_lb);}
ll extractBitRange(ll x, ll pow_lb, ll pow_ub) {return x & rangeBitmask(pow_lb, pow_ub);}
template <typename T> bool inRange(T x, pair<T,T> range) {return range.x<=x && x<=range.y;}
ll lowbit(ll i) {return i & -i;}
ll highbit(ll x) {while(x!=lowbit(x)) {x-=lowbit(x);} return x;}
ll lowpow(ll x) {return log2int(lowbit(x));}
ll highpow(ll x) {return log2int(highbit(x));}
template <typename T>
int popCount(T x) {std::make_unsigned_t<T> ux(x); return __builtin_popcount(ux);}
// template <typename T>
// void readint(T &first, int i) {
//     x=0;int f=1;char c;
//     for(c=getchar();!isdigit(c);c=getchar())if(c=='-')f=-1;
//     for(;isdigit(c);c=getchar())x=x*10+(c-'0');
//     x*=f;
// }
template <typename T> void read(T &x) {cin >> x;}
template <typename T, typename... Ts> void read(T &x, Ts&... xs) {read(x); read(xs...);}
template <typename T> void readint_n(T *a, int n) {for(int i=0;i<n;++i) cin>>a[i];}
template <typename T> void readint_n(vector<T> &a, int n) {T tmp; a.pb(T()); for(int i=0;i<n;++i) cin>>tmp, a.pb(tmp);}
template <typename T> void readint_n_with_n(T *a, int &n) {cin>>n; readint_n(a, n);}
template <typename T> void readint_n_with_n(vector<T> &a, int &n) {cin>>n; readint_n(a, n);}
template <typename T> void printint_n(T pbegin, T pend, char *format)  {for(auto p=pbegin;p!=pend;++p) printf(format, *p); printf("\n");}
template <typename T> void printint_n(T pbegin, T pend)  {for(auto p=pbegin;p!=pend;++p) cout<<*p<<' '; cout<<'\n';}
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
    std::copy(all(c1), std::back_inserter(ret));
    std::copy(all(c2), std::back_inserter(ret));
    return ret;
}
inline ll Qpow(ll a,ll b){ll s=1;while(b){if(b&1){s=s*a;}a=a*a;b>>=1;}return s;}
inline ll Qpow(ll a,ll b,ll M){ll s=1;while(b){if(b&1){s=(s*a)%M;}a=a*a%M;b>>=1;}return s;}
inline ll Qinv(ll a, ll M){return Qpow(a,M-2,M);}
template <typename T> T divceil(T x, T y) {return (x-1)/y + 1;}
template <typename T>
T gcd(T a,T b) {
    if(a==0) return b;
    return gcd(b%a,a);
}
mt19937 rng(chrono::steady_clock::now().time_since_epoch().count()+1);

/*
class solver {
public:
    int t;
    int n;
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


const int MAXN = 400005;

class solver {
public:
    int t;
    int n;
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

int main()
{
    ios::sync_with_stdio(false); cin.tie(nullptr);
#ifdef LOCAL
    freopen("/Users/andrewwu/CLionProjects/cp-templates-cpp/input.txt", "r", stdin);
#endif

    solver().solve();
    // solver().solve();
    return 0;
}