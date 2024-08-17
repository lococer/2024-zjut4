#define _CRT_SECURE_NO_WARNINGS
#include<bits/stdc++.h>
#define ll long long int
#define db double
#define tp ll
#define ptp pair<tp,tp>
#define pdb pair<db,db>
#define umap unordered_map
#define P 998244353ll
#define ed '\n'

using namespace std;
using C = complex<double>;


tp n, num, sum, flag, ans, tmp, ls, len, wz, pos, m, k, p, q;
tp lt, rt, mid;
tp min1, min2, min3, max1, max2, max3;
string s;
tp h, w, t;

const int N = 4100001;

double PI = acos(-1);
int rev[N];

vector<ll> f, g;

ll ksm(ll a, ll b, const ll mod) {
    ll ret = 1;
    for (; b; b >>= 1, a = a * a % mod)if (b & 1)ret = ret * a % mod;
    return ret;
}

ll inv(ll x, const ll mod) { return ksm(x, mod - 2, mod); }

struct MINT {
    const static ll mod1 = 998244353, mod2 = 1004535809, mod3 = 469762049, G = 3;
    const static ll invg1 = 156587350, invg2 = 332748118, invg3 = 334845270;
    const static ll mod_1_2 = static_cast<ll> (mod1) * mod2;
    //const static ll inv_1 = inv(mod1, mod2), inv_2 = inv(mod_1_2 % mod3, mod3);
    const static ll inv_1 = 669690699, inv_2 = 354521948;
    ll A, B, C;
    inline MINT(ll __num = 0) : A(__num% mod1), B(__num% mod2), C(__num% mod3) { }
    inline MINT(ll __A, ll __B, ll __C) : A(__A% mod1), B(__B% mod2), C(__C% mod3) { }
    static inline MINT reduce(const MINT& x) {
        return MINT(x.A + (x.A >> 31 & mod1), x.B + (x.B >> 31 & mod2), x.C + (x.C >> 31 & mod3));
    }
    inline friend MINT operator + (const MINT& lhs, const MINT& rhs) {
        return reduce(MINT(lhs.A + rhs.A - mod1, lhs.B + rhs.B - mod2, lhs.C + rhs.C - mod3));
    }
    inline friend MINT operator - (const MINT& lhs, const MINT& rhs) {
        return reduce(MINT(lhs.A - rhs.A, lhs.B - rhs.B, lhs.C - rhs.C));
    }
    inline friend MINT operator * (const MINT& lhs, const MINT& rhs) {
        return MINT(static_cast<ll> (lhs.A) * rhs.A % mod1, static_cast<ll> (lhs.B) * rhs.B % mod2, static_cast<ll> (lhs.C) * rhs.C % mod3);
    }
    inline friend MINT operator / (const MINT& lhs, const MINT& rhs) {
        return MINT(static_cast<ll> (lhs.A) * inv(rhs.A, mod1) % mod1, static_cast<ll> (lhs.B) * inv(rhs.B, mod2) % mod2, static_cast<ll> (lhs.C) * inv(rhs.C, mod3) % mod3);
    }
    MINT operator+=(const MINT& rhs) {
        return *this = *this + rhs;
    }
    MINT operator-=(const MINT& rhs) {
        return *this = *this - rhs;
    }
    MINT operator*=(const MINT& rhs) {
        return *this = *this * rhs;
    }
    MINT operator/=(const MINT& rhs) {
        return *this = *this / rhs;
    }
    bool operator==(const MINT& rhs)const {
        return A == rhs.A && B == rhs.B && C == rhs.C;
    }
    bool operator!=(const MINT& rhs)const {
        return A != rhs.A || B != rhs.B || C != rhs.C;
    }
    MINT operator-()const {
        return MINT(mod1 - A, mod2 - B, mod3 - C);
    }
    static MINT getw(ll n, bool inv = false) {
        return MINT(ksm(inv ? invg1 : 3, (mod1 - 1) / n, mod1), ksm(inv ? invg2 : 2, (mod2 - 1) / n, mod2), ksm(inv ? invg3 : 3, (mod3 - 1) / n, mod3));
    }
    inline int get(const ll mod) {
        ll x = static_cast<ll> (B - A + mod2) % mod2 * inv_1 % mod2 * mod1 + A;
        return (static_cast<ll> (C - x % mod3 + mod3) % mod3 * inv_2 % mod3 * (mod_1_2 % mod) % mod + x) % mod;
    }
    inline MINT getinv() {
        return MINT(inv(A, mod1), inv(B, mod2), inv(C, mod3));
    }



};

struct poly {
    vector<ll> x;
    poly() = default;
    poly(const vector<ll>& a) :x(a) {};
    poly(ll a) :x(a) {};
    poly resize(int n)const {
        vector<ll> ret(n);
        for (int i = 0; i < min(n, (int)x.size()); i++)ret[i] = x[i];
        return move(poly(ret));
    }
    ll& operator[](const int& i) { return x[i]; }
};
poly operator*(poly a, poly b);
poly operator-(const poly& a, const poly& b);
poly operator+(const poly& a, const poly& b);
pair<poly, poly> operator/(poly a, poly b);
poly operator*(poly a, ll b);
poly operator*(ll a, poly b);

namespace POLY {
    ll p = 998244353, g = 3, invg = 332748118;
    vector<ll> vinv;
    void getrev(int s) {
        for (int i = 0; i < (1 << s); i++) {
            rev[i] = ((rev[i >> 1] >> 1) | ((i & 1) << (s - 1)));
        }
    }
    void mtt(vector<MINT>& a, int s, bool inv) {
        getrev(s);
        for (int i = 0; i < (1 << s); i++) {
            if (i < rev[i])swap(a[i], a[rev[i]]);
        }
        for (int h = 1; h <= s; h++) {
            int n = 1 << h;
            MINT t = 1, w = MINT::getw(n, inv);
            for (int i = 0; i < (1 << s); i += n) {
                t = 1;
                for (int j = i; j < i + (n >> 1); j++) {
                    MINT tmp = t * a[j + (n >> 1)];
                    a[j + (n >> 1)] = a[j] - tmp;
                    a[j] = a[j] + tmp;
                    t = t * w;
                }
            }
        }
        if (inv) {
            MINT invs = MINT(1 << s).getinv();
            for (int i = 0; i < (1 << s); i++) {
                a[i] = a[i] * invs;
            }
        }
    }
    void fft(C* a, int s, bool inv) {
        getrev(s);
        for (int i = 0; i < (1 << s); i++) {
            if (i < rev[i])swap(a[i], a[rev[i]]);
        }
        for (int h = 1; h <= s; h++) {
            int n = 1 << h;
            C t(1, 0), w(cos(2 * PI / n), sin(2 * PI / n));
            if (inv)w = C(cos(2 * PI / n), -sin(2 * PI / n));
            for (int i = 0; i < (1 << s); i += n) {
                t = C(1, 0);
                for (int j = i; j < i + (n >> 1); j++) {
                    C tmp = t * a[j + (n >> 1)];
                    a[j + (n >> 1)] = a[j] - tmp;
                    a[j] = a[j] + tmp;
                    t = t * w;
                }
            }
        }
        if (inv) {
            for (int i = 0; i < (1 << s); i++) {
                a[i] /= (1 << s);
            }
        }
    }
    void ntt(vector<ll>& a, int s, bool inv) {
        getrev(s);
        for (int i = 0; i < (1 << s); i++) {
            if (i < rev[i])swap(a[i], a[rev[i]]);
        }
        for (int h = 1; h <= s; h++) {
            int n = 1 << h;
            ll t = 1, w = ksm(inv ? invg : g, (p - 1) / n, p);
            for (int i = 0; i < (1 << s); i += n) {
                t = 1;
                for (int j = i; j < i + (n >> 1); j++) {
                    ll tmp = t * a[j + (n >> 1)] % p;
                    a[j + (n >> 1)] = ((a[j] - tmp) % p + p) % p;
                    a[j] = (a[j] + tmp) % p;
                    t = t * w % p;
                }
            }
        }
        if (inv) {
            ll invs = ksm(1 << s, p - 2, p);
            for (int i = 0; i < (1 << s); i++) {
                a[i] = a[i] * invs % p;
            }
        }
    }
    poly inv(const poly& a, int k) {
        poly ret(vector<ll>(1, ksm(a.x.front(), p - 2, p)));
        for (int i = 1; i < k; i <<= 1) {
            ret = ret * (2 - a.resize(i << 1) * ret);
            ret.x.resize(i << 1);
        }
        ret.x.resize(k);
        return ret;
    }
    poly d(poly a) {
        for (int i = 0; i + 1 < a.x.size(); i++) {
            a.x[i] = a.x[i + 1] * (i + 1) % p;
        }
        a.x.pop_back();
        return a;
    }
    poly i(poly a) {
        a.x.push_back(0);
        for (int i = a.x.size() - 1; i; i--) {
            a.x[i] = a.x[i - 1] * ksm(i, p - 2, p) % p;
        }
        a.x[0] = 0;
        return a;
    }
    poly ln(poly a, int k) {//a0=1
        a.x.resize(k);
        return i((d(a) * inv(a, k)).resize(k)).resize(k);
    }
    poly exp(const poly& a, int k) {//a0=1
        poly ret(1);
        for (int i = 1; i < k; i <<= 1) {
            ret = ret * (1 + a.resize(i << 1) - ln(ret, i << 1));
            ret.x.resize(i << 1);
        }
        ret.x.resize(k);
        return ret;
    }
};
poly operator*(poly a, poly b) {
    //单模
    //ll al = a.x.size(), bl = b.x.size(), cl = al + bl - 1;
    //int s = 0;
    //while ((1 << s) < cl)s++;
    //a.x.resize(1 << s, 0), b.x.resize(1 << s, 0);
    //POLY::ntt(a.x, s, 0);
    //POLY::ntt(b.x, s, 0);
    //for (int i = 0; i < (1 << s); i++)a.x[i] = a.x[i] * b.x[i] % POLY::p;
    //POLY::ntt(a.x, s, 1);
    //a.x.resize(cl);
    //return move(a);
    //任意模数 读到POLY::mp
    ll al = a.x.size(), bl = b.x.size(), cl = al + bl - 1;
    vector<MINT> A(a.x.begin(), a.x.end()), B(b.x.begin(), b.x.end());
    int s = 0;
    while ((1 << s) < cl)s++;
    A.resize(1 << s);
    B.resize(1 << s);
    POLY::mtt(A, s, 0);
    POLY::mtt(B, s, 0);
    for (int i = 0; i < (1 << s); i++)A[i] = A[i] * B[i];
    POLY::mtt(A, s, 1);
    a.x.resize(cl);
    for (int i = 0; i < cl; i++)a.x[i] = A[i].get(POLY::p);
    return move(a);
}
poly operator-(const poly& a, const poly& b) {
    ll al = a.x.size(), bl = b.x.size(), cl = max(al, bl);
    poly c = poly(vector<ll>(cl));
    for (int i = 0; i < cl; i++) {
        if (i < al)c.x[i] += a.x[i];
        if (i < bl)c.x[i] -= b.x[i];
        c.x[i] = (c.x[i] + POLY::p) % POLY::p;
    }
    return move(c);
}
poly operator*(poly a, ll b) {
    poly c(a);
    for (auto& aa : c.x)aa = aa * b % POLY::p;
    return move(c);
}
poly operator*(ll a, poly b) {
    poly c(b);
    for (auto& aa : c.x)aa = aa * a % POLY::p;
    return move(c);
}
poly operator+(const poly& a, const poly& b) {
    ll al = a.x.size(), bl = b.x.size(), cl = max(al, bl);
    poly c = poly(vector<ll>(cl));
    for (int i = 0; i < cl; i++) {
        if (i < al)c.x[i] += a.x[i];
        if (i < bl)c.x[i] += b.x[i];
        c.x[i] %= POLY::p;
    }
    return move(c);
}
pair<poly, poly> operator/(poly a, poly b) {
    int n = a.x.size(), m = b.x.size();
    if (n < m)return make_pair(poly(vector<ll>(1, 0)), move(a));
    reverse(a.x.begin(), a.x.end());
    reverse(b.x.begin(), b.x.end());
    poly c = a * (POLY::inv(b, n - m + 1));
    c.x.resize(n - m + 1);
    reverse(c.x.begin(), c.x.end());
    reverse(a.x.begin(), a.x.end());
    reverse(b.x.begin(), b.x.end());
    poly r = a - c * b;
    r.x.resize(m - 1, 0);
    return make_pair(move(c), move(r));
}
poly operator<<(poly a, int b) {
    poly c(a);
    for (int i = 0; i < c.x.size(); i++) {
        if (i + b < c.x.size())c.x[i] = c.x[i + b];
        else c.x[i] = 0;
    }
    c.x.resize(max((int)c.x.size() - b, 1));
    return move(c);
}
poly operator>>(poly a, int b) {
    poly c(a);
    c.x.resize(c.x.size() + b);
    for (int i = (int)c.x.size() - 1; i >= 0; i--) {
        if (i - b >= 0)c.x[i] = c.x[i - b];
        else c.x[i] = 0;
    }
    return move(c);
}



void init() {

}

void clear() {

}

void solve() {
    cin >> n >> m >> p;
    POLY::p = p;
    poly a(n + 1);
    poly b(m + 1);
    for (tp i = 0; i <= n; i++) {
        cin >> a[i];
    }
    for (tp i = 0; i <= m; i++) {
        cin >> b[i];
    }
    poly c = a * b;
    for (tp i = 0; i <= n + m; i++) {
        cout << c[i] << ' ';
    }
    cout << ed;


}

int main(void) {
    ios::sync_with_stdio(false);
    cin.tie(0);
    cout.tie(0);
    int _t = 1;
    //cin >> _t;
    init();
    while (_t--) {
        solve();
    }
}
//样例
/*



*/