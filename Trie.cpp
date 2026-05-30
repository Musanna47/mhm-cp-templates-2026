#include "bits/stdc++.h"

using namespace std;

const int N = 1e6 + 10;
int trie[N][26];
bool isWord[N];
int tot = 0;

inline namespace Trie {
    void add(string& s) {
        int u = 0;
        for (auto& c : s) {
            int x = c - 'a';
            if (!trie[u][x])
                trie[u][x] = ++tot;
            u = trie[u][x];
        }
        isWord[u] = true;
    }
}
