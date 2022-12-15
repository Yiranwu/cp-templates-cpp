#pragma GCC optimize ("-Ofast")
#pragma GCC target("sse,sse2,sse3,ssse3,sse4,popcnt,abm,mmx,avx,avx2,tune=native")
#pragma GCC optimize ("unroll-loops")
#include<cstdio>
#include<iostream>
#include<cstring>
#include<vector>
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
using namespace std;
const int H=23333;
//const int M=998244353;
const int M=1000000007;
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
#define modM(a) ((a)%M)
typedef long long ll;
typedef unsigned long long ull;
typedef pair<int,int> pii;
typedef vector<int> vi;
typedef vector<ll> vl;
typedef vector<vector<int>> vvi;
typedef vector<vector<ll>> vvl;
typedef map<int,int> mii;
template <typename T> void chkmax(T &x,T y){x<y?x=y:T();}
template <typename T> void chkmin(T &x,T y){y<x?x=y:T();}
template <typename T> T parity(T x) {return x&1;}
template <typename T> bool is_odd(T x) {return parity(x)==1;}
template <typename T> bool is_even(T x) {return parity(x)==0;}
template <typename T> bool is_prime(T x) {
    assert(x>=1); if(x==1) return false;
    for(T i=2;i<=sqrt(x);++i) if(x%i==0) return false;
    return true;
}
template <typename T> bool is_composite(T x) {
    assert(x>=1); if(x==1) return false;
    return !is_prime(x);
}
ll pow2(ll x){return 1LL<<x;}
template <typename T> int bitOneCount(T x) {int ans=0; while(x) ++ans, x&=x-1; return ans;}
template <typename T> bool pairRCmp(pair<T,T> x, pair<T,T> y) {return x.y<y.y || x.y==y.y && x.x<y.x;}
template <typename T>
void readint(T &first, int i) {
    x=0;int f=1;char c;
    for(c=getchar();!isdigit(c);c=getchar())if(c=='-')f=-1;
    for(;isdigit(c);c=getchar())x=x*10+(c-'0');
    x*=f;
}
template <typename T, typename... Ts> void readint(T &x, Ts&... xs) {readint(x); readint(xs...);}
template <typename T> void readint_n(T *a, int n)  {for(int i=0;i<n;++i) readint(a[i]);}
template <typename T> void readint_with_n(T *a, int &n) { readint(n, 0); readint_n(a, n);}
template <typename T> void printint_n(T *a, int n, char *format)  {for(int i=0;i<n;++i) printf(format, a[i]); printf("\n");}
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
template<class T>
class PairHash {
public:
    ll operator()(const T& x) const {return modM(x.x + x.y * H);}
};
template <typename T>
class PowHasher {
public:
    vl powH;
    explicit PowHasher(int len): powH(len) {
        powH[0]=1;
        rep(i,1,len) powH[i]=modM(powH[i-1] * H);
    }
    ll hash(T *a, int n) {
        ll hash=0;
        rep0(i,n) hash = modM(hash + powH[i]*ll(a[i]));
        return hash;
    }
    ll updateHash(const ll &hash, ll v, ll pow) {
        return modM(hash+v*powH[pow]);
    }
    ll updateHash(ll &hash, ll v, ll pow) {
        hash = modM(hash+v*powH[pow]);
        return hash;
    }
};
template <typename T> unordered_map<T, T> getMapToRank(T *a, int n) {
    unique_ptr<T[]> a2(new T[n]); copy(a, a+n, a2.get()); sort(a2.get(),a2.get()+n);
    auto ptr=unique(a2.get(),a2.get()+n); unordered_map<T, T> M;
    rep0(i,ptr-a2.get()) M[a2[i]]=i; return M;
}
template <typename T> void mapToRank(T *a, int n) {
    unordered_map<T, T> M= getMapToRank(a, n);
    rep0(i,n) a[i] = M[a[i]];
}
template <typename T> void mapToRank(T *a, int n, unordered_map<T, T> M) {rep0(i,n) a[i] = M[a[i]];}
template <typename T> unordered_set<T> toUSet (T *a, int n) {unordered_set<T> ret; rep0(i,n) ret.insert(a[i]); return ret;}
inline ll Qpow(ll a,ll b,ll M){ll s=1;while(b){if(b&1){s=(s*a)%M;}a=a*a%M;b>>=1;}return s;}
inline ll Qinv(ll a, ll M){return Qpow(a,M-2,M);}
template <typename T> T divceil(T x, T y) {return (x-1)/y + 1;}
mt19937 rng(chrono::steady_clock::now().time_since_epoch().count()+1);

ll t,n;

ll get_query(ll x,ll y) {
    if(y<=x) return 0;
    printf("? %lld %lld\n", x, y); fflush(stdout);
    ll ret;
    readint(ret, 0);
    if(ret==-1LL) exit(0);
    return ret;
}
int get_sum_num(ll v0, ll s) {
    // find nterm, start from v0, sum is sta
    assert(s>=v0);
    //if(v0==sta) return 1;
    ll l=0,r=ll(sqrt(2*s))+1;
    while(l<r-1) {
        ll mid = (l+r)/2;
        if(mid*v0 + (mid-1)*mid/2<s) l=mid; else r=mid;
    }
    if(s == v0*r + (r-1)*r/2) return r;
    else return -1LL;
}

ll find_rbound(ll p, ll v0, ll sum, ll sl) {
    // find rightmost position, start from pos p, value v0
    ll l=1, r=ll(sqrt(2*(sum-sl)))+2;
    // binary search length: l is invalid, r is valid
    while(l<r-1) {
        ll mid=(l+r)/2, smid = get_query(1, p+mid-1);
        if(mid*v0 + (mid-1)*mid/2==smid-sl) l=mid; else r=mid;
    }
    return p+l-1;
}


int main()
{
    //ios::sync_with_stdio(false);
    //cin.tie(0);
//#ifdef LOCAL
//    freopen("/Users/yiran/CLionProjects/codeforces/input.txt", "r", stdin);
//#endif
    readint(t, 0);
    while(t--) {
        readint(n, 0);
        ll sum = get_query(1,n);
        ll l=0,r=n, mid, i,j,k;
        ll sum_mid;
        while(l<r) {
            mid=(l+r)/2;
            sum_mid = get_query(1,mid);
            if(sum_mid==sum) {r=mid; continue;}
            if(sum_mid==0) {l=mid; continue;}
            else break;
        }
        //test test
        ll mid_v = sum_mid - get_query(1, mid-1);
        ll possible_nl = get_sum_num(0,sum_mid);
        if(mid_v == possible_nl-1) {
            ll nl = possible_nl;
            i=mid-nl+1;
            j=find_rbound(mid, mid_v, sum, sum_mid-mid_v)+1;
            ll nr= get_sum_num(0, sum-(j-i)*(j-i-1)/2);
            k=j+nr-1;
        }
        else {
            ll nr = get_sum_num(mid_v+1,sum-sum_mid);
            k=mid+nr;
            j=mid-mid_v;
            ll nl = get_sum_num(0, sum - (k-j+1)*(k-j)/2);
            i=j-nl;
        }
        printf("! %lld %lld %lld\n", i,j,k); fflush(stdout);
    }
    return 0;
}