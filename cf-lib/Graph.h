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

    int n,m,nodeSize;
    vector<vector<Edge>> G;
    vector<dataT> Edata;

    explicit GraphBase(int _n, int _m) : n(_n), m(_m), nodeSize(n+1) {
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
            addDummyEdge(x,y);
        }
    }

    void readGraph() {
        int x,y;
        dataT edgeData;
        for(int i=0;i<m;++i) {
            cin >> x >> y;
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

    UndirectedGraph(int _n, int _m): GraphBase<dataT>(_n, _m) {}

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

    explicit Tree(int _n): UndirectedGraph<dataT>(_n,_n-1) {}

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
        f.resize(this->nodeSize);
        d.resize(this->nodeSize);
        sz.resize(this->nodeSize);
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
