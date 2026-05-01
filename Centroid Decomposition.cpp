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


template<typename T>
void pout(T &a, string sep = " ", string fin = "\n") {
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


const int MOD = 1e9 + 7;
const int INF = 1e9;
const ll LL_INF = 1e18;
const double PI = 3.141592653589793;
const double EPS = 1e-12;


const int MAXN = 2e5;
V<int> adj[MAXN + 1];
int subsize[MAXN + 1];
bitset<MAXN + 1> done;
int cnt[MAXN + 1];


ll ans = 0;
int n = 0, k = 0, mxDepth = 0;


void getSubSize(int node, int par) {
    subsize[node] = 1;
    for (int &child: adj[node]) {
        if (child != par && !done[child]) {
            getSubSize(child, node);
            subsize[node] += subsize[child];
        }
    }
}

void fillCnt(int node, int par, int depth) {
    if (depth > k) return;
    mxDepth = max(mxDepth, depth);
    cnt[depth]++;
    for (int &child: adj[node]) {
        if (child != par && !done[child]) {
            fillCnt(child, node, depth + 1);
        }
    }
}

void getCnt(int node, int par, int depth) {
    if (depth > k) return;
    ans += cnt[k - depth];
    for (int &child: adj[node]) {
        if (child != par && !done[child]) {
            getCnt(child, node, depth + 1);
        }
    }
}

void centroidDecomp(int node = 1) {
    // Get subtree sizes
    getSubSize(node, -1);

    // Get centroid
    int centroid = node, par = -1;
    while (true) {
        bool stop = true;
        for (int &child: adj[centroid]) {
            if (child != par && !done[child]) {
                if (subsize[child] > subsize[node] / 2) {
                    stop = false;
                    par = centroid, centroid = child;
                    break;
                }
            }
        }
        if (stop)
            break;
    }

    // Mark centroid as done
    done[centroid] = true;
    mxDepth = 0;

    // Perform task / query
    for (int &child: adj[centroid]) {
        if (!done[child]) {
            getCnt(child, centroid, 1);
            fillCnt(child, centroid, 1);
        }
    }
    fill(cnt + 1, cnt + mxDepth + 1, 0);

    // Find next centroid
    for (int &child: adj[centroid]) {
        if (!done[child])
            centroidDecomp(child);
    }
}

void solve() {
    read(n, k);

    REPF(i, 1, n - 1) {
        int u, v;
        read(u, v);
        adj[u].emplace_back(v);
        adj[v].emplace_back(u);
    }


    cnt[0] = 1;

    centroidDecomp();

    outln(ans);
}


int main() {
    auto OJ = []() -> void {
#ifndef ONLINE_JUDGE
        freopen("input.txt", "r", stdin);
        freopen("output.txt", "w", stdout);
#endif
    };

    cin.tie(0)->sync_with_stdio(0);

    OJ();

    // cout << fixed << setprecision(10);

    // precomp();

    int tc = 1;
    // cin >> tc;
    for (int i = 1; i <= tc; i++) {
        // cout << "Case " << i << ": ";
        solve();
        // cout << nl;
    }

    return 0;
}