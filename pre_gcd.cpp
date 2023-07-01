#include <bits/stdc++.h>
using namespace std;
using i64 = long long;

constexpr int N = 1E6, M = sqrt(N) + 1;
int minp[N + 1];
vector<int> primes;
array<int, 3> factors[N + 1];
int _gcd[M + 1][M + 1];

void sieve() {
    factors[1] = {1, 1, 1};
    minp[1] = 1;
    for (int i = 2; i <= N; i++) {
        if (minp[i] == 0) {
            minp[i] = i;
            primes.push_back(i);
        }
        for (auto p : primes) {
            if (p * i > N) break;
            minp[p * i] = p;
            if (i % p == 0) break;
        }
        factors[i] = factors[i / minp[i]];
        factors[i][0] *= minp[i];
        if (factors[i][0] > factors[i][1]) swap(factors[i][0], factors[i][1]);
        if (factors[i][1] > factors[i][2]) swap(factors[i][1], factors[i][2]);
    }
}

int get(int x, int y) {
    int ans = 1;
    for (auto u : factors[x]) {
        if (u > M) {
            if ((y % u == 0))
                ans *= u;
        } else {
            ans *= _gcd[u][y % u];
            y /= _gcd[u][y % u];
        }
    }
    return ans;
}


int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    sieve();

    for (int i = 1; i <= 1000; i++) {
        _gcd[i][0] = _gcd[0][i] = i;
        for (int j = 1; j <= 1000; j++) {
            _gcd[i][j] = _gcd[j][i % j];
        }
    }
    

    return 0;
}