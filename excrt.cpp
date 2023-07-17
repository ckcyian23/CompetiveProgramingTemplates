i64 exgcd(i64 a, i64 b, i64 &x, i64 &y) {
    if (b == 0) {
        x = 1, y = 0;
        return a;
    }
    i64 g = exgcd(b, a % b, y, x);
    y -= a / b * x;
    return g;
}
 
bool merge(i64 &m1, i64 &a1, i64 m2, i64 a2) {
    i64 u, v;
    i64 g = exgcd(m1, m2, u, v);
    i64 m = m1 / g * m2;
    if ((a2 - a1) % g != 0) {
        return false;
    }
    i64 d = (a2 - a1) / g;
    i64 x = (__int128(u) * m1 * d + a1) % m;
    if (x < 0) {
        x += m;
    }
    m1 = m, a1 = x;
    return true;
}