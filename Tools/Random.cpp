#include <chrono>
// Seed only once
mt19937 rng(chrono::steady_clock::now().
time_since_epoch().count());
// Shuffle randomly
shuffle(arr.begin(), arr.end(), rng);
// Uniformly random in range [l,r] inclusive
uniform_int_distribution<int>(l,r)(rng)
// For 64 bit use
mt19937_64 and uniform_int_distribution<long long>