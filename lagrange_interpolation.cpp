#include <bits/stdc++.h>
using namespace std;

using i64 = long long;

constexpr int P = 1E9 + 7;

constexpr int power(int a, i64 b) {
    int res = 1;
    while (b) {
        if (b & 1) res = 1LL * res * a % P;
        a = 1LL * a * a % P;
        b /= 2;
    }
    return res;
}

template<class T>
int Norm(T x) {
    return (x % P + P) % P;
}

template<class T>
int Inv(T x) {
    return power(Norm(x), P - 2);
}


//普通拉格朗日插值，求出系数, O(n^2)
vector<int> lagrange(vector<int> &x, vector<int> &y) {
    int n = x.size();

    //1.求出\prod(x - x[i])多项式M，并预处理出-x[i]逆元
    vector<int> inv(n), M(n + 1);
    M[0] = 1;
    for (int i = 0; i < n; i++) {
        inv[i] = Inv(x[i]);
        vector<int> t(n + 1);
        //t = M * (x - x[i])
        for (int j = 1; j <= n; j++) t[j] = M[j - 1];
        for (int j = 0; j <= n; j++) t[j] = Norm(t[j] - 1LL * x[i] * M[j]);
        swap(t, M);
    }


    //2.插值
    vector<int> ret(n), t(n);
    for (int i = 0; i < n; i++) {
        //\prod_{j != i} Inv(x_i - x_j)
        int prod = 1;
        for (int j = 0; j < n; j++) {
            if (i != j) prod = 1LL * prod * (x[i] - x[j]) % P;
        }
        prod = Inv(prod);

        // 模拟多项除法 t = M / (x - x[i]) => t[j] = (t[j - 1] - M[j]) / x[i]
        for (int j = 0, lst = 0; j < n; j++) {
            t[j] = (x[i] == 0) ? M[j + 1] : Norm(1LL * (lst - M[j]) * inv[i]);
            ret[j] = (ret[j] + 1LL * y[i] * prod % P * t[j]) % P;
            lst = t[j];
        }
    }

    return ret;
}


//重心拉格朗日插值(O(n)插一个，O(n)求值(预处理逆元?)?, 不解出系数)
struct LI {
    vector<int> coef;
    vector<int> X, Y, prod;

    void insert(int x, int y) {
        int n = X.size();
        X.push_back(x);
        Y.push_back(y);

        int w = 1;
        for (int i = 0; i < n; i++) {
            prod[i] = Norm(1LL * prod[i] * (X[i] - x));
            w = Norm(1LL * w * (x - X[i]));
        }
        prod.push_back(w);
    }

    int eval(int x) {
        int n = X.size(), v = 0, M = 1;
        for (int i = 0; i < n; i++) {
            if (X[i] == x) return Y[i];
            v = Norm(v + 1LL * Y[i] * Inv(1LL * (x - X[i]) * prod[i]));
            M = Norm(1LL * M * (x - X[i]));
        }
        return Norm(1LL * v * M);
    }
};

//[0, n - 1),连续值插值，不求出系数，O(n)求值
Z eval(vector<Z> &Y, int x) {
    int n = Y.size();
    vector<Z> pref(n + 1), suf(n + 1);
    pref[0] = 1;
    for (int i = 0; i < n; i++) {
        pref[i + 1] = pref[i] * (x - i);
    }

    suf[n] = 1;
    for (int i = n - 1; i >= 0; i--) {
        suf[i] = suf[i + 1] * (x - i);
    }

    Z res = 0;
    for (int i = 0; i < n; i++) {
        Z sg = ((n - 1 - i) % 2 ? -1 : 1);
        res += Y[i] * (pref[i] * suf[i + 1]) * (comb.invfac(i) * comb.invfac(n - 1 - i)) * sg;
    }
    return res;
}