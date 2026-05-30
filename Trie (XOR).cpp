#include "bits/stdc++.h"

using namespace std;

const int N = 1e6 + 5, D = 30;
int trie[N * D][2], cnt[N * D], tot = 0;

inline namespace Trie {
    void add(int x) {
        int u = 0;
        for (int d = D - 1; d >= 0; d--) {
            bool v = x & (1 << d);
            if (!trie[u][v])
                trie[u][v] = ++tot;
            u = trie[u][v];
            cnt[u]++;
        }
    }

    void del(int x) {
        int u = 0;
        for (int d = D - 1; d >= 0; d--) {
            bool v = x & (1 << d);
            u = trie[u][v];
            cnt[u]--;
        }
    }

    int getMin(int x) {
        int u = 0, ret = 0;
        for (int d = D - 1; d >= 0; d--) {
            bool v = x & (1 << d);
            if (trie[u][v] && cnt[trie[u][v]]) {
                u = trie[u][v];
            } else {
                ret |= (1 << d);
                u = trie[u][!v];
            }
        }
        return ret;
    }

    int getMax(int x) {
        int u = 0, ret = 0;
        for (int d = D - 1; d >= 0; d--) {
            bool v = x & (1 << d);
            if (trie[u][!v] && cnt[trie[u][!v]]) {
                ret |= (1 << d);
                u = trie[u][!v];
            } else {
                u = trie[u][v];
            }
        }
        return ret;
    }
}
