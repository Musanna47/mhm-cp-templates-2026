#include "bits/stdc++.h"

using namespace std;

using ll = long long;

const int MOD = 1e9 + 7;

ll expo(ll base, ll pow) {
    ll ans = 1;
    while (pow) {
        if (pow & 1) ans = ans * base % MOD;
        base = base * base % MOD;
        pow >>= 1;
    }
    return ans;
}
