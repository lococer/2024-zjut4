struct internet_flow {
	vector<tp>head, dis, vis;
	vector<tp>cur, dep;//最大流
	vector<tp>mf, pre;//费用流
	vector<tp>nxt, to, val, cost;
	tp tot = 1;
	tp inf = 1e10;//无穷大
	tp ret = 0;//最小费用
	internet_flow(tp n, tp m) {//点数量，边数量(已开两倍)
		head = dis = vis = cur = dep = mf = pre = vector<tp>(n + 5);
		nxt = to = val = cost = vector<tp>(2 * m + 5);
		tot = 1;
		ret = 0;
	}

	void add(tp u, tp v, tp w) {
		nxt[++tot] = head[u];
		to[tot] = v;
		val[tot] = w;
		head[u] = tot;
	}

	void addedge(tp u, tp v, tp w) {
		add(u, v, w); add(v, u, 0);
	}

	void add(tp u, tp v, tp w, tp c) {
		add(u, v, w); cost[tot] = c;
	}

	void addedge(tp u, tp v, tp w, tp c) {
		add(u, v, w, c); add(v, u, 0, -c);
	}

	tp bfs(tp s, tp t) {
		dep = vector<tp>(dep.size());
		cur = head;
		queue<tp> q;
		q.push(s), dep[s] = 1;
		while (!q.empty()) {
			tp u = q.front();
			q.pop();
			for (tp i = head[u]; i; i = nxt[i]) {
				tp v = to[i];
				if (val[i] && !dep[v]) q.push(v), dep[v] = dep[u] + 1;
			}
		}
		return dep[t];
	}

	tp dfs(tp u, tp t, tp flow) {
		if (u == t) return flow;
		tp ans = 0;
		for (tp& i = cur[u]; (i) && ans < flow; i = nxt[i]) {
			tp v = to[i];
			if (val[i] && dep[v] == dep[u] + 1) {
				tp x = dfs(v, t, min(val[i], flow - ans));
				if (x) val[i] -= x, val[i ^ 1] += x, ans += x;
			}
		}
		if (ans < flow) dep[u] = -1;
		return ans;
	}

	tp dinic(tp s, tp t) {
		tp ans = 0;
		while (bfs(s, t)) {
			tp x;
			while ((x = dfs(s, t, inf))) ans += x;
		}
		return ans;
	}


	bool spfa(tp s, tp t) {
		dis = vector<tp>(dis.size(), inf);
		queue<tp> q;
		q.push(s), dis[s] = 0, mf[s] = inf, mf[t] = 0;
		while (!q.empty()) {
			tp u = q.front();
			q.pop(), vis[u] = 0;
			for (tp i = head[u]; i; i = nxt[i]) {
				const tp& v = to[i], & w = val[i], & c = cost[i];
				if (w && dis[v] > dis[u] + c) {
					dis[v] = dis[u] + c;
					mf[v] = min(mf[u], w);
					pre[v] = i;
					if (!vis[v]) {
						vis[v] = 1;
						q.push(v);
					}
				}
			}
		}
		return mf[t];
	}

	tp EK(tp s, tp t) {
		tp ans = 0;
		while (spfa(s, t)) {
			ans += mf[t];
			for (tp u = t; u != s; u = to[pre[u] ^ 1]) {
				int i = pre[u];
				val[i] -= mf[t];
				val[i ^ 1] += mf[t];
				ret += mf[t] * cost[i];
			}
		}
		return ans;
	}
};
