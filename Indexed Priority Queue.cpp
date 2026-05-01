#include "bits/stdc++.h"

using namespace std;

#define nl "\n"
#define all(_x) _x.begin(), _x.end()

const int INF = 1e9;

// Indexed Priority Queue / Value Sorted Map
// Get Max Element - O(1)
// Get value of i-th key - O(1)
// Update value of i-th key - O(logN)
struct IPQ {
    int sz; // Total number of elements in the heap - Keys range from 1 to sz
    vector<int> heap; // heap[i] = value stored at i-th position in the heap
    vector<int> pos; // pos[i] = position of i-th key in the heap
    vector<int> keys; // keys[i] = key at i-th position in the heap


    IPQ() {

    }

    IPQ(int _sz) {
        init(_sz);
    }

    int top() {
        return heap[1];
    }

    int operator[](int key) {
        return heap[pos[key]];
    }

    void insert(int key, int val) {
        heap[pos[key]] = val;
        swim(pos[key]);
        sink(pos[key]);
    }

    void erase(int key) {
        insert(key, -INF);
    }

    void init(int _sz) {
        sz = _sz;
        heap.assign(sz + 1, 0);
        pos.assign(sz + 1, 0);
        keys.assign(sz + 1, 0);
        iota(all(pos), 0);
        iota(all(keys), 0);
        heap[0] = INF;
    }

    void resize(int _sz) {
        heap.resize(_sz + 1);
        pos.resize(_sz + 1);
        keys.resize(_sz + 1);
        if (_sz > sz) {
            iota(pos.begin() + sz + 1, pos.end(), sz + 1);
            iota(keys.begin() + sz + 1, keys.end(), sz + 1);
        }
        sz = _sz;
    }

    void swapNodes(int i, int j) {
        swap(pos[keys[i]], pos[keys[j]]);
        swap(heap[i], heap[j]);
        swap(keys[i], keys[j]);
    }

    void swim(int idx) {
        while (heap[idx] > heap[idx >> 1]) {
            swapNodes(idx, idx >> 1);
            idx >>= 1;
        }
    }

    void sink(int idx) {
        while ((idx << 1) <= sz) {
            int child = idx << 1;
            if ((child | 1) <= sz && heap[child | 1] >= heap[child])
                child |= 1;
            if (heap[idx] >= heap[child])
                break;
            swapNodes(idx, child);
            idx = child;
        }
    }
};


int main() {
    IPQ ipq(10);

    cout << ipq.top() << nl;

    ipq.insert(5, 10);
    cout << ipq.top() << nl;
    ipq.insert(6, 20);
    cout << ipq.top() << nl;
    ipq.insert(6, 15);
    cout << ipq.top() << nl;
    cout << ipq.pos[6] << nl;
    cout << ipq.heap[ipq.pos[6]] << nl;
    ipq.insert(5, 20);
    cout << ipq.top() << nl;
    cout << ipq.pos[6] << nl;
    cout << ipq.heap[ipq.pos[6]] << nl;
    cout << ipq.pos[5] << nl;
    cout << ipq.heap[ipq.pos[5]] << nl;
    cout << nl;
    cout << ipq[5] << nl;
    cout << ipq[6] << nl;

    return 0;
}
