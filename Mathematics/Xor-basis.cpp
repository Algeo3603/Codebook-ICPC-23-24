int const D = 20;
int basis[D];
int sz;
void insert_vector(int mask) {
    for (int i = 0; i < D; i++) {
        if (mask & (1 << i))
        {
            if (!basis[i]) {
                basis[i] = mask;
                sz++;
                return;
            }
            mask ^= basis[i];
        }
    }
}

bool in_basis(int mask) {
    for (int i = 0; i < D; i++) {
        if (mask & (1 << i)) {
            if (!basis[i])
                return false;
            mask ^= basis[i];
        }
    }
    return true;
}