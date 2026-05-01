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
template<typename T>
struct BIT {
    int sz;
    vector<T> tree;

    BIT(int n) : sz(n), tree(n + 1) {}

    void upd(int i, T x) {
        for (; i <= sz; tree[i] += x, i += (i & -i));
    }

    void upd(int l, int r, T x) {
        upd(l, x);
        upd(r + 1, -x);
    }

    T query(int i) {
        i = min(i, sz);
        T sum = 0;
        for (; i > 0; sum += tree[i], i -= (i & -i));
        return sum;
    }

    T query(int l, int r) {
        return query(r) - query(l - 1);
    }
};
//--------------------------------------------------------------------------
