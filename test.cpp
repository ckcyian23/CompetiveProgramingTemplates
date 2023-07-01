#include <bits/stdc++.h>
using namespace std;

using i64 = long long;



int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    int n;
    cin >> n;
    
    vector<int> a(n), stk;
    vector<i64> s(n + 1);
    for (int i = 0; i < n; i++) {
        cin >> a[i];
        s[i + 1] = s[i] + a[i];
    }

    for(int i = 0; i <= n; i++) {
        while (!stk.empty() && s[stk.back()] <= s[i]) stk.pop_back();
        stk.push_back(i);
    }

    i64 val = -1E18;
    int mx = 0, cur = 0;
    array<int, 3> ans{};
    for (int x = 0; x <= n; x++) {
        if (s[x] > s[mx]) mx = x; 
        while (stk[cur] < x) cur++;
        i64 res = (2 * s[mx] - s[x]) + (2 * s[stk[cur]] - s[n] - s[x]);
        if (res > val) {
            val = res;
            ans = {mx, x, stk[cur]};
        }
    }
    cout << ans[0] << ' ' << ans[1] << ' ' << ans[2] << '\n';

    return 0;
}