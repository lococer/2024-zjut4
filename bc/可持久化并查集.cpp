struct sustain_disjoint_set {
	struct node {
		int lr, rr;//左右区间
		int rk, father;//秩和父亲的值
		int lc, rc;//左右儿子
	};
	vector<node>tree;
	int tot;

	sustain_disjoint_set(int n) {
		tree = vector<node>(n + 50);
		tot = 0;
	}

	void build(int& p, int s, int t) {
		p = ++tot;
		tree[p].lr = s; tree[p].rr = t;
		if (s == t) {
			tree[p].father = s;
			return;
		}
		int m = s + ((t - s) >> 1);
		build(tree[p].lc, s, m), build(tree[p].rc, m + 1, t);
	}
	//返回节点下标
	int find_place(int x, int p) {
		if (tree[p].lr == tree[p].rr) {
			return p;
		}
		int m = tree[p].lr + ((tree[p].rr - tree[p].lr) >> 1);
		if (x <= m) {
			return find_place(x, tree[p].lc);
		}
		else {
			return find_place(x, tree[p].rc);
		}
	}
	//返回根节点的下标
	int find(int x, int p) {
		int p1 = find_place(x, p);
		if (x == tree[p1].father) {
			return p1;
		}
		return find(tree[p1].father, p);
	}
	//把x的父亲的值改为c
	void change_f(int x, int c, int& p) {
		tree[++tot] = tree[p];
		p = tot;
		if (tree[p].lr == tree[p].rr) {
			tree[p].father = c;
			return;
		}
		int m = tree[p].lr + ((tree[p].rr - tree[p].lr) >> 1);
		if (x <= m) {
			change_f(x, c, tree[p].lc);
		}
		else {
			change_f(x, c, tree[p].rc);
		}
	}
	//把x的秩改为c
	void change_rk(int x, int c, int& p) {
		tree[++tot] = tree[p];
		p = tot;
		if (tree[p].lr == tree[p].rr) {
			tree[p].rk = c;
			return;
		}
		int m = tree[p].lr + ((tree[p].rr - tree[p].lr) >> 1);
		if (x <= m) {
			change_rk(x, c, tree[p].lc);
		}
		else {
			change_rk(x, c, tree[p].rc);
		}
	}
	//判断两点是否一起
	int judge(int u, int v, int p) {
		return find(u, p) == find(v, p);
	}
	//合并两点，注意合并时不是把u指向v而是把u的根父亲指向v的根父亲
	int merge(int u, int v, int p) {
		int u_f = find(u, p);
		int v_f = find(v, p);
		if (u_f == v_f) {
			return p;
		}
		if (tree[u_f].rk > tree[v_f].rk) {
			swap(u_f, v_f);
		}
		change_f(tree[u_f].father, tree[v_f].father, p);
		if (tree[u_f].rk == tree[v_f].rk) {
			change_rk(tree[v_f].father, tree[v_f].rk + 1, p);
		}
		return p;
	}
};
