#include "bits/stdc++.h"

using namespace std;

using ll = long long;
const int MAXN = 1e6;
const int MOD = 1e9 + 7;

ll fac[MAXN + 1];
ll inv[MAXN + 1];

ll expo(ll base, ll pow) {
    ll ans = 1;
    while (pow) {
        if (pow & 1) ans = ans * base % MOD;
        base = base * base % MOD;
        pow >>= 1;
    }
    return ans;
}

void factorial() {
    fac[0] = 1;
    for (int i = 1; i <= MAXN; i++) { fac[i] = fac[i - 1] * i % MOD; }
}

void inverses() {
    inv[MAXN] = expo(fac[MAXN], MOD - 2);
    for (int i = MAXN; i >= 1; i--) { inv[i - 1] = inv[i] * i % MOD; }
}

ll choose(int n, int k) { return fac[n] * inv[k] % MOD * inv[n - k] % MOD; }

