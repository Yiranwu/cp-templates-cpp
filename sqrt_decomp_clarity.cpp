#pragma GCC optimize ("-Ofast")
#pragma GCC target("sse,sse2,sse3,ssse3,sse4,popcnt,abm,mmx,avx,avx2,tune=native")
#pragma GCC optimize ("unroll-loops")
#include<cmath>
#include<cstdio>
#include<vector>
#include<algorithm>
#include<cassert>
#include<ctime>
//#include "cf-lib/SegmentTree.h"
//#include "cf-lib/BlockedList.h"

class BlockedList{
public:
    int block_size, list_size;
    std::vector<std::vector<int>> data;
    std::vector<int> block_add;
    std::vector<int> blockL, blockR;
    BlockedList() {
        data=std::vector<std::vector<int>>();
        block_add=std::vector<int>();
        blockL=std::vector<int>();
        blockR=std::vector<int>();
        block_size=0;
        list_size=0;
    }
    void CalculateBlockRange() {
        for(int i=0;i<=list_size/block_size;++i) {
            blockL.emplace_back(i*block_size);
            blockR.emplace_back(std::min((i+1)*block_size-1, list_size-1));
        }
    }
    BlockedList(int block_size, int list_size) {
        data=std::vector<std::vector<int>>();
        block_add=std::vector<int>();
        this->block_size=block_size;
        this->list_size = list_size;
        CalculateBlockRange();
        for(int i=0;i<=list_size / block_size; ++i) {
            std::vector<int> data_block(blockR[i]-blockL[i]+1);
            data.push_back(data_block);
            block_add.push_back(0);
        }
    }

    BlockedList(int block_size, const std::vector<int> &list_data) {
        this->block_size=block_size;
        this->list_size=list_data.size();
        data=std::vector<std::vector<int>>();
        block_add=std::vector<int>(block_size);
        CalculateBlockRange();
        for(int i=0;i<=list_size / block_size; ++i) {
            std::vector<int> data_block(list_data.begin()+blockL[i],
                                        list_data.begin() + blockR[i]+1);
            data.push_back(data_block);
            block_add.push_back(0);
        }
    }

    BlockedList(int block_size, int *list_data, int list_size) {
        this->block_size=block_size;
        this->list_size=list_size;
        data=std::vector<std::vector<int>>();
        block_add=std::vector<int>(block_size);
        CalculateBlockRange();
        for(int i=0;i<=list_size / block_size; ++i) {
            std::vector<int> data_block(list_data+blockL[i],
                                        list_data + blockR[i]+1);
            data.push_back(data_block);
            block_add.push_back(0);
        }
    }

    int GetIndex(int index) {
        return data[index / block_size][index % block_size] + block_add[index / block_size];
    }

    void AddIndex(int index, int v) {
        data[index / block_size][index % block_size] += v;
    }

    void SetIndex(int index, int v) {
        data[index / block_size][index % block_size] = v;
    }

    void AddRange(int l, int r, int v) {
        int lblock = l / block_size, rblock= r / block_size;
        if(lblock==rblock) {
            for(int i=l%block_size;i<r%block_size;++i)
                data[lblock][i]+=v;
            return;
        }

        for(int i=l%block_size; i<block_size; ++i) {
            data[lblock][i]+=v;
        }
        for(int i=0;i<=r%block_size; ++i) {
            data[rblock][i]+=v;
        }
        for(int i=lblock+1;i<rblock;++i) {
            block_add[i]+=v;
        }
    }
};

class SegmentTree {
public:
    std::vector<int> data_min{};
    std::vector<int> add_tag{};
    int n;
    explicit SegmentTree(int n) {
        this->n = n;
        data_min = std::vector<int>(3*n, 2000000000);
        add_tag = std::vector<int>(3*n, 0);
    }

    ~SegmentTree() = default;

    void TreeSetLeaf(int root, int l, int r, int p, int v) {
        if(l==r) {
            data_min[root]=v;
            return;
        }
        PushDownAddTag(root, l, r);
        int mid = (l+r)>>1, lson = root<<1, rson = lson|1;
        if(p<=mid) {
            TreeSetLeaf(lson, l, mid, p, v);
        }
        else {
            TreeSetLeaf(rson, mid+1, r, p, v);
        }
        data_min[root] = std::min(data_min[lson], data_min[rson]);
    }

    void SetLeaf(int p, int v) {
        TreeSetLeaf(1,1,n,p,v);
    }

    void TreeAddLeaf(int root, int l, int r, int p, int v) {
        if(l==r) {
            data_min[root]+=v;
            return;
        }
        PushDownAddTag(root, l, r);
        int mid = (l+r)>>1, lson = root<<1, rson = lson|1;
        if(p<=mid) {
            TreeAddLeaf(lson, l, mid, p, v);
        }
        else {
            TreeAddLeaf(rson, mid+1, r, p, v);
        }
        data_min[root] = std::min(data_min[lson], data_min[rson]);
    }

    void TreeNodeAdd(int root, int l, int r, int v) {
        data_min[root]+=v;
        add_tag[root]+=v;
    }

    void PushDownAddTag(int root, int l, int r) {
        int mid=(l+r)>>1, lson=root<<1, rson=lson|1;
        if(add_tag[root]!=0) {
            TreeNodeAdd(lson, l, mid, add_tag[root]);
            TreeNodeAdd(rson, mid + 1, r, add_tag[root]);
            add_tag[root]=0;
        }
    }

    void TreeAddRange(int root, int l, int r, int x, int y, int v) {
        int mid = (l+r)>>1, lson = root<<1, rson = lson|1;
        if(x<=l && r<=y) {
            TreeNodeAdd(root, l, r, v);
            return;
        }

        PushDownAddTag(root, l, r);
        if(x<=mid) {
            TreeAddRange(lson, l, mid, x, y, v);
        }
        if(y>=mid+1) {
            TreeAddRange(rson, mid + 1, r, x, y, v);
        }
        data_min[root] = std::min(data_min[lson], data_min[rson]);
    }

    void AddRange(int l, int r, int v) {
        if(l>r)
            return;
        TreeAddRange(1, 1, n, l, r, v);
    }

    std::pair<int, int> TreeLowerBound(int root, int l,int r, int v) {
        if(l==r) {
            return std::make_pair(l, data_min[root]);
        }
        PushDownAddTag(root, l, r);
        int mid = (l+r)>>1, lson = root<<1, rson = lson|1;
        if(data_min[rson]<=v) {
            return TreeLowerBound(rson, mid+1, r, v);
        }
        else {
            return TreeLowerBound(lson, l, mid, v);
        }
    }

    std::pair<int, int> LowerBound(int v) {
        return TreeLowerBound(1,1,n,v);
    }
};

using namespace std;

int n;

int calculate_pos_from_c(const vector<int>::iterator vbegin, const vector<int>::iterator vend, int pos) {
    int ret=pos;
    for(auto i=vbegin;i!=vend;++i) {
        if((*i)<=ret)
            ++ret;
    }
    return ret;
}

void update_next(vector<int>::iterator cbegin, vector<int>::iterator cend, BlockedList &next, vector<int> &suffix, int p) {

    //clock_t next_upd_time=0, segtree_build_time=0, segtree_upd_time=0;

    int B=cend-cbegin;

    //clock_t next_upd_begin=clock();

    next.AddRange(suffix[p], next.list_size-1, -1);

    //next_upd_time+=clock()-next_upd_begin;
    //clock_t segtree_build_begin=clock();

    SegmentTree segtree(B);
    for(int i=0;i<B;++i) {
        segtree.SetLeaf(i+1, *(cbegin+i));
    }

    //segtree_build_time+=clock()-segtree_build_begin;

    for(int i=0;i<B;++i) {

        //clock_t segtree_upd_begin=clock();

        pair<int,int> lower_bound=segtree.LowerBound(segtree.data_min[1]);

        //segtree_upd_time+=clock()-segtree_upd_begin;

        int list_index=lower_bound.first-1, value=lower_bound.second;

        //next_upd_begin=clock();

        if(list_index!=p) {
            /*
            if(value<suffix[list_index]) {
                //assert(value==suffix[list_index]-1);
                next.AddIndex(value, 1);
            }
            if(value>suffix[list_index]) {
                //assert(value==suffix[list_index]+1);
                next.AddIndex(suffix[list_index], -1);
            }
            */
            next.AddIndex(min(value, suffix[list_index]), suffix[list_index]-value);
        }
        else {
            next.AddRange(value, next.list_size-1, 1);
        }

        //next_upd_time+=clock()-next_upd_begin;
        //segtree_upd_begin=clock();

        suffix[list_index] = value;
        segtree.SetLeaf(list_index+1, 2*n);
        segtree.AddRange(list_index+1+1, B, -1);

        //segtree_upd_time+=(double)(clock()-segtree_upd_begin)/CLOCKS_PER_SEC;

    }
    /*
    printf("next upd time: %f, segtree build time: %f, segtree upd time: %f\n",
           (double)next_upd_time/CLOCKS_PER_SEC,
           (double)segtree_build_time/CLOCKS_PER_SEC,
           (double)segtree_upd_time/CLOCKS_PER_SEC);

    printf("updated next:");
    for(int i=0;i<n;++i) {
        printf("%d ", next.GetIndex(i));
    }
    printf("\n");
    */
}

pair<BlockedList, vector<int>> build_next_block(vector<int>::iterator cbegin, vector<int>::iterator cend, int len) {
    int B=cend-cbegin;
    int ori_n=n,n=len;
    BlockedList next(ceil(sqrt(n)), n);
    vector<int> suffix(B);

    for(int i=0;i<n;++i) {
        next.SetIndex(i, i);
    }

    SegmentTree segtree(B);
    for(int i=0;i<B;++i) {
        segtree.SetLeaf(i+1, *(cbegin+i));
    }
    for(int i=0;i<B;++i) {
        pair<int,int> lower_bound=segtree.LowerBound(segtree.data_min[1]);
        int list_index=lower_bound.first-1, value=lower_bound.second;
        suffix[list_index] = value;
        next.AddRange(value, n-1, 1);
        segtree.SetLeaf(list_index+1, 2*n);
        segtree.AddRange(list_index+1+1, B, -1);
    }
    return make_pair(next, suffix);
}

int main() {
    freopen("/Users/yiran/CLionProjects/codeforces/input.txt", "r", stdin);
    //freopen("~/ClionProjects/codeforces/output.txt", "w", stdout);
    vector<int> c;
    scanf("%d", &n);
    for(int i=0;i<n;++i) {
        int b;
        scanf("%d", &b);
        c.push_back(i-b);
    }
    // i-th element should be at pos ci for first i elements (indexed from 0)

    clock_t build_begin=clock();

    vector<BlockedList> next4block;
    vector<vector<int>> suffix4block;
    int B,m;
    if(n<10000) {
        B=ceil(sqrt(float(n) / (log(n)/log(2))));
        m=ceil(float(n)/B);
    }
    else {
        B=ceil(sqrt(float(n) / (log(n)/log(2))/3));
        m=ceil(float(n)/B);
    }
    //printf("B=%d\n", B);
    for(int i=0;i<m;++i) {
        int block_start = i * B, block_end = min((i + 1) * B, n);
        auto block_and_suffix=build_next_block(c.begin()+block_start, c.begin()+block_end, block_end);
        next4block.push_back(block_and_suffix.first);
        suffix4block.push_back(block_and_suffix.second);
    }

    clock_t sol_begin=clock();
    double upd_time=0.0, qry_time=0.0;
    int upd_cnt=0, qry_cnt=0;
    printf("build time %f\n", (double)(sol_begin-build_begin)/CLOCKS_PER_SEC);

    int q, qid, qi, qx;
    scanf("%d", &q);
    for(int i=0;i<q;++i) {
        scanf("%d", &qid);
        if(qid==1) {
            scanf("%d %d", &qi, &qx);
            c[qi-1]=(qi-1)-qx;

            clock_t upd_begin = clock();

            int block_index=(qi-1)/B, block_start=block_index*B, block_end=min((block_index+1)*B,n);
            update_next(c.begin()+block_start, c.begin()+block_end,
                        next4block[block_index], suffix4block[block_index], qi-1-B*block_index);

            upd_time+=(double) (clock()-upd_begin)/CLOCKS_PER_SEC;
            ++upd_cnt;
        }
        else {
            scanf("%d", &qi);

            clock_t qry_begin = clock();

            int ans=c[qi-1], block_index=(qi-1)/B, block_start=block_index*B, block_end=min((block_index+1)*B,n);
            ans=calculate_pos_from_c(c.begin()+qi, c.begin()+block_end, ans);
            for(int j=block_index+1;j<m;++j)
                ans = next4block[j].GetIndex(ans);
            //printf("%d\n", ans+1);

            qry_time+=(double) (clock()-qry_begin)/CLOCKS_PER_SEC;
            ++qry_cnt;
        }
    }

    clock_t sol_end=clock();
    printf("sol time: %f\n", (double)(sol_end-sol_begin)/CLOCKS_PER_SEC);
    printf("upd time: %f, qry time: %f\n", upd_time, qry_time);
    printf("per upd time: %f, per qry time: %.8f\n", upd_time/upd_cnt, qry_time/qry_cnt);

    //fclose(stdin);
    //fclose(stdout);
    return 0;
}