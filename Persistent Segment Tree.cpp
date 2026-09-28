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

struct Node {
    Node* lc = nullptr, * rc = nullptr;
    ll sum = 0;
};

const int N = 2e5 + 5;
int sz, a[N];
Node* tree[N];

void pull(Node* u) {
    u->sum = u->lc->sum + u->rc->sum;
}

void build(Node* u, int l, int r) {
    if (l == r) {
        u->sum = a[l];
        return;
    }
    int mid = l + (r - l) / 2;
    build(u->lc = new Node, l, mid);
    build(u->rc = new Node, mid + 1, r);
    pull(u);
}

void build(int n) {
    sz = n;
    build(tree[1] = new Node, 1, sz);
}

void upd(Node* u, Node* v, int l, int r, int i, int x) {
    if (l == r) {
        v->sum = x;
        return;
    }
    v->lc = u->lc, v->rc = u->rc;
    int mid = l + (r - l) / 2;
    if (i <= mid) upd(u->lc, v->lc = new Node, l, mid, i, x);
    else upd(u->rc, v->rc = new Node, mid + 1, r, i, x);
    pull(v);
}

void upd(Node* u, Node* v, int i, int x) {
    upd(u, v, 1, sz, i, x);
}

ll query(Node* u, int l, int r, int ql, int qr) {
    if (l > qr || r < ql) return 0;
    if (l >= ql && r <= qr) return u->sum;
    int mid = l + (r - l) / 2;
    return query(u->lc, l, mid, ql, qr) + query(u->rc, mid + 1, r, ql, qr);
}

ll query(Node* u, int ql, int qr) {
    return query(u, 1, sz, ql, qr);
}

void solve(int tc) {
    int n, q;
    read(n, q);
    REPF(i, 1, n) read(a[i]);
    build(n);
    int tot = 1;
    while (q--) {
        int t;
        read(t);
        if (t == 1) {
            int k, i, x;
            read(k, i, x);
            Node* u = tree[k];
            upd(u, tree[k] = new Node, i, x);
        } else if (t == 2) {
            int k, l, r;
            read(k, l, r);
            outln(query(tree[k], l, r));
        } else {
            int k;
            read(k);
            tree[++tot] = tree[k];
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
        // cout << "Case " << i << ":" << nl;
        solve(i);
    }

    return 0;
}
