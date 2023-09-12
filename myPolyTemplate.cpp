constexpr int P = 998244353;
//1004535809, 469762049

template<int P = P>
constexpr int power(int a, i64 b) {
    int res = 1;
    while (b) {
        if (b & 1) res = 1LL * a * res % P;
        a = 1LL * a * a % P;
        b /= 2;
    }
    return res;
}

template<int V, int P>
constexpr int CInv = power<P>(V, P - 2);

template<int P>
vector<int> roots{0, 1};
vector<int> rev;
template<int P>
void dft(vector<int> &a) {
    int n = a.size();
    if (rev.size() != n) {
        rev.resize(n);
        int k = __builtin_ctz(n) - 1;
        for (int i = 0; i < n; i++) {
            rev[i] = rev[i >> 1] >> 1 | (i & 1) << k;
        }
    }

    for (int i = 0 ; i < n; i++) {
        if (i < rev[i]) swap(a[i], a[rev[i]]);
    }

    if (roots<P>.size() < n) {
        int k = __builtin_ctz(roots<P>.size());
        roots<P>.resize(n);

        while ((1 << k) < n) {
            int e = power<P>(3, (P - 1) >> (k + 1));
            for (int i = 1 << (k - 1); i < 1 << k; i++) {
                roots<P>[2 * i] = roots<P>[i];
                roots<P>[2 * i + 1] = 1LL * roots<P>[i] * e % P;
            }
            k++;
        }
    }

    for (int k = 1; k < n; k *= 2) {
        for (int i = 0; i < n; i += 2 * k) {
            for (int j = 0; j < k; j++) {
                int u = a[i + j], v = 1LL * a[i + j + k] * roots<P>[k + j] % P;
                a[i + j] = (u + v) % P;
                a[i + j + k] = (u - v + P) % P;
            }
        }
    }

}
template<int P>
void idft(vector<int> &a) {
    reverse(a.begin() + 1, a.end());
    dft<P>(a);
    int n = a.size(), inv = (1 - P) / n + P;
    for (int i = 0; i < n; i++) {
        a[i] = 1LL * a[i] * inv % P;
    }
}

template<int P = 998244353>
struct Poly {
    vector<int> a;
    Poly() {}
    explicit Poly(int n, int val = 0) : a(n, val) {}
    Poly(const vector<int> &a) : a(a) {}
    Poly(const vector<int> &&a) : a(a) {}
    Poly(const initializer_list<int> &t) : a(t) {}
    template<class It>
    explicit constexpr Poly(It first, It last) : a(first, last) {}
    template<class F>
    explicit constexpr Poly(int n, const F &f) : a(n) {
        for (int i = 0; i < n; i++) {
            a[i] = f(i);
        }
    }
    Poly shift(int k) const {
        if (k >= 0) {
            auto b = a;
            b.insert(b.begin(), k, 0);
            return b;
        } else if (size() <= -k) {
            return Poly();
        } else {
            return Poly(a.begin() - k, a.end());
        }
    }
    //ok
    int size() const {
        return a.size();
    }

    constexpr Poly& resize(int k) {
        this->a.resize(k);
        return *this;
    }

    //ok
    Poly trunc(int k) const {
        if (k <= size()) return Poly(a.begin(), a.begin() + k);
        return Poly{a} .resize(k);
    }

    bool empty() const {
        return a.empty();
    }
    //ok
    int& operator[](int idx) {
        return a[idx];
    }
    //ok
    int operator[] (int idx) const {
        if (idx < size()) return a[idx];
        return 0;
    }

    void push_back(int v) {
        a.push_back(v);
    }

    Poly deriv() const {
        if (a.empty()) return Poly();
        Poly res(size() - 1);
        for (int i = 0; i < size() - 1; i++) {
            res[i] = 1LL * (i + 1) * a[i + 1] % P;
        }
        return res;
    }
    Poly integr() const {
        Poly res(size() + 1);
        for (int i = 1; i <= size(); i++) {
            res[i] = 1LL * a[i - 1] * power<P>(i, P - 2) % P;
        }
        return res;
    }
    //ok
    Poly inv(int n) const {
        Poly res{power<P>(a[0], P - 2)};
        int k = 1;
        while (k < n) {
            k *= 2;
            res = res * (Poly{2} - trunc(k) * res).resize(k);
        }
        return res.resize(n);
    }
    Poly sqrt(int n) const {
        Poly res{1};
        int k = 1;
        while (k < n) {
            k *= 2;
            res = (trunc(k) * res.inv(k) + res).resize(k) * CInv<2, P>;
        }
        return res.resize(n);
    }
    Poly log(int n) const {
        return (deriv() * inv(n)).integr().resize(n);
    }
    Poly exp(int n) const {
        Poly res{1};
        int k = 1;
        while (k < n) {
            k *= 2;
            res = res * (Poly{1} - res.log(k) + trunc(k)).resize(k);
        }
        return res.resize(n);
    }

    Poly pow(int k, int n) const {
        int i = 0;
        while (i < size() && a[i] == 0) {
            i++;
        }
        if (i == size() || 1LL * i * k >= n) {
            return Poly(n);
        }
        int v = a[i];
        auto f = shift(-i) * power<P>(v, P - 2);
        return (f.log(n - i * k) * k).exp(n - i * k).shift(i * k) * power<P>(v, k);
    }

    Poly pow(const string &s, int n) {
        int k = 0, k1 = 0;
        for (auto x : s) {
            k = (10LL * k + x - '0') % P;
            k1 = (10LL * k1 + x - '0') % (P - 1);
        }
        int i = 0;
        while (i < size() && a[i] == 0) {
            i++;
        }
        if ((i && (s.size() > 10 || stoll(s) > n)) || i == size() || 1LL * i * k >= n) {
            return Poly(n);
        }
        int v = a[i];
        auto f = shift(-i) * power<P>(v, P - 2);
        return (f.log(n - i * k) * k).exp(n - i * k).shift(i * k) * power<P>(v, k1);
    }

    //ok
    friend Poly operator* (Poly a, Poly b) {
        if (a.empty() || b.empty()) return Poly();
        if (a.size() > b.size()) swap(a, b);
        if (a.size() < 64) {
            Poly c(a.size() + b.size() - 1);
            for (int i = 0; i < a.size(); i++) {
                for (int j = 0; j < b.size(); j++) {
                    c[i + j] = (c[i + j] + 1LL * a[i] * b[j]) % P;
                }
            }
            return c;
        }
        int sz = 1, tot = a.size() + b.size() - 1;
        while (sz < tot) sz *= 2;
        a.resize(sz);
        b.resize(sz);

        dft<P>(a.a);
        dft<P>(b.a);
        for (int i = 0; i < sz; i++) {
            a[i] = 1LL * a[i] * b[i] % P;
        }

        idft<P>(a.a);
        a.resize(tot);
        return a;
    }

    Poly& operator/= (int k) {
        return (*this) = (*this) / k;
    }
    Poly& operator*= (int k) {
        return (*this) = (*this) * k;
    }
    Poly& operator*= (const Poly &b) {
        return (*this) = (*this) * b;
    }
    Poly& operator+= (const Poly &b) {
        return (*this) = (*this) + b;
    }
    Poly& operator-= (const Poly &b) {
        return (*this) = (*this) - b;
    }

    friend Poly operator/ (Poly a, int k) {
        int inv = power<P>(k, P - 2);
        for (int i = 0; i < a.size(); i++) {
            a[i] = 1LL * a[i] * inv % P;
        }
        return a;
    }
    friend Poly operator* (Poly a, int k) {
        for (int i = 0; i < a.size(); i++) {
            a[i] = 1LL * a[i] * k % P;
        }
        return a;
    }
    friend Poly operator* (int k, Poly a) {
        for (int i = 0; i < a.size(); i++) {
            a[i] = 1LL * a[i] * k % P;
        }
        return a;
    }
    friend Poly operator+ (const Poly &a, const Poly &b) {
        Poly res(max(a.size(), b.size()));
        for (int i = 0; i < res.size(); i++) {
            res[i] = 1LL * (a[i] + b[i]) % P;
        }
        return res;
    }
    friend Poly operator- (const Poly &a, const Poly &b) {
        Poly res(max(a.size(), b.size()));
        for (int i = 0; i < res.size(); i++) {
            res[i] = 1LL * (a[i] - b[i] + P) % P;
        }
        return res;
    }

    //ok
    auto begin() const {
        return a.begin();
    }
    auto end() const {
        return a.end();
    }
};

template<int P>
void DAC(Poly<P> &f, Poly<P> &g, int l, int r) {
    if (l == r - 1) return;
    int mid = (l + r) / 2;
    DAC(f, g, l, mid);
    auto t = Poly(f.begin() + l, f.begin() + mid) * g.trunc(r - l);

    for (int i = mid; i < r; i++) {
        f[i] = (f[i] + t[i - l]) % P;
    }
    DAC(f, g, mid, r);
};


constexpr int N = 1E5;

int fac[N + 1], invfac[N + 1];
void init_fac() {
    fac[0] = 1;
    for (int i = 1; i <= N; i++) {
        fac[i] = 1LL * fac[i - 1] * i % P;
    }
    invfac[N] = power(fac[N], P - 2);
    for (int i = N; i > 0; i--) {
        invfac[i - 1] = 1LL * invfac[i] * i % P;
    }
}

using poly = Poly<P>;
poly shift(const poly &f, int k) {
    if (k < 0) k += P;
    int n = f.size() - 1;
    Poly a(n + 1);
    for (int i = 0; i <= n; i++) {
        a[i] = 1LL * f[n - i] * fac[n - i] % P;
    }
    Poly b(n + 1);
    for (int i = 0; i <= n; i++) {
        b[i] = 1LL * power(k, i) * invfac[i] % P;
    }

    a = a * b;

    a.resize(n + 1);
    reverse(a.a.begin(), a.a.end());
    for (int i = 0; i <= n; i++) {
        a[i] = 1LL * a[i] * invfac[i] % P;
    }
    return a;
}