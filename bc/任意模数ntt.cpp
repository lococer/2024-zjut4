namespace anymod_poly {
    ll mod;

    ll ksm(ll a, ll b, ll p) {
        a %= p;
        ll lsans = 1;
        while (b) {
            if (b & 1ll) {
                lsans = (lsans * a) % p;
            }
            a = (a * a) % p;
            b >>= 1;
        }
        return lsans;
    }

    ll inv(ll x, const ll mod) { return ksm(x, mod - 2, mod); }

    const ll mod1 = 998244353, mod2 = 1004535809, mod3 = 469762049, G = 3;
    const ll mod_1_2 = static_cast<ll> (mod1) * mod2;
    const ll inv_1 = inv(mod1, mod2), inv_2 = inv(mod_1_2 % mod3, mod3);
    struct Int {
        int A, B, C;
        explicit inline Int() { }
        explicit inline Int(int __num) : A(__num), B(__num), C(__num) { }
        explicit inline Int(int __A, int __B, int __C) : A(__A), B(__B), C(__C) { }
        static inline Int reduce(const Int& x) {
            return Int(x.A + (x.A >> 31 & mod1), x.B + (x.B >> 31 & mod2), x.C + (x.C >> 31 & mod3));
        }
        inline friend Int operator + (const Int& lhs, const Int& rhs) {
            return reduce(Int(lhs.A + rhs.A - mod1, lhs.B + rhs.B - mod2, lhs.C + rhs.C - mod3));
        }
        inline friend Int operator - (const Int& lhs, const Int& rhs) {
            return reduce(Int(lhs.A - rhs.A, lhs.B - rhs.B, lhs.C - rhs.C));
        }
        inline friend Int operator * (const Int& lhs, const Int& rhs) {
            return Int(static_cast<ll> (lhs.A) * rhs.A % mod1, static_cast<ll> (lhs.B) * rhs.B % mod2, static_cast<ll> (lhs.C) * rhs.C % mod3);
        }
        inline int get() {
            ll x = static_cast<ll> (B - A + mod2) % mod2 * inv_1 % mod2 * mod1 + A;
            return (static_cast<ll> (C - x % mod3 + mod3) % mod3 * inv_2 % mod3 * (mod_1_2 % mod) % mod + x) % mod;
        }
    };

    tp lim, s;
    vector<ll>rev;
    vector<Int>Wn;
    void poly_init(tp n) {
        s = -1, lim = 1;
        while (lim < n) lim <<= 1, ++s;
        rev = vector<ll>(lim + 5);
        Wn = vector<Int>(lim + 5);
        for (register int i = 1; i < lim; ++i) rev[i] = rev[i >> 1] >> 1 | (i & 1) << s;
        const Int t(ksm(G, (mod1 - 1) / lim, mod1), ksm(G, (mod2 - 1) / lim, mod2), ksm(G, (mod3 - 1) / lim, mod3));
        Wn[0] = Int(1);
        for (auto it = Wn.begin(); it != Wn.begin() + lim; ++it) *(it + 1) = *it * t;
    }
    void ntt(Int* A, const int op) {//传入的数组尺寸至少要比lim大
        for (register int i = 1; i < lim; ++i) if (i < rev[i]) std::swap(A[i], A[rev[i]]);
        for (register int mid = 1; mid < lim; mid <<= 1) {
            const tp t = lim / mid >> 1;
            for (register int i = 0; i < lim; i += mid << 1) {
                for (register int j = 0; j < mid; ++j) {
                    const Int W = op ? Wn[t * j] : Wn[lim - t * j];
                    const Int X = A[i + j], Y = A[i + j + mid] * W;
                    A[i + j] = X + Y;
                    A[i + j + mid] = X - Y;
                }
            }
        }
        if (!op) {
            const Int ilim(inv(lim, mod1), inv(lim, mod2), inv(lim, mod3));
            for (register Int* i = A; i != A + lim; ++i) *i = (*i) * ilim;
        }
    }

    void mul(Int* a, Int* b, Int* c) {//只保留小于等于m的阶

        for (tp i = 0; i < lim; ++i) c[i] = a[i] * b[i];

        ntt(c, 0);
        for (tp i = 0; i <= m; i++) {
            c[i] = Int(c[i].get() % mod);
        }
        for (tp i = m + 1; i < lim; i++) {//去除大于m的阶
            c[i] = Int(0);
        }
        ntt(c, 1);
    }

}
