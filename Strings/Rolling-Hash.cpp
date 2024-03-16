int hashs[100005],pows[100005];

int getHash(int l,int r) {
    return  ((hashs[r+1] - (hashs[l] * pows[r-l+1]) %MOD) +MOD) %MOD;
}

void hash(string &s){
    int p=331;
    pows[0]=1;
    for(int i=1;i<100005;i++) {
        pows[i]=(pows[i-1]*p)%MOD;
    }
    int n=s.length();
    for(int i=0;i<n;i++) {
        hashs[i+1]=(hashs[i]*p+s[i])%MOD;
    }
}