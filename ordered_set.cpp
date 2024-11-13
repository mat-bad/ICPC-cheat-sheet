// ordered set
#include <ext/pb_ds/assoc_container.hpp>
#include <ext/pb_ds/tree_policy.hpp>
using namespace __gnu_pbds;

typedef tree<pair <int, int>,
   null_type,
   less<pair <int, int>>,
   rb_tree_tag,
   tree_order_statistics_node_update> ordered_set;

struct multi_ordered_set {
   ordered_set os;
   unordered_map <int, int> cnt;
   void insert(int x) {
       os.insert({x, cnt[x]});
       cnt[x]++;
   }
   void erase(int x) {
       if (cnt[x]) {
           cnt[x]--;
           os.erase({x, cnt[x]});
       }
   }
   int find_by_order(int x) { // meqdare x om ro mide (0 base)
       return os.find_by_order(x)->first;
   }
   int order_of_key(int x) { // mige adade x avalin ja koja ast (0 base)
       return os.order_of_key({x, 0});
   }
   int size() {
       return os.size();
   }
};

