// (Point query + Range updates)
class Fenwick { // 1 based indexing
    public:
    int n;
    vector<int> ft;
    Fenwick(int n_) {
        n = n_;
        ft.resize(n+1);
    }

    int qry(int i) {
        int sum = 0;
        while (i > 0) {
            sum += ft[i];
            i -= i&-i;
        }
        return sum;
    }

    void update(int i, int x) {
        while (i <= n) {
            ft[i] += x;
            i += i&-i;
        }
    }

    int query(int i) {
        return qry(i);
    }

    void update(int l,int r,int x) {
        update(l, x);
        if (r < n) update(r+1, -x);
    }
};

// (Range query + Point updates)
class Fenwick { // 1 based indexing
    public:
    int n;
    vector<int> ft;
    // query(x) is qry() as above
    // Same constructor and update(i,x)
    int query(int l,int r) {
        return query(r) - query(l-1);
    }
};