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
struct SCC {
    int n, compCnt;
    vector<vector<int>> OG, TG, comp;
    vector<int> compNum;
    vector<bool> vis;

    SCC(int n) : n(n), compCnt(0), OG(n + 1), TG(n + 1), comp(n + 1), compNum(n + 1), vis(n + 1) {}

    void dfs(int u, vector<int> &cont, bool rev = false) {
        auto &G = rev ? TG : OG;
        vis[u] = true;
        for (auto &v: G[u]) {
            if (!vis[v]) { dfs(v, cont, rev); }
        }
        cont.emplace_back(u);
        compNum[u] = compCnt;
    }

    void build() {
        vector<int> stk;
        for (int i = 1; i <= n; i++) {
            if (!vis[i]) { dfs(i, stk); }
        }
        fill(vis.begin(), vis.end(), false);
        for (int i = n - 1; i >= 0; i--) {
            int u = stk[i];
            if (!vis[u]) {
                compCnt++;
                dfs(u, comp[compCnt], true);
            }
        }
    }
};
//--------------------------------------------------------------------------

void solve() {
    int n, m;
    read(n, m);
    SCC scc(n);
    for (int i = 1; i <= m; i++) {
        int u, v;
        read(u, v);
        scc.OG[u].emplace_back(v);
        scc.TG[v].emplace_back(u);
    }
    scc.build();
    outln(scc.compCnt);
    for (int i = 1; i <= n; i++) { out(scc.compNum[i]); }
}
