#include <vector>
using namespace std;

template <typename k, typename v>
    class Hashmap
{
    struct Entry{
        const k Key;
        v value; 
    };
    vector <forward_list<Entry>> Buckets;
    public :
        Hashmap(size_t alloc) : Buckets(alloc) {}
}

bool put(const k& Key, const v&value){
    size_t n = std::hash<k>()(Key);
    size_t target = k%Buckets.size();
    for (auto &ent : Buckets[target]){
        if (ent.key == key){
            ent.value = value;
            return true;
        }
    }
}

