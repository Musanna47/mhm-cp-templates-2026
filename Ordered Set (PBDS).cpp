#include "bits/stdc++.h"

using namespace std;


#include <ext/pb_ds/assoc_container.hpp>
#include <ext/pb_ds/tree_policy.hpp>

using namespace __gnu_pbds;
template<typename T>
using ordered_set = tree<T, null_type, less<T>, rb_tree_tag, tree_order_statistics_node_update>;


int main() {
    ordered_set<int> oset, oset2;
    cout << oset.order_of_key(-5) << "\n";
    cout << *oset.find_by_order(1) << "\n";
    oset.swap(oset2);
    oset.join(oset2);

    return 0;
}
