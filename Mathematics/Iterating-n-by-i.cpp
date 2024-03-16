void solve() {
    // Iterate over n/i values in sqrt(n)
    ll ans = 0;
    ll val = 1;
    while (val <= n) {
        ll q = n / val;
        ll nval = n / q + 1; // next i giving new n / i(without + 1 gives largest i giving that q)
        val = nval;
    }
}