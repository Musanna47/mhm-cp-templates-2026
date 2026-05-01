#include "bits/stdc++.h"

using namespace std;

bool comp(int a, int b) { return a < b; }
bool pqComp(int a, int b) { return !comp(a, b); }

int main() {
    set<int, decltype(&comp)> s1(&comp); // Use with set, map, etc.
    priority_queue<int, vector<int>, decltype(&pqComp)> pq1(&pqComp);

    auto cmp = [](int a, int b) -> bool {
        return a < b;
    };

    set<int, decltype(cmp)> s2(cmp);
    priority_queue<int, vector<int>, decltype(cmp)> pq2(cmp);


    return 0;
}
