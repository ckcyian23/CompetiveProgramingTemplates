#include <bits/stdc++.h>
using namespace std;
using i64 = long long;
template<class T = i64, int N = 64>
struct LinearBasis{
    vector<T> a;
    bool zero;
    LinearBasis() : a(N), zero(false) {}
    LinearBasis& insert(T x) {
        for(int i = N - 1; i >= 0; i--) {
            if(!(x >> i & 1)) continue;
            if(a[i]) {
                x ^= a[i];
                continue;
            }
            for(int j = i - 1; j >= 0; j--) 
                if(x >> j & 1) x ^= a[j];
            for(int j = N - 1; j > i; j--) 
                if(a[j] >> i & 1) a[j] ^= x;
            a[i] = x;
            return *this;
        }
        zero = true;
        return *this;
    }

    T Min() {
        if(zero) return 0;
        for(int i = 0; i <= N - 1; i++)
            if(a[i]) return a[i];
    }
    T Max() {
        T res = 0;
        for(int i = N - 1; i >= 0; i--) 
            res = res ^ a[i];
        return res;
    }
    bool in(T x) {
        for(int i = N - 1; i >= 0; i--) {
            if(x >> i & 1) {
                if(a[i])
                    x ^= a[i];
                else 
                    return false;
            }
        }
        return true;
    }
    T nthMin(T x) {
        if (x <= 0) return -1;
        T res = 0;
        x -= zero;
        vector<T> own;
        for(int i = 0; i <= N - 1; i++) {
            if(a[i]) own.push_back(a[i]);
        }
        if(x >= 1LL << own.size()) return -1;
        for(int i = 0; i < int(own.size()); i++) {
            if(x >> i & 1)
                res ^= own[i];
        }
        return res;
    }

    T nthMax(T x) {
        vector<T> own;
        for(int i = N - 1; i >= 0; i--)
            if(a[i]) own.push_back(a[i]);
        return nthMin(((1LL << own.size()) + zero) - x);
    }

    friend LinearBasis operator+ (const LinearBasis &lhs, const LinearBasis &rhs) {
        LinearBasis ret = lhs;
        for (int i = 0; i < N; i++) {
            if (rhs.a[i]) ret.insert(rhs.a[i]);
        }
        ret.zero |= rhs.zero;
        return ret;
    }
    LinearBasis& operator+= (const LinearBasis &rhs) {
        return *this = *this + rhs;;
    }
};




int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);
    LinearBasis ls;
    
    return 0;
}