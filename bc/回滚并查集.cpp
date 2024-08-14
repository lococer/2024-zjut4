struct rollback_disjoint_set {
	int n;
	vector<int>fa, sz;
	vector<ll>cnt;
	vector<pair<int, int>> his_sz, his_fa;
	int his_sz_sz, his_fa_sz;

	rollback_disjoint_set(const tp& n) {
		this->n = n;
		sz = fa = vector<int>(n + 50);
		cnt = vector<ll>(n + 50);
		his_fa = his_sz = vector<pair<int, int>>(n + 50);
		his_sz_sz = 0; his_fa_sz = 0;
		for (int i = 1; i <= n; i++) {
			fa[i] = i;
			sz[i] = 1;
		}
	}

	int find(int x) {
		while (x != fa[x])
			x = fa[x];
		return fa[x];
	}

	void merge(int x, int y) {
		x = find(x);
		y = find(y);
		if (x != y) {
			if (sz[x] < sz[y])
				swap(x, y);
			his_sz[his_sz_sz++] = { x,sz[x] };
			sz[x] += sz[y];
			his_fa[his_fa_sz++] = { y,fa[y] };
			fa[y] = x;
			cnt[y] -= cnt[x];
		}
	}

	void roll(const int& h) { //»Ø¹ö
		while (his_fa_sz > h) {
			tp his_fa_last = his_fa_sz - 1;
			tp his_sz_last = his_sz_sz - 1;
			const tp y = his_fa[his_fa_last].first;
			cnt[y] += cnt[fa[y]];

			fa[his_fa[his_fa_last].first] = his_fa[his_fa_last].second;
			--his_fa_sz;
			sz[his_sz[his_sz_last].first] = his_sz[his_sz_last].second;
			--his_sz_sz;
		}
	}
};

