#include "bits/stdc++.h"

using namespace std;

using ll = long long;
template<typename T>
using V = vector<T>;

template<typename T>
V<ll> makePref(vector<T> &a) {
    int n = (int) a.size();
    V<ll> res(n);
    res[0] = a[0];
    for (int i = 1; i < n; i++) {
        res[i] = res[i - 1] + a[i];
    }
    return res;
}

template<typename T>
ll query(vector<T> &a, int l, int r) {
    if (l == 0) return a[r];
    return a[r] - a[l - 1];
}