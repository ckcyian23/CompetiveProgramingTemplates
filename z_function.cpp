struct Zfunc {
    int n;
    string s;
    vector<int> z;
    Zfunc() {};
    Zfunc(const string &s) {
        init(s);
    }

    void init(const string &s) {
        this->s = s;
        n = s.size();
        z.assign(n, 0);
        for (int i = 1, j = 0; i < n; i++) {
            z[i] = max(0, min(j + z[j] - i, z[i - j]));
            while (s[z[i]] == s[i + z[i]]) z[i]++;
            if (i + z[i] > j + z[j]) j = i;
        }
        z[0] = n;
    }

    vector<int> get(const string &t) {
        int m = t.size();
        vector<int> p(m);
        for (int i = 0, j = 0; i < m; i++) {
            p[i] = max(0, min(z[i - j], j + p[j] - i));
            while (i + p[i] < m && p[i] < n && t[i + p[i]] == s[p[i]]) p[i]++;
            if (i + p[i] > j + p[j]) j = i;
        }
        return p;
    }
};
