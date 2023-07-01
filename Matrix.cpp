#include <bits/stdc++.h>

using namespace std;
using i64 = long long;

template<class T = int>
struct Matrix {
    int n, m;
    vector<vector<T>> a;

    Matrix(int n = 0, int m = 0) : n(n), m(m), a(n, vector<T>(m)) {}
    Matrix(const initializer_list<T> &dat) : n(1), m(dat.size()), a(n, dat){
    }
    Matrix(const initializer_list<initializer_list<T>> &dat) {
        n = dat.size();
        a.resize(n);
        m = 0;
        for (auto it = dat.begin(); it != dat.end(); it++) {
            m = max<int>(m, it->size());
        }
        auto cur = a.begin();
        for (auto it = dat.begin(); it != dat.end(); it++, cur++) {
            *cur = *it;
            cur->resize(m);
        }
    }
    vector<T>& operator[] (int k) {
        assert(k < n);
        return a[k];
    }
    vector<T> operator[] (int k) const {
        assert(k < n);
        return a[k];
    }

    static Matrix eye(int n, int m) {
        auto res = Matrix(n, m);
        int x = min(n, m);
        for (int i = 0; i < x; i++) {
            res.a[i][i] = 1;
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
        auto res = Matrix<T>::eye(this->n, this->m);

        auto t = *this;
        for (i64 i = k; i; i /= 2) {
            if (i & 1) {
                res *= t;
            }
            t *= t;
        }

        return res;
    }
};


int main() {

    Matrix m{2};
    cout << m.n << ' ' << m.m << '\n';
    m = m.pow(2);
    auto x = m.a;
    for (auto i : x) {
        for (auto j : i) {
            cout << j << ' ';
        }
        cout << '\n';
    }




    return 0;
}