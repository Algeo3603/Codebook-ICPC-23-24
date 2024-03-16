struct LCA {
      
    int MAX_N, LOG;
    vector<vector<int>> up;
    vector<int> depth;
    vector<vector<int>> children;

    LCA(int n){
      MAX_N = n;
      LOG = log2(MAX_N) + 1;
      up.resize(MAX_N, vector<int>(LOG));
      children.resize(MAX_N, vector<int>());
      depth.resize(MAX_N);
    }

    void dfs(int a) {
        for(int b : children[a]) {
            depth[b] = depth[a] + 1;
            up[b][0] = a; // a is parent of b
            for(int j = 1; j < LOG; j++) {
                up[b][j] = up[up[b][j-1]][j-1];
            }
            dfs(b);
        }
    }

    int getLCA(int a ,int b) {
        // ensure a is deeper than b
        if (depth[a] < depth[b]) {
            swap(a, b);
        }

        // lift a to the same depth as b
        int k = depth[a] - depth[b];
        for (int j = LOG - 1; j >= 0; j--) {
            if (k & (1 << j)) {
                a = up[a][j];
            }
        }

        // lift both a and b as high as possible without them having the same ancestor
        for (int j = LOG - 1; j >= 0; j--) {
            if (up[a][j] != up[b][j]) {
                a = up[a][j];
                b = up[b][j];
            }
        }

        if (a == b) {
            return a;
        } else {
            return up[a][0];
        }
    }
};