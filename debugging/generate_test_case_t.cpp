//
// Created by yiran on 2021/7/1.
//
#include<cstdio>
#include<random>
#include "cf-lib/RandomUtils.h"
using namespace std;

const int NP=80000, MAXV=1000000;
int a[100000];
bool flag[MAXV+5];

int main() {
    srand((unsigned) time(0));
    freopen("/Users/yiran/CLionProjects/codeforces/input.txt", "w", stdout);
    int t=100;
    printf("%d\n", t);
    for(int k=0;k<t;++k) {
        printf("%d\n",1+2+9+12);
        vector<int> sz{1,2,9,12};
        int cur=0;
        for(auto v:sz) {
            for(int i=1;i<v;++i) printf("%d ", cur+i+1);
            printf("%d ", cur+1);
            cur+=v;
        }
        printf("\n");
    }
}