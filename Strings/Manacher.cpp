 struct manacher{
    vector<int> p;
    void run_manacher(string s){
         int n = s.size();
         p.assign(n,1);
         int l = 1 ,r = 1;
         for(int i = 1; i< n;i++){
            p[i] = max(0, min(r -i ,p[l + r - i]));
            while(i + p[i] < n && i - p[i] >=0 && s[i + p[i]] == s[i-p[i]]){
                p[i]++;
            }
            if(i + p[i] > r){
                l = i - p[i];
                r = i + p[i];
            }
         }

    }
    void build(string &s){

        string t="";
        for(int i = 0;i < s.size();i++){
            t += "#";
            t +=s[i];
        }
        //trace(t);
        run_manacher(t + "#");
    }
    int longest(int cen ,bool odd){
        int pos = 2*cen  + 1 + (!odd);
        return p[pos] - 1;
    }
    bool check(int l ,int r){
        if((r - l + 1) <= longest((l + r)/2, l%2 == r%2))return true;
        return false;
    }

   };