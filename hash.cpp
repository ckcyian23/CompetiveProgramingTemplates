//(i64)1E16 + 99 233
// const i64 P = 1e12 + 39;
// const int B = 114351;
struct Hash {
    static constexpr i64 P = (i64)1E16 + 99;
    static constexpr int B = 233;
    int n;
    vector<i64> h, p;
    Hash(const string &s) : n(s.size()), h(n + 1), p(n + 1) {
        p[0] = 1;
        for (int i = 0; i < n; i++) {
            p[i + 1] = p[i] * B % P;
            h[i + 1] = (h[i] * B + s[i]) % P;
        }
    }

    i64 get(int l, int r) {
        return (h[r] + (__int128)h[l] * (P - p[r - l])) % P;
    }
};
