#include "bits/stdc++.h"

using namespace std;

using ll = long long;

const int MOD = 1e9 + 7;

ll expo(ll base, ll pow, ll mod = MOD) {
    ll ans = 1;
    while (pow) {
        if (pow & 1) ans = ans * base % mod;
        base = base * base % mod;
        pow >>= 1;
    }
    return ans;
}
