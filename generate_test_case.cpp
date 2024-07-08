//
// Created by yiran on 2021/7/1.
//
#include<cstdio>
#include<random>
#include<iostream>
#include "cf-lib/RandomUtils.h"
using namespace std;

const int NP=80000, MAXV=1000000;
int a[100000];
bool flag[MAXV+5];

int main() {
    srand((unsigned) time(0));
    freopen("/Users/andrewwu/CLionProjects/cp-templates-cpp/input.txt", "w", stdout);
    int n=100;
    printf("%d\n", n);
    for(int i=1;i<=n;++i) {
        for(int j=i;j<=n;++j) cout << 0 << " ";
        cout << endl;
    }
}