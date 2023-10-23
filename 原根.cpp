#include <bits/stdc++.h>
using namespace std;

using i64 = long long;

constexpr int N = 1E6;
int minp[N + 1], haveRoot[N + 1], phi[N + 1];
vector<int> primes;
void init() {
    for (int i = 2; i <= N; i++) {
        if (minp[i] == 0) {
            minp[i] = i;
            phi[i] = i - 1;
            primes.push_back(i);
        }
        for (auto p : primes) {
            if (p * i > N) break;
            minp[i * p] = p;
            if (i % p == 0) {
                phi[i * p] = phi[i] * p;
                break;
            }
            phi[i * p] = phi[i] * phi[p];
        }
    }

    haveRoot[2] = haveRoot[4] = 1;
    for (auto p : primes) {
        if (p == 2) continue;
        for (i64 i = p; i <= N; i *= p) {
            haveRoot[i] = true;
            if (2 * i <= N) haveRoot[2 * i] = true;
        }
    }
}

vector<int> factors(int x) {
    vector<int> ret;
    for (int i = 2; i * i <= x; i++) {
        if (x % i == 0) {
            while (x % i == 0) x /= i;
            ret.push_back(i);
        }
    }
    if (x > 1) ret.push_back(x);

    return ret;
}

int power(int a, i64 b, int p) {
    int res = 1 % p;
    for (; b; b /= 2, a = 1LL * a * a % p) {
        if (b & 1) res = 1LL * res * a % p;
    }
    return res;
}

int findRoot(int p) {
    auto fac = factors(phi[p]);
    for (int i = 1; i < p; i++) {
        if (power(i, phi[p], p) == 1) {
            bool ok = true;
            for (auto x : fac) {
                if (x == 1) continue;
                if (power(i, phi[p] / x, p) == 1) {
                    ok = false;
                    break;
                }
            }
            if (ok) return i;
        }
    }
    return -1;
}

void solve() {
    int n, d;
    cin >> n >> d;

    if (haveRoot[n]) {
        int g = findRoot(n);

        vector<int> ans;
        for (int i = 1, t = g; i <= phi[n]; i++, t = 1LL * t * g % n) {
            if (gcd(i, phi[n]) == 1) {
                ans.push_back(t);
            }
        }
        sort(ans.begin(), ans.end());
        cout << ans.size() << '\n';

        for (int i = d - 1; i < ans.size(); i += d) {
            cout << ans[i] << ' ';
        }
        cout << '\n';


    } else {
        cout << 0 << "\n\n";
    }
    
}

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);


    init();

    int t = 1;
    cin >> t;

    while (t--) {
        solve();
    }

    return 0;
}