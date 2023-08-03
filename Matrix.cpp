template<class T = int>
struct Matrix {
    int n, m;
    vector<vector<T>> a;

    Matrix(int n = 0, int m = 0) : n(n), m(m), a(n, vector<T>(m)) {}
    Matrix(const initializer_list<T> &dat) : n(1), m(dat.size()), a(n, dat) {}
    Matrix(const initializer_list<T> &&dat) : n(1), m(dat.size()) {a.emplace_back(dat);}
    Matrix(const initializer_list<initializer_list<T>> &dat) {
        n = dat.size();
        m = 0;
        for (auto &h : dat) a.emplace_back(h), m = max<int>(m, h.size());
        for (auto &h : a) h.resize(m);
    }
    
    vector<T>& operator[] (int k) {
        assert(k < n);
        return a[k];
    }
    vector<T> operator[] (int k) const {
        assert(k < n);
        return a[k];
    }

    static Matrix eye(int n, int m = -1) {
        if (m == -1) m = n;
        auto res = Matrix(n, m);
        int x = min(n, m);
        for (int i = 0; i < x; i++) {
            res[i][i] = 1;
        }
        return res;
    }

    friend Matrix operator* (const Matrix &lhs, const Matrix &rhs) {
        int n = lhs.n, m = rhs.m;
        assert(lhs.m == rhs.n);
        int t = lhs.m;

        Matrix ret(n, m);
        for (int i = 0; i < n; i++) {
            for (int j = 0; j < m; j++) {
                for (int k = 0; k < t; k++) {
                    ret[i][j] += lhs[i][k] * rhs[k][j];
                }
            }
        }
        return ret;
    }

    friend Matrix operator+ (const Matrix &lhs, const Matrix &rhs) {
        int n = lhs.n, m = lhs.m;
        assert(lhs.n == rhs.n && lhs.m == rhs.m);

        Matrix ret(n, m);
        for (int i = 0; i < n; i++) {
            for (int j = 0; j < m; j++) {
                ret[i][j] = lhs[i][j] + rhs[i][j];
            }
        }
        return ret;
    }
    friend Matrix operator- (const Matrix &lhs, const Matrix &rhs) {
        int n = lhs.n, m = lhs.m;
        assert(lhs.n == rhs.n && lhs.m == rhs.m);

        Matrix ret(n, m);
        for (int i = 0; i < n; i++) {
            for (int j = 0; j < m; j++) {
                ret[i][j] = lhs[i][j] - rhs[i][j];
            }
        }
        return ret;
    }
    Matrix& operator*= (const Matrix &rhs) {
        *this = *this * rhs;
        return *this;
    }
    Matrix& operator+= (const Matrix &rhs) {
        *this = *this + rhs;
        return *this;
    }
    Matrix& operator-= (const Matrix &rhs) {
        *this = *this - rhs;
        return *this;
    }

    Matrix pow(i64 k) const {
        assert(this->n == this->m);
        auto res = Matrix::eye(this->n, this->m);

        auto t = *this;
        for (i64 i = k; i; i /= 2) {
            if (i & 1) {
                res *= t;
            }
            t *= t;
        }

        return res;
    }

    void show() const {
        cout << "Matrix(showing):\n";
        for (int i = 0; i < n; i++) {
            for (int j = 0; j < m; j++) {
                cout << this->a[i][j] << " \n"[j == m - 1];
            }
        }
        cout << '\n';
    }
};
