template <typename T, class Merge = function<T(const T&, const T&)>>
struct ST {
    int n;
    vector<vector<T>> st;
    Merge merge;
    ST() {}
    ST(vector<T> &a, const Merge &merge) {init(a, merge);}
    void init(vector<T> &a, const Merge &merge) {
        n = a.size();
        this->merge = merge;
        int lg = __lg(n) + 1;
        st.resize(lg);
        st[0] = a;
        for(int j = 1; j < lg; j++) {
            st[j].resize(n - (1 << j) + 1);
            for(int i = 0; i <= n - (1 << j); i++) {
                st[j][i] = merge(st[j - 1][i], st[j - 1][i + (1 << j - 1)]);
            }
        }
    }
    T get(int l, int r) const {
        int lg = __lg(r - l);
        return merge(st[lg][l], st[lg][r - (1 << lg)]);
    }
};
