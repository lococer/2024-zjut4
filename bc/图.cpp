struct chain_forward_star {
	vector<int>head;
	vector<int>vis;
	vector<int>nxt, to;
	vector<int>sz;//树，每棵子树大小
	vector<int>dep;//树，树深
	vector<int>son;//树，重儿子
	vector<int>fa;//树，父亲
	vector<int>link_top;//树,链顶
	vector<pii>dfn;//dfs序，先序遍历，可以用作
	chain_forward_star(tp n = 0) {
		init(n);
	}

	void init(tp n) {
		head = vector<int>(n, -1);
		vis = sz = dep = son = fa = link_top = vector<int>(n);
		dfn = vector<pii>(n);
		nxt.clear();
		to.clear();
	}

	void add(int u, int v) {
		nxt.push_back(head[u]);
		head[u] = to.size();
		to.push_back(v);
	}

	void addedge(int u, int v) {
		add(u, v); add(v, u);
	}

	void dfs(int u, int last = 0) {
		if (vis[u]) return;
		vis[u] = true;
		for (int i = head[u]; ~i; i = nxt[i]) {
			int v = to[i];
			if (v != last) {
				dfs(v, u);
			}
		}
	}

	void lca_init(int u) {
		lca_dfs1(u, 0); lca_dfs2(u, u);
	}

	void lca_dfs1(int u, int last) {
		dep[u] = dep[last] + 1;
		sz[u] = 1;
		for (int i = head[u]; ~i; i = nxt[i]) {
			int v = to[i];
			if (v == last) continue;
			lca_dfs1(v, u);
			sz[u] += sz[v];
			if (sz[v] > sz[son[u]]) son[u] = v;
		}
	}

	void lca_dfs2(int u, int linktop, int last = 0) {
		link_top[u] = linktop;
		fa[u] = last;
		if (son[u]) lca_dfs2(son[u], linktop, u);
		for (int i = head[u]; ~i; i = nxt[i]) {
			int y = to[i];
			if (y == last || y == son[u]) continue;
			lca_dfs2(y, y, u);
		}
	}

	int lca(int u, int v) {
		while (link_top[u] != link_top[v]) {
			if (dep[link_top[u]] < dep[link_top[v]]) swap(u, v);
			u = fa[link_top[u]];
		}
		if (dep[u] < dep[v]) swap(u, v);
		return v;
	}

	int xh_dfs(int u, int last = 0, int num = 1) {
		dfn[u].first = num;
		for (int i = head[u]; ~i; i = nxt[i]) {
			int v = to[i];
			if (v != last) {
				num += xh_dfs(v, u, num + 1);
			}
		}
		dfn[u].second = num;
		return (dfn[u].second - dfn[u].first + 1);
	}

};
