struct segment_tree {
	struct node {
		tp sum;//ºÍ
		tp lazy;//ÀÁ±ê¼Ç
		tp lc, rc;//×óÓÒ¶ù×Ó
		tp lr, rr;//×óÓÒ·¶Î§
	};
	vector<node>tree;
	tp tot;

	segment_tree(tp n = 0) {
		init(n);
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
			tree[p].sum = ori[s];
			return;
		}
		tp m = s + ((t - s) >> 1);
		build(s, m, tree[p].lc, ori), build(m + 1, t, tree[p].rc, ori);
		pushup(p);
	}

	void build_node(tp s, tp t, tp& p) {
		if (!p) {
			p = ++tot;
			tree[p].lr = s;
			tree[p].rr = t;
		}
	}

	void pushup(tp p) {
		tree[p].sum = tree[tree[p].lc].sum + tree[tree[p].rc].sum;
	}

	void update(tp c, tp p, tp xh) {
		if (xh == 1) {
			tree[p].sum = (tree[p].sum + ((tree[p].rr - tree[p].lr + 1) * c));
			tree[p].lazy = (tree[p].lazy + c);
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

	tp getans(tp l, tp r, tp p) {
		if (l <= tree[p].lr && tree[p].rr <= r)
			return tree[p].sum;
		tp m = tree[p].lr + ((tree[p].rr - tree[p].lr) >> 1), ans = 0;
		build_node(tree[p].lr, m, tree[p].lc);
		build_node(m + 1, tree[p].rr, tree[p].rc);
		pushdown(p);
		if (l <= m) ans = (ans + getans(l, r, tree[p].lc));
		if (r > m) ans = (ans + getans(l, r, tree[p].rc));
		return ans;
	}
};
