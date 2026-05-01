#include "bits/stdc++.h"

using namespace std;

int main() {

    tuple<int, int, char> x = {1, 2, 'a'};
    cout << get<0>(x); // Get single element

    get<1>(x) = 5; // Change single element

    x = {5, 6, 'f'}; // Change all elements

    auto [a, b, c] = x; // Store elements in variables
    cout << a << "\n";
    cout << b << "\n";
    cout << c << "\n";


    return 0;
}