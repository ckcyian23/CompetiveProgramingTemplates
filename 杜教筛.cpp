#include <ext/pb_ds/assoc_container.hpp>
#include <ext/pb_ds/hash_policy.hpp>
constexpr int N = 2E6;
int minp[N + 1], sMu[N + 1];
i64 sPhi[N + 1];

vector<int> primes;
void sieve() {
    sPhi[1] = sMu[1] = 1;
    for (int i = 2; i <= N; i++) {
        if (!minp[i]) {
            minp[i] = i;
            primes.push_back(i);
            sPhi[i] = i - 1;
            sMu[i] = -1;
        }

        for (auto p : primes) {
            if (p * i > N) break;
            minp[i * p] = p;
            if (i % p == 0) {
                sMu[i * p] = 0;
                sPhi[i * p] = sPhi[i] * p;
                break;
            }
            sPhi[i * p] = sPhi[i] * sPhi[p];
            sMu[i * p] = sMu[i] * sMu[p];
        }
    }

    for (int i = 1; i <= N; i++) {
        sPhi[i] += sPhi[i - 1];
        sMu[i] += sMu[i - 1];
    }
}
    

int getMu(int x) {
    static __gnu_pbds::gp_hash_table<int, int> t;

    if (x <= N) return sMu[x];

    if (t.find(x) != t.end()) return t[x];
    int res = 1;

    for (i64 i = 2, j; i <= x; i = j + 1) {
        j = x / (x / i);
        res -= (j - i + 1LL) * getMu(x / i);
    }
    return t[x] = res;
}

i64 getPhi(int x) {
    static __gnu_pbds::gp_hash_table<int, i64> t;

    if (x <= N) return sPhi[x];

    if (t.find(x) != t.end()) return t[x];
    i64 res = x * (x + 1LL) / 2;

    for (i64 i = 2, j; i <= x; i = j + 1) {
        j = x / (x / i);
        res -= (j - i + 1LL) * getPhi(x / i);
    }
    return t[x] = res;
}
