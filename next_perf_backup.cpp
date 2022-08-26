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
typedef pair<int,int> pii;
typedef long long ll;
typedef unsigned long long ull;
typedef vector<int> vi;
typedef vector<vector<int>> vvi;
typedef map<int,int> mii;
template <typename T> void chkmax(T &x,T y){x<y?x=y:T();}
template <typename T> void chkmin(T &x,T y){y<x?x=y:T();}
template <typename T> void readint(T &x) {
    x=0;int f=1;char c;
    for(c=getchar();!isdigit(c);c=getchar())if(c=='-')f=-1;
    for(;isdigit(c);c=getchar())x=x*10+(c-'0');
    x*=f;
}
template <typename T> void readint_n(T *a, int n)  {
    for(int i=0;i<n;++i)
        readint(a[i]);
}
template <typename T> void readint_with_n(T *a, int &n) {
    readint(n); readint_n(a, n);
}
template <typename T> void printint_n(T *a, int n, char *format)  {
    for(int i=0;i<n;++i)
        printf(format, a[i]);
    printf("\n");
}
inline ll Qpow(ll a,ll b,ll M){ll s=1;while(b){if(b&1){s=(s*a)%M;}a=a*a%M;b>>=1;}return s;}
inline ll Qinv(ll a, ll M){return Qpow(a,M-2,M);}
template <typename T> T divceil(T x, T y) {return (x-1)/y + 1;}

const int MAXN=200005;
int n,q,tmp;
ll d[MAXN], v[MAXN], sd[MAXN];

template <typename valueT>
class PointUpdate_MinMaxNode {
public:
    valueT maxv, minv, add_tag, set_tag;
    bool add_flag, set_flag;
    PointUpdate_MinMaxNode() = default;
    explicit PointUpdate_MinMaxNode(valueT _v): maxv(_v), minv(_v), add_tag(valueT()), set_tag(valueT()), add_flag(false), set_flag(false) {}
    PointUpdate_MinMaxNode(bool _add_flag, valueT _add_tag, bool _set_flag, valueT _set_tag): add_tag(_add_tag), set_tag(_set_tag), add_flag(_add_flag), set_flag(_set_flag) {}
    bool tagged() {return add_flag || set_flag;}
    void tag(int root, int l, int r, PointUpdate_MinMaxNode &tagNode) {

    }
    void untag() {}
    void pushUp(int root, int l, int r, PointUpdate_MinMaxNode &lnode, PointUpdate_MinMaxNode &rnode) {
        maxv = max(lnode.maxv, rnode.maxv);
        minv = min(lnode.minv, rnode.minv);
    }
    static vector<PointUpdate_MinMaxNode> &buildNodeListFromData(const vector<valueT> datas) {
        vector<PointUpdate_MinMaxNode> ret;
        for(valueT v: datas) ret.pb(PointUpdate_MinMaxNode(v));
        return ret;
    }
};
template <typename valueT>
inline PointUpdate_MinMaxNode<valueT> operator + (const PointUpdate_MinMaxNode<valueT>& lnode, const PointUpdate_MinMaxNode<valueT>& rnode){
    return {valueT(), max(lnode.maxv, rnode.maxv), min(lnode.minv, rnode.minv)};
}

#define mid ((l+r)>>1)
#define lson (root<<1)
#define rson (root<<1|1)
template <typename nodeT>
class LazySegmentTree {
public:
    int n;
    nodeT tree[MAXN*4];
    int p2index[MAXN*4];
    explicit LazySegmentTree(int _n): n(_n) {}

    explicit LazySegmentTree(const vector<nodeT> &node_data) {
        n=node_data.size();
        build(node_data);
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

    void treeBuild(int root, int l, int r, const vector<nodeT> &node_data) {
        if(l==r) {
            p2index[l]=root;
            tree[root] = node_data[l-1];
            return;
        }
        treeBuild(lson, l, mid, node_data);
        treeBuild(rson, mid+1, r, node_data);
        pushUp(root, l, r);
    }

    void build(const vector<nodeT> &node_data) {
        treeBuild(1,1,n,node_data);
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
};

typedef LazySegmentTree<PointUpdate_MinMaxNode<ll>> SegTree;

ll d_range_sum(int l, int r) {
    return sd[r]-sd[l-1];
}

int main()
{
    //ios::sync_with_stdio(false);
    //cin.tie(0);
#ifdef LOCAL
    freopen("/Users/yiran/CLionProjects/codeforces/input.txt", "r", stdin);
#endif
    readint(n), readint(q);
    fill_n(d, n+1, 0LL);
    repin(i,1,n) {readint(tmp), d[i]+=tmp;}
    repin(i,1,n) {readint(tmp), d[i]-=tmp;}
    fill_n(sd, n+1, 0LL);
    repin(i,1,n) {
        sd[i] = sd[i-1] + d[i];
    }
    SegTree segTree(PointUpdate_MinMaxNode<ll>::buildNodeListFromData({begin(sd)+1, begin(sd)+n+1}));

}
return 0;
}