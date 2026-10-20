#include <ext/pb_ds/assoc_container.hpp>
#include <ext/pb_ds/tree_policy.hpp>
using namespace __gnu_pbds;
template<class T> using OrderedSet = tree<T, null_type, less<T>, rb_tree_tag, tree_order_statistics_node_update>;
template<class K, class V> using OrderedMap = tree<K, V, less<K>, rb_tree_tag, tree_order_statistics_node_update>;
// *s.find_by_order(k): k-th smallest (0-indexed), end() if k >= size.  s.order_of_key(x): number of keys < x
// multiset: OrderedSet<pii> with {x, unique id}.  map: m.find_by_order(k)->second, m[key] = value
