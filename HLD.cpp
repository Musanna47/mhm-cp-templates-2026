// Author: Muhtasim Hossain Musanna (Musanna47 / mhmusanna)

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


template<typename T1, typename T2>
using P = pair<T1, T2>;
template<typename T>
using V = vector<T>;
template<typename T>
using VV = V<V<T>>;
template<typename T>
using VVV = V<V<V<T>>>;
template<typename T>
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


template<typename T>
void pout(T a, string sep = " ", string fin = "\n") {
    cout << a.first << sep << a.second << fin;
}

template<typename T>
void print(T &a, ll l, ll r, string sep = " ", string fin = "\n") {
    for (ll i = l; i <= r; i++)
        cout << a[i] << sep;
    cout << fin;
}

template<typename T>
void printPairs(T &a, ll l, ll r, string fin = "\n") {
    for (ll i = l; i <= r; i++)
        pout(a[i]);
    cout << fin;
}

template<typename T>
void printAll(T &a, string sep = " ", string fin = "\n") {
    for (auto &ele: a)
        cout << ele << sep;
    cout << fin;
}

template<typename T>
void printPairsAll(T &a, string fin = "\n") {
    for (auto &ele: a)
        pout(ele);
    cout << fin;
}

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

template<typename T>
void makeUnique(T &a) {
    a.erase(unique(all(a)), a.end());
}


using bll = __int128;
const int MOD = 1e9 + 7;
const int INF = 0x3f3f3f3f;
const ll LL_INF = 0x3f3f3f3f3f3f3f3f;
const double PI = 3.141592653589793;
const double EPS = 1e-12;

mt19937_64 rnd(239);
//mt19937_64 rnd(chrono::steady_clock::now().time_since_epoch().count());


void prec() {

}

const int N = 2e5 + 5, D = 19;
int a[N], seg[1 << D], n, q, ct = 0, st[N], heavy[N], par[N], depth[N], top[N];
vi G[N];


void segUpdate(int u, int x) {
    seg[u += n] = x;
    for (u /= 2; u; u /= 2) seg[u] = max(seg[u << 1], seg[u << 1 | 1]);
}

int segQuery(int lo, int hi) {
    int ra = 0, rb = 0;
    for (lo += n, hi += n + 1; lo < hi; lo /= 2, hi /= 2) {
        if (lo & 1) ra = max(ra, seg[lo++]);
        if (hi & 1) rb = max(rb, seg[--hi]);
    }
    return max(ra, rb);
}

int dfs_sz(int u = 1, int p = 0) {
    par[u] = p;
    depth[u] = depth[p] + 1;
    int sz = 1, mx = 0;
    for (auto &v: G[u]) {
        if (v == p) continue;
        int child_sz = dfs_sz(v, u);
        if (child_sz > mx) mx = child_sz, heavy[u] = v;
        sz += child_sz;
    }
    return sz;
}

void dfs_hld(int u = 1, int p = 0) {
    segUpdate(st[u] = ++ct, a[u]);
    if (heavy[p] == u) top[u] = top[p];
    else top[u] = u;
    if (heavy[u]) {
        dfs_hld(heavy[u], u);
        for (auto &v: G[u]) {
            if (v == p || v == heavy[u]) continue;
            dfs_hld(v, u);
        }
    }
}

int query(int u, int v) {
    int res = 0;
    while (true) {
        int x = top[u], y = top[v];
        if (x == y) {
            res = max(res, segQuery(min(st[u], st[v]), max(st[u], st[v])));
            break;
        }
        if (depth[x] >= depth[y]) {
            res = max(res, segQuery(st[x], st[u]));
            u = par[x];
        } else {
            res = max(res, segQuery(st[y], st[v]));
            v = par[y];
        }
    }
    return res;
}

void solve() {
    read(n, q);
    REPF(i, 1, n) {
        read(a[i]);
    }
    REPF(i, 1, n - 1) {
        int u, v;
        read(u, v);
        G[u].emplace_back(v);
        G[v].emplace_back(u);
    }
    dfs_sz();
    dfs_hld();
    while (q--) {
        int t, u, v;
        read(t, u, v);
        if (t == 1) {
            segUpdate(st[u], v);
        } else {
            out(query(u, v));
        }
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
        // cout << "Case " << i << ": ";
        solve();
    }

    return 0;
}