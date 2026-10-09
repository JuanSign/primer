#include <ext/pb_ds/assoc_container.hpp>
#include <ext/pb_ds/tree_policy.hpp>
using namespace __gnu_pbds;
template<class T>
using OrderedSet = tree<T, null_type, less<T>, rb_tree_tag,
                        tree_order_statistics_node_update>;
// *s.find_by_order(k)   k-th smallest, 0-indexed
// s.order_of_key(x)     number of elements < x
// multiset: OrderedSet<pii>, store {x, unique id}
