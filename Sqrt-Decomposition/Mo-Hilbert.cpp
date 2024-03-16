// Larger n/q ratio => better performance of Hilbert 
class Fenwick{};

int const siz = 2e5;
int block_size, arr[siz + 1], curr_ans, n;
Fenwick X;

inline int64_t hilbertOrder(int x, int y, int pow, int rotate) {
    if (pow == 0) {
        return 0;
    }
    int hpow = 1 << (pow - 1);
    int seg = (x < hpow) ? ((y < hpow) ? 0 : 3): ((y < hpow) ? 1 : 2);
    seg = (seg + rotate) & 3;
    const int rotateDelta[4] = {3, 0, 0, 1};
    int nx = x & (x ^ hpow), ny = y & (y ^ hpow);
    int nrot = (rotate + rotateDelta[seg]) & 3;
    int64_t subSquareSize = int64_t(1) << (2 * pow - 2);
    int64_t ans = seg * subSquareSize;
    int64_t add = hilbertOrder(nx, ny, pow - 1, nrot);
    ans += (seg == 1 || seg == 2) ? add: (subSquareSize - add - 1);
    return ans;
}

struct Query {
    int L, R, idx;
    int64_t ord;
    inline void calcOrder() {
        ord = hilbertOrder(L, R, 21, 0);
    }
};

inline bool operator<(const Query &a, const Query &b) {
    return a.ord < b.ord;
}

void add(int idx, bool right) {}

void remove(int idx, bool right) {}

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
    vector<Query> Q(q);
    vector<int> ans(q);
    for (int i = 0; i < q; i++) {
        int l, r; cin >> l >> r;
        Q[i].L = l, Q[i].R = r;
        Q[i].idx = i;
        Q[i].calcOrder();
    }
    sort(Q.begin(), Q.end());
}