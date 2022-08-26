//
// Created by yiran on 2021/8/10.
//

#ifndef CF_BASE_SEGTREENODES_H
#define CF_BASE_SEGTREENODES_H

template <typename valueT>
class PointUpdate_MinMaxNode {
public:
    valueT maxv, minv, add_tag, set_tag;
    bool add_flag, set_flag;
    PointUpdate_MinMaxNode() = default;
    explicit PointUpdate_MinMaxNode(valueT _v): maxv(_v), minv(_v), add_tag(valueT()), set_tag(valueT()), add_flag(false), set_flag(false) {}
    PointUpdate_MinMaxNode(valueT _maxv, valueT _minv): maxv(_maxv), minv(_minv) {}
    PointUpdate_MinMaxNode(bool _add_flag, valueT _add_tag, bool _set_flag, valueT _set_tag): add_tag(_add_tag), set_tag(_set_tag), add_flag(_add_flag), set_flag(_set_flag) {}
    bool tagged() {return add_flag || set_flag;}
    void tag(int root, int l, int r, PointUpdate_MinMaxNode &tagNode) {
        if(tagNode.set_flag) {
            maxv = tagNode.set_tag, minv = tagNode.set_tag;
            set_flag=true; set_tag=tagNode.set_tag;
            add_flag=false; add_tag=valueT();
        }
        if(tagNode.add_flag) {
            maxv+=tagNode.add_tag, minv +=tagNode.add_tag;
            add_flag=true; add_tag+=tagNode.add_tag;
        }
    }
    void untag() {set_flag=add_flag=false; add_tag=valueT();}
    void pushUp(int root, int l, int r, PointUpdate_MinMaxNode &lnode, PointUpdate_MinMaxNode &rnode) {
        maxv = max(lnode.maxv, rnode.maxv);
        minv = min(lnode.minv, rnode.minv);
    }
    static vector<PointUpdate_MinMaxNode> buildNodeListFromData(const vector<valueT> datas) {
        vector<PointUpdate_MinMaxNode> ret;
        for(valueT dat: datas) ret.pb(PointUpdate_MinMaxNode(dat));
        return ret;
    }
};
template <typename valueT>
inline PointUpdate_MinMaxNode<valueT> operator + (const PointUpdate_MinMaxNode<valueT>& lnode, const PointUpdate_MinMaxNode<valueT>& rnode){
    return {max(lnode.maxv, rnode.maxv), min(lnode.minv, rnode.minv)};
}

template <typename dataT>
class Max_MaxNode {
public:
    const static dataT INVALID;
    dataT max_tag, data_max;
    int data_idx;
    bool max_flag;

    Max_MaxNode(dataT _max_tag=INVALID, bool _max_flag=false, dataT _data_max=INVALID, int _data_idx=0): max_tag(_max_tag), max_flag(_max_flag), data_max(_data_max), data_idx(_data_idx) {}
    bool tagged() {return max_flag;}
    void tag(int root, int l, int r, Max_MaxNode &tagNode) {
        if(!max_flag || max_tag<tagNode.max_tag) {
            max_flag=true, max_tag=tagNode.max_tag;
            data_max = max(data_max, tagNode.max_tag);
        }
    }
    void untag() {max_flag=false;}
    void pushUp(int root, int l, int r, Max_MaxNode &lnode, Max_MaxNode &rnode) {
        data_max = max(lnode.data_max, rnode.data_max);
        data_idx = lnode.data_max>rnode.data_max?lnode.data_idx:rnode.data_idx;
    }
};
template <typename dataT>
inline Max_MaxNode<dataT> operator + (const Max_MaxNode<dataT>& lnode, const Max_MaxNode<dataT>& rnode){
    return {Max_MaxNode<dataT>::INVALID, false,
            max(lnode.data_max, rnode.data_max),
            lnode.data_max>rnode.data_max?lnode.data_idx:rnode.data_idx};
}

template<>
const int Max_MaxNode<int> :: INVALID = INT_MIN;

template<>
const ll Max_MaxNode<ll> :: INVALID = ll(INT_MIN);

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


template <typename valueT>
class Set_SumNode {
public:
    valueT data_sum=valueT(), set_tag=valueT();
    bool set_flag=false;
    Set_SumNode() = default;
    explicit Set_SumNode(valueT _v): data_sum(_v), set_tag(valueT()), set_flag(false) {}
    Set_SumNode(valueT _set_tag, bool _set_flag): data_sum(valueT()), set_tag(_set_tag), set_flag(_set_flag) {}
    bool tagged() {return set_flag;}
    void tag(int root, int l, int r, Set_SumNode<valueT> &tagNode) {
        data_sum = valueT(r-l+1) * tagNode.set_tag;
        set_flag=true; set_tag = tagNode.set_tag;
    }
    void untag() {set_flag=false;}
    void pushUp(int root, int l, int r, Set_SumNode<valueT> &lnode, Set_SumNode<valueT> &rnode) {
        data_sum = lnode.data_sum + rnode.data_sum;
    }
    static vector<Set_SumNode<valueT>> buildNodeListFromData(vector<valueT> &data) {
        vector<Set_SumNode<valueT>> V;
        for(valueT v: data) V.pb(Set_SumNode<valueT>(v));
        return V;
    }
};
// for merging result from lson and rson
template <typename valueT>
inline Set_SumNode<valueT> operator + (const Set_SumNode<valueT>& lnode, const Set_SumNode<valueT>& rnode){
    return Set_SumNode(lnode.data_sum + rnode.data_sum);
}
#endif //CF_BASE_SEGTREENODES_H
