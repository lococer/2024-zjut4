namespace anymod_poly {
	tp ksm(tp a, tp b, tp p) {
		tp lsans = 1;
		while (b) {
			if (b & 1ll) {
				lsans = (lsans * a) % p;
			}
			a = (a * a) % p;
			b >>= 1;
		}
		return lsans;
	}
	tp inv(tp x, tp mod) { return ksm(x, mod - 2, mod); }
	tp mod;
	umap<int, int>lim_mp;
	const tp mod1 = 998244353, mod2 = 1004535809, mod3 = 469762049, G = 3;
	const ll mod_1_2 = static_cast<ll> (mod1) * mod2;
	const tp inv_1 = inv(mod1, mod2), inv_2 = inv(mod_1_2 % mod3, mod3);
	struct Int {
		ll A, B, C;
		explicit Int(ll __num = 0) : A(__num), B(__num), C(__num) {
			if (__num >= mod) {
				__num = __num;
			}
		}
		explicit Int(ll __A, ll __B, ll __C) : A(__A), B(__B), C(__C) {
			if (__A >= mod1 || __B >= mod2 || __C >= mod3) {
				__A = __A;
			}
		}
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
	vector<vector<tp>>rev;
	vector<vector<Int>>Wn;
	struct poly_Int;
	void ntt(poly_Int& A, tp lim, const tp op);
	struct poly_Int {
		vector<Int>x;

		poly_Int(int n) {//最大第n阶
			x.resize(n);
		}

		inline Int& operator[](const int index) {
			return x[index];
		}

		inline void resize(const int sz) {
			x.resize(sz);
		}

		inline int size() {
			return x.size();
		}

		friend inline poly_Int operator*(poly_Int a, poly_Int b) {
			tp sz = a.size() + b.size() - 1;
			tp tmp = max((tp)1, sz);
			tp lim = 1;
			while (lim < tmp) lim <<= 1;
			a.resize(lim);
			b.resize(lim);
			poly_Int result(lim);
			ntt(a, lim, 1);
			ntt(b, lim, 1);
			for (tp i = 0; i < lim; ++i) result[i] = a[i] * b[i];
			ntt(result, lim, 0);
			result.resize(sz);
			return result;
		}

		inline poly_Int& operator*=(poly_Int other) {
			(*this) = (*this) * other;
			return *this;
		}

	};

	void ntt_init(tp n) {//最大阶数
		tp s = -1, lim = 1;
		while (lim < n) {
			lim <<= 1, ++s;
			vector<tp> tmprev(lim + 5);
			vector<Int> tmpWn(lim + 5);
			for (register tp i = 1; i < lim; ++i) tmprev[i] = tmprev[i >> 1] >> 1 | (i & 1) << s;
			const Int t(ksm(G, (mod1 - 1) / lim, mod1), ksm(G, (mod2 - 1) / lim, mod2), ksm(G, (mod3 - 1) / lim, mod3));
			tmpWn[0] = Int(1);
			for (auto it = tmpWn.begin(); it != tmpWn.begin() + lim; ++it) *(it + 1) = *it * t;
			lim_mp[lim] = rev.size();
			rev.push_back(tmprev);
			Wn.push_back(tmpWn);
		}
	}

	void ntt(poly_Int& A, tp lim, const tp op) {
		tp pos = lim_mp[lim];
		vector<tp>& tmprev = rev[pos];
		vector<Int>& tmpWn = Wn[pos];
		for (register tp i = 1; i < lim; ++i) if (i < tmprev[i]) swap(A[i], A[tmprev[i]]);
		for (register tp mid = 1; mid < lim; mid <<= 1) {
			const tp t = lim / mid >> 1;
			for (register tp i = 0; i < lim; i += mid << 1) {
				for (register tp j = 0; j < mid; ++j) {
					const Int W = op ? tmpWn[t * j] : tmpWn[lim - t * j];
					const Int X = A[i + j], Y = A[i + j + mid] * W;
					A[i + j] = X + Y, A[i + j + mid] = X - Y;
				}
			}
		}
		if (!op) {
			const Int ilim(inv(lim, mod1), inv(lim, mod2), inv(lim, mod3));
			for (register int i = 0; i < lim; ++i) A[i] = A[i] * ilim;
		}
	}


}
