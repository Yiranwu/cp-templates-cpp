#ifndef CF_LIB_CP_INCLUDES_H
#define CF_LIB_CP_INCLUDES_H

#include "std_includes.h"

#define mp make_pair
#define pb push_back
#define eb emplace_back
#define x first
#define y second
#define rep(i,l,r) for(int i=l;i<r;++i)
#define repin(i,l,r) for(int i=l;i<=r;++i)
#define rrep(i,r,l) for(int i=r;i>l;--i)
#define rrepin(i,r,l) for(int i=r;i>=l;--i)
#define all(data) (data).begin(), (data).end()
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
using vl = vector<ll>;
using vpii = vector<pii>;
template <typename valueT>
using vv_t = vector<vector<valueT>>;
using vvi = vector<vector<int>>;
using mii = map<int,int>;
template<typename valueT>
using pq = priority_queue<valueT>;
template<typename valueT>
using pq_rev = priority_queue<valueT, vector<valueT>, greater<>>;

// io utils

// template <typename T>
// void readint(T &first, int i) {
//     x=0;int f=1;char c;
//     for(c=getchar();!isdigit(c);c=getchar())if(c=='-')f=-1;
//     for(;isdigit(c);c=getchar())x=x*10+(c-'0');
//     x*=f;
// }
template <typename T> void read_all(T &x) {cin >> x;}
template <typename T, typename... Ts> void read_all(T &x, Ts&... xs) {read_all(x); read_all(xs...);}
template <typename T> void read_range(T pbegin, T pend)  {for(auto p=pbegin;p!=pend;++p) cin>>*p;}
template <typename T> void read_n(T *a, int n) {for(int i=0;i<n;++i) cin>>a[i];}
template <typename T> void read_n(vector<T> &a, int n) {T tmp; a.pb(T()); for(int i=0;i<n;++i) cin>>tmp, a.pb(tmp);}
template <typename T> void print_all(T &x) {cout << x;}
template <typename T, typename... Ts> void print_all(T &x, Ts&... xs) {cout << x << ' '; print_all(xs...);}
template <typename T> void print_range(T pbegin, T pend)  {for(auto p=pbegin;p!=pend;++p) cout<<*p<<' '; cout<<'\n';}

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
inline ll Qinv(ll a, ll M){return Qpow(a,M-2,M);}
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
    std::copy(all(c1), std::back_inserter(ret));
    std::copy(all(c2), std::back_inserter(ret));
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
// mt19937 rng(chrono::steady_clock::now().time_since_epoch().count()+1);
// Removing rng definition to avoid multiple definition errors if included in multiple files?
// Or we can keep it as static/inline or just declare it?
// Usually rng is used globally. Using `inline` or `static` in header is better.
// I'll make it inline.
inline mt19937 rng(chrono::steady_clock::now().time_since_epoch().count()+1);

#endif //CF_LIB_CP_INCLUDES_H
