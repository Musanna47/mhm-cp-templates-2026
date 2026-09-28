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
void pout(T& a, string sep = " ", string fin = "\n") {
    cout << a.first << sep << a.second << fin;
}

template<typename T>
void print(T& a, ll l, ll r, string sep = " ", string fin = "\n") {
    for (ll i = l; i <= r; i++)
        cout << a[i] << sep;
    cout << fin;
}

template<typename T>
void printPairs(T& a, ll l, ll r, string fin = "\n") {
    for (ll i = l; i <= r; i++)
        pout(a[i]);
    cout << fin;
}

template<typename T>
void printAll(T& a, string sep = " ", string fin = "\n") {
    for (auto& ele : a)
        cout << ele << sep;
    cout << fin;
}

template<typename T>
void printPairsAll(T& a, string fin = "\n") {
    for (auto& ele : a)
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
void vin(T& a, ll l, ll r) {
    for (ll i = l; i <= r; i++)
        cin >> a[i];
}

template<typename T>
void makeUnique(T& a) {
    a.erase(unique(all(a)), a.end());
}


using bll = __int128;
const int MOD = 1e9 + 7;
const int INF = 0x3f3f3f3f;
const ll LL_INF = 0x3f3f3f3f3f3f3f3f;
const double PI = 3.141592653589793;
const double EPS = 1e-12;


void prec() {}

const int N = 2e5 + 5, SZ = 461;
int a[N], cnt[N], lq[N], rq[N], blk[N], ans[N], SQ[SZ];

struct Query {
    int l, r, id;
    bool operator<(const Query& other) const {
        int b1 = l / SZ;
        int b2 = other.l / SZ;
        if (b1 != b2) return b1 < b2;
        return (b1 & 1) ? (r < other.r) : (r > other.r); // Even/Odd optimization
    }
} queries[N];

void add(int u) {
    cnt[a[u]]++;
}

void del(int u) {
    cnt[a[u]]--;
}

void getAns(int id) {
    int l = lq[id], r = rq[id];
    int bl = blk[l], br = blk[r];

    if (bl == br) {
        for (int i = l; i <= r; i++) ans[id] += cnt[i];
    } else {
        for (int i = l; blk[i] == bl; i++) ans[id] += cnt[i];
        for (int b = bl + 1; b < br; b++) ans[id] += SQ[b];
        for (int i = r; blk[i] == br; i--) ans[id] += cnt[i];
    }
}

void solve(int tc) {
    int n;
    cin >> n;
    for (int i = 0; i < n; i++) {
        cin >> a[i];
    }
    int q;
    cin >> q;
    for (int i = 0; i < q; i++) {
        int l, r;
        cin >> l >> r;
        l--, r--;
        queries[i] = { l,r,i };
    }
    sort(queries, queries + q);
    int curr_l = 0, curr_r = -1;
    for (int i = 0; i < q; i++) {
        while (curr_l > queries[i].l) { add(--curr_l); }
        while (curr_r < queries[i].r) { add(++curr_r); }
        while (curr_l < queries[i].l) { del(curr_l++); }
        while (curr_r > queries[i].r) { del(curr_r--); }
        getAns(queries[i].id);
    }
    for (int i = 0; i < q; i++) {
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
