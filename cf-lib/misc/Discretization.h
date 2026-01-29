
//
// Created by yiran on 2021/11/22.
//

#ifndef CF_BASE_DISCRETIZATION_H
#define CF_BASE_DISCRETIZATION_H

#include "../../template/cp_template.h"

// Mode Tokens
struct HashMode {};
struct RankMode {};

/**
 * @brief Unified Discretizer
 *
 * Modes:
 *   - HashMode (default): O(1) get(). Needs Hashable T. Good for generic types.
 *   - RankMode: O(logN) getRank(). Needs Comparable T. Good for order-sensitive ops (e.g. BIT).
 *
 * API:
 *   - put(x)        [HashMode]: Add element.
 *   - fromRange(r)  [Both]:     Load elements from range.
 *   - get(x)        [HashMode]: Return id (throws if missing).
 *   - getRank(x)    [RankMode]: Return 0-indexed rank (throws if missing).
 *   - applyRange(r) [Both]:     Map range to ids.
 *   - inverse(id)   [Both]:     Get original value.
 */
template <typename T, typename Mode = HashMode, typename ...Policies>
class Discretizer;


// --- Hash Mode Implementation ---
template <typename T, typename ...Policies>
class Discretizer<T, HashMode, Policies...> {
    // If Policies... is empty: HashPolicy = std::hash<T>, PredPolicy = std::equal_to<T>
    // If Policies... is {H}: HashPolicy = H, PredPolicy = std::equal_to<T>
    // If Policies... is {H, P}: HashPolicy = H, PredPolicy = P

    static_assert(sizeof...(Policies) <= 2, "HashMode accepts at most 2 policies: Hash and Predicate");
    
    using HashPolicy = std::conditional_t<sizeof...(Policies) >= 1, 
                                          typename std::tuple_element<0, std::tuple<Policies..., void>>::type, 
                                          std::hash<T>>;
    using PredPolicy = std::conditional_t<sizeof...(Policies) >= 2, 
                                          typename std::tuple_element<1, std::tuple<Policies..., void, void>>::type, 
                                          std::equal_to<T>>;
    
    std::unordered_map<T, int, HashPolicy, PredPolicy> M;
    std::vector<T> inverse_M;
    int start_index;

public:
    explicit Discretizer(int start_idx = 0) : start_index(start_idx) {
        if (start_idx > 0) {
           inverse_M.resize(start_idx); // Fill 0 to start_idx-1 with default constructed T
        }
    }

    void put(const T& x) {
        if (M.find(x) == M.end()) {
            M[x] = start_index + (int)inverse_M.size() - ((start_index > 0) ? start_index : 0);
            inverse_M.push_back(x);
        }
    }

    void fromRange(std::ranges::input_range auto&& r) {
        for (auto&& x : r) {
            put(x);
        }
    }

    int get(const T& x) const {
        auto it = M.find(x);
        if (it == M.end()) throw std::out_of_range("Discretizer: Key not found");
        return it->second;
    }

    std::vector<int> applyRange(std::ranges::input_range auto&& r) const {
        std::vector<int> res;
        if constexpr (std::ranges::sized_range<decltype(r)>) {
            res.reserve(std::ranges::size(r));
        }
        for (auto&& x : r) {
            res.push_back(get(x));
        }
        return res;
    }

    const T& inverse(int id) const {
        return inverse_M[id]; 
    }
    
    int size() const {
        if (start_index > 0) return (int)inverse_M.size() - start_index;
        return (int)inverse_M.size();
    }
};


// --- Rank Mode Implementation ---
template <typename T, typename ...Policies>
class Discretizer<T, RankMode, Policies...> {
    static_assert(sizeof...(Policies) <= 1, "RankMode accepts at most 1 policy: Comparator");
    using Compare = std::conditional_t<sizeof...(Policies) >= 1, 
                                       typename std::tuple_element<0, std::tuple<Policies..., void>>::type, 
                                       std::less<T>>;
    
    std::vector<T> values;
    Compare comp;

public:
    explicit Discretizer() = default;

    void fromRange(std::ranges::input_range auto&& r) {
        values.assign(std::ranges::begin(r), std::ranges::end(r));
        std::sort(values.begin(), values.end(), comp);
        values.erase(std::unique(values.begin(), values.end(), [this](const T& a, const T& b){
            return !comp(a, b) && !comp(b, a); // Equivalence using less
        }), values.end());
    }

    int getRank(const T& x) const {
        auto it = std::lower_bound(values.begin(), values.end(), x, comp);
        if (it == values.end() || comp(x, *it)) throw std::out_of_range("Discretizer: Key not found"); // Not found
        return (int)(it - values.begin()); 
    }

    std::vector<int> applyRange(std::ranges::input_range auto&& r) const {
        std::vector<int> res;
        if constexpr (std::ranges::sized_range<decltype(r)>) {
            res.reserve(std::ranges::size(r));
        }
        for (auto&& x : r) {
            res.push_back(getRank(x));
        }
        return res;
    }

    const T& inverse(int id) const {
        return values[id];
    }
    
    int size() const {
        return (int)values.size();
    }
};

#endif //CF_BASE_DISCRETIZATION_H
