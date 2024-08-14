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
        int sz;

        poly(int n) {//最大第n阶
            sz = n;
            x.resize(n + 1);
        }

        inline tp& operator[](const int index) {
            return x[index];
        }

        inline void resize(const int sz) {
            x.resize(sz + 1);
            this->sz = sz;
        }

        friend inline poly operator*(poly a, poly b) {
            tp sz = a.sz + b.sz;
            tp tmp = max((tp)1, sz);
            tp lim = 1;
            while (lim < (tmp + 1)) lim <<= 1;
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

        inline poly& operator*=(poly other) {
            tp sz = this->sz + other.sz;
            tp tmp = max((tp)1, sz);
            tp lim = 1;
            while (lim < (tmp + 1)) lim <<= 1;
            this->resize(lim);
            other.resize(lim);
            ntt((*this), lim, 1);
            ntt(other, lim, 1);
            for (tp i = 0; i < lim; ++i) (*this)[i] = 1ll * (*this)[i] * other[i] % mod;
            ntt((*this), lim, 0);
            this->resize(sz);
            return (*this);
        }

    };

    void ntt_init(int n) {//处理的最大阶
        n = max(1, n);
        tp lim = 1;
        tp cnt = 0;
        while (lim < (n + 1)) lim <<= 1, cnt++;
        r.resize(cnt + 1);
        lim = 1;
        cnt = 0;
        while (lim < (n + 1)) {
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

}
