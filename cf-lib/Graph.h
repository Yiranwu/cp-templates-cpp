//
// Created by yiran on 2021/12/24.
//

#ifndef CF_BASE_GRAPHBASE_H
#define CF_BASE_GRAPHBASE_H

class Edge {
public:
    // id: id of edge
    // v: next vertex in edge
    int id, v;
    Edge(int _id, int _v): id(_id), v(_v) {}
};

// Graph(int n)
// n: number of nodes
// nodeSize: size that we will use for vectors, in case we need soldiers at the beginning or at the end.
template <typename dataT>
class GraphBase {
public:

    int n,m, nodeOffset, nodeSize;
    vector<vector<Edge>> G;
    vector<dataT> Edata;

    explicit GraphBase(int _n, int _m, int _nodeOffset=1) : n(_n), m(_m), nodeOffset(_nodeOffset), nodeSize(n+nodeOffset) {
        G.resize(nodeSize);
        Edata.reserve(m);
    }

    void appendEdge(int x, int y, int id) {
        G[x].pb({id, y});
    }

    virtual void addEdge(int x,int y, dataT data) = 0;
    void addDummyEdge(int x,int y) {
        addEdge(x,y,dataT());
    }

    void readGraphWithDummyEdge() {
        int x,y;
        for(int i=0;i<m;++i) {
            cin >> x >> y;
            x-=nodeOffset; y-=nodeOffset;
            addDummyEdge(x,y);
        }
    }

    void readGraph() {
        int x,y;
        dataT edgeData;
        for(int i=0;i<m;++i) {
            cin >> x >> y;
            x-=nodeOffset; y-=nodeOffset;
            cin >> edgeData;
            addEdge(x,y, edgeData);
        }
    }

    const vector<Edge>& operator [] (int x) {
        return G[x];
    }
};

template <typename dataT>
class DirectedGraph: public GraphBase<dataT> {
public:

    void addEdge(int x, int y, dataT data) override {
        this->appendEdge(x,y,this->Edata.size());
        this->Edata.push_back(data);
    }
};

template <typename dataT>
class UndirectedGraph: public GraphBase<dataT> {
public:

    UndirectedGraph(int _n, int _m, int _nodeOffset=1): GraphBase<dataT>(_n,_m,_nodeOffset) {}

    void addEdge(int x, int y, dataT data) override {
        this->appendEdge(x,y,this->Edata.size());
        this->appendEdge(y,x,this->Edata.size());
        this->Edata.push_back(data);
    }
};

template <typename dataT>
class Tree: public UndirectedGraph<dataT> {
public:
    vector<int> f,d,sz;
    using baseT = UndirectedGraph<dataT>;

    explicit Tree(int _n, int _nodeOffset=1): baseT(_n,_n-1, _nodeOffset) {
        f.resize(this->nodeSize);
        d.resize(this->nodeSize);
        sz.resize(this->nodeSize);
    }

    // 0 is always the root
    // read n-1 numbers, p1...pn-1, pi number is ancestor of vertex i
    void readTreeWithDummyEdgeByAncestors() {
        int x,y;
        for(int i=1;i<baseT::n;++i) {
            cin >> x;
            baseT::addDummyEdge(x-baseT::nodeOffset,i);
        }
    }

    void _dfs(int root, int fa, int depth) {
        f[root]=fa;
        d[root]=depth;
        sz[root]=1;
        for(auto &e: this->G[root]) {
            int son = e.v;
            if(son == fa) continue;
            _dfs(son, root, depth+1);
            sz[root] += sz[son];
        }
    }

    void dfs(int root) {
        _dfs(root, -1, 1);
    }

    vi getPath(int a, int b) {
        // assuming a is deeper or equal depth than b
        if(d[a]<d[b]) {
            auto rev_path = getPath(b,a);
            std::reverse(rev_path.begin(), rev_path.end());
            return rev_path;
        }
        vi pa, pb;
        pa.pb(a);
        while(d[a]>d[b]) {
            a = f[a];
            pa.pb(a);
        }
        pb.pb(b);
        while(a!=b) {
            a=f[a];
            b=f[b];
            pa.pb(a);
            pb.pb(b);
        }
        pb.pop_back();
        std::reverse(pb.begin(), pb.end());
        pa.insert(pa.end(), pb.begin(), pb.end());
        return pa;
    }
};

using DummyTree = Tree<int>;

#endif //CF_BASE_GRAPHBASE_H
