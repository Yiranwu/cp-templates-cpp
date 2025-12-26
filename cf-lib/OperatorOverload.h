//
// Created by Andrew Wu on 4/7/24.
//

#ifndef CF_BASE_CUSTOMASSOCUTILS_H
#define CF_BASE_CUSTOMASSOCUTILS_H

#include "../template/cp_template.h"

// Examples with functor

set<obj, cmp> S;
unordered_set<obj, hash, cmp> S;
map<obj, mapped_type, cmp> M;
unordered_map<obj, mapped_type, hash, cmp> M;
priority_queue<obj, vector<obj>, cmp> Q;
sort(begin, end, greater<>());
sort(begin, end, cmp);


// Ways of passing overloaded operators to stdlib

// 1. overload comparator of the custom class

class obj {
public:
    bool operator < (const obj& o) { return true;}
    friend bool operator< (const obj &o1, const obj &o2);
};
set<obj> S;

// 2. pass comparator as functor
class objCmp {
public:
    template<typename T>
    bool operator()(const T &o1, const T &o2) const
    {
        // Custom comparison logic
        return o1<o2; // this sorts in ascending order
    }
};
set<obj, objCmp> S;

// 3. pass function as comparator
// A major drawback is that every time you declare a set, you need to pass in the comparator.

bool objCmp (const obj &o1, const obj &o2) { return true; }
set<obj, decltype(&objCmp)> S(objCmp);

auto objCmpAuto = [](const obj &o1, const obj &o2) { return true; };
set<obj, decltype(objCmpAuto)> S(objCmpAuto);


#endif //CF_BASE_CUSTOMASSOCUTILS_H
