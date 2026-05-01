#include "bits/stdc++.h"

using namespace std;

/******************* TEMPLATE START *****************************/
const int N = 1e5 + 2e5 + 10;
const int M = 2 * N; // Total number of edges
int n; // n will be modified by binarize()
int o = 2, to[M], wgt[M], prv[M], nxt[M];
int lst[N], deg[N];

void add_edge(int u, int v, int w) {
    to[o] = v; wgt[o] = w; deg[v]++;
    prv[o] = lst[u]; nxt[lst[u]] = o;
    lst[u] = o; o++;
}

void binarize(int u = 1, int f = 0) {
  int d = deg[u] - 2 - (f != 0);
  if (d > 0) {
    int tmp_lst = (to[lst[u]] == f ? prv[lst[u]] : lst[u]), x;
    for (int e = lst[u], at = n + d; at > n;) {
      x = prv[e];
      if (to[e] == f) { e = x; continue; }
      nxt[x] = nxt[e];
      nxt[e] ? prv[nxt[e]] = x : lst[u] = x;
      prv[e] = lst[at], nxt[e] = 0;
      lst[at] = nxt[lst[at]] = e, deg[at]++;
      to[e ^ 1] = at;
      if (e != tmp_lst) --at;
      e = x;
    }
    for (int i = 1, p = u; i <= d; p = n + i++)
      add_edge(p, n + i, 0), add_edge(n + i, p, 0);
      n += d, deg[u] -= d + 1;
    }
    for (int e = lst[u]; e; e = prv[e])
      if (to[e] != f) binarize(to[e], u);
}

/******************* TEMPLATE FINISH *****************************/


/*
 * Binarize a tree and then centroid decomposition template
 * Description: The graph is store in edge listing representation. Check add_edge() to understand how it works
 * You will first create the graph in the following fashion:
 */

// Sample main function
void solve() {
    cin >> n;
    for (int i = 1; i < n; ++i) {
        int u, v, w;
        cin >> u >> v >> w;
        add_edge(u, v, w);
        add_edge(v, u, w); // must add two opposite edges sequentially
    }
    binarize(1); //
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


/*
 * Now binarize will add at most 2n extra nodes totaling to 3N nodes maximum.
 * But the new tree will be binary (deg[u] <= 3 for all nodes).
 * This guarantees that in our centroid decomposition we will have only 3 children for any vertex
 *
 * Here is a sample dfs function to calculate subtree sizes, just to ilustrate how to use this edge list representation
 */

//void dfs_siz (int u, int f) {
//    sub[u] = 1;
//    for (int e = lst[u]; e; e = prv[e])
//        if (!bad[to[e]] && to[e] ^ f) {
//            dfs_siz(to[e], u);
//            sub[u] += sub[to[e]];
//        }
//}
