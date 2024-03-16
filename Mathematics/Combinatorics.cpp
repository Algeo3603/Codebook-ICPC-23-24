ll fact[siz + 1], inv_fact[siz + 1];
void compute_factorials() {
    fact[0] = 1;
    for (ll i = 1; i <= siz; i++)
        fact[i] = fact[i - 1] * i % mod;
}

void compute_inv_factorials() {
    inv_fact[siz] = poww(fact[siz],
                         mod - 2);
    for (ll i = siz - 1; i >= 0; i--)
        inv_fact[i] = inv_fact[i + 1] *
                      (i + 1) % mod;
}

ll Binomial(ll n, ll r) {
    if (n < r || r < 0)
        return 0;
    return (fact[n] * inv_fact[n - r] % mod) * inv_fact[r] % mod;
}

void precomputation() {
    compute_factorials();
    compute_inv_factorials();
}