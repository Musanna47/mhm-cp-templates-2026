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

const int N = 2e5 + 5, D = 18, SZ = 903, SZ2 = 457;
int a[N], cnt[N], to[N][D], depth[N], tin[N], tout[N], node_at[N << 1], blk[N], timer = -1;
int ans[N], xq[N], yq[N], uq[N], vq[N], lcaq[N], vis[N], SQ[SZ2], freq_cnt[N];
vi G[N];

struct Query {
    int l, r, id;
    bool operator<(const Query& other) const {
        int b1 = l / SZ;
        int b2 = other.l / SZ;
        if (b1 != b2) return b1 < b2;
        return (b1 & 1) ? (r < other.r) : (r > other.r); // Even/Odd optimization
    }
} queries[N];

void toggle(int t) {
    int u = node_at[t];
    vis[u] ^= 1;
    if (vis[u]) {
        if (cnt[a[u]]) freq_cnt[cnt[a[u]]]--, SQ[blk[cnt[a[u]]]]--;
        cnt[a[u]]++;
        freq_cnt[cnt[a[u]]]++, SQ[blk[cnt[a[u]]]]++;
    } else {
        freq_cnt[cnt[a[u]]]--, SQ[blk[cnt[a[u]]]]--;
        cnt[a[u]]--;
        if (cnt[a[u]]) freq_cnt[cnt[a[u]]]++, SQ[blk[cnt[a[u]]]]++;
    }
}

void getAns(int id) {
    int l = xq[id], r = yq[id];
    int bl = blk[l], br = blk[r];
    if (bl == br) {
        for (int i = l; i <= r; i++) ans[id] += freq_cnt[i];
    } else {
        for (int i = l; blk[i] == bl; i++) ans[id] += freq_cnt[i];
        for (int b = bl + 1; b < br; b++) ans[id] += SQ[b];
        for (int i = r; blk[i] == br; i--) ans[id] += freq_cnt[i];
    }
    if (lcaq[id] != uq[id]) {
        ans[id] -= (cnt[a[lcaq[id]]] >= xq[id] && cnt[a[lcaq[id]]] <= yq[id]);
        ans[id] += (cnt[a[lcaq[id]]] + 1 >= xq[id] && cnt[a[lcaq[id]]] + 1 <= yq[id]);
    }
}

void dfs(int u = 1, int p = 0) {
    to[u][0] = p;
    depth[u] = 1 + depth[p];
    tin[u] = ++timer;
    node_at[timer] = u;
    for (auto& v : G[u]) {
        if (v == p) continue;
        dfs(v, u);
    }
    tout[u] = ++timer;
    node_at[timer] = u;
}

int jump(int u, int k) {
    REPB(d, D - 1, 0) {
        if (k & (1 << d)) {
            u = to[u][d];
        }
    }
    return u;
}

int get_lca(int u, int v) {
    if (depth[u] < depth[v]) swap(u, v);
    u = jump(u, depth[u] - depth[v]);
    if (u == v) return u;
    REPB(d, D - 1, 0) {
        if (to[u][d] != to[v][d]) {
            u = to[u][d], v = to[v][d];
        }
    }
    return max(1, to[u][0]);
}

void solve(int tc) {
    int n, q;
    read(n, q);
    REPF(i, 1, n) read(a[i]);
    REPF(i, 0, N - 1) blk[i] = i / SZ2;
    REPF(i, 1, n - 1) {
        int u, v;
        read(u, v);
        G[u].eb(v);
        G[v].eb(u);
    }
    dfs();
    REPF(d, 1, D - 1) {
        REPF(i, 1, n) {
            to[i][d] = to[to[i][d - 1]][d - 1];
        }
    }
    REPF(i, 0, q - 1) {
        read(uq[i], vq[i], xq[i], yq[i]);
        if (tin[uq[i]] > tin[vq[i]]) swap(uq[i], vq[i]);
        lcaq[i] = get_lca(uq[i], vq[i]);
        if (lcaq[i] == uq[i]) queries[i] = { tin[uq[i]], tin[vq[i]],i };
        else queries[i] = { tout[uq[i]], tin[vq[i]], i };
    }
    sort(queries, queries + q);
    int curr_l = 0, curr_r = -1;
    for (int i = 0; i < q; i++) {
        while (curr_l > queries[i].l) { toggle(--curr_l); }
        while (curr_r < queries[i].r) { toggle(++curr_r); }
        while (curr_l < queries[i].l) { toggle(curr_l++); }
        while (curr_r > queries[i].r) { toggle(curr_r--); }
        getAns(queries[i].id);
    }
    print(ans, 0, q - 1, nl, "");
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
