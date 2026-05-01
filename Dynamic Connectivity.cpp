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


void prec() {

}

struct DSU {
    int n, comp;
    vi par, sz;
    vpii history; // v, sz[u]

    DSU() = default;

    DSU(int n) : n(n), comp(n), par(n + 1), sz(n + 1, 1) { iota(all(par), 0); }

    int find(int u) {
        return u == par[u] ? u : find(par[u]);
    }

    void unite(int u, int v) {
        u = find(u), v = find(v);
        if (u == v) {
            history.emplace_back(u, sz[u]);
            return;
        }
        if (sz[u] < sz[v]) swap(u, v);
        history.emplace_back(v, sz[u]);
        sz[u] += sz[v];
        par[v] = u;
        comp--;
    }

    void rollback() {
        auto [v, szu] = history.back();
        history.pop_back();
        auto u = par[v];
        if (u != v) {
            sz[u] = szu;
            par[v] = v;
            comp++;
        }
    }
};

struct Edge {
    int u, v, l, r;

    Edge() = default;

    Edge(int u, int v, int l, int r) : u(u), v(v), l(l), r(r) {}
};

const int N = 2e5 + 5;
int ans[N];
vector<Edge> edges;
map<pii, int> start;

struct SEG {
    int sz;
    vector<vector<int>> updates;
    DSU dsu;

    SEG() = default;

    SEG(int n, int sz) : sz(sz), dsu(n), updates(4 * sz + 5) {}

    void update(int x, int l, int r, int i) {
        auto &[u, v, ql, qr] = edges[i];
        if (l >= ql && r <= qr) {
            updates[x].emplace_back(i);
            return;
        }
        int mid = (l + r) >> 1;
        if (ql <= mid)
            update(x << 1, l, mid, i);
        if (qr > mid)
            update(x << 1 | 1, mid + 1, r, i);
    }

    void update(int i) {
        update(1, 1, sz, i);
    }

    void dfs(int x, int l, int r) {
        for (auto &i: updates[x]) {
            auto &[u, v, ql, qr] = edges[i];
            dsu.unite(u, v);
        }
        if (l == r) {
            ans[l] = dsu.comp;
            for (auto &i: updates[x]) { dsu.rollback(); }
            return;
        }
        int mid = (l + r) >> 1;
        dfs(x << 1, l, mid);
        dfs(x << 1 | 1, mid + 1, r);
        for (auto &i: updates[x]) { dsu.rollback(); }
    }

    void dfs() {
        dfs(1, 1, sz);
    }
};

void solve() {
    int n, m, q;
    read(n, m, q);
    int sz = m + q;
    SEG seg(n, sz);
    REPF(i, 1, m) {
        int u, v;
        read(u, v);
        if (u > v) swap(u, v);
        edges.emplace_back(u, v, i, sz);
        start[{u, v}] = sza(edges) - 1;
    }
    REPF(i, m + 1, m + q) {
        int t, u, v;
        read(t, u, v);
        if (u > v) swap(u, v);
        if (t == 1) {
            edges.emplace_back(u, v, i, sz);
            start[{u, v}] = sza(edges) - 1;
        } else {
            edges[start[{u, v}]].r = i - 1;
        }
    }
    REPF(i, 0, sza(edges) - 1) { seg.update(i); }
    seg.dfs();
    print(ans, m, m + q);
}


signed main() {
    auto OJ = []() -> void {
#ifndef ONLINE_JUDGE
        freopen("input.txt", "r", stdin);
        freopen("output.txt", "w", stdout);
#endif
    };

    cin.tie(0)->sync_with_stdio(0);

    OJ();

    // cout << fixed << setprecision(10);

    // prec();

    int tc = 1;
    // cin >> tc;
    for (int i = 1; i <= tc; i++) {
        // cout << "Case " << i << ": ";
        solve();
        // cout << nl;
    }

    return 0;
}