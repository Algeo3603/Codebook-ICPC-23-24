for (int i = 0; i < n; i++) // 0 indexed
    d[i][i] = 0;
for (int k = 0; k < n; k++)
    for (int i = 0; i < n; i++)
        for (int j = 0; j < n; j++)
            d[i][j] = min(d[i][j],
                d[i][k] + d[k][j]);