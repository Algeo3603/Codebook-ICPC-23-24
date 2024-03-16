int phi[siz + 1];
ll res[siz + 1]; // phi(i/d)*d
void precomputation() {
    phi[0] = 1;
    for (int i = 1; i <= siz; i++)
        phi[i] = i;
    for (int i = 2; i <= siz; i++) {
        if (phi[i] == i) {
            for (int j = i; j <= siz; j += i)
                phi[j] -= phi[j] / i;
        }
    }
    for (int i = 1; i <= siz; i++) {
        for (int j = i; j <= siz; j += i)
            res[j] += ((ll)phi[j / i]) * ((ll)i);
    }
}

// In sqrt time
int phi(int n) {
    int result = n;
    for (int i = 2; i * i <= n; i++) {
        if (n % i == 0) {
            while (n % i == 0)
                n /= i;
            result -= result / i;
        }
    }
    if (n > 1)
        result -= result / n;
    return result;
}

// GCD and ETF
Number of i such that 1 <= i <= n and [gcd(n, i) = d] is phi(n / d)
So _(i = 1 to n) gcd(n, i) = _(d | n) d * phi(n / d)
// Divisor sum property
_(d | n) phi(d) = n 
So gcd(i, j) = _(d | gcd(i, j)) phi(d) 
            = _(d = 1 to n) phi(d) 
            [d | i][d | j]