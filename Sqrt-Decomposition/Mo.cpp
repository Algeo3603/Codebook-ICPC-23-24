struct query {
    int L, R, bn, index;
};

int const siz = 2e5;
int block_size, arr[siz + 1], curr_ans, n;
Fenwick X;

bool comp(query &a, query &b) { // Mo’ s sol to TSP 
    return (a.bn < b.bn) || (a.bn == b.bn && (a.bn & 1 ? a.R < b.R : a.R > b.R));
    // slight optimisation
}

void add(int idx, bool right){
    curr_ans += right ? X.qry(arr[idx] + 1, n) : X.qry(1, arr[idx] - 1);
    X.update(arr[idx], 1);
}

void remove(int idx, bool right) {
    curr_ans -= right ? X.qry(arr[idx] + 1, n) : X.qry(1, arr[idx] - 1);
    X.update(arr[idx], -1);
}

void solve() {
    cin >> n;
    block_size = sqrt(n);
    set<int> sparse;
    for (int i = 1; i <= n; i++) {
        cin >> arr[i];
        sparse.insert(arr[i]);
    }
    map<int, int> compress;
    for (int i : sparse)
        compress.insert({i, compress.size() + 1});
    for (int i = 1; i <= n; i++)
        arr[i] = compress[arr[i]];
    X = Fenwick(n);

    int q; cin >> q;
    vector<query> Q(q);
    vector<int> ans(q);
    for (int i = 0; i < q; i++) {
        int l, r; cin >> l >> r;
        Q[i] = {l, r, l / block_size, i};
    }
    sort(Q.begin(), Q.end(), comp);

    int l = 1, r = 0;
    for (auto i : Q) {
        while (r < i.R) {
            r++;
            add(r, true);
        }
        while (l > i.L) {
            l--;
            add(l, false);
        }
        while (r > i.R) {
            remove(r, true);
            r--;
        }
        while (l < i.L) {
            remove(l, false);
            l++;
        }
        ans[i.index] = curr_ans;
    }
    for (int i : ans) cout << i << "\n";
}