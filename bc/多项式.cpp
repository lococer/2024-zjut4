namespace polynomial {
    vector<vector<tp> >r;
    const ll mod = 998244353;
    umap<int, int>lim_mp;
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
    void ntt(poly& x, tp lim, tp opt);

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
            a.resize(lim);
            b.resize(lim);
            poly result(lim);
            ntt(a, lim, 1);
            ntt(b, lim, 1);
            for (tp i = 0; i < lim; ++i) result[i] = 1ll * a[i] * b[i] % mod;
            ntt(result, lim, 0);
            result.resize(sz);
            return result;
        }

        inline poly& operator*=(const poly& other) {
            (*this) = (*this) * other;
            return *this;
        }

        poly inv() {
            tp k = this->size();
            poly ret(vector<ll>(1, ksm((*this)[0], mod - 2, mod)));
            for (tp i = 1; i < k; i <<= 1) {
                ret *= (poly(vector<tp>(1, 2)) - poly(*this, i << 1) * ret);
                ret.resize(i << 1);
            }
            ret.resize(k);
            return ret;
        }

    };

    void ntt_init(int n) {//处理的最大项数
        n = max(1, n);
        tp lim = 1;
        tp cnt = 0;
        while (lim < n) lim <<= 1, cnt++;
        r.resize(cnt + 1);
        lim = 1;
        cnt = 0;
        while (lim < n) {
            lim <<= 1;
            cnt++;
            lim_mp[lim] = cnt;
            r[cnt].resize(lim);
            for (tp i = 0; i < lim; ++i) {
                r[cnt][i] = (i & 1) * (lim >> 1) + (r[cnt][i >> 1] >> 1);
            }
        }
    }

    void ntt(poly& x, tp lim, tp opt) {
        tp k, gn, g, tmp;
        tp cnt = lim_mp[lim];
        for (tp i = 0; i < lim; ++i)
            if (r[cnt][i] < i) swap(x[i], x[r[cnt][i]]);
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
        if (opt == 0) {
            reverse(x.x.begin() + 1, x.x.begin() + lim);
            int inv = ksm(lim, mod - 2, mod);
            for (tp i = 0; i < lim; ++i) x[i] = 1ll * x[i] * inv % mod;
        }
    }

    poly dsu_mul(vector<poly>& v, tp s, tp t) {
        if (s == t) {
            return v[s];
        }
        tp m = s + ((t - s) >> 1);
        return dsu_mul(v, s, m) * dsu_mul(v, m + 1, t);
    }

}
