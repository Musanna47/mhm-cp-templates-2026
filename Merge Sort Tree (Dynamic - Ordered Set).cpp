#include "bits/stdc++.h"

using namespace std;

#include <ext/pb_ds/assoc_container.hpp>
#include <ext/pb_ds/tree_policy.hpp>

using namespace __gnu_pbds;
template<typename T>
using ordered_set = tree<T, null_type, greater_equal<T>, rb_tree_tag, tree_order_statistics_node_update>;


const int MAXN = 3e4;
ordered_set<int> seg[4 * MAXN + 5];
int a[MAXN + 1];

// Build the merge sort tree from an existing array (static) - O(Nlog^2(N))
void build(int node, int start, int fin) {
    if (start == fin) {
        seg[node].insert(a[start]);
        return;
    }
    int mid = (start + fin) / 2;
    build(2 * node, start, mid);
    build(2 * node + 1, mid + 1, fin);
    for (int i: seg[2 * node]) {
        seg[node].insert(i);
    }
    for (int i: seg[2 * node + 1]) {
        seg[node].insert(i);
    }
}

// Add new element to the merge sort tree (dynamic) - O(log^2(N)) per element
void insert(int node, int start, int fin, int l, int r, int val) {
    if (start > fin || start > r || fin < l)
        return;
    seg[node].insert(val);
    if (start >= l && fin <= r)
        return;
    int mid = (start + fin) / 2;
    if (l <= mid)
        insert(2 * node, start, mid, l, r, val);
    else
        insert(2 * node + 1, mid + 1, fin, l, r, val);
}

// Find the number of elements less than or equal to val - O(log^2(N)) per query
int query(int node, int start, int fin, int l, int r, int val) {
    if (start > fin || start > r || fin < l)
        return 0;
    if (start >= l && fin <= r)
        return seg[node].order_of_key(val + 1);
    int mid = (start + fin) / 2;
    int p1 = query(2 * node, start, mid, l, r, val);
    int p2 = query(2 * node + 1, mid + 1, fin, l, r, val);
    return p1 + p2;
}
