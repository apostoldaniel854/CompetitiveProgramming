struct fenwick {
    int n;
    vector <int> BIT;
    fenwick(int n) {
        this->n = n;
        BIT.resize(1 + n);
    }
    void upd(int pos, int val) {
        while (pos <= n) {
            BIT[pos] += val;
            pos += pos & -pos;
        }
    }
    int qry(int pos) {
        int ans = 0;
        while (pos > 0) {
            ans += BIT[pos];
            pos -= pos & -pos;
        }
        return ans;
    }
};
 
