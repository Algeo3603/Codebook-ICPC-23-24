#include <ext/pb_ds/assoc_container.hpp>
using namespace __gnu_pbds;
struct custom_hash {
    static uint64_t splitmix64(uint64_t x) {
        x += 0x9e3779b97f4a7c15;
        x = (x ^ (x >> 30)) *
        0xbf58476d1ce4e5b9;
        x = (x ^ (x >> 27)) *
        0x94d049bb133111eb;
        return x ^ (x >> 31);
    }
    size_t operator()(uint64_t x) const {
        static const uint64_t
        FIXED_RANDOM =
        chrono::steady_clock::now().time_sinreturn splitmix64(x + FIXED_RANDOM);
    }
};

gp_hash_table<int,int, custom_hash> compress; // cc fast
m.reserve(4096);
m.max_load_factor(0.25); // reserve also
// For pairs
struct custom_hash {
    static uint64_t splitmix64(uint64_t x) {
    // same as above
    }
    size_t operator()(pair<uint64_t,uint64_t> x) const {
        static const uint64_t FIXED_RANDOM = chrono::steady_clock::now().
        time_since_epoch().count();
        return splitmix64(x.first + FIXED_RANDOM)^(splitmix64(x.second + FIXED_RANDOM) >> 1);
    }
};