void dfs2(int v, int p) {
    ans[v] = res;
    for (int i : adj[v]) {
        if (i == p)
            continue;
        // save the states
        int state_i, v, ...
                        // do the changes before transition v->i 
        res = (dp[v] - dp[i] + n - sb[i]) + (dp[i] - sb[i]);
        dp[v] = dp[v] - dp[i] + n - sb[i];
        dp[i] = res;
        sb[v] -= sb[i];
        sb[i] = n;
        // perform rerouting dp
        dfs2(i, v);
        // rollback the states
    }
}