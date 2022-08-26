//
// Created by yiran on 2021/10/30.
//

#ifndef CF_BASE_SEGTREEINCOMPLETE_H
#define CF_BASE_SEGTREEINCOMPLETE_H
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
template <typename T> void readint(T &x) {
    x=0;int f=1;char c;
    for(c=getchar();!isdigit(c);c=getchar())if(c=='-')f=-1;
    for(;isdigit(c);c=getchar())x=x*10+(c-'0');
    x*=f;
}
template <typename T, typename... Ts> void readint(T &x, Ts&... xs) {readint(x); readint(xs...);}
template <typename T> void readint_n(T *a, int n)  {for(int i=0;i<n;++i) readint(a[i]);}
template <typename T> void readint_with_n(T *a, int &n) {readint(n); readint_n(a, n);}
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

const int MAXN=1000005;
int t,n,m;
int a[MAXN],b[MAXN];

class SegTreeOp;
class SegTreeOpGroup;
class SegTreeNodeMem;
class SegTreeNode;

class SegTreeOp {
public:
    int id;
    bool flag;
    virtual void apply_to_tree_node(SegTreeNode &tnode) = 0;
};

class SegTreeOpGroup {
public:
    vector<SegTreeOp> ops;
    SegTreeOpGroup(initializer_list<SegTreeOp> _ops) {// TODO
    }
    void apply_to_tree_node(SegTreeNode &tnode) {
        for(auto &op: ops) op.apply_to_tree_node(tnode);
    }
};

class SegTreeNodeMem {
    virtual ~SegTreeNodeMem()=0;
};

class SegTreeNode {
public:
    // data member:
    // one SegTreeNodeMem for stats
    // one SegTreeOpGroup for tags
    SegTreeNodeMem mem;
    unordered_map<int, bool> op_flag;

    virtual bool tagged()=0;
    virtual void tag(int root, int l, int r, SegTreeOpGroup &mNode)=0;
};


template <typename valueT>
class M_QNode {
public:
    //data member here
    M_QNode() = default;
    // constructor here
    bool tagged() {}
    bool superiorThan(M_QNode &other) {}
    void tag(int root, int l, int r, M_QNode &tagNode) {
        if(!tagNode.superiorThan(this)) return;

    }
    void untag() {}
    void pushUp(int root, int l, int r, M_QNode &lnode, M_QNode &rnode) {

    }

    static vector<M_QNode> buildNodeListFromData(vector<valueT> &data) {
        // given vector of data, build node list
    }
};
template <typename valueT>
inline M_QNode<valueT> operator + (const M_QNode<valueT>& lnode, const M_QNode<valueT>& rnode){
    // for merging query result from lson and rson
}
#define mid ((l+r)>>1)
#define lson (root<<1)
#define rson (root<<1|1)
template <class dataIteratorT, class treeNodeT, class queryNodeT>
class LazySegmentTree {
public:
    int n;
    treeNodeT tree[MAXN*4];
    int p2index[MAXN*4];
    explicit LazySegmentTree(int _n): n(_n) {}

    explicit LazySegmentTree(dataIteratorT start_it, dataIteratorT end_it) {
        build(start_it, end_it);
    }

    ~LazySegmentTree() = default;

    void pushDown(int root, int l, int r) {
        //assert(root<MAXN);
        if(tree[root].tagged()) {
            tree[lson].tag(lson, l,mid, tree[root]);
            tree[rson].tag(rson, mid+1,r, tree[root]);
            tree[root].untag();
        }
    }

    void pushUp(int root, int l, int r) {
        tree[root].pushUp(root, l, r, tree[lson], tree[rson]);
    }

    void treeBuild(int root, int l, int r, dataIteratorT start_it) {
        if(l==r) {
            p2index[l]=root;
            tree[root] = M_QNode(*(start_it+(l-l)));
            return;
        }
        treeBuild(lson, l, mid, start_it);
        treeBuild(rson, mid+1, r, start_it);
        pushUp(root, l, r);
    }

    void build(dataIteratorT start_it, dataIteratorT end_it) {
        n=end_it - start_it;
        treeBuild(1,1,n,start_it);
    }

    void treeAccessNode(int root, int l, int r, int i) {
        if(l==r) return;

        pushDown(root, l, r);
        if(i<=mid) treeAccessNode(lson, l, mid, i);
        else treeAccessNode(rson, mid+1, r, i);
        pushUp(root, l, r);
    }

    nodeT& accessNode(int i) {
        treeAccessNode(1,1,n,i);
        return tree[p2index[i]];
    }

    void treeUpdateRange(int root, int l, int r, int x, int y, nodeT tagNode) {
        if(x<=l && r<=y) {
            tree[root].tag(root, l, r, tagNode);
            return;
        }

        pushDown(root, l, r);
        if(x<=mid) treeUpdateRange(lson, l, mid, x, y, tagNode);
        if(y>=mid+1) treeUpdateRange(rson, mid + 1, r, x, y, tagNode);
        pushUp(root, l, r);
    }

    void updateRange(int x, int y, nodeT tagNode) {
        treeUpdateRange(1,1,n,x,y,tagNode);
    }

    nodeT treeQueryRange(int root, int l, int r, int x, int y) {
        if(x<=l && r<=y) return tree[root];
        pushDown(root, l, r);

        nodeT Lret, Rret;
        int Lflag=false, Rflag=false;
        if(x<=mid) {
            Lflag=true;
            Lret = treeQueryRange(lson,l,mid,x,y);
        }
        if(mid+1<=y) {
            Rflag=true;
            Rret = treeQueryRange(rson,mid+1,r,x,y);
        }
        pushUp(root, l, r);
        if(Lflag && Rflag) return Lret+Rret;
        return Lflag?Lret:Rret;
    }

    nodeT queryRange(int x,int y) {
        return treeQueryRange(1,1,n,x,y);
    }

    //not tested
    std::pair<int, nodeT&> treeFindFirst(int root, int l, int r, bool (*predicate)(nodeT&, nodeT&)) {
        if(l==r) return std::make_pair(l, tree[root]);
        pushDown(root, l, r);
        std::pair<int, nodeT> ret;
        if(predicate(tree[lson], tree[rson])) ret = treeFindFirst(lson, l, mid, predicate);
        else ret = treeFindFirst(rson, mid+1, r, predicate);
        pushUp(root, l, r);
        return ret;
    }

    //not tested
    std::pair<int, nodeT&> findFirst(int v) {
        return treeFindFirst(1,1,n,v);
    }
};

class Add_MinMaxNode {
public:
    int add_tag, data_min, data_max;
    Add_MinMaxNode(): add_tag(0), data_min(0), data_max(0) {};
    Add_MinMaxNode(int _add_tag, int _data_min, int _data_max): add_tag(_add_tag), data_min(_data_min), data_max(_data_max) {}
    bool tagged() {return add_tag;}
    void tag(int root, int l, int r, Add_MinMaxNode &tagNode) {
        add_tag+=tagNode.add_tag;
        data_min+=tagNode.add_tag;
        data_max+=tagNode.add_tag;
    }
    void untag() {add_tag=0;}
    void pushUp(int root, int l, int r, Add_MinMaxNode &lnode, Add_MinMaxNode &rnode) {
        data_min = min(lnode.data_min, rnode.data_min);
        data_max = max(lnode.data_max, rnode.data_max);
    }
};
inline Add_MinMaxNode operator + (const Add_MinMaxNode& lhs, const Add_MinMaxNode& rhs){
    return Add_MinMaxNode(0, min(lhs.data_min, rhs.data_min), max(lhs.data_max, rhs.data_max));
}

typedef LazySegmentTree<Add_MinMaxNode> SegTree;
int main()
{
    //ios::sync_with_stdio(false);
    //cin.tie(0);
#ifdef LOCAL
    freopen("/Users/yiran/CLionProjects/codeforces/input.txt", "r", stdin);
#endif
    readint(t);
    while(t--) {
        readint(n,m); readint_n(a+1, n); readint_n(b+1,m);
        sort(b+1,b+m+1);
        SegTree segtree(n);
    }
    return 0;
}
#endif //CF_BASE_SEGTREEINCOMPLETE_H
