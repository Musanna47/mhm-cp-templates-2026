#include "bits/stdc++.h"

using namespace std;
using ll = long long;


const int MAXN = 1e7 + 5;
bitset<MAXN + 1> isPrime;
vector<int> primes;


void sieve() {
    isPrime.set();
    isPrime[0] = isPrime[1] = false;
    for (int i = 2; i * i <= MAXN; i++) {
        if (isPrime[i]) {
            for (ll j = 1LL * i * i; j <= MAXN; j += i)
                isPrime[j] = false;
        }
    }
    for (int i = 2; i <= MAXN; i++) {
        if (isPrime[i])
            primes.emplace_back(i);
    }
}
