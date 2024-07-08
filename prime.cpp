#pragma GCC optimize ("-Ofast")
#pragma GCC target("sse,sse2,sse3,ssse3,sse4,popcnt,abm,mmx,avx,avx2,tune=native")
#pragma GCC optimize ("unroll-loops")
#include<cstdio>
#include<iostream>
#include<cstring>
#include<utility>
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
#include<stdexcept>
#include<ranges>
//#include<bit>
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
#define memset0(a) memset(a,0,sizeof(a))
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
ll full_bitmask(ll n) {return pow2(n)-1;}
ll range_bitmask(ll pow_lb, ll pow_ub) {return full_bitmask(pow_ub) - full_bitmask(pow_lb);}
ll extract_bit_range(ll x, ll pow_lb, ll pow_ub) {return x & range_bitmask(pow_lb, pow_ub);}
template <typename T> bool inRange(pair<T,T> range, T x) {return range.x<=x && x<=range.y;}
//std::popcount(unsigned_type x)
ll lowbit(ll i) {return i & -i;}
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

template <typename T> T mergeContainer(T c1, T c2) {
    T ret;
    ret.reserve(c1.size()+c2.size());
    ret.insert(ret.end(), c1.start(), c1.end());
    ret.insert(ret.end(), c2.start(), c2.end());
}
template <typename kT, typename vT> void mapIncCount(map<kT, vT> &M, kT key) {
    if(!M.contains(key)) M[key]=0;
    ++M[key];
}
template <typename T> unordered_set<T> arrayToUSet (T *a, int n) {unordered_set<T> ret; rep0(i,n) ret.insert(a[i]); return ret;}
inline ll Qpow(ll a,ll b){ll s=1;while(b){if(b&1){s=s*a;}a=a*a;b>>=1;}return s;}
inline ll Qpow(ll a,ll b,ll M){ll s=1;while(b){if(b&1){s=(s*a)%M;}a=a*a%M;b>>=1;}return s;}
inline ll Qinv(ll a, ll M){return Qpow(a,M-2,M);}
template <typename T> T divceil(T x, T y) {return (x-1)/y + 1;}
template <typename T>
T gcd(T a,T b) {
    if(a==0) return b;
    return gcd(b%a,a);
}
//inline template <typename predT, typename valT> valueWithBoundaryGuard(predT pre, predT lb, predT ub, )
mt19937 rng(chrono::steady_clock::now().time_since_epoch().count()+1);

/*
class solver {
public:
    int t;

    explicit solver() {
    }

    void solve() {
        cin >> t;
        while(t--) {
        }
    }
};
 */


const int H=23333;
//const ll M=998244353;
const ll M = 1000000007;

const int MAXN=300005;
const int MAXP=31;

// Sieve of Euler: mark each composite x as not prime with its least prime factor
// Suppose x=pq, will mark x when finding multiples of q, and considering prime factor p.
class SieveOfEuler {
public:
    // const static int NP=80000, MAXN=1000000;
    int n;
    vector<int> p, fac;
    vector<bool> flag;

    explicit SieveOfEuler(int _n, bool withFactor=false) : n(_n) {
        flag.resize(n+1, false);
        if(!withFactor) findPrime();
        else findPrimeAndFactor();
    }

    void findPrime() {
        for(int i=2;i<=n;++i) {
            if(!flag[i]) {
                p.pb(i);
            }
            for(auto &pj : p) {
                if(i * pj>n) break;
                flag[i*pj]=true;
                if(i%pj==0) break;
            }
        }
    }

    // Also find least prime factor fac[i] for composite i
    void findPrimeAndFactor() {
        fac.resize(n+1);
        for(int i=2;i<=n;++i) {
            if(!flag[i]) {
                p.pb(i);
                fac[i]=i;
            }
            for(auto &pj : p) {
                if(i * pj>n) break;
                flag[i*pj]=true;
                fac[i*pj] = pj;
                if(i%pj==0) break;
            }
        }
    }

    // Handles factorization of v
    // v range: n^2
    mii factorize(ll v) {
        mii ret;
        for(auto &prime: p) {
            if(v%prime!=0) continue;
            while(v%prime==0) {
                ++ret[prime];
                v/=prime;
            }
        }
        if(v>1) ++ret[v];
        return ret;
    }
};

class solver {
public:
    int t;
    int n;
    ll a[2050], lcm=1;
    mii lcm_fac;
    map<ll, mii> facs;

    SieveOfEuler sieve;

    solver(): sieve(100000, true) {}

    int find_lcm_with_limit(const mii& fac_limit) {
        ll lcm_sub=1;
        repin(i,1,n) {
            for(auto)
        }
    }

    void try_lcm(ll x) {
        mii cur_fac = facs[x];
        for(auto &p_pair: lcm_fac) {
            auto p=p_pair.x;
            if(cur_fac[p]==0) continue;
            --cur_fac[p];
            int new_lcm = find_lcm_with_limit(cur_fac);

            ++cur_fac[p];
        }
    }

    void solve() {
        cin >> t;
        while(t--) {
            cin >> n;
            readint_n(a+1, n);
            bool lcm_overflow=false;
            repin(i,1,n) {
                lcm = lcm * a[i] / gcd(a[i], lcm);
                if(lcm > INT_MAX) {
                    lcm_overflow=true;
                    break;
                }
            }
            if(lcm_overflow || find(a+1, a+n+1, lcm) - a <=n) {
                cout << n << endl;
                continue;
            }

            lcm_fac =
            facs[lcm] = sieve.factorize(lcm);
            auto kv = std::views::keys(facs[lcm]);
            lcm_fac = lcm;

            try_lcm(lcm);

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