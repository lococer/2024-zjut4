struct segment_tree {
	tp inf = 2e9;
	struct node {
		tp ma, mi;
		tp lazy;
		tp lc, rc;//左右儿子
		tp lr, rr;//左右范围
	};
	vector<node>tree;
	tp tot;

	segment_tree(tp n = 0) {
		init(n);
	}

	void build_node(tp s, tp t, tp& p) {
		if (!p) {
			p = ++tot;
			tree[p].lr = s;
			tree[p].rr = t;
		}
	}

	void init(tp n) {
		tree = vector<node>(n + 5);
		tot = 0;
	}

	void build(tp s, tp t, tp& p, vector<tp>& ori) {
		p = ++tot;
		tree[p].lr = s;
		tree[p].rr = t;
		if (s == t) {
			tree[p].ma = ori[s];
			tree[p].mi = ori[s];
			return;
		}
		tp m = s + ((t - s) >> 1);
		build(s, m, tree[p].lc, ori), build(m + 1, t, tree[p].rc, ori);
		pushup(p);
	}

	void pushup(tp p) {
		tree[p].ma = max(tree[tree[p].lc].ma, tree[tree[p].rc].ma);
		tree[p].mi = min(tree[tree[p].lc].mi, tree[tree[p].rc].mi);
	}

	void update(tp c, tp p, tp xh) {
		if (xh == 1) {
			tree[p].ma = c;
			tree[p].mi = c;
			tree[p].lazy = c;
		}
	}

	void pushdown(tp p) {
		if (tree[p].lr != tree[p].rr) {
			if (tree[p].lazy) {
				update(tree[p].lazy, tree[p].lc, 1);
				update(tree[p].lazy, tree[p].rc, 1);
			}
		}
		tree[p].lazy = 0;
	}

	void change(tp l, tp r, tp c, tp p, tp xh) {
		if (l <= tree[p].lr && tree[p].rr <= r) {
			update(c, p, xh);
			return;
		}
		tp m = tree[p].lr + ((tree[p].rr - tree[p].lr) >> 1);
		build_node(tree[p].lr, m, tree[p].lc);
		build_node(m + 1, tree[p].rr, tree[p].rc);
		pushdown(p);
		if (l <= m)change(l, r, c, tree[p].lc, xh);
		if (r > m) change(l, r, c, tree[p].rc, xh);
		pushup(p);
	}

	tp getmax(tp l, tp r, tp p) {
		if (l <= tree[p].lr && tree[p].rr <= r)
			return tree[p].ma;
		tp m = tree[p].lr + ((tree[p].rr - tree[p].lr) >> 1), ans = -inf;
		build_node(tree[p].lr, m, tree[p].lc);
		build_node(m + 1, tree[p].rr, tree[p].rc);
		pushdown(p);
		if (l <= m) ans = max(ans, getmax(l, r, tree[p].lc));
		if (r > m) ans = max(ans, getmax(l, r, tree[p].rc));
		return ans;
	}

	tp getmin(tp l, tp r, tp p) {
		if (l <= tree[p].lr && tree[p].rr <= r)
			return tree[p].mi;
		tp m = tree[p].lr + ((tree[p].rr - tree[p].lr) >> 1), ans = inf;
		build_node(tree[p].lr, m, tree[p].lc);
		build_node(m + 1, tree[p].rr, tree[p].rc);
		pushdown(p);
		if (l <= m) ans = min(ans, getmin(l, r, tree[p].lc));
		if (r > m) ans = min(ans, getmin(l, r, tree[p].rc));
		return ans;
	}

	tp pd(tp p, tp c) {
		return tree[p].ma > c;
	}

	tp find_from_rt(tp lt, tp rt, tp c, tp p) {//从rt向左找合法的第一个值,0为不存在
		if (tree[p].lr == tree[p].rr) {
			if (tree[p].lr >= lt && pd(p, c)) {
				return tree[p].lr;
			}
			else {
				return 0;
			}
		}
		tp m = tree[p].lr + ((tree[p].rr - tree[p].lr) >> 1), ans = 0;
		if (rt > m && pd(tree[p].rc, c)) {
			ans = find_from_rt(lt, rt, c, tree[p].rc);
		}
		if (ans) {
			return ans;
		}
		return find_from_rt(lt, rt, c, tree[p].lc);
	}

	tp find_from_lt(tp lt, tp rt, tp c, tp p) {//从lt向右合法的第一个值，0为不存在
		if (tree[p].lr == tree[p].rr) {
			if (tree[p].lr <= rt && pd(p, c)) {
				return tree[p].lr;
			}
			else {
				return 0;
			}
		}
		tp m = tree[p].lr + ((tree[p].rr - tree[p].lr) >> 1), ans = 0;
		if (lt <= m && pd(tree[p].lc, c)) {
			ans = find_from_lt(lt, rt, c, tree[p].lc);
		}
		if (ans) {
			return ans;
		}
		return find_from_lt(lt, rt, c, tree[p].rc);
	}
};
