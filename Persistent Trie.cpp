#include "bits/stdc++.h"

using namespace std;

const int D = 31;
const int N = 3e5 + 5;

struct TrieNode {
    TrieNode* child[2];

    TrieNode() {
        child[0] = child[1] = nullptr;
    }
};

TrieNode* pt[N];

struct Trie {
    void add(TrieNode* u, TrieNode* v, int x) {
        for (int d = D - 1; d >= 0; d--) {
            bool c = x & (1 << d);
            if (u) {
                v->child[!c] = u->child[!c];
                u = u->child[c];
            }
            v->child[c] = new TrieNode();
            v = v->child[c];
        }
    }

    int getMin(TrieNode* u, int x) {
        int ret = 0;
        for (int d = D - 1; d >= 0; d--) {
            bool v = x & (1 << d);
            if (u->child[v]) {
                u = u->child[v];
            } else {
                u = u->child[!v];
                ret |= 1 << d;
            }
        }
        return ret;
    }

    int getMax(TrieNode* u, int x) {
        int ret = 0;
        for (int d = D - 1; d >= 0; d--) {
            bool v = x & (1 << d);
            if (u->child[!v]) {
                u = u->child[!v];
                ret |= 1 << d;
            } else {
                u = u->child[v];
            }
        }
        return ret;
    }
} trie;
