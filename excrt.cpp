
array<i64, 3> exgcd(i64 a, i64 b) {
    if (b == 0) return {1, 0, a};
    auto [x, y, g] = exgcd(b, a % b);
    return {y, x - a / b * y, g};
}

i64 mod(i64 x, i64 p) {
    return (x % p + p) % p;
}

bool excrt(i64 &m1, i64 &r1, i64 m2, i64 r2) {
    auto [x, y, g] = exgcd(m1, m2);
    if ((r2 - r1) % g) return false; 
    x = mod(x * (r2 - r1) / g, m2 / g);
    r1 = mod(m1 * x + r1, m1 / g * m2);
    m1 *= m2 / g;
    return true;
}