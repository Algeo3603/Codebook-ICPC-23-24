vector<vector<int>> build(vector<vector<int>>& grid,int n,int m) {
    vector<vector<int>> pre(grid);
    for (int i = 1; i <= n; i++)
        for (int j = 1; j <= m; j++)
            pre[i][j] += pre[i][j-1];
    for (int i = 1; i <= n; i++)
        for (int j = m; j >= 1; j--)
            pre[i][j] += pre[i-1][j];
    return pre;
}

int query(int x1,int y1,int x2,int y2,vector<vector<int>>& pre) {
    return pre[x2][y2] - pre[x2][y1-1] - pre[x1-1][y2] + pre[x1-1][y1-1];
}