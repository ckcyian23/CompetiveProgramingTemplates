//int: {2, 7, 61}
//i64: {2, 325, 9375, 28178, 450775, 9780504, 1795265022}

bool MillerRabin(i64 p) {
    if (p < 3) return p == 2;
    if (p % 2 == 0) return false;
    i64 u = p - 1, t = 0;
    while (u % 2 == 0) u /= 2, t++;
    for (i64 a : {2, 325, 9375, 28178, 450775, 9780504, 1795265022}) {
        a = power(a, u, p);
        if (a <= 1 || a == p - 1) continue;
        for (int i = 0; i < t - 1; i++) {
            a = mul(a, a, p);
            if (a == p - 1) break;
        }
        if (a != p - 1) return false;
    }
    return true;
}

