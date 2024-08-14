struct topological_sorting {
	vector<tp>a;
	vector<vector<tp>>v;
	vector<tp>indegree;

	topological_sorting(tp n) {
		a = vector<tp>(n + 5);
		v = vector<vector<tp>>(n + 5);
		indegree = vector<tp>(n + 5);
	}

	void add(tp head, tp to) {
		v[head].push_back(to);
		++indegree[to];
	}

	void work(tp sz) {
		tp topo_pos = 0;
		for (int i = 1; i <= sz; i++) {
			if (indegree[i] == 0) {
				a[++topo_pos] = i;
			}
		}
		for (int i = 1; i <= sz; i++) {
			if (a[i] == 0) {
				break;//²»ÄÜÍØÆËÅÅÐò
			}
			for (int j = 0; j < v[a[i]].size(); j++) {
				--indegree[v[a[i]][j]];
				if (indegree[v[a[i]][j]] == 0) {
					a[++topo_pos] = v[a[i]][j];
				}
			}
		}
	}
};
