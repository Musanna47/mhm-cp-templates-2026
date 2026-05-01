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
const int R = 1005, C = 1005;
ll tree[R][C];

inline namespace BIT2D {
    int r, c;

    void build(int _r, int _c) {
        r = _r, c = _c;
        REPF(i, 0, r) {
            fill(tree[i], tree[i] + c + 5, 0);
        }
    }

    void update(int x, int y, ll val) {
        for (int i = x; i <= r; i += (i & -i)) {
            for (int j = y; j <= c; j += (j & -j)) {
                tree[i][j] += val;
            }
        }
    }

    ll pointQuery(int x, int y) {
        ll sum = 0;
        for (int i = x; i > 0; i -= (i & -i)) {
            for (int j = y; j > 0; j -= (j & -j)) {
                sum += tree[i][j];
            }
        }
        return sum;
    }

    ll rangeQuery(int x1, int y1, int x2, int y2) {
        return pointQuery(x2, y2) - pointQuery(x1 - 1, y2)
               - pointQuery(x2, y1 - 1) + pointQuery(x1 - 1, y1 - 1);
    }
}
//--------------------------------------------------------------------------
