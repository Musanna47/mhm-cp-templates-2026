#include "bits/stdc++.h"

using namespace std;

#define nl "\n"
#define REPF(_i, _a, _b) for(int _i = _a; _i <= _b; _i++)
#define REPB(_i, _a, _b) for(int _i = _a; _i >= _b; _i--)
#define mp make_pair
#define pb push_back
#define eb emplace_back
#define X first
#define Y second
#define sza(_x) ((int)_x.size())
#define all(_x) _x.begin(), _x.end()
#define sort_des(_x) sort(all(_x), greater())
#define min_heap(_T, _pq, _cmp) auto _cmp = greater(); priority_queue<_T, vector<_T>, decltype(_cmp)> _pq(_cmp)

using ll = long long;

template<typename... Args>
void read(Args &... args) {
    ((cin >> args), ...);
}

template<typename... Args>
void out(Args... args) {
    ((cout << args << " "), ...);
}

template<typename... Args>
void outln(Args... args) {
    ((cout << args << " "), ...);
    cout << nl;
}

template<typename T>
void vin(T& a, ll l, ll r) {
    for (ll i = l; i <= r; i++)
        cin >> a[i];
}

//--------------------------------------------------------------------------
template<typename T = int>
struct SPARSE {
    int n, D;
    vector<vector<T>> table;

    SPARSE(V<T>& a) : n(sza(a)), D(__lg(n) + 2), table(n + 1, vector<T>(D)) {
        for (int i = 1; i <= n; ++i) table[i][0] = a[i];
        for (int k = 1; k < D; ++k) {
            for (int i = 1; i + (1 << k) - 1 <= n; ++i) {
                table[i][k] = min(table[i][k - 1], table[i + (1 << (k - 1))][k - 1]);
            }
        }
    }

    T query(int l, int r) {
        int k = 31 - __builtin_clz(r - l + 1);
        return min(table[l][k], table[r - (1 << k) + 1][k]);
    }
};
//--------------------------------------------------------------------------
