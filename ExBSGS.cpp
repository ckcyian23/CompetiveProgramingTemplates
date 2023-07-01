//A * a ^ x == b (mod p) => x
int exbsgs(int a, int b, int p) {
    a %= p, b %= p;
    if (1 % p == b) return 0;

    int k = 0, A = 1;
    while (true) {
        int d = gcd(a, p);
        if (d == 1) break;
        if (b % d) return -1;
        b /= d, p /= d;
        A = 1LL * A * a / d % p;
        k++;
        if (A == b) return k; 
    }

    int t = sqrt(p) + 1;
    map<int, int> rc;
    for (int i = 0, j = b; i < t; i++) {
        rc[j] = i;
        j = 1LL * j * a % p;
    }
    int at = 1;
    for (int i = 0; i < t; i++) {
        at = 1LL * at * a % p;
    }
    for (int i = 1; i <= t; i++) {
        A = 1LL * A * at % p;
        if (rc.count(A)) return i * t - rc[A] + k;
    }
    return -1;

}