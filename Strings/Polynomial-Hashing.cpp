struct polynomial_hash {
    static const int p = 31; // prime close to 26 
    static const ll mod = 1e9 + 9;
    string s;
    int n;
    vector<ll> hash, rev_hash; // forward hash, backward hash 
    vector<ll> p_pow, p_inv;
    polynomial_hash(string x) {
        s = x;
        n = s.size();
    }
    void precomputation() {
        hash.resize(n);
        rev_hash.resize(n);
        p_pow.resize(n);
        p_inv.resize(n);
        p_pow[0] = p_inv[0] = 1;
        ll f = poww(p, mod - 2, mod);
        for (int i = 1; i < n; i++) {
            p_pow[i] = p_pow[i - 1] * p % mod;
            p_inv[i] = p_inv[i - 1] * f % mod;
        }
    }
    void compute_forward_hash() {
        hash[0] = s[0] -’a’ + 1;
        for (int i = 1; i < n; i++)
            hash[i] = (hash[i - 1] + p_pow[i] * (s[i] -’a’ + 1) % mod) % mod;
    }
    void compute_backward_hash() {
        rev_hash[n - 1] = s[n - 1] -’a’ + 1;
        for (int i = n - 2; i >= 0; i--)
            rev_hash[i] = (rev_hash[i + 1] + p_pow[n - i - 1] * (s[i] -’a’ + 1) % mod) % mod;
    }
    int substring_forward_hash(int i, int j) {
        if (i > j)
            swap(i, j);
        ll q = hash[j] - ((i == 0) ? 0 : hash[i - 1]);
        if (q < 0)
            q += mod;
        return q * p_inv[i] % mod;
    }
    int substring_backward_hash(int i, int j) {
        if (i > j)
            swap(i, j);
        ll q = rev_hash[i] - ((j == n - 1) ? 0 : rev_hash[j + 1]);
        if (q < 0)
            q += mod;
        return q * p_inv[n - 1 - j] % mod;
    }
    bool is_palindrome(int sp, int ep, polynomial_hash &H) {
        int mid = (sp + ep) / 2;
        if ((sp + ep) % 2 == 0)
            return H.substring_forward_hash(sp, mid) == H.substring_backward_hash(mid, ep);
        return H.substring_forward_hash(sp, mid) == H.substring_backward_hash(mid + 1, ep);
    }
};
int type1_palindrome(int idx, string &s, int n, polynomial_hash &H) {
    int L = idx - 1, R = min(idx + idx + 1, n);
    while (R - L > 1) {
        int mid = (L + R) / 2;
        if (H.substring_forward_hash(idx, mid) == H.substring_backward_hash(idx - (mid - idx), idx))
            L = mid;
        else
            R = mid;
    }
    return (L - idx + 1) * 2 - 1;
}
int type2_palindrome(int idx, string &s, int n, polynomial_hash &H) {
    int p1 = idx, p2 = idx + 1;
    int L = idx, R = min(n, idx + idx + 2);
    while (R - L > 1) {
        int mid = (L + R) / 2;
        if (H.substring_forward_hash(p2,mid) == H.substring_backward_hash(p1- (mid - p2p1)))
            L = mid;
        else
            R = mid;
    }
    return 2 * (L - p1);
}

string s; cin >> s;
polynomial_hash H = polynomial_hash(s);
H.precomputation();
H.compute_forward_hash();
H.compute_backward_hash();