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
void vin(T &a, ll l, ll r) {
    for (ll i = l; i <= r; i++)
        cin >> a[i];
}

//--------------------------------------------------------------------------
const int N = 1e5 + 5, D = 18;
int a[N], TABLE[N][D];

inline namespace SPARSE {

    template<typename T = int>
    function<T(T, T)> func = [](T x, T y) -> T { return min(x, y); };

    void build(int n) {
        for (int i = 1; i <= n; ++i) TABLE[i][0] = a[i];
        for (int k = 1; k < D; ++k) {
            for (int i = 1; i + (1 << k) - 1 <= n; ++i) {
                TABLE[i][k] = func<>(TABLE[i][k - 1], TABLE[i + (1 << (k - 1))][k - 1]);
            }
        }
    }

    ll query(int l, int r) {
        int k = 31 - __builtin_clz(r - l + 1);
        return func<>(TABLE[l][k], TABLE[r - (1 << k) + 1][k]);
    }
}
//--------------------------------------------------------------------------
