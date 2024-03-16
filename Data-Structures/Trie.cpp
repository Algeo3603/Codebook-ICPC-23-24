class Trie {
    private:
    static const int al = 26;
    struct node {
        bool isEnd;
        node* next[al];
        node() {
        for (int i = 0; i < al; i++)
            next[i] = NULL;
        }
    };
    node root;
    public:
    void insert(const string& s) {
        node* temp = &root;
        for (char c: s) {
            if (temp->next[c-'a'] == NULL)
                temp->next[c-'a'] = new
                    node();
            temp = temp->next[c-'a'];
        }
        temp->isEnd = true;
    }
};

// we don’t literally delete, just make counts to 0
// bool sameBit = (temp->next[bit] != NULL && temp->next[bit]->cnt > 0);
class Bit_Trie {
    private:
    struct node {   
        node* next[2];
        int cnt = 0;
        node() {
            next[0] = next[1] = NULL;
        }
    };
    node root;
    public:
    void insert(int s) {
        node* temp = &root;
        ++temp->cnt;
        for (int i = word_size-1; i >= 0; i--) {
            int bit = (s >> i) & 1;
            if (temp->next[bit] == NULL) 
                temp->next[bit] = new
                    node();
            temp = temp->next[bit];
            ++temp->cnt; // -- for deletion
        }
    }
}