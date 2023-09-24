template<class T>
constexpr T power(T a, i64 b) {
    T res = 1;
    for (; b; b /= 2, a = a * a) {
        if (b & 1 ) res = res * a;
    }
    return res;
}

constexpr int P = 998244353;
struct Z {
    int x;
    constexpr static int norm(int x) {
        if (x < 0) return x + P;
        else if (x >= P) return x - P;
        return x;
    }
    constexpr Z(int x = 0) : x(norm(x)) {}
    constexpr Z(i64 x) : x(norm(x % P)) {}

    constexpr friend Z operator* (Z a, Z b) {
        return 1LL * a.x * b.x;
    }
    constexpr friend Z operator/ (Z a, Z b) {
        return a.x * power(b, P - 2);
    }
    constexpr friend Z operator+ (Z a, Z b) {
        return norm(a.x + b.x);
    }
    constexpr friend Z operator- (Z a, Z b) {
        return norm(a.x - b.x);
    }
};
template<int V>
constexpr Z CInv = power(Z(V), P - 2);
