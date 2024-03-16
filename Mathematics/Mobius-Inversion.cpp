int const siz = 1e6;
bitset<siz + 1> is_prime;
int mu[siz + 1];
void mobius() {
    is_prime.set();
    vector<int> primes;
    mu[1] = 1;
    for (int i = 2; i <= siz; ++i) {
        if (is_prime[i]) {
            mu[i] = -1;
            primes.push_back(i);
        }
        for (int j = 0; j < (int)primes.size() && i * primes[j] <= siz; ++j) {
            is_prime[i * primes[j]] = 0;
            if (i % primes[j] == 0) {
                mu[i * primes[j]] = 0;
                break;
            } else
                mu[i * primes[j]] = -mu[i];
        }
    }
}

// ----
[gcd(i, j) == 1] 
= _(d | gcd(i, j)) mu[d] 
= _(d = 1 to n)[d | gcd(i, j)] mu[d] 
= _(d = 1 to n)[d | i][d | j] mu[d] 
= mu[d]([d | i]) ^ 2 

f(n) = gcd(i, j) 
= _(i = 1 to n) _(j = 1 to n) _(k = 1 to n) k[gcd(i, j) == k] 
= _(k = 1 to n) k _(a = 1 to n / k) _(b = 1 to n / k)[gcd(a, b) == 1] 
= _(k = 1 to n) k _(d = 1 to n / k) mu[d](n / (kd))^2 
// ^ O(nlogn) cause of harmonic lemma