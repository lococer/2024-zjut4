namespace polynomial {
    const ll mod = 998244353ll;
    ll ksm(ll a, ll b, const ll p) {
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
    struct poly;
    struct poly_Int;

    //以下为任意模数部分

    ll inv(ll x, ll mod) { return ksm(x, mod - 2, mod); }
    const ll mod1 = 998244353, mod2 = 1004535809, mod3 = 469762049, G = 3;
    const ll mod_1_2 = static_cast<ll> (mod1) * mod2;
    const ll inv_1 = inv(mod1, mod2), inv_2 = inv(mod_1_2 % mod3, mod3);
    struct Int {
        ll A, B, C;
        explicit Int(ll __num = 0) : A(__num% mod1), B(__num% mod2), C(__num% mod3) {}
        explicit Int(ll __A, ll __B, ll __C) : A(__A% mod1), B(__B% mod2), C(__C% mod3) {}
        static Int reduce(const Int& x) {
            return Int(x.A + (x.A >> 31 & mod1), x.B + (x.B >> 31 & mod2), x.C + (x.C >> 31 & mod3));
        }
        friend Int operator + (const Int& lhs, const Int& rhs) {
            return reduce(Int(lhs.A + rhs.A - mod1, lhs.B + rhs.B - mod2, lhs.C + rhs.C - mod3));
        }
        friend Int operator - (const Int& lhs, const Int& rhs) {
            return reduce(Int(lhs.A - rhs.A, lhs.B - rhs.B, lhs.C - rhs.C));
        }
        friend Int operator * (const Int& lhs, const Int& rhs) {
            return Int(static_cast<ll> (lhs.A) * rhs.A % mod1, static_cast<ll> (lhs.B) * rhs.B % mod2, static_cast<ll> (lhs.C) * rhs.C % mod3);
        }
        tp get() {
            ll x = static_cast<ll> (B - A + mod2) % mod2 * inv_1 % mod2 * mod1 + A;
            return (static_cast<ll> (C - x % mod3 + mod3) % mod3 * inv_2 % mod3 * (mod_1_2 % mod) % mod + x) % mod;
        }
    };
    struct poly_Int {
        vector<Int>x;

        poly_Int(int n) {
            x.resize(n);
        }

        poly_Int(const poly& a);

        inline Int& operator[](const int index) {
            return x[index];
        }

        inline void resize(const int sz) {
            x.resize(sz);
        }

        inline int size() const {
            return x.size();
        }

        friend void ntt(poly_Int& x, tp lim, const tp op) {
            tp s = 0;
            while ((1ll << (s + 1)) < lim) {
                ++s;
            }
            vector<tp>rev(lim + 1);
            vector<Int>Wn(lim + 1);
            for (register tp i = 1; i < lim; ++i) rev[i] = rev[i >> 1] >> 1 | (i & 1) << s;
            const Int t(ksm(G, (mod1 - 1) / lim, mod1), ksm(G, (mod2 - 1) / lim, mod2), ksm(G, (mod3 - 1) / lim, mod3));
            Wn[0] = Int(1);
            for (auto it = Wn.begin(); it != Wn.begin() + lim; ++it) {
                *(it + 1) = *it * t;
            }
            for (register tp i = 1; i < lim; ++i) if (i < rev[i]) swap(x[i], x[rev[i]]);
            for (register tp mid = 1; mid < lim; mid <<= 1) {
                const tp t = lim / mid >> 1;
                for (register tp i = 0; i < lim; i += mid << 1) {
                    for (register tp j = 0; j < mid; ++j) {
                        const Int W = op ? Wn[t * j] : Wn[lim - t * j];
                        const Int X = x[i + j], Y = x[i + j + mid] * W;
                        x[i + j] = X + Y, x[i + j + mid] = X - Y;
                    }
                }
            }
            if (!op) {
                const Int ilim(inv(lim, mod1), inv(lim, mod2), inv(lim, mod3));
                for (register int i = 0; i < lim; ++i) x[i] = x[i] * ilim;
            }
        }

    };

    //以上为任意模数部分

    struct poly {
        vector<tp>x;

        inline tp& operator[](const int& index) {
            return x[index];
        }

        poly(int n = 0) { x.resize(n); };

        poly(const vector<ll>& a) :x(a) {};

        poly(const poly& a, int sz) {
            sz = min(sz, a.size());
            x.resize(sz);
            for (tp i = 0; i < sz; i++) {
                x[i] = a.x[i];
            }
        }

        //任意模数转换用
        poly(poly_Int& a);

        inline int size() const {
            return x.size();
        }

        inline void resize(const int& sz) {
            x.resize(sz);
        }

        inline poly operator-() const {
            poly result(this->x.size());
            for (tp i = 0; i < result.size(); i++) {
                result[i] = mod - this->x[i];
            }
            return move(result);
        }

        friend inline poly operator+(const poly& a, const poly& b) {
            tp sz = max(a.size(), b.size());
            poly result(sz);
            for (tp i = 0; i < a.size(); i++) {
                result[i] += a.x[i];
            }
            for (tp i = 0; i < b.size(); i++) {
                (result[i] += b.x[i]) %= mod;
            }
            if (a.size() == b.size()) {
                for (sz = a.size(); sz > 0; sz--) {
                    if (result[sz - 1]) {
                        break;
                    }
                }
                result.resize(sz);
            }
            return move(result);
        }

        inline poly& operator+=(const poly& other) {
            (*this) = (*this) * other;
            return *this;
        }

        friend inline poly operator-(const poly& a, const poly& b) {
            return move(a + (-b));
        }

        inline poly& operator-=(const poly& other) {
            (*this) = (*this) - other;
            return *this;
        }

        friend inline poly operator*(poly a, poly b) {
            tp sz = a.size() + b.size() - 1;
            tp tmp = max((tp)1, sz);
            tp lim = 2;
            while (lim < tmp) lim <<= 1;
            if (mod == 998244353ll) {
                a.resize(lim);
                b.resize(lim);
                poly result(lim);
                ntt(a, lim, 1);
                ntt(b, lim, 1);
                for (tp i = 0; i < lim; ++i) result[i] = 1ll * a[i] * b[i] % mod;
                ntt(result, lim, 0);
                result.resize(sz);
                return move(result);
            }
            else {
                poly_Int Inta(a), Intb(b);
                Inta.resize(lim);
                Intb.resize(lim);
                poly_Int Intresult(lim);
                ntt(Inta, lim, 1);
                ntt(Intb, lim, 1);
                for (tp i = 0; i < lim; ++i)Intresult[i] = Inta[i] * Intb[i];
                ntt(Intresult, lim, 0);
                Intresult.resize(sz);
                poly result(Intresult);
                return move(result);
            }
        }

        inline poly& operator*=(const poly& other) {
            (*this) = (*this) * other;
            return *this;
        }

        friend inline poly operator/(poly a, poly b) {
            if (a.size() < b.size()) {
                return poly(1);
            }
            reverse(a.x.begin(), a.x.end());
            reverse(b.x.begin(), b.x.end());
            poly c = a * b.inv(a.size() - b.size() + 1);
            c.resize(a.size() - b.size() + 1);
            reverse(c.x.begin(), c.x.end());
            return move(c);
        }

        inline poly& operator/=(const poly& other) {
            (*this) = (*this) / other;
            return *this;
        }

        friend inline poly operator%(poly a, poly b) {
            if (a.size() < b.size()) {
                return move(a);
            }
            poly r = a - (a / b) * b;
            return move(r);
        }

        inline poly& operator%=(const poly& other) {
            (*this) = (*this) % other;
            return *this;
        }


        friend void ntt(poly& x, tp lim, tp opt) {
            tp k, gn, g, tmp;
            vector<tp>r(lim);
            for (tp i = 0; i < lim; ++i) {
                r[i] = (i & 1) * (lim >> 1) + (r[i >> 1] >> 1);
            }
            for (tp i = 0; i < lim; ++i)
                if (r[i] < i) swap(x[i], x[r[i]]);
            for (tp m = 2; m <= lim; m <<= 1) {
                k = m >> 1;
                gn = ksm(3, (mod - 1) / m, mod);
                for (tp i = 0; i < lim; i += m) {
                    g = 1;
                    for (tp j = 0; j < k; ++j, g = 1ll * g * gn % mod) {
                        tmp = 1ll * x[i + j + k] * g % mod;
                        x[i + j + k] = (x[i + j] - tmp + mod) % mod;
                        x[i + j] = (x[i + j] + tmp) % mod;
                    }
                }
            }
            if (!opt) {
                reverse(x.x.begin() + 1, x.x.begin() + lim);
                int inv = ksm(lim, mod - 2, mod);
                for (tp i = 0; i < lim; ++i) x[i] = 1ll * x[i] * inv % mod;
            }
        }

        poly inv(int k = 0) {
            if (k == 0) {
                k = this->size();
            }
            poly ret(vector<ll>(1, ksm((*this)[0], mod - 2, mod)));
            for (tp i = 1; i < k; i <<= 1) {
                ret *= (poly(vector<tp>(1, 2)) - poly(*this, i << 1) * ret);
                ret.resize(i << 1);
            }
            ret.resize(k);
            return ret;
        }

    };

    //以下为任意模数部分
    poly::poly(poly_Int& a) {
        x.resize(a.size());
        for (tp i = 0; i < x.size(); ++i) {
            x[i] = a[i].get();
        }
    }

    poly_Int::poly_Int(const poly& a) {
        x.resize(a.size());
        for (tp i = 0; i < x.size(); ++i) {
            x[i] = (Int)a.x[i];
        }
    }
    //以上为任意模数部分

    //启发式连乘
    poly dsu_mul(vector<poly>& v, tp s, tp t) {
        if (s == t) {
            return v[s];
        }
        tp m = s + ((t - s) >> 1);
        return dsu_mul(v, s, m) * dsu_mul(v, m + 1, t);
    }

}
