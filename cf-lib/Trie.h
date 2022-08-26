//
// Created by yiran on 2022/1/14.
//

#ifndef CF_BASE_TRIE_H
#define CF_BASE_TRIE_H

class TrieIntKey {
public:
    int value,n;
    TrieIntKey(int _value, int _n): value(_value), n(_n) {}

    int digitAt(int pos) const {return (value&pow2(pos))>0;}
};

class TrieIntRevKey {
public:
    int value,n;
    TrieIntRevKey(int _value, int _n): value(_value), n(_n) {}

    int digitAt(int pos) const {return (value&pow2(n-pos))>0;}
};

class TrieStringKey {
public:
    string * const value_ptr;
    int n;
    TrieStringKey(string &_value): value_ptr(&_value), n(_value.length()) {}

    int digitAt(int pos) const {return value_ptr->at(pos) - 'a';}
};

// Trie(int n_ch)
// n_ch: number of chars in the alphabet
template <typename keyT, typename dataT>
class Trie {
public:
    int n_trie, n_ch;
    vector<vector<int>> trie;
    vector<int> subtree_size;
    vector<vector<dataT>> node_data;
    const keyT * key_ptr;
    const dataT * data_ptr;

    void createNewNode() {
        trie.push_back(vector<int>(n_ch, 0));
        subtree_size.push_back(0);
        node_data.push_back({});
    }

    Trie(int _n_ch): n_ch(_n_ch), n_trie(0) {
        createNewNode();
    }

    int trieInsert(int root, int pos) {
        ++subtree_size[root];
        if(pos>=key_ptr->n) {
            node_data[root].push_back(*data_ptr);
            return root;
        }
        int son = key_ptr->digitAt(pos);
        if(!trie[root][son]) {
            trie[root][son] = ++n_trie;
            createNewNode();
        }
        return trieInsert(trie[root][son], pos+1);
    }

    void insert(keyT &value, dataT &data) {
        key_ptr = &value;
        data_ptr = &data;
        trieInsert(0, 0);
    }

    dataT findLeaf(int root) {
        assert(subtree_size[root]>=1);
        if(node_data[root].size()) return node_data[root][0];
        if(trie[root][0]) return findLeaf(trie[root][0]);
        return findLeaf(trie[root][1]);
    }
};

#endif //CF_BASE_TRIE_H
