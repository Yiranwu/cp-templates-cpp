#include<cmath>
#include<cstdio>
#include<vector>
#include<algorithm>
#include<cassert>
#include<ctime>

class BlockedList{
public:
    int block_size, list_size;
    std::vector<std::vector<int>> data;
    std::vector<int> block_add;
    BlockedList(int block_size, int list_size) {
        data=std::vector<std::vector<int>>();
        block_add=std::vector<int>();
        this->block_size=block_size;
        this->list_size = list_size;
        for(int i=0;i<=list_size / block_size; ++i) {
            std::vector<int> data_block(std::min(list_size, (i+1) * block_size) - i * block_size);
            data.push_back(data_block);
            block_add.push_back(0);
        }
    }

    BlockedList(int block_size, const std::vector<int> &list_data) {
        data=std::vector<std::vector<int>>();
        block_add=std::vector<int>();
        this->block_size=block_size;
        this->list_size=list_data.size();
        data=std::vector<std::vector<int>>();
        int list_size=list_data.size();
        for(int i=0;i< list_size / block_size; ++i) {
            std::vector<int> data_block(list_data.begin()+(i * block_size),
                                        list_data.begin() + (std::min(list_size, (i + 1) * block_size)));
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
        for(int i=l; i < std::min((lblock+1) * block_size, list_size); ++i) {
            data[lblock][i % block_size]+=v;
        }
        for(int i= rblock * block_size; i < std::min((rblock+1) * block_size, list_size); ++i) {
            data[rblock][i % block_size]+=v;
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
    }

    ~SegmentTree() = default;
    void EnableMin() {
        data_min = std::vector<int>(4*n, 2000000000);
    }
    void EnableRangeAdd() {
        add_tag = std::vector<int>(4*n, 0);
    }

    void TreeSetLeaf(int root, int l, int r, int p, int v) {
        if(l==r) {
            data_min[root]=v;
            return;
        }
        PushDownAddTag(root, l, r);
        int mid = (l+r)>>1, lson = root<<1, rson = lson + 1;
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
        int mid = (l+r)>>1, lson = root<<1, rson = lson | 1;
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
        int mid = (l+r)>>1, lson = root<<1, rson = lson + 1;
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

void update_next(vector<int>::iterator cbegin, vector<int>::iterator cend, BlockedList &next, vector<int> &suffix, int p, int last_v) {
    int B=cend-cbegin;
    double next_time=0.0, segtree_time=0.0;
    clock_t next_begin=clock();
    next.AddRange(suffix[p], n-1, -1);
    next_time+=(double)(clock()-next_begin)/CLOCKS_PER_SEC;
    clock_t segtree_begin=clock();
    SegmentTree segtree(B);
    segtree.EnableMin();
    segtree.EnableRangeAdd();
    for(int i=0;i<B;++i) {
        segtree.SetLeaf(i+1, *(cbegin+i));
    }
    segtree_time+=(double)(clock()-segtree_begin)/CLOCKS_PER_SEC;
    for(int i=0;i<B;++i) {
        segtree_begin=clock();
        pair<int,int> lower_bound=segtree.LowerBound(segtree.data_min[1]);
        segtree_time+=(double)(clock()-segtree_begin)/CLOCKS_PER_SEC;
        int list_index=lower_bound.first-1, value=lower_bound.second;
        if(list_index!=p) {
            next_begin=clock();
            if(value<suffix[list_index]) {
                assert(value==suffix[list_index]-1);
                next.AddIndex(value, 1);
            }
            if(value>suffix[list_index]) {
                assert(value==suffix[list_index]+1);
                next.AddIndex(suffix[list_index], -1);
            }
            next_time+=(double)(clock()-next_begin)/CLOCKS_PER_SEC;
        }
        else {
            next_begin=clock();
            next.AddRange(value, n-1, 1);
            next_time+=(double)(clock()-next_begin)/CLOCKS_PER_SEC;
        }
        suffix[list_index] = value;
        segtree_begin=clock();
        segtree.SetLeaf(list_index+1, 2*n);
        segtree.AddRange(list_index+1+1, B, -1);
        segtree_time+=(double)(clock()-segtree_begin)/CLOCKS_PER_SEC;
    }

    printf("update next time: %f, segtree time:%f\n", next_time, segtree_time);
    /*
    printf("updated next:");
    for(int i=0;i<n;++i) {
        printf("%d ", next.GetIndex(i));
    }
    printf("\n");
    */
}

pair<BlockedList, vector<int>> build_next_block(vector<int>::iterator cbegin, vector<int>::iterator cend) {
    int B=cend-cbegin;
    double next_time=0.0, segtree_time=0.0;

    clock_t next_begin=clock();
    //BlockedList next(ceil(sqrt(float(n) * (log(n)/log(2)))), n);
    vector<int> next(n);
    vector<int> suffix(B);

    for(int i=0;i<n;++i) {
        next.SetIndex(i, i);
    }
    next_time+=(double)(clock()-next_begin)/CLOCKS_PER_SEC;
    clock_t segtree_begin=clock();

    SegmentTree segtree(B);
    segtree.EnableMin();
    segtree.EnableRangeAdd();


    for(int i=0;i<B;++i) {
        segtree.SetLeaf(i+1, *(cbegin+i));
    }
    segtree_time+=(double)(clock()-segtree_begin)/CLOCKS_PER_SEC;
    for(int i=0;i<B;++i) {
        segtree_begin=clock();

        pair<int,int> lower_bound=segtree.LowerBound(segtree.data_min[1]);

        segtree_time+=(double)(clock()-segtree_begin)/CLOCKS_PER_SEC;

        int list_index=lower_bound.first-1, value=lower_bound.second;
        suffix[list_index] = value;

        next_begin=clock();
        next.AddRange(value, n-1, 1);
        next_time+=(double)(clock()-next_begin)/CLOCKS_PER_SEC;
        segtree_begin=clock();
        segtree.SetLeaf(list_index+1, 2*n);
        segtree.AddRange(list_index+1+1, B, -1);
        segtree_time+=(double)(clock()-segtree_begin)/CLOCKS_PER_SEC;
    }
    printf("build next time: %f, segtree time:%f\n", next_time, segtree_time);
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

    clock_t build_start=clock();
    vector<BlockedList> next4block;
    vector<vector<int>> suffix4block;
    int B=ceil(sqrt(float(n) / (log(n)/log(2)))), m=ceil(float(n)/B);
    printf("B=%d\n", B);
    for(int i=0;i<m;++i) {
        int block_start = i * B, block_end = min((i + 1) * B, n);
        auto block_and_suffix=build_next_block(c.begin()+block_start, c.begin()+block_end);
        next4block.push_back(block_and_suffix.first);
        suffix4block.push_back(block_and_suffix.second);
    }
    clock_t build_end=clock();
    printf("build time: %f\n", (double)(build_end-build_start)/CLOCKS_PER_SEC);

    clock_t query_start=clock();
    double update_time=0.0, query_time=0.0;
    double update_cnt=0, query_cnt=0;
    int q, qid, qi, qx;
    scanf("%d", &q);
    for(int i=0;i<q;++i) {
        scanf("%d", &qid);
        if(qid==1) {
            scanf("%d %d", &qi, &qx);
            int last_v = c[qi-1];
            c[qi-1]=(qi-1)-qx;
            clock_t update_start=clock();

            int block_index=(qi-1)/B, block_start=block_index*B, block_end=min((block_index+1)*B,n);
            update_next(c.begin()+block_start, c.begin()+block_end,
                        next4block[block_index], suffix4block[block_index], qi-1-B*block_index, last_v);
            update_time+=(double)(clock()-update_start)/CLOCKS_PER_SEC;
        }
        else {
            scanf("%d", &qi);
            clock_t point_query_start=clock();
            int ans=c[qi-1], block_index=(qi-1)/B, block_start=block_index*B, block_end=min((block_index+1)*B,n);
            ans=calculate_pos_from_c(c.begin()+qi, c.begin()+block_end, ans);
            for(int j=block_index+1;j<m;++j)
                ans = next4block[j].GetIndex(ans);
            query_time+=(double)(clock()-point_query_start)/CLOCKS_PER_SEC;
            ++query_cnt;
            //printf("%d\n", ans+1);
        }
    }
    clock_t query_end=clock();
    printf("query time: %f\n", (double)(query_end-query_start)/CLOCKS_PER_SEC);
    printf("upd time: %f, point query_time: %f, per point query time: %f", update_time, query_time, query_time/query_cnt);
    fclose(stdin);
    //fclose(stdout);
    return 0;
}