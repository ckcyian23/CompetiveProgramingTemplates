template <class T = int>
struct Fenwick {
    int n, cur;
    vector<T> a;
    vector<int> tag;
    Fenwick(int n = 0) {init(n);}
    void init(int sz) {
        n = sz, cur = 0;
        a.assign(n, T());
        tag.assign(n, 0);
    }
    void clear() {
        cur++;
    }
    void add(int x, T v) {
        for (int i = x + 1; i <= n; i += i & -i) {
            if (tag[i - 1] != cur) a[i - 1] = T();
            a[i - 1] += v, tag[i - 1] = cur;
        }
    }

    T sum(int x) {
        T ans = T();
        for (int i = x; i > 0; i -= i & -i) {
            if (tag[i - 1] != cur) a[i - 1] = T();
            ans += a[i - 1], tag[i - 1] = cur;
        }
        return ans;
    }
    T sum(int l, int r) {
        return sum(r) - sum(l);
    }

    int kth(int k) {
        int x = 0;
        for (int i = 1 << __lg(n); i; i /= 2) {
            if (x + i <= n && a[x + i - 1] <= k) {
                x += i;
                k -= a[x - 1];
            }
        }
        return x;
    }
};


template<class T>
struct Fenwick_2d {
    const int n, m;
    vector<vector<T>> a;
    Fenwick_2d(int n, int m) : n(n), m(m), a(n, vector<T>(m)) {}
    void add(int x, int y, T v) {
        for (int i = x + 1; i <= n; i += i & -i) {
            for (int j = y + 1; j <= m; j += j & -j) {
                a[i - 1][j - 1] += v;
            }
        }
    }

    T sum(int x, int y) {
        T res = T();
        for (int i = x; i > 0; i -= i & -i) {
            for (int j = y; j > 0; j -= j & -j) {
                res += a[i - 1][j - 1];
            }
        }
        return res;
    }

    T sum(int x1, int y1, int x2, int y2) {
        return sum(x2, y2) - sum(x1, y2) - sum(x2, y1) + sum(x1, y1);
    }

};


template <class T>
struct FenwickM {
    int n, cur;
    vector<T> a, c;
    FenwickM(int n = 0) {init(n);}
    void init(int sz) {
        n = sz;
        a.assign(n, T());
        c.assign(n, T());
    }

    void set(int x, const T& v) {
        x++;
        a[x - 1] = v;
        for (int i = x; i <= n; i += i & -i) {
            c[i - 1] = a[i - 1];
            for (int j = 1; j < (i & -i); j <<= 1) {
                c[i - 1] += c[i - j - 1];
            }
        }
    }

    T sum(int x) {
        T ans = T();
        for (int i = x; i > 0; i -= i & -i) {
            ans += c[i - 1];
        }
        return ans;
    }

    T query(int l, int r) {
        T ans = T();
        while (l < r) {
            ans += a[r - 1];
            for (--r; r - (r & -r) > l; r -= r & -r) {
                ans += c[r - 1];
            }
        }
        return ans;
    }

    int lower_bound(int k) {
        int x = 0;
        for (int i = 1 << __lg(n); i; i /= 2) {
            if (x + i <= n && c[x + i - 1].x > k)
            //                        Min:>第一个小于等于，>=第一个小于
            //                        Max:<第一个大于等于，<=第一个大于
                x += i;
        }
        return x;
    }

    int upper_bound(int k) {
        int x = 0;
        for (int i = 1 << __lg(n); i; i /= 2) {
            if (x + i <= n && c[x + i - 1].x >= k)
            //                        Min:>第一个小于等于，>=第一个小于
            //                        Max:<第一个大于等于，<=第一个大于
                x += i;
        }
        return x; 
    }

};

struct Min {
    int x;
    Min(int x = 1E9) : x(x) {}
    Min& operator += (const Min& rhs) {
        x = min(x, rhs.x);
        return *this;
    }
    friend ostream& operator << (ostream& os, const Min &rhs) {
        os << rhs.x;
        return os;
    }
};
