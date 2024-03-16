const int maxn = 5*1e5  +5;
vector<int> spf(maxn);
   
void sieve() {
    spf[1] = 1;
    for(int i = 2; i < maxn; i++){
        if(i%2)spf[i] = i;
        else spf[i] = 2;
    }
    for(int i = 3; i*i < maxn ; i++){
        if(spf[i] == i){
            for(int j = i*i; j < maxn ; j += i){
                if (spf[j] == j)spf[j] = i;
            }
        }
    }
}

vector<int> fact(int x) {
    vector<int> ret;
    while (x != 1) {
        ret.push_back(spf[x]);
        x = x / spf[x];
    }
    return ret;
}