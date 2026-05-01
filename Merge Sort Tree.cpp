#include "bits/stdc++.h"

using namespace std;

#define sza(_x) _x.size()
#define all(_x) _x.begin(), _x.end()


vector<int> a;

struct MergeTree {
    int sz;
    vector<vector<int>> tree;

    MergeTree(int n) : sz(n), tree(4 * n + 5) {
        build(1, 1, sz);
    }

    void build(int u, int l, int r) {
        if (l == r) {
            tree[u] = {a[l]};
            return;
        }
        int mid = l + (r - l) / 2;
        build(u << 1, l, mid);
        build(u << 1 | 1, mid + 1, r);
        tree[u].assign(sza(tree[u << 1]) + sza(tree[u << 1 | 1]), 0);
        merge(all(tree[u << 1]), all(tree[u << 1 | 1]), tree[u].begin());
    }

    int query(int u, int l, int r, int ql, int qr, int val) {
        if (l > qr || r < ql)
            return 0;
        if (l >= ql && r <= qr)
            return (int) (upper_bound(all(tree[u]), val) - tree[u].begin());
        int mid = (l + r) / 2;
        int p1 = query(u << 1, l, mid, ql, qr, val);
        int p2 = query(u << 1 | 1, mid + 1, r, ql, qr, val);
        return p1 + p2;
    }

    int query(int l, int r) {
        return query(1, 1, sz, l, r, l);
    }
};
