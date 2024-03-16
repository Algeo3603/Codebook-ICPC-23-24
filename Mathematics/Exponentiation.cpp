ll poww(ll a, ll b) {
    a %= mod;
    ll res = 1;
    while (b) {
        if (b & 1)
            res = res * a % mod;
        a = a * a % mod;
        b >>= 1;
    }
    return res;
}

// a^(b^c)
ll solve(ll a, ll b, ll c) {
    // Fermat’s lil theorem: (a^b)%mod = (a ^ (b % phi(m))) % mod
    // calc b^c under phi(m) = m-1
    return poww(a, poww(b, c, mod - 1) % (mod - 1), mod);
}