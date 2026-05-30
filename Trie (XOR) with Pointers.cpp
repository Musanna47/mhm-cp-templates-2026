#include "bits/stdc++.h"

using namespace std;

const int D = 30;

struct TrieNode {
    TrieNode* child[2];
    int cnt = 0;

    TrieNode() {
        child[0] = child[1] = nullptr;
    }
};

struct Trie {
    TrieNode* root = new TrieNode();

    void add(int x) {
        TrieNode* u = root;
        for (int d = D - 1; d >= 0; d--) {
            bool v = x & (1 << d);
            if (!u->child[v])
                u->child[v] = new TrieNode();
            u = u->child[v];
            u->cnt++;
        }
    }

    void del(int x) {
        TrieNode* u = root;
        for (int d = D - 1; d >= 0; d--) {
            bool v = x & (1 << d);
            u = u->child[v];
            u->cnt--;
        }
    }

    int getMin(int x) {
        TrieNode* u = root;
        int ret = 0;
        for (int d = D - 1; d >= 0; d--) {
            bool v = x & (1 << d);
            if (u && u->child[v] && u->child[v]->cnt) {
                u = u->child[v];
            } else {
                if (u) u = u->child[!v];
                ret |= 1 << d;
            }
        }
        return ret;
    }

    int getMax(int x) {
        TrieNode* u = root;
        int ret = 0;
        for (int d = D - 1; d >= 0; d--) {
            bool v = x & (1 << d);
            if (u && u->child[!v] && u->child[!v]->cnt) {
                u = u->child[!v];
                ret |= 1 << d;
            } else {
                if (u) u = u->child[!v];
            }
        }
        return ret;
    }
};
