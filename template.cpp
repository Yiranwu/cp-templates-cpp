#pragma GCC optimize ("-Ofast")
#pragma GCC target("sse,sse2,sse3,ssse3,sse4,popcnt,abm,mmx,avx,avx2,tune=native")
#pragma GCC optimize ("unroll-loops")
#include<cstdio>
#include<iostream>
#include<cstring>
#include <utility>
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
#include<climits>
#include<bit>
using namespace std;
const int H=23333;
const int M=998244353;
//const int M=1000000007;
#define mp make_pair
#define pb push_back
#define x first
#define y second
#define rep0(i,n) for(int i=0;i<n;++i)
#define rep(i,l,r) for(int i=l;i<r;++i)
#define repin(i,l,r) for(int i=l;i<=r;++i)
#define rrep(i,r,l) for(int i=r;i>l;--i)
#define rrepin(i,r,l) for(int i=r;i>=l;--i)
#define memset0(a) memset(a,0,sizeof(a))
#define modM(a) (((a)%M+M)%M)
#define my_fill_n(arr, cnt, v) fill_n(arr, (cnt)+1, v)
#define all(data) (data).begin(), (data).end()
#define println() printf("\n")
#define selectOther(x,y,z) ((z)==(x)?(y):(x))
#define endlCh '\n'
#define log2int(x) (int(log2(x)))
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
template <typename T> bool is_prime(T x) {
    assert(x>=0); if(x<=1) return false;
    for(T i=2;i<=T(sqrt(x)+1e-7);++i) if(x%i==0) return false;
    return true;
}
template <typename T> T mod(T a, T x) {return (((a)%x+x)%x);}
template <typename T> bool is_composite(T x) {
    assert(x>=0); if(x<=1) return false;
    return !is_prime(x);
}
ll pow2(ll x){return 1LL<<x;}
ll digitAt(ll x, int pow) {return x&pow2(pow);}
template <typename T> bool inRange(pair<T,T> range, T x) {return range.x<=x && x<=range.y;}
//std::popcount(unsigned_type x)
ll lowbit(ll i) {return i & -i;}
class pairHashClass {
public:
    template <class T1, class T2>
    std::size_t operator() (const std::pair<T1, T2> &pair) const {
        return std::hash<T1>()(pair.first) ^ std::hash<T2>()(pair.second);
    }
};
template <typename T> std::vector<int> argsort(T it_begin, T it_end, int start_id=0) {
    // start_id: the index of first element. Usually is 0 or 1.
    assert(start_id>=0);
    std::vector<int> indices(it_end - it_begin);
    std::iota(all(indices), start_id);
    std::sort(
            all(indices),
            [&](int a, int b) { return *(it_begin+a-start_id) < *(it_begin+b-start_id); }
    );
    return indices;
}
template <typename T> std::vector<int> iterableToRank(T it_begin, T it_end, int start_id=0) {
    auto argV = argsort(it_begin, it_end);
    vi rank(it_end-it_begin);
    for(size_t i=0;i<it_end-it_begin;++i) {
        rank[argV[i]]=i+start_id;
    }
    return rank;
}
template <typename T>
void readint(T &first, int i) {
    x=0;int f=1;char c;
    for(c=getchar();!isdigit(c);c=getchar())if(c=='-')f=-1;
    for(;isdigit(c);c=getchar())x=x*10+(c-'0');
    x*=f;
}
//template <typename T, typename... Ts> void readint(T &x, Ts&... xs) {readint(x); readint(xs...);}
//template <typename T> void readint_n(T *a, int n)  {for(int i=0;i<n;++i) readint(a[i]);}
//template<typename T> void readint_n(vector<T> &V, int n) {for(int i=0;i<n;++i) {T tmp; readint(tmp); V.pb(tmp);}}
//template <typename T> void readint_n_with_n(T *a, int &n) {readint(n); readint_n(a, n);}
//template <typename T> void readint_n_with_n(vector<T> &a, int &n) {readint(n); readint_n(a, n);}
template <typename T> void readint_n(T *a, int n) {for(int i=0;i<n;++i) cin>>a[i];}
template <typename T> void readint_n(vector<T> &a, int n) {T tmp; a.pb(T()); for(int i=0;i<n;++i) cin>>tmp, a.pb(tmp);}
template <typename T> void readint_n_with_n(T *a, int &n) {cin>>n; readint_n(a, n);}
template <typename T> void readint_n_with_n(vector<T> &a, int &n) {cin>>n; readint_n(a, n);}
//template <typename T> void printint_n(T pbegin, T pend, char *format)  {for(auto p=pbegin;p!=pend;++p) printf(format, *p); printf("\n");}
//template <typename T> void printint_n(T pbegin, T pend)  {for(auto p=pbegin;p!=pend;++p) cout<<p<<' '; cout<<endl;}
template <typename T> void printint_n(T pbegin, T pend, char *format)  {for(auto p=pbegin;p!=pend;++p) printf(format, *p); printf("\n");}
template <typename T> void printint_n(T pbegin, T pend)  {for(auto p=pbegin;p!=pend;++p) cout<<*p<<' '; cout<<'\n';}
template <typename dataT>
class vectorWithOffset {
public:
    using vecT = vector<dataT>;
    vector<dataT> vec;
    int offset;
    explicit vectorWithOffset(const vector<dataT>& _vec, int _offset=1): vec(_vec), offset(_offset) {}
    explicit vectorWithOffset(vector<dataT>&& _vec, int _offset=1): vec(_vec), offset(_offset) {}
    size_t size() {return vec.size();}
    decltype(vec.begin()) begin() {return vec.begin();}
    decltype(vec.end()) end() {return vec.end();}
    decltype(vec.rbegin()) rbegin() {return vec.rbegin();}
    decltype(vec.rend()) rend() {return vec.rend();}

    void push_back(dataT data) {vec.push_back(data);}
    dataT& operator[] (int index) {return vec[index-offset];}
    void clear() {vec.clear();}
};
template <typename T> T merge_container(T c1, T c2) {
    T ret;
    ret.reserve(c1.size()+c2.size());
    ret.insert(ret.end(), c1.start(), c1.end());
    ret.insert(ret.end(), c2.start(), c2.end());
}
template <typename T, typename funcT> T binSearchL(T pl, T pr, funcT check) {
    //assert(check(pl)); assert(!check(pr));
    while(pl<pr-1) {
        T pmid=(pl+pr)/2;
        if(check(pmid)) pl=pmid; else pr=pmid;
    }
    return pl;
}
template <typename T, typename funcT> T binSearchR(T pl, T pr, funcT check) {
    auto neg_check = [check](T input) {return !check(input);};
    return binSearchL(pl,pr,neg_check);
}
template <typename kT, typename vT> void incMapCount(map<kT, vT> &M, kT key) {
    if(!M.contains(key)) M[key]=0;
    ++M[key];
}
template <typename T> unordered_set<T> toUSet (T *a, int n) {unordered_set<T> ret; rep0(i,n) ret.insert(a[i]); return ret;}
inline ll Qpow(ll a,ll b,ll M){ll s=1;while(b){if(b&1){s=(s*a)%M;}a=a*a%M;b>>=1;}return s;}
inline ll Qinv(ll a, ll M){return Qpow(a,M-2,M);}
template <typename T> T divceil(T x, T y) {return (x-1)/y + 1;}
template <typename T>
T gcd(T a,T b) {
    if(a==0) return b;
    return gcd(b%a,a);
}
mt19937 rng(chrono::steady_clock::now().time_since_epoch().count()+1);

const int MAXN=5;
int t,n;
int a[MAXN];

int main()
{
    ios::sync_with_stdio(false); cin.tie(nullptr);
#ifdef LOCAL
    freopen("/Users/yiran/CLionProjects/codeforces/input.txt", "r", stdin);
#endif
    cin >>t;
    while(t--) {
        cin>>n;
    }
    return 0;
}