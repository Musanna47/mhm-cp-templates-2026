#include "bits/stdc++.h"

using namespace std;


const int LEN = 32;

bitset<LEN> bs;
// bs - count, size, all, any, none, set, reset, flip, to_string, to_ulong, to_ullong


// __builtin_popcount(num); __builtin_popcountll(num);
// __builtin_ctz(num); __builtin_ctzll(num);
// __builtin_clz(num); __builtin_clzll(num);


// Set Bit: n | (1 << x)
// Flip Bit: n ^ (1 << x)
// Clear Bit: n & ~(1 << x)
// Bit is set?: (n >> x) & 1
// Num is a power of 2: n && !(n & (n - 1))
// Num is divisible by power of 2: (n & ((1 << k) - 1)) == 0
// Clear all trailing ones: n & (n + 1)
// Set last cleared bit n | (n + 1)
// Extract last set bit: n & -n
// __bit_width(), __bit_floor(), __bit_ceil(), __builtin_parity, __builtin_ffs()

