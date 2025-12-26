//
// Created by yiran on 2021/6/30.
//
#ifndef CF_BASE_SEGMENTTREE_H
#define CF_BASE_SEGMENTTREE_H

#include "../template/cp_template.h"



#define segtree_mid ((l+r)>>1)
#define segtree_lson (root<<1)
#define segtree_rson (root<<1|1)

class SegTree {
public:
    int n;
    vector<int> tree;

    explicit SegTree(int n): n(n) {
        tree.resize((n+1)*4);
        buildTree(1,1,n);
    }

    void buildTree(int root, int l, int r) {
        if(l==r) {
            tree[root] = 0;
            return;
        }
        buildTree(segtree_lson, l, segtree_mid);
        buildTree(segtree_rson, segtree_mid + 1, r);
        pushUp(root, l, r);
    }

    void pushUp(int root, int l, int r) {
        tree[root] = max(tree[segtree_lson], tree[segtree_rson]);
    }

    void updateRange(int root, int l, int r, int x, int y, int v) {
        if(x<=l && r<=y) {
            chkmax(tree[root], v);
            return;
        }

        if(x <= segtree_mid) updateRange(segtree_lson, l, segtree_mid, x, y, v);
        if(y >= segtree_mid + 1) updateRange(segtree_rson, segtree_mid + 1, r, x, y, v);
        pushUp(root, l, r);
    }

    int query(int root, int l, int r, int x) {
        if (l==r) return tree[root];

        if (x<= segtree_mid) return query(segtree_lson, l, segtree_mid, x);
        else return query(segtree_rson, segtree_mid + 1, r, x);
    }
};

class SegTree2d {
public:
    int n,m;
    vector<SegTree> tree;
    vector<int> tag;

    explicit SegTree2d(int n, int m): n(n), m(m) {
        tree.reserve((n+1)*4);
        tag.resize(n+1);
        buildTree(1,1,n);
    }

    void buildTree(int root, int l, int r) {
        if(l==r) {
            tree.emplace_back(m);
            tag[root] = 0;
            return;
        }
        buildTree(segtree_lson, l, segtree_mid);
        buildTree(segtree_rson, segtree_mid + 1, r);
        pushUp(root, l, r);
    }

    void pushUp(int root, int l, int r) {
        tree[root] = max(tree[segtree_lson], tree[segtree_rson]);
    }

    void updateRange(int root, int l, int r, int lx, int rx, int ly, int ry, int v) {
        if(lx<=l && r<=rx) {
            tree[root].updateRange(1,1,m,ly,ry,v);
            return;
        }

        if(lx <= segtree_mid) updateRange(segtree_lson, l, segtree_mid, lx, rx, ly, ry, v);
        if(rx >= segtree_mid + 1) updateRange(segtree_rson, segtree_mid + 1, r, lx, rx, ly, ry, v);
        pushUp(root, l, r);
    }

    int query(int root, int l, int r, int x, int y) {
        if (l==r) return tree[root].query(1,1,m,y);

        if (x<= segtree_mid) return query(segtree_lson, l, segtree_mid, x, y);
        else return query(segtree_rson, segtree_mid + 1, r, x, y);
    }
};



// Some discussion regarding the design of M_QNode:
// In a lazy segtree, we need to support range update (M) and range query (Q).
// On each segtree node, we need to store a tag field for each M op, and a data field for each Q op.

// During a range update, we will apply a series of M ops to segtree nodes.
//   Each M op will potentially change multiple tag fields and multiple data fields.
//   The final result of data on a segtree node is: MOpZ( MOpY( ... MOpA(data) ) )
//   So there's a natural precedence of operators. Higher priority op will change tag of lower prio op, but not in the opposite direction.

// During a range query, we will merge data fields of each requested Q op from segtree nodes.

// TODO: support LazySegTree(vector<int/ll>) and M_QNode(int/ll) so that we can init segtree directly from array/vector

//need a node class that supports
//bool tagged(), void tag(int root,int l,int r, nodeT &tagNode), void untag()
//void pushUp(int root, int l, int r, nodeT &lson_node, nodeT &rson_node)
//inline nodeT operator + (const nodeT& lhs, const nodeT& rhs) // for result merging in range query

//node naming convention: <modification type>_<query type>Node
template <typename valueT>
class M_QNode {
public:
    //data member here
    int member;
    // constructor here
    M_QNode() {}
    M_QNode(int _member()) {}
    static M_QNode from_value(valueT value) {return {valueT(), value, value};}
    static M_QNode from_tag(valueT tag) {return {tag, valueT(), valueT()};}
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
    // for merging query result from _segtree_lson and _segtree_rson
}

#define segtree_mid ((l+r)>>1)
#define segtree_lson (root<<1)
#define segtree_rson (root<<1|1)
template <typename valueT, typename nodeT>
class LazySegmentTree {
public:
    int n;
    vector<nodeT> tree;
    vector<int> p2index;

    void init() {
        tree.resize((n+1)*4);
        p2index.resize((n+1)*4);
    }

    explicit LazySegmentTree(int _n): n(_n) {
        init();
        vector<nodeT> node_data(n+1);
        build(node_data);
    }

    explicit LazySegmentTree(const vector<valueT> &node_value): n(node_value.size()) {
        init();
        vector<nodeT> node_data;
        node_data.reserve(n+1);
        node_data.pb(nodeT());
        for(auto &v: node_value) node_data.push_back(nodeT(v));
        build(node_data);
    }

    ~LazySegmentTree() = default;

    void build(const vector<nodeT> &node_data) {
        treeBuild(1,1,n,node_data);
    }

    nodeT& accessNode(int i) {
        treeAccessNode(1,1,n,i);
        return tree[p2index[i]];
    }
    void updateRange(int x, int y, nodeT tagNode) {
        treeUpdateRange(1,1,n,x,y,tagNode);
    }
    void updatePoint(int x, nodeT tagNode) {
        treeUpdateRange(1,1,n,x,x,tagNode);
    }
    nodeT queryRange(int x,int y) {
        return treeQueryRange(1,1,n,x,y);
    }

    //not tested
    std::pair<int, nodeT&> findFirst(int v) {
        return treeFindFirst(1,1,n,v);
    }

private:
    // Note: internal functions use two conventions:
    // 1. index starts at 1
    // 2. range is represented as [lb, ub] instead of [lb, ub)
    void pushDown(int root, int l, int r) {
        //assert(root<MAXN);
        if(tree[root].tagged()) {
            tree[segtree_lson].tag(segtree_lson, l, segtree_mid, tree[root]);
            tree[segtree_rson].tag(segtree_rson, segtree_mid + 1, r, tree[root]);
            tree[root].untag();
        }
    }

    void pushUp(int root, int l, int r) {
        tree[root].pushUp(root, l, r, tree[segtree_lson], tree[segtree_rson]);
    }

    void treeBuild(int root, int l, int r, const vector<nodeT> &node_data) {
        if(l==r) {
            p2index[l]=root;
            tree[root] = node_data[l];
            return;
        }
        treeBuild(segtree_lson, l, segtree_mid, node_data);
        treeBuild(segtree_rson, segtree_mid + 1, r, node_data);
        pushUp(root, l, r);
    }

    void treeAccessNode(int root, int l, int r, int i) {
        if(l==r) return;

        pushDown(root, l, r);
        if(i <= segtree_mid) treeAccessNode(segtree_lson, l, segtree_mid, i);
        else treeAccessNode(segtree_rson, segtree_mid + 1, r, i);
        pushUp(root, l, r);
    }

    void treeUpdateRange(int root, int l, int r, int x, int y, nodeT tagNode) {
        if(x<=l && r<=y) {
            tree[root].tag(root, l, r, tagNode);
            return;
        }

        pushDown(root, l, r);
        if(x <= segtree_mid) treeUpdateRange(segtree_lson, l, segtree_mid, x, y, tagNode);
        if(y >= segtree_mid + 1) treeUpdateRange(segtree_rson, segtree_mid + 1, r, x, y, tagNode);
        pushUp(root, l, r);
    }

    nodeT treeQueryRange(int root, int l, int r, int x, int y) {
        if(x<=l && r<=y) return tree[root];
        pushDown(root, l, r);

        nodeT Lret, Rret;
        int Lflag=false, Rflag=false;
        if(x <= segtree_mid) {
            Lflag=true;
            Lret = treeQueryRange(segtree_lson, l, segtree_mid, x, y);
        }
        if(segtree_mid + 1 <= y) {
            Rflag=true;
            Rret = treeQueryRange(segtree_rson, segtree_mid + 1, r, x, y);
        }
        pushUp(root, l, r);
        if(Lflag && Rflag) return Lret+Rret;
        return Lflag?Lret:Rret;
    }

    //not tested
    std::pair<int, nodeT&> treeFindFirst(int root, int l, int r, bool (*predicate)(nodeT&, nodeT&)) {
        if(l==r) return std::make_pair(l, tree[root]);
        pushDown(root, l, r);
        std::pair<int, nodeT> ret;
        if(predicate(tree[segtree_lson], tree[segtree_rson])) ret = treeFindFirst(segtree_lson, l, segtree_mid, predicate);
        else ret = treeFindFirst(segtree_rson, segtree_mid + 1, r, predicate);
        pushUp(root, l, r);
        return ret;
    }
};

typedef LazySegmentTree<M_QNode<  !!!DATA_TYPE_HERE!!!  >> SegTree;


#endif //CF_BASE_SEGMENTTREE_H
