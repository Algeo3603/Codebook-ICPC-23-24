struct SparseTable {
    int n, LOG;
    vector<vector<int>> table;

    int merge(int x, int y) {
        return min(x, y);
    }

    SparseTable(const vector<int> &a) : n(size(a)), LOG(__lg(n)), table(n, vector<int>(LOG + 1, -1)) {
        for (int j = 0; j <= LOG; j++) {
            for (int i = 0; i <= n - (1 << j); i++) {
                if (j == 0) table[i][j] = a[i];
                else table[i][j] = merge(table[i][j - 1], table[i + (1 << (j - 1))][j - 1]);
            }
        }
    }

    int query(int l, int r) {
        int j = __lg(r - l + 1);
        return merge(table[l][j], table[r - (1 << j) + 1][j]);
    }
};