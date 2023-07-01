#include <bits/stdc++.h>
using namespace std;
using i64 = long long;
using u64 = unsigned long long;

i64 mul(u64 a, u64 b, u64 p) {
    u64 res = a * b - (u64)((long double)a / p * b + 0.5L) * p;
    return (res + p) % p;
}

i64 pow(i64 a, i64 b, i64 p) {
    i64 res = 1 % p;
    while (b) {
        if (b & 1) res = mul(res, a, p);
        a = mul(a, a, p);
        b /= 2;
    }
    return res;
}

bool MillerRabin(i64 p) {
    if (p < 3) return p == 2;
    if (p % 2 == 0) return false;
    i64 u = p - 1, t = 0;
    while (u % 2 == 0) u /= 2, t++;
    for (i64 a : {2, 325, 9375, 28178, 450775, 9780504, 1795265022}) {
        a = pow(a, u, p);
        if (a <= 1 || a == p - 1) continue;
        for (int i = 0; i < t - 1; i++) {
            a = mul(a, a, p);
            if (a == p - 1) break;
        }
        if (a != p - 1) return false;
    }
    return true;
}

mt19937_64 rng(18519);
i64 PollardRho(i64 x) {
    i64 val = 1, s = 0, t = 0, c = rng() % (x - 1) + 1;
    for (int i = 1; ; i *= 2, s = t, val = 1) {
        for (int j = 1; j <= i; j++) {
            t = (mul(t, t, x) + c) % x;
            val = mul(val, abs(t - s), x);
            if (j % 127 == 0) {
                i64 d = gcd(val, x);
                if (d > 1) return d;
            }
        }
        i64 d = gcd(x, val);
        if (d > 1) return d;
    }
}

void get(vector<i64> &data, i64 x) {
    if (x < 2) return;
    if (MillerRabin(x)) {
        data.push_back(x);
        return;
    }
    i64 p = x;
    while (p == x) p = PollardRho(x);
    while (x % p == 0) x /= p;
    get(data, p);
    get(data, x); 
}

void solve() {
    i64 n;
    cin >> n;

    vector<i64> fac;
    get(fac, n);
    sort(fac.begin(), fac.end());
    if (fac.back() == n) {
        cout << "Prime\n";
    } else {
        cout << fac.back() << '\n';
    }
}

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    int t;
    cin >> t;

    while (t--) {
        solve();
    }

    return 0;
}