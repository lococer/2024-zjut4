struct chain_forward_star {
	vector<int>head;
	vector<int>vis;
	vector<int>nxt, to;
	vector<tp>val;//ͼ,��Ȩ
	vector<tp>dis;//ͼ,����
	vector<int>sz;//��,ÿ��������С
	vector<int>dep;//��,����
	vector<int>son;//��,�ض���
	vector<int>fa;//��,����
	vector<int>link_top;//��,����
	vector<pii>dfn;//dfs��,�������,��������
	tp inf = 1e9;
	chain_forward_star(tp n = 0) {
		init(n);
	}

	void init(tp n) {
		head = vector<int>(n, -1);
		dis = vector<tp>(n);
		vis = sz = dep = son = fa = link_top = vector<int>(n);
		dfn = vector<pii>(n);
		nxt.clear();
		to.clear();
	}

	void add(int u, int v) {
		nxt.push_back(head[u]);
		head[u] = to.size();
		to.push_back(v);
		val.push_back(1);//Ĭ�ϱ�ȨΪ1
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

	void dijkstra(int s) {
		dis = vector<tp>(dis.size(), inf);
		vis = vector<int>(vis.size());
		dis[s] = 0;
		priority_queue<ptp, vector<ptp>, greater<ptp>>q;
		q.push({ 0,s });
		while (!q.empty()) {
			int u = q.top().second;
			q.pop();
			if (vis[u]) continue;
			vis[u] = 1;
			for (int i = head[u]; ~i; i = nxt[i]) {
				int v = to[i], w = val[i];
				if (dis[v] > dis[u] + w) {
					dis[v] = dis[u] + w;
					q.push({ dis[v], v });
				}
			}
		}
	}

};
