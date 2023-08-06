using u64 = unsigned long long;
struct Bits {
    constexpr static int B = 64;
    int b, n;
    std::vector<u64> bits;
    Bits(int _b = 0) {
        init(_b);
    }
    void init(int _b) {
        b = _b;
        n = (b + B - 1) / B;
        bits.assign(n, 0);
    }

    void _clean() {
        if (n * B != b) 
            bits.back() &= (1ULL << (b - B * (n - 1))) - 1;
    }
    Bits operator<< (int k) const {
        Bits ret(b);
        u64 lst = 0;
        int div = k / B, mod = k % B;
        for (int i = 0; i + div < n; i++) {
            ret.bits[i + div] = (lst | bits[i] << mod);
            if (mod) lst = (bits[i] >> (B - mod));
        }
        return ret;
    }
    Bits operator>> (int k) const {
        Bits ret(b);
        u64 lst = 0;
        int div = k / B, mod = k % B;
        for (int i = n - 1; i >= div; i--) {
            ret.bits[i - div] = (lst | bits[i] >> mod);
            if (mod) lst = (bits[i] << (B - mod));
        }
        return ret;
    }

    Bits& operator<<= (int k) {
        return *this = *this << k;
    }
    Bits& operator>>= (int k) {
        return *this = *this >> k;
    }

    friend Bits operator| (Bits lhs, const Bits &rhs) {
        for (int i = 0; i < lhs.n; i++) {
            lhs.bits[i] |= rhs.bits[i];
        }
        return lhs;
    }
    friend Bits operator& (Bits lhs, const Bits &rhs) {
        for (int i = 0; i < lhs.n; i++) {
            lhs.bits[i] &= rhs.bits[i];
        }
        return lhs;
    }
    friend Bits operator^ (Bits lhs, const Bits &rhs) {
        for (int i = 0; i < lhs.n; i++) {
            lhs.bits[i] ^= rhs.bits[i];
        }
        return lhs;
    }
    Bits operator~ () const {
        Bits ret(b);
        for (int i = 0; i < n; i++) {
            ret.bits[i] = ~bits[i];
        }
        return ret;
    }

    Bits& operator|= (const Bits &t) {
        return *this = *this | t;
    }
    Bits& operator&= (const Bits &t) {
        return *this = *this & t;
    }
    Bits& operator^= (const Bits &t) {
        return *this = *this ^ t;
    }

    int find_first() const {
        for (int i = 0; i < n; i++)
            if (bits[i] != 0)
                return B * i + __builtin_ctzll(bits[i]);
        return -1;
    }
    int find_last() const {
        for (int i = n - 1; i >= 0; i--)
            if (bits[i] != 0)
                return B * i + (B - 1 - __builtin_clzll(bits[i]));
        return -1;
    }

    int find_next(int k) const {
        int div = k / B, mod = k % B;
        u64 tmp = bits[div] & ~((1ULL << (mod + 1)) - 1);
        if (mod != 63 && tmp) return div * B + __builtin_ctzll(tmp);
        for (int i = div + 1; i < n; i++) {
            if (bits[i]) {
                return B * i + __builtin_ctzll(bits[i]);
            }
        }
        return -1;
    }

    // Simulates `bs |= bs << shift;`
    void or_shift(int shift) {
        int div = shift / B, mod = shift % B;
 
        if (mod == 0) {
            for (int i = n - 1; i >= div; i--)
                bits[i] |= bits[i - div];
 
            return;
        }
 
        for (int i = n - 1; i >= div + 1; i--)
            bits[i] |= bits[i - (div + 1)] >> (B - mod) | bits[i - div] << mod;
 
        if (div < n)
            bits[div] |= bits[0] << mod;
 
        _clean();
    }
    // Simulates `bs &= bs << shift;`
    void and_shift(int shift) {
        int div = shift / B, mod = shift % B;
 
        if (mod == 0) {
            for (int i = n - 1; i >= div; i--)
                bits[i] &= bits[i - div];
            return;
        }
 
        for (int i = n - 1; i >= div + 1; i--)
            bits[i] &= bits[i - (div + 1)] >> (B - mod) | bits[i - div] << mod;
 
        if (div < n)
            bits[div] &= bits[0] << mod;
 
        _clean();
    }
    // Simulates `bs ^= bs << shift;`
    void xor_shift(int shift) {
        int div = shift / B, mod = shift % B;
 
        if (mod == 0) {
            for (int i = n - 1; i >= div; i--)
                bits[i] ^= bits[i - div];
            return;
        }
 
        for (int i = n - 1; i >= div + 1; i--)
            bits[i] ^= bits[i - (div + 1)] >> (B - mod) | bits[i - div] << mod;
 
        if (div < n)
            bits[div] ^= bits[0] << mod;
 
        _clean();
    }

    // Simulates `bs |= bs >> shift;`
    void or_shift_down(int shift) {
        int div = shift / B, mod = shift % B;

        if (mod == 0) {
            for (int i = div; i < n; i++)
                bits[i - div] |= bits[i];

            return;
        }

        for (int i = 0; i < n - (div + 1); i++)
            bits[i] |= bits[i + (div + 1)] << (B - mod) | bits[i + div] >> mod;

        if (div < n)
            bits[n - div - 1] |= bits[n - 1] >> mod;

        _clean();
    }
    // Simulates `bs &= bs >> shift;`
    void and_shift_down(int shift) {
        int div = shift / B, mod = shift % B;

        if (mod == 0) {
            for (int i = div; i < n; i++)
                bits[i - div] &= bits[i];

            return;
        }

        for (int i = 0; i < n - (div + 1); i++)
            bits[i] &= bits[i + (div + 1)] << (B - mod) | bits[i + div] >> mod;

        if (div < n)
            bits[n - div - 1] &= bits[n - 1] >> mod;

        _clean();
    }
    // Simulates `bs ^= bs >> shift;`
    void xor_shift_down(int shift) {
        int div = shift / B, mod = shift % B;

        if (mod == 0) {
            for (int i = div; i < n; i++)
                bits[i - div] ^= bits[i];

            return;
        }

        for (int i = 0; i < n - (div + 1); i++)
            bits[i] ^= bits[i + (div + 1)] << (B - mod) | bits[i + div] >> mod;

        if (div < n)
            bits[n - div - 1] ^= bits[n - 1] >> mod;

        _clean();
    }

    friend std::ostream& operator<< (std::ostream &os, const Bits &x) {
        for (int i = x.n - 1; i >= 0; i--) {
            for (int j = B - 1; j >= 0; j--) {
                os << (x.bits[i] >> j & 1);
            }
        }
        return os;
    }

    bool any() const {
        for (int i = 0; i < n; i++) {
            if (bits[i]) return true;
        }
        return false;
    }
    bool none() const {
        for (int i = 0; i < n; i++) {
            if (bits[i]) return false;
        }
        return true;
    }
    bool all() const {
        for (int i = 0; i + 1 < n; i++) {
            if (bits[i] != -1ULL) return false;
        }
        if ((n * B != b)) return bits.back() == ((1ULL << (b - (n - 1) * B)) - 1);
        return bits.back() == -1ULL;
    }
    void flip() {
        for (int i = 0; i < n; i++) {
            bits[i] ^= -1ULL;
        }
        _clean();
    }
    void set() {
        for (int i = 0; i < n; i++) {
            bits[i] = -1ULL;
        }
        _clean();
    }
    void reset() {
        bits.assign(n, 0);
    }
    void flip(int x) {
        bits[x / B] ^= 1ULL << (x % B);
    }
    void set(int x) {
        bits[x / B] |= 1ULL << (x % B);
    }
    void reset(int x) {
        bits[x / B] &= ~(1ULL << (x % B));
    }
    bool get(int k) const {
        return bits[k / B] >> (k % B) & 1;
    }
};