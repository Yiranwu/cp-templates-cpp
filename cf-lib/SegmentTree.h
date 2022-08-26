//
// Created by yiran on 2021/6/30.
//
#ifndef CF_BASE_SEGMENTTREE_H
#define CF_BASE_SEGMENTTREE_H

#include<vector>
#include<algorithm>

// TODO: decouple M and Q
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
        tree.resize(n*4);
        p2index.resize(n*4);
    }

    explicit LazySegmentTree(int _n): n(_n) {
        init();
        vector<nodeT> node_data;
        node_data.resize(n);
        build(node_data);
    }

    explicit LazySegmentTree(const vector<nodeT> &node_data): n(node_data.size()) {
        init();
        build(node_data);
    }

    explicit LazySegmentTree(const vector<valueT> &node_value): n(node_value.size()) {
        init();
        vector<nodeT> node_data;
        node_data.reserve(n);
        for(auto &v: node_value) node_data.push_back(nodeT(node_value));
    }

    explicit LazySegmentTree(valueT* begin, valueT* end): n(end-begin) {
        init();
        vector<nodeT> node_data;
        node_data.reserve(n);
        for_each(begin, end, [&node_data](const valueT& v){node_data.push_back(v);});
    }

    ~LazySegmentTree() = default;


    void build(const vector<nodeT> &node_data) {
        treeBuild(1,1,n,node_data);
    }

    nodeT& accessNode(int i) {
        ++i;
        treeAccessNode(1,1,n,i);
        return tree[p2index[i]];
    }
    void updateRange(int x, int y, nodeT tagNode) {
        ++x; ++y;
        if(x==y) return nodeT();
        treeUpdateRange(1,1,n,x,y-1,tagNode);
    }
    void updatePoint(int x, nodeT tagNode) {
        ++x;
        treeUpdateRange(1,1,n,x,x,tagNode);
    }
    nodeT queryRange(int x,int y) {
        ++x; ++y;
        if(x==y) return nodeT();
        return treeQueryRange(1,1,n,x,y-1);
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
            tree[root] = node_data[l-1];
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
