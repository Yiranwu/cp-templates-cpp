//
// Created by Andrew Wu on 12/3/23.
//

#ifndef CF_BASE_BINSEARCH_H
#define CF_BASE_BINSEARCH_H

#include "../template/cp_template.h"

// Always assumes L inclusive, R exclusive

// Find first F in TTTTTFFFFF
// If negate=true, find first T in FFFFFTTTTT
template <typename T, typename funcT> T binSearch(T L, T R, funcT check, bool negate=false) {
    //assert(check(pl) && !check(pr));
    while(L<R-1) {
        T mid = (L+R)>>1;
        if(check(mid) xor negate) L=mid; else R=mid;
    }
    return R;
}

#endif //CF_BASE_BINSEARCH_H
