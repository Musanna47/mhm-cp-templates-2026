#include "bits/stdc++.h"

using namespace std;
using ll = long long;

ll myFloor(ll x, ll y) {
    assert (y != 0);
    if (x % y == 0) return x / y;
    if ((x >= 0 && y > 0) || (x < 0 && y < 0))
        return x / y;
    return x / y - 1;
}

ll myCeil(ll x, ll y) {
    return -myFloor(-x, y);
}


int main() {

    {
        // Normally use this [for non-negative numbers]

        ll x = 13, y = 5;
        ll f = x / y; // Floor
        ll c = (x + y - 1) / y; // Ceil

        cout << f << " " << c << endl;
    }

    {
        // For negative and non-negative numbers use this
        ll x = 13, y = -5;
        ll f = myFloor(x, y);
        ll c = myCeil(x, y);

        cout << f << " " << c << endl;
    }


    return 0;
}