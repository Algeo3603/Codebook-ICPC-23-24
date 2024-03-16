vector<int> z_function(string &s) {
    int n = s.size();
    vector<int> z(n);
    // z0 not well defined
    for (int i = 1, l = 0, r = 0; i < n; i++) {
        if (i <= r)
            z[i] = min(r - i + 1, z[i - l]);
        // s[l..r] => s[0..r-l] so s[l..i] = > s[0..i - l] 
        while (i + z[i] < n && s[z[i]] == s[i + z[i]]) // launch
            z[i]++;
        if (i + z[i] - 1 > r)
            l = i, r = i + z[i] - 1;
    }
    return z;
}
// Periodicity of string
vector<int> z = z_function(s);
int n = s.size();
vector<int> v;
for (int i = 1; i < n; i++) {
    if (i + z[i] == n)
        v.push_back(i);
}
// String Matching
void solve() {
    string t;
    cin >> t; // text
    string p;
    cin >> p;               // pattern
    string s = p + "!" + t; // apply z
    on this vector<int> z = z_function(s);
    int cnt = 0, sp = p.size() + 1, n = s.size();
    for (int i = sp; i < n; i++)
        cnt += (z[i] == (int)p.size());
    cout << cnt;
}