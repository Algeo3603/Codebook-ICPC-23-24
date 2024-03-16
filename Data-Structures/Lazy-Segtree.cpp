struct segmenttree {
    int n;
    vector<int> st, lazy;

    void init(int _n) {
        this->n = _n;
        st.resize(4 * n, LLONG_MAX);
        lazy.resize(4 * n, 0);
    }

    void push(int start, int ending, int node) {
        if (lazy[node]) {
            st[node] += lazy[node];
            if (start != ending) {
                lazy[2 * node + 1] += lazy[node];
                lazy[2 * node + 2] += lazy[node];
            }

            lazy[node] = 0;
        }
    }

    void build(int start, int ending, int node, vector<int> &v) {
        // leaf node base case
        if (start == ending) {
            st[node] = v[start];
            return;
        }

        int mid = (start + ending) / 2;
        build(start, mid, 2 * node + 1, v);
        build(mid + 1, ending, 2 * node + 2, v);
        st[node] = min(st[node * 2 + 1], st[node * 2 + 2]);
    }

    int query(int start, int ending, int l, int r, int node){
        push(start, ending, node);
        if (start > r || ending < l) {
            return LLONG_MAX;
        }

        if (start >= l && ending <= r) {
            return st[node];
        }

        int mid = (start + ending) / 2;
        int q1 = query(start, mid, l, r, 2 * node + 1);
        int q2 = query(mid + 1, ending, l, r, 2 * node + 2);
        return min(q1, q2);
    }

    void update(int start, int ending, int node, int l, int r, int value){
        push(start, ending, node);
        if (start > r || ending < l){
            return;
        }
        if (start >= l && ending <= r) {
            lazy[node] = value;
            push(start, ending, node);
            return;
        }

        int mid = (start + ending) / 2;
        update(start, mid, 2 * node + 1, l, r, value);
        update(mid + 1, ending, 2 * node + 2, l, r, value);
        st[node] = min(st[node * 2 + 1], st[node * 2 + 2]);
        return;
    }

    void build(vector<int> &v){
        build(0, n - 1, 0, v);
    }

    int query(int l, int r){
        return query(0, n - 1, l, r, 0);
    }

    void update(int l, int r, int x){
        update(0, n - 1, 0, l, r, x);
    }
};
