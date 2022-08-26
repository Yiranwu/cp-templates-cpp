//
// Created by yiran on 2022/3/4.
//

#ifndef CF_BASE_COMPAREOVERLOAD_H
#define CF_BASE_COMPAREOVERLOAD_H

// 1. overload object comparator <

class obj {
public:
    bool operator < (const obj& o) { return true;}
};

// 2. pass class overloading () operator as comparator

class objCmp {
public:
    bool operator < (const obj &o1, const obj &o2) { return true; }
};
set<obj, objCmp> S;

// 3. pass function as comparator

bool objCmp (const obj &o1, const obj &o2) { return true; }
set<obj, decltype(&objCmp)> S(objCmp);

auto objCmpAuto = [](const obj &o1, const obj &o2) { return true; };
set<obj, decltype(objCmpAuto)> S(objCmpAuto);

// 4. pass class static member as comparator

class objCmp {
public:
    const static bool cmp (const obj &o1, const obj &o2) { return true; }
};
set<obj, decltype(&objCmp::cmp)> S(objCmp::cmp);

#endif //CF_BASE_COMPAREOVERLOAD_H
