#pragma GCC optimize ("-Ofast")
#pragma GCC target("sse,sse2,sse3,ssse3,sse4,popcnt,abm,mmx,avx,avx2,tune=native")
#pragma GCC optimize ("unroll-loops")
#include<cmath>
#include<cstdio>
#include<vector>
#include<algorithm>
#include<cassert>
#include<ctime>
#include<iostream>
using namespace std;

const int MAXN=100005, B=70;
const int NB=(MAXN-1)/B+1, SQRTN=320;
//const int NB=100, SQRTN=320;
int n, data_min[MAXN*2], add_tag[MAXN*2], c[MAXN];
int next_block_size, next_size[NB+2], next_loc[NB+2][SQRTN][SQRTN], block_add[NB+2][SQRTN], suffix[NB+2][B+2];
int Bid[MAXN], Bp[MAXN], BL[NB+2], BR[NB+2], nextid[MAXN], nextp[MAXN], nextL[SQRTN], nextR[SQRTN];

template <typename T>
void readint(T &first, int i)
{
    first=0;int f=1;char c;
    for(c=getchar();!isdigit(c);c=getchar())if(c=='-')f=-1;
    for(;isdigit(c);c=getchar())first= first * 10 + (c - '0');
    first*=f;
}

void nextAddRange(int bid, int l, int r, int v) {
    int lblock = nextid[l], rblock= nextid[r];
    if(lblock==rblock) {
        for(int i=nextp[l];i<=nextp[r];++i)
            next_loc[bid][lblock][i]+=v;
        return;
    }
    if(nextp[l]==0) {
        --lblock;
    }
    else {
        for(int i=nextp[l]; i<next_block_size; ++i) {
            next_loc[bid][lblock][i]+=v;
        }
    }
    if(r+1==nextR[rblock]) {
        ++rblock;
    }
    else {
        for(int i=0;i<=nextp[r]; ++i) {
            next_loc[bid][rblock][i]+=v;
        }
    }
    for(int i=lblock+1;i<rblock;++i) {
        block_add[bid][i]+=v;
    }
}

void buildSegTree(int root, int l, int r, int cbegin) {
    add_tag[root]=0;
    if(l==r) {
        data_min[root]=c[l-1+cbegin];
        return;
    }
    int mid=(l+r)>>1;
    buildSegTree(root<<1, l, mid ,cbegin);
    buildSegTree(root<<1|1,mid+1,r, cbegin);
    data_min[root]=min(data_min[root<<1], data_min[root<<1|1]);
}

void PushDownAddTag(int root, int l, int r) {
    int delta=add_tag[root];
    if(add_tag[root]!=0) {
        data_min[root<<1]+=delta;
        add_tag[root<<1]+=delta;
        data_min[root<<1|1]+=delta;
        add_tag[root<<1|1]+=delta;
        add_tag[root]=0;
    }
}

void setLeaf(int root, int l, int r, int p, int v) {
    if(l==r) {
        data_min[root]=v;
        return;
    }
    PushDownAddTag(root, l, r);
    int mid=(l+r)>>1;
    if(p<=mid) {
        setLeaf(root<<1, l, mid, p, v);
    }
    else {
        setLeaf(root<<1|1, mid+1,r,p,v);
    }
    data_min[root] = std::min(data_min[root<<1], data_min[root<<1|1]);
}

void addRange(int root, int l, int r, int x, int y, int v) {
    if(x<=l && r<=y) {
        data_min[root]+=v;
        add_tag[root]+=v;
        return;
    }
    if(l==r)
        return;

    PushDownAddTag(root, l, r);
    int mid = (l+r)>>1;
    if(x<=mid) {
        addRange(root<<1, l, mid, x, y, v);
    }
    if(y>=mid+1) {
        addRange(root<<1|1, mid + 1, r, x, y, v);
    }
    data_min[root] = std::min(data_min[root<<1], data_min[root<<1|1]);
}

int lowerBoundAndSet(int root, int l,int r, int v, int new_v) {
    if(l==r) {
        data_min[root]=new_v;
        return l;
    }
    PushDownAddTag(root, l, r);
    int mid = (l+r)>>1, ret;
    if(data_min[root<<1|1]<=v) {
        ret=lowerBoundAndSet(root<<1|1, mid+1, r, v, new_v);
    }
    else {
        ret=lowerBoundAndSet(root<<1, l, mid, v, new_v);
    }
    data_min[root] = std::min(data_min[root<<1], data_min[root<<1|1]);
    return ret;
}


void update_next(int cl, int cr, int bid, int p) {

    //clock_t next_upd_time=0, segtree_build_time=0, loop_time=0;

    int B=cr-cl+1, N=next_size[bid];
    auto next_loc_block = next_loc[bid];
    auto suffix_block = suffix[bid];

    //clock_t next_upd_begin=clock();

    nextAddRange(bid, suffix[bid][p], N-1, -1);

    //next_upd_time+=clock()-next_upd_begin;
    //clock_t segtree_build_begin=clock();

    buildSegTree(1,1,B,cl);

    //segtree_build_time+=clock()-segtree_build_begin;
    //clock_t loop_begin = clock();

    for(int i=0;i<B;++i) {
        int value=data_min[1], list_index=lowerBoundAndSet(1,1,B,value,2*n)-1;

        if(list_index!=p) {
            /*
            if(value<suffix_block[list_index]) {
                //assert(value==suffix[list_index]-1);
                ++next_loc[bid][nextid[value]][nextp[value]];
            }
            if(value>suffix_block[list_index]) {
                //assert(value==suffix[list_index]+1);
                --next_loc[bid][nextid[list_index]][nextp[list_index]];
            }
            */
            if(value!=suffix[bid][list_index]) {
                int new_suffix=min(value, suffix[bid][list_index]);
                if(new_suffix>=next_size[bid] || new_suffix<0)
                    ;
                    //next_loc[bid][nextid[new_suffix]][nextp[new_suffix]]+=suffix[bid][list_index]-value;
                else
                    next_loc_block[nextid[new_suffix]][nextp[new_suffix]]+=suffix_block[list_index]>value?1:-1;
            }
        }
        else {
            nextAddRange(bid, max(0,value), N-1, 1);
        }
        suffix[bid][list_index] = value;
        addRange(1,1,B,list_index+1+1, B, -1);
    }
    //loop_time+=clock()-loop_begin;
    /*
    printf("nxt build time: %f, segtree build time: %f, loop time: %f\n",
           (double)next_upd_time/CLOCKS_PER_SEC,
           (double)segtree_build_time/CLOCKS_PER_SEC,
           (double)loop_time/CLOCKS_PER_SEC);
    */
    /*
    printf("updated nxt:");
    for(int i=0;i<n;++i) {
        printf("%d ", nxt.GetIndex(i));
    }
    printf("\n");
    */
}

void build_next_block(int cl, int cr, int bid, int len) {

    //clock_t next_build_time=0, segtree_build_time=0, loop_time=0, next_build_begin=clock();

    int B=cr-cl+1;
    next_size[bid]=len;
    for(int i=0;i<len;++i) {
        next_loc[bid][nextid[i]][nextp[i]]=i;
    }
    for(int i=0;i<nextid[len];++i)
        block_add[bid][i]=0;

    //next_build_time+= clock() - next_build_begin;
    //clock_t segtree_begin=clock();

    buildSegTree(1,1,B,cl);

    //segtree_build_time+=clock()-segtree_begin;
    //clock_t loop_begin=clock();

    for(int i=0;i<B;++i) {
        int value=data_min[1], list_index=lowerBoundAndSet(1,1,B,value,2*len)-1;
        if(value<0)
            value=0;
        suffix[bid][list_index] = value;
        nextAddRange(bid, value, len-1, 1);
        if (list_index+2<=B)
            addRange(1,1,B,list_index+1+1, B, -1);
    }
    //loop_time+=clock()-loop_begin;
    //printf("build: nxt build time: %f, segtree build time: %f, loop time: %f\n",
    //       (double)next_build_time / CLOCKS_PER_SEC,
    //       (double)segtree_build_time/CLOCKS_PER_SEC,
    //       (double)loop_time/CLOCKS_PER_SEC);
}

int main() {
    clock_t begin=clock();
    ios::sync_with_stdio(false);
    cin.tie(0);
    //freopen("/Users/yiran/CLionProjects/codeforces/input.txt", "r", stdin);
    //freopen("~/ClionProjects/codeforces/output.txt", "w", stdout);
    readint(n, 0);
    next_block_size = ceil(sqrt(n));

    for(int i=0;i<n;++i) {
        readint(c[i], 0);
        c[i]=i-c[i];
    }

    clock_t build_begin=clock();

    //int B,m;
    //B=ceil(sqrt(float(n) / (log(n)/log(2))/3));
    int m=(n-1)/B+1, nextm=(n-1)/next_block_size+1;
    //printf("B=%d\n", B);
    for(int i=0;i<n;++i) {
        Bid[i]=i/B;
        Bp[i]=i%B;
        nextid[i]=i/next_block_size;
        nextp[i]=i%next_block_size;
    }
    for(int i=0;i<m;++i) {
        int block_start = i * B, block_end = min((i + 1) * B, n);
        BL[i]=block_start;
        BR[i]=block_end;
        build_next_block(block_start, block_end-1,i, block_end);
    }
    for(int i=0;i<nextm;++i) {
        nextL[i]=i*next_block_size;
        nextR[i]=min((i+1)*next_block_size, n);
    }

    clock_t sol_begin=clock();
    //double upd_time=0.0, qry_time=0.0;
    //int upd_cnt=0, qry_cnt=0;
    //printf("build time %f\n", (double)(sol_begin-build_begin)/CLOCKS_PER_SEC);

    int q, qid, qi, qx;
    readint(q, 0);
    for(int i=0;i<q;++i) {
        readint(qid, 0);
        if(qid==1) {
            readint(qi, 0), readint(qx, 0);
            c[qi-1]=(qi-1)-qx;

            //clock_t upd_begin = clock();

            int block_index=Bid[qi-1], block_start=BL[block_index], block_end=BR[block_index];
            update_next(block_start, block_end-1,
                        block_index, qi-1-block_start);

            //upd_time+=(double) (clock()-upd_begin)/CLOCKS_PER_SEC;
            //++upd_cnt;
        }
        else {
            readint(qi, 0);

            //clock_t qry_begin = clock();

            int ans=c[qi-1], block_index=Bid[qi-1], block_end=BR[block_index];

            for(int i=qi;i<block_end;++i) {
                ans+=c[i]<=ans;
            }
            for(int j=block_index+1;j<m;++j) {
                int ans_bid=nextid[ans];
                ans = next_loc[j][ans_bid][nextp[ans]]+block_add[j][ans_bid];
            }
            printf("%d\n", ans+1);

            //qry_time+=(double) (clock()-qry_begin)/CLOCKS_PER_SEC;
            //++qry_cnt;
        }
    }

    clock_t sol_end=clock();
    //printf("sol time: %f\n", (double)(sol_end-sol_begin)/CLOCKS_PER_SEC);
    //printf("upd time: %f, qry time: %f\n", upd_time, qry_time);
    //printf("per upd time: %f, per qry time: %.8f\n", upd_time/upd_cnt, qry_time/qry_cnt);

    //fclose(stdin);
    //fclose(stdout);
    //printf("time: %f", (double)(clock()-begin)/CLOCKS_PER_SEC);
    return 0;
}