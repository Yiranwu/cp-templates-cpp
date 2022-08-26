//
// Created by yiran on 2021/12/24.
//

#ifndef CF_BASE_GRAPHBASE_H
#define CF_BASE_GRAPHBASE_H

class Edge {
public:
    int id,v;
    Edge(int _id, int _v): id(_id), v(_v) {}
};

// Graph(int n)
// n: number of nodes
template <typename dataT>
class Graph {
public:

    int n;
    vector<vector<Edge>> G;
    vector<dataT> Edata;

    Graph() = default;

    explicit Graph(int _n) : n(_n) {
        G.resize(n);
    }

    void addEdge(int x, int y, int id) {
        G[x].pb({id, y});
    }

    void AddEdgeDirectional(int x, int y, dataT data=dataT()) {
        addEdge(x,y,Edata.size());
        Edata.push_back(data);
    }

    void AddEdgeBidirectional(int x,int y, dataT data=dataT()) {
        addEdge(x,y,Edata.size());
        addEdge(y,x,Edata.size());
        Edata.push_back(data);
    }

    void readUndirectedGraphDummy(int m) {
        int x,y;
        repin(i,1,m) {
            cin>>x>>y;
            AddEdgeBidirectional(x,y);
        }
    }

    vector<Edge>& operator [] (int x) {
        return G[x];
    }
};

typedef Graph<int> graphDummyT;

template <typename dataT>
class Tree: public Graph<dataT> {
public:

    explicit Tree(int _n, int _index_offset=1) : Graph<dataT>(_n, _index_offset) {}

    void readTreeDummy() {
        readUndirectedGraphDummy(this->n-1);
    }
};

typedef Tree<int> treeDummyT;

#endif //CF_BASE_GRAPHBASE_H
