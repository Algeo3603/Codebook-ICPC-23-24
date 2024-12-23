// Build Merge Sort Tree over indices
class MergeSortTree { // 0 indexed queries
    public:
    vector<vector<int>> t;
    int n;

    MergeSortTree() {}
    void build(vector<int>& arr) {
        n = arr.size();
        t.resize(4*n);
        vector<pair<int,int>> a(n);
        for (int i = 0; i < n; i++)
            a[i] = {arr[i], i};
        sort(a.begin(), a.end());
        build(a, 1, 0, n-1);
    }

    void build(vector<pair<int,int>>&a,int v,int l,int r) {
        if (l == r)
            t[v].push_back(a[l].second);
        else {
            int mid = (l+r)>>1;
            build(a, v<<1, l, mid);
            build(a, (v<<1)+1, mid+1, r);
            merge(t[v<<1].begin(),
            t[v<<1].end(),
            t[(v<<1)+1].begin(),
            t[(v<<1)+1].end(),
            back_inserter(t[v]));
        }
    }

    // kth smallest in [l..r] (its index)
    int kthOrder(int l,int r,int k) {
        return kthOrder(1, 0, n-1, l, r,k);
    }

    // tl and tr are segment tree boundaries
    int kthOrder(int v,int tl,int tr,int l,int r,int k) {
        if ((int)t[v].size() < k)
        return -1;
        if (tl == tr)
        return t[v][0];
        int mid = (tl+tr)>>1;
        // Is kth element in left subtree?
        int m = util(t[v<<1], l, r);
        if (m >= k)
            return kthOrder(v<<1, tl, mid, l, r, k);
        else
            return kthOrder((v<<1)+1, mid+1, tr, l, r, k-m);
    }
    
    // How many elements i such that l <= i <= r
    int util(vector<int>& arr,int l,int r) {
        return upper_bound(arr.begin(), arr.end(), r) - upper_bound(arr.begin(), arr.end(), l-1);
    }
};