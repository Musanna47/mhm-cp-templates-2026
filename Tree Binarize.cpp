#include "bits/stdc++.h"
using namespace std;

/******************* TEMPLATE START *****************************/
const int N = 1e5 + 2e5;   // Need 3 * Max nodes in statement
const int M = 2 * N;       // Total number of edges


int n; // n will be modified by binarize()
int o = 2, to[M], wgt[M], prv[M], nxt[M];
int lst[N], deg[N];

void add_edge (int u, int v, int w) {
    to[o] = v; // directed endpoint of the edge
    wgt[o] = w; // weight of the edge
    deg[v]++; // degree for binarizing purposes
    prv[o] = lst[u]; // store link to the previous edge with same source (prv[o] is the edge before, nxt[o] is the edge after, so a doubly linked list)
    nxt[lst[u]] = o; // update the next link from the previous last edge
    lst[u] = o; // mark this new edge to be the last for u
    o++; // storing bidirectional edgese sequentially in this way means at any moment (o, o^1) will give the same edge from different side
}

void binarize (int u, int f = 0) {
    int d = deg[u] - 2 - (f != 0);
    if (d > 0) {
        int tmp_lst = (to[lst[u]] == f ? prv[lst[u]] : lst[u]), x;
        for (int e = lst[u], at = n + d; at > n; ) {
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
    for (int e = lst[u]; e; e = prv[e]) if (to[e] != f)
        binarize(to[e], u);
}

/******************* TEMPLATE FINISH *****************************/


/*
 * Binarize a tree and then centroid decomposition template
 * Description: The graph is store in edge listing representation. Check add_edge() to understand how it works
 * You will first create the graph in the following fashion:
 */

// Sample main function
int main () {
    for (int i = 1; i < n; ++i) {
        int u, v, w; scanf("%d %d %d", &u, &v, &w);
        add_edge(u, v, w);
        add_edge(v, u, w); // must add two opposite edges sequentially
    }
    binarize(1); //
}

/*
 * Now binarize will add at most 2n extra nodes totaling to 3N nodes maximum.
 * But the new tree will be binary (deg[u] <= 3 for all nodes).
 * This guarantees that in our centroid decomposition we will have only 3 children for any vertex
 *
 * Here is a sample dfs function to calculate subtree sizes, just to ilustrate how to use this edge list representation
 */

void dfs_siz (int u, int f) {
    sub[u] = 1;
    for (int e = lst[u]; e; e = prv[e])
        if (!bad[to[e]] && to[e] ^ f) {
            dfs_siz(to[e], u);
            sub[u] += sub[to[e]];
        }
}
