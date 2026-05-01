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

const int N = 3e4;
const int SZ = 174;
int a[N], cnt[1000001];

const int Q = 2e5;

struct Query {
    int l, r, idx;

    bool operator<(Query other) const {
        return pii{l / SZ, r} < pii{other.l / SZ, other.r};
    }
} queries[Q];

int ans[Q];
int curr_ans = 0;

void add(int u) {
    if (cnt[a[u]] == 0) curr_ans++;
    cnt[a[u]]++;
}

void del(int u) {
    cnt[a[u]]--;
    if (cnt[a[u]] == 0) curr_ans--;
}

void solve() {
    int n;
    read(n);

    vin(a, 0, n - 1);

    int q;
    read(q);
    REPF(i, 0, q - 1) {
        int l, r;
        read(l, r);
        l--, r--;
        queries[i].l = l, queries[i].r = r, queries[i].idx = i;
    }

    sort(queries, queries + q);

    int curr_l = 0, curr_r = -1;
    REPF(i, 0, q - 1) {
        while (curr_l > queries[i].l) { add(--curr_l); }
        while (curr_r < queries[i].r) { add(++curr_r); }
        while (curr_l < queries[i].l) { del(curr_l++); }
        while (curr_r > queries[i].r) { del(curr_r--); }
        ans[queries[i].idx] = curr_ans;
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