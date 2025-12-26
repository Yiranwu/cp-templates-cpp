//
// Created by Andrew Wu on 7/7/24.
//

#ifndef CF_BASE_MERGESORT_H
#define CF_BASE_MERGESORT_H

#include "../../template/cp_template.h"

template <typename dataT>
class MergeSort {
public:
    vector<dataT> V;


    explicit MergeSort(vector<dataT> V): V(V) {}

    // returns inverse pair count of the range
    ll sort(int l, int r) {
        if(r-l==1) return 0;

        int mid = (l+r) >> 1;
        ll subProblemInversePairCnt = sort(l, mid) + sort(mid, r);
        int lbegin = l, lend = mid, lptr = lbegin;
        int rbegin = mid, rend = r, rptr = rbegin;
        ll mainProblemInversePairCnt = 0;

        vector<dataT> orderedV;
        while(lptr != lend && rptr !=rend) {
            if(V[lptr] <= V[rptr]) {
                mainProblemInversePairCnt += rptr - rbegin;
                orderedV.pb(V[lptr++]);
            }
            else {
                mainProblemInversePairCnt += lend - lptr;
                orderedV.pb(V[rptr++]);
            }
        }
        while(lptr != lend) {
            mainProblemInversePairCnt += rend-rbegin;
            orderedV.pb(V[lptr++]);
        }
        while(rptr != rend) orderedV.pb(V[rptr++]);

        std::copy(all(orderedV), V.begin() + l);
        return mainProblemInversePairCnt/2 + subProblemInversePairCnt;
    }

};

#endif //CF_BASE_MERGESORT_H
