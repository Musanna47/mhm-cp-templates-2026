// Author: Muhtasim Hossain Musanna (Musanna47 / mhmusanna)

#include "bits/stdc++.h"

using namespace std;

#define nl "\n"
#define REPF(_i, _a, _b) for (int _i = _a; _i <= _b; _i++)
#define REPB(_i, _a, _b) for (int _i = _a; _i >= _b; _i--)
#define mp make_pair
#define pb push_back
#define eb emplace_back
#define X first
#define Y second
#define sza(_x) ((int)_x.size())
#define all(_x) _x.begin(), _x.end()
#define sort_des(_x) sort(all(_x), greater())
#define min_heap(_T, _pq, _cmp) auto _cmp = greater(); priority_queue<_T, vector<_T>, decltype(_cmp)> _pq(_cmp)

template <typename T1, typename T2>
using P = pair<T1, T2>;
template <typename T>
using V = vector<T>;
template <typename T>
using VV = V<V<T>>;
template <typename T>
using VVV = V<V<V<T>>>;
template <typename T>
using VVVV = V<V<V<V<T>>>>;

using S = string;
using ll = long long;
using ld = long double;
using ull = unsigned long long;
using pii = P<int, int>;
using pll = P<ll, ll>;
using vi = V<int>;
using vvi = VV<int>;
using vll = V<ll>;
using vvll = VV<ll>;
using vpii = V<pii>;
using vpll = V<pll>;

template <typename T>
void pout(T a, string sep = " ", string fin = "\n") {
    cout << a.first << sep << a.second << fin;
}

template <typename T>
void print(T& a, ll l, ll r, string sep = " ", string fin = "\n") {
    for (ll i = l; i <= r; i++)
        cout << a[i] << sep;
    cout << fin;
}

template <typename T>
void printPairs(T& a, ll l, ll r, string fin = "\n") {
    for (ll i = l; i <= r; i++)
        pout(a[i]);
    cout << fin;
}

template <typename T>
void printAll(T& a, string sep = " ", string fin = "\n") {
    for (auto& ele : a)
        cout << ele << sep;
    cout << fin;
}

template <typename T>
void printPairsAll(T& a, string fin = "\n") {
    for (auto& ele : a)
        pout(ele);
    cout << fin;
}

template <typename... Args>
void read(Args &...args) {
    ((cin >> args), ...);
}

template <typename... Args>
void out(Args... args) {
    ((cout << args << " "), ...);
}

template <typename... Args>
void outln(Args... args) {
    ((cout << args << " "), ...);
    cout << nl;
}

template <typename T>
void vin(T& a, ll l, ll r) {
    for (ll i = l; i <= r; i++)
        cin >> a[i];
}

template <typename T>
void makeUnique(T& a) {
    a.erase(unique(all(a)), a.end());
}

using bll = __int128;
const int MOD = 1e9 + 7;
const int INF = 0x3f3f3f3f;
const ll LL_INF = 0x3f3f3f3f3f3f3f3f;
const double PI = 3.141592653589793;
const double EPS = 1e-12;

mt19937_64 rnd(239);
// mt19937_64 rnd(chrono::steady_clock::now().time_since_epoch().count());

void prec() {}

const int N = 2e5 + 5;
ll tree[4 * N], lazy[4 * N], sz, ans[N];
pll a[N], b[N];
vi add[N], sub[N];

void pull(int u) {
    tree[u] = tree[u << 1] + tree[u << 1 | 1];
}

void push(int u, int l, int r) {
    if (lazy[u]) {
        tree[u] += lazy[u] * (r - l + 1);
        if (l != r) {
            lazy[u << 1] += lazy[u];
            lazy[u << 1 | 1] += lazy[u];
        }
        lazy[u] = 0;
    }
}

void upd(int u, int l, int r, int ql, int qr, ll x) {
    push(u, l, r);
    if (l > qr || r < ql) return;
    if (l >= ql && r <= qr) {
        lazy[u] = x;
        push(u, l, r);
        return;
    }
    int mid = l + (r - l) / 2;
    upd(u << 1, l, mid, ql, qr, x);
    upd(u << 1 | 1, mid + 1, r, ql, qr, x);
    pull(u);
}

void upd(int ql, int qr, ll x) {
    upd(1, 1, sz, ql, qr, x);
}

ll query(int u, int l, int r, int ql, int qr) {
    push(u, l, r);
    if (l > qr || r < ql) return 0;
    if (l >= ql && r <= qr) return tree[u];
    int mid = l + (r - l) / 2;
    return query(u << 1, l, mid, ql, qr) + query(u << 1 | 1, mid + 1, r, ql, qr);
}

ll query(int ql, int qr) {
    return query(1, 1, sz, ql, qr);
}

void solve(int tc) {
    int row, col, q;
    read(row, col, q);
    sz = col;
    REPF(i, 1, row) {
        read(a[i].first, a[i].second);
    }
    REPF(i, 1, q) {
        int l, r, x, y;
        read(l, r, x, y);
        b[i] = { x,y };
        add[r].eb(i);
        sub[l - 1].eb(i);
    }
    REPF(i, 1, row) {
        upd(a[i].first, a[i].second, 1);
        for (auto& id : sub[i]) {
            ans[id] -= query(b[id].first, b[id].second);
        }
        for (auto& id : add[i]) {
            ans[id] += query(b[id].first, b[id].second);
        }
    }
    REPF(i, 1, q) {
        cout << ans[i] << nl;
    }
}

void OJ() {
#ifndef ONLINE_JUDGE
    freopen("input.txt", "r", stdin);
    freopen("output.txt", "w", stdout);
#endif
}

signed main() {
    OJ();

    cin.tie(0)->sync_with_stdio(0);

    // cout << fixed << setprecision(10);

    // prec();

    int tc = 1;
    // cin >> tc;
    for (int i = 1; i <= tc; i++) {
        // cout << "Case " << i << ":" << nl;
        solve(i);
    }

    return 0;
}
