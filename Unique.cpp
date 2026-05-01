#include "bits/stdc++.h"

using namespace std;

template<typename T>
vector<T> makeUnique(vector<T> &a) {
    // Sort a beforehand to remove all duplicates
    vector<T> res; // Remove all adjacent duplicates
    int n = (int) a.size();
    for (int i = 0; i < n; i++) {
        if (i > 0 && a[i] == a[i - 1]) continue;
        res.emplace_back(a[i]);
    }
    return res;
}