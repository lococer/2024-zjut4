struct sustain_segment_tree {
	struct node {
		tp sum;//和
		tp lazy;//懒标记
		tp lc, rc;//左右儿子
	};
	vector<node>tree;
	tp tot;

	sustain_segment_tree(tp n) {
		tree = vector<node>(n + 50);
		tot = 0;
	}

	void build(tp s, tp t, tp& p, tp ori[]) {
		p = ++tot;
		if (s == t) {
			tree[p].sum = ori[s];
			return;
		}
		tp m = s + ((t - s) >> 1);
		build(s, m, tree[p].lc, ori), build(m + 1, t, tree[p].rc, ori);
		pushup(p);
	}

	void build_child(tp& p) {
		tree[++tot] = tree[tree[p].lc];
		tree[p].lc = tot;
		tree[++tot] = tree[tree[p].rc];
		tree[p].rc = tot;
	}

	void pushup(tp p) {
		tree[p].sum = tree[tree[p].lc].sum + tree[tree[p].rc].sum;
	}

	void update(tp c, tp p, tp s, tp t, tp xh) {
		if (xh == 1) {
			tree[p].sum = ((t - s + 1) * c);
			tree[p].lazy = c;
		}
	}

	void pushdown(tp p, tp s, tp t) {
		if (s != t) {
			if (tree[p].lazy) {
				tp m = s + ((t - s) >> 1);
				update(tree[p].lazy, tree[p].lc, s, m, 1);
				update(tree[p].lazy, tree[p].rc, m + 1, t, 1);
			}
		}
		tree[p].lazy = 0;
	}

	void change_help(tp l, tp r, tp c, tp p, tp s, tp t, tp xh) {
		if (l <= s && t <= r) {
			update(c, p, s, t, xh);
			return;
		}
		tp m = s + ((t - s) >> 1);
		build_child(p);
		pushdown(p, s, t);
		if (l <= m)change_help(l, r, c, tree[p].lc, s, m, xh);
		if (r > m) change_help(l, r, c, tree[p].rc, m + 1, t, xh);
		pushup(p);
	}

	tp change(tp l, tp r, tp c, tp p, tp s, tp t, tp xh) {
		tree[++tot] = tree[p];
		p = tot;
		if (l <= s && t <= r) {
			update(c, p, s, t, xh);
			return p;
		}
		tp m = s + ((t - s) >> 1);
		build_child(p);
		pushdown(p, s, t);
		if (l <= m)change_help(l, r, c, tree[p].lc, s, m, xh);
		if (r > m) change_help(l, r, c, tree[p].rc, m + 1, t, xh);
		pushup(p);
		return p;
	}

	tp getans(tp l, tp r, tp p, tp s, tp t) {
		if (l <= s && t <= r)
			return tree[p].sum;
		tp m = s + ((t - s) >> 1), ans = 0;
		if (tree[p].lazy) {
			build_child(p);
		}
		pushdown(p, s, t);
		if (l <= m) ans = (ans + getans(l, r, tree[p].lc, s, m));
		if (r > m) ans = (ans + getans(l, r, tree[p].rc, m + 1, t));
		return ans;
	}
};
