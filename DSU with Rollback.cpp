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

mt19937_64 rng(239);
// mt19937_64 rng(chrono::steady_clock::now().time_since_epoch().count());
// const int M = (1LL << 61) - 1; // Large Prime
// const int P = uniform_int_distribution<ll>(0, M - 1)(rng); // Random Number Less Than M


void prec() {}

int ans = 0;

struct DSU {
    int n;
    vector<int> par, sz, checkpoint;
    vector<tuple<int, int, int>> history; // <time, node, sz>

    DSU(int n) : n(n), par(n + 1), sz(n + 1, 1) { iota(all(par), 0); }

    int find(int u) {
        return u == par[u] ? u : find(par[u]);
    }

    bool unite(int u, int v, int t) {
        u = find(u), v = find(v);
        if (u == v) return false;
        if (sz[u] < sz[v]) swap(u, v);
        history.emplace_back(t, v, sz[u]);
        sz[u] += sz[v];
        par[v] = u;
        return true;
    }

    void rollback() {
        while (!history.empty() && get<0>(history.back()) > checkpoint.back()) {
            auto [t, v, szu] = history.back();
            history.pop_back();
            auto u = par[v];
            sz[u] = szu;
            par[v] = v;
            ans++;
        }
        checkpoint.pop_back();
    }
};

void solve(int tc) {
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
