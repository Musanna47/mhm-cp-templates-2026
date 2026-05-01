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
    vector<int> par, sz;
    vector<tuple<int, int, int>> history; // t, v, sz[u]

    DSU() = default;

    DSU(int n) : n(n), comp(n), par(n + 1), sz(n + 1, 1) {
        iota(all(par), 0);
        history.emplace_back(0, 0, 0);
    }

    int find(int u) {
        return u == par[u] ? u : find(par[u]);
    }

    void unite(int u, int v, int t) {
        u = find(u), v = find(v);
        if (u == v) return;
        if (sz[u] < sz[v]) swap(u, v);
        history.emplace_back(t, v, sz[u]);
        sz[u] += sz[v];
        par[v] = u;
        comp--;
    }

    void rollback(int cp = 0) {
        while (cp < get<0>(history.back())) {
            auto [t, v, szu] = history.back();
            history.pop_back();
            auto u = par[v];
            sz[u] = szu;
            par[v] = v;
            comp++;
        }
    }
};

const int N = 5e4, SQ = 225;
int ans[N];
pii edges[N];

struct Query {
    int l, r, idx;

    Query(int l, int r, int idx) : l(l), r(r), idx(idx) {}

    bool operator<(Query &other) {
        if (r == other.r) return l > other.l;
        return r < other.r;
    }
};

vector<Query> queries[SQ];

void solve() {
    int n, m;
    read(n, m);
    REPF(i, 0, m - 1) {
        read(edges[i].first, edges[i].second);
    }
    int q;
    read(q);
    REPF(i, 0, q - 1) {
        int l, r;
        read(l, r);
        l--, r--;
        queries[l / SQ].emplace_back(l, r, i);
    }
    for (auto &i: queries) {
        sort(all(i));
    }
    DSU dsu(n);
    int br = -1;
    REPF(i, 0, SQ - 1) {
        int j;
        br += SQ;
        for (j = 0; j < sza(queries[i]) && queries[i][j].r <= br; j++) {
            auto &[l, r, idx] = queries[i][j];
            REPF(k, l, r) dsu.unite(edges[k].first, edges[k].second, 1);
            ans[idx] = dsu.comp;
            dsu.rollback();
        }
        int cr = br + 1, time = 0;
        for (; j < sza(queries[i]);) {
            int R = queries[i][j].r;
            for (; cr <= R; cr++) dsu.unite(edges[cr].first, edges[cr].second, ++time);
            int cp = ++time, cl = br;
            for (; j < sza(queries[i]) && queries[i][j].r == R; j++) {
                auto &[l, r, idx] = queries[i][j];
                for (; cl >= l; cl--) dsu.unite(edges[cl].first, edges[cl].second, ++time);
                ans[idx] = dsu.comp;
            }
            dsu.rollback(cp);
        }
        dsu.rollback();
    }
    print(ans, 0, q - 1, nl, "");
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
