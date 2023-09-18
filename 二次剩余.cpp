int I;
i64 norm(i64 x) {
    x %= P;
    if (x < 0) x += P;
    return x;
}
struct Complex {
    i64 x, y;
    Complex(i64 x = 0, i64 y = 0) : x(norm(x)), y(norm(y)) {}
    friend Complex operator* (Complex a, Complex b) {
        return {a.x * b.x + a.y * b.y % P * I, a.x * b.y + a.y * b.x};
    }
    friend bool operator== (Complex a, Complex b) {
        return a.x == b.x && a.y == b.y;
    }
};

Complex power(Complex a, i64 b) {
    Complex res = 1;
    for (; b; b /= 2, a = a * a) {
        if (b & 1) res = res * a;
    }
    return res;
}
int power(int a, i64 b) {
    int res = 1;
    for (; b; b /= 2, a = 1LL * a * a % P) {
        if (b & 1) res = 1LL * res * a % P;
    }
    return res;
}
bool residue(int x) {
    return power(x, (P - 1) / 2) == 1;
}

void Qresidue(int x) {
    static mt19937 rng(561);
    if (x == 0) {
        // 为0
        return;
    }
    if (residue(x) == 0) {
        //无解
        return;
    }

    int a = rng() % P;
    while (a == 0 || residue(norm(1LL * a * a - x))) {
        a = rng() % P;
    }
    I = norm(1LL * a * a - x);

    int x0 = power(Complex(a, 1), (P + 1) / 2).x;
    int x1 = P - x0;
    //x0 x1
}
