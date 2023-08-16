using i64 = long long;

int power(int a, i64 b, int P) {
    int res = 1;
    for (; b; b /= 2) {
        if (b & 1) res = 1LL * res * a % P;
        a = 1LL * a * a % P;
    }
    return res;
}

i64 exgcd(i64 a, i64 b, i64 &x, i64 &y) {
    if (b == 0) {
        x = 1;
        y = 0;
        return a;
    }
    i64 g = exgcd(b, a % b, y, x);
    y -= a / b * x;
    return g;
}

int inv(i64 n, int p) {
    i64 x, y;
    exgcd(n, p, x, y);
    x %= p;
    return x < 0 ? x + p : x;
}

//fac(n) / (p^k)
int calc(i64 n, int p, int pk) {
    if (n == 0) return 1;
    i64 s = 1;
    for (int i = 1; i <= pk; i++) {
        if (i % p) s = s * i % pk;
    }
    s = power(s, n / pk, pk);
    for (i64 i = n / pk * pk + 1; i <= n; i++) {
        if (i % p) s = i % pk * s % pk; // i:i64 mod first
    }
    return s * calc(n / p, p, pk) % pk;
}
//binom(n, m) mod p^k
int multilucas(i64 n, i64 m, int p, int pk) {
    int cnt = 0;
    for (i64 i = n; i; i /= p) cnt += i / p;
    for (i64 i = m; i; i /= p) cnt -= i / p;
    for (i64 i = (n - m); i; i /= p) cnt -= i / p;
    return 1LL * power(p, cnt, pk) * calc(n, p, pk) % pk * 
            inv(calc(m, p, pk), pk) % pk * inv(calc(n - m, p, pk), pk) % pk;
}
int crt(int r, int m, int M) {
    return 1LL * r * (M / m) % M * inv(M / m, m) % M;
}
int exlucas(i64 n, i64 m, int P) {
    if (m < 0 || m > n) return 0;
    int M = P;
    i64 res = 0;
    for (int i = 2; i * i <= P; i++) {
        if (P % i == 0) {
            int x = 1;
            while (P % i == 0) P /= i, x *= i;
            res += crt(multilucas(n, m, i, x), x, M);
        }
    }

    if (P > 1) res += crt(multilucas(n, m, P, P), P, M);
    res %= M;
    return res < 0 ? res + M : res;
}

