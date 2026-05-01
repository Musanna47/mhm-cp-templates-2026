#include "bits/stdc++.h"
using namespace std;
using ll = long long;

#include <ext/pb_ds/assoc_container.hpp>
#include <ext/pb_ds/tree_policy.hpp>

using namespace __gnu_pbds;

struct chash {
    const uint64_t C = ((ll) (
          4e18 * acos(0))) | 71;
    ll operator()(ll x) const {
    return __builtin_bswap64(x * C); }
};

template<typename T1, typename T2>
using hash_table = gp_hash_table<T1, T2, chash>;
hash_table<int, int> ht({}, {}, {}, {},   {1 << 16});
