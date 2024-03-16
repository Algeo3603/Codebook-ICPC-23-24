// S(mask, i) = S(mask, i-1) if i is off
// = S(mask, i-1) U S(mask ^ (1<<i), i-1) if i is on
// S(mask, i) = contains all subsets of mask which differ from it only in the first i bits.
for(int i = 0; i<(1<<N); ++i)
    F[i] = A[i]; // Base Case for masks
for(int i = 0;i < N; ++i) 
    for (int mask = 0; mask < (1<<N); ++mask) {
        if (mask & (1<<i)) F[mask] += F[mask^(1<<i)];
}