//f \sum{i in [0, n]} ((a * i + b) / c)
//g \sum{i in [0, n]} (i * (a * i + b) / c)
//h \sum{i in [0, n]} ((a * i + b) ^ 2)
struct Data {
    Z f, g, h;
    Data() {};
};

Data calc(i64 a, i64 b, i64 c, i64 n) {
    i64 ac = a / c, bc = b / c, m = (a * n + b) / c, n1 = n + 1, n21 = n * 2 + 1;
    Data d;
    if (a == 0) {
        d.f = Z(bc) * n1;
        d.g = Z(bc) * n * n1 * CInv<2>;
        d.h = Z(bc) * bc * n1;
        return d;
    }

    if (a >= c || b >= c) {
        d.f = Z(n) * n1 * CInv<2> * ac + Z(bc) * n1;
        d.g = Z(ac) * n * n1 * n21 * CInv<6> + Z(bc) * n * n1 * CInv<2>; 
        d.h = Z(ac) * ac * n * n1 * n21 * CInv<6> + 
              Z(bc) * bc * n1 + Z(ac) * bc * n * n1;
        Data e = calc(a % c, b % c, c, n);

        d.h = d.h + e.h + Z(2) * bc * e.f + Z(2) * ac * e.g;
        d.g = d.g + e.g;
        d.f = d.f + e.f;
        return d;
    }
    Data e = calc(c, c - b - 1, a, m - 1);
    d.f = Z(n) * m - e.f;
    d.g = (Z(n) * m * n1 - e.h - e.f) * CInv<2>;
    d.h = Z(n) * m * (m + 1) - 2 * e.g - 2 * e.f - d.f;
    return d;
}