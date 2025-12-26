//
// Created by Andrew Wu on 9/20/24.
//

#ifndef CHUNKEDLINKEDLIST_H
#define CHUNKEDLINKEDLIST_H

#include "../template/cp_template.h"


// Chunked linked list that maintains a ordered array of elements
template<typename dataT>
class ChunkedLinkedListNodeOrdered {
public:

    const int MAX_CHUNK_SIZE = 550;

    using nodeT = ChunkedLinkedListNodeOrdered<dataT>;

    vector<dataT> data;
    dataT offset;

    ChunkedLinkedListNodeOrdered() {}
    explicit ChunkedLinkedListNodeOrdered(dataT x): data({x}), offset(0) {}
    explicit ChunkedLinkedListNodeOrdered(const vector<dataT> &&V, int offset=0): data(V), offset(offset) {}

    inline int end() {
        return data.size();
    }
    inline int size() {
        return data.size();
    }
    inline dataT getElement(int i) {
        return data[i];
    }
    void insert(dataT x) {
        auto p = this->upperBound(x);
        data.insert(data.begin()+p, x);
    }
    int upperBound(dataT x) {
        x += offset;
        if (x>=data.back()) return end();
        return std::upper_bound(my_all(data), x) - data.begin();
    }
    inline bool needSplit() {
        return data.size() >= 2*MAX_CHUNK_SIZE;
    }
    pair<nodeT, nodeT> split() {
        vector<dataT> ldata(data.begin(), data.begin() + MAX_CHUNK_SIZE+1), rdata(data.begin() + MAX_CHUNK_SIZE+1, data.end());
        return {nodeT(move(ldata), offset), nodeT(move(rdata), offset)};
    }
};

template<typename dataT>
class ChunkedLinkedList {
public:
    using nodeT = ChunkedLinkedListNodeOrdered<dataT>;
    using nodeItT = typename list<nodeT>::iterator;
    using elementItT = pair<nodeItT, int>;
    list<nodeT> nodes;

    ChunkedLinkedList(): nodes() {}

    inline bool empty() {
        return nodes.empty();
    }
    inline elementItT end() {
        return {nodes.end(), 0};
    }
    inline elementItT back() {
        if(empty()) return end();
        return {prev(nodes.end()), nodes.back().size()-1};
    }
    elementItT prev(elementItT &it) {
        if(it.y > 0) return {it.x, it.y-1};
        if(it.x != nodes.begin()) return {std::prev(it.x), std::prev(it.x)->size()-1};
        else return end();
    }
    inline dataT getElement(elementItT elementIt) {
        return elementIt.x->getElement(elementIt.y);
    }
    int toGlobalIndex(elementItT elementIt) {
        int index=0;
        for(auto it=nodes.begin();it!=elementIt.x;++it) {
            index += it->data.size();
        }
        index += elementIt.y;
        return index;
    }
    elementItT upperBound(dataT x) {
        if(empty()) return end();
        for(auto it=nodes.begin();it!=nodes.end(); ++it) {
            auto &node = *it;
            auto ub_node = node.upperBound(x);
            if(ub_node != node.end()) return {it, ub_node};
        }
        return end();
    }

    void insert(dataT x) {
        if(empty()) {
            nodes.push_back(nodeT(x));
            return;
        }
        auto nodeIt=nodes.end();
        for(auto it=nodes.begin(); it!=nodes.end(); ++it) {
            auto &node = *it;
            if(node.upperBound(x) != node.end()) {
                node.insertOffset(x);
                nodeIt = it;
                break;
            }
        }
        if(nodeIt == nodes.end()) {
            nodeIt = std::prev(nodes.end());
            nodeIt->insertOffset(x);
        }
        if(nodeIt->needSplit()) splitNode(nodeIt);
    }

    void splitNode(nodeItT nodeIt) {
        auto &&split_result = nodeIt->split();
        auto nxtIt = std::next(nodeIt);
        nodes.insert(nxtIt, move(split_result.x));
        nodes.insert(nxtIt, move(split_result.y));
        nodes.erase(nodeIt);
    }

};

using ChunkedListT = ChunkedLinkedList<int>;


#endif //CHUNKEDLINKEDLIST_H
