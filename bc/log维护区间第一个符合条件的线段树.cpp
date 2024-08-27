struct segment_tree {
	struct node {
		tp ma;
		tp lc, rc;//左右儿子
		tp lr, rr;//左右范围
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
			tree[p].ma = ori[s];
			return;
		}
		tp m = s + ((t - s) >> 1);
		build(s, m, tree[p].lc, ori), build(m + 1, t, tree[p].rc, ori);
		pushup(p);
	}

	void pushup(tp p) {
		tree[p].ma = max(tree[tree[p].lc].ma, tree[tree[p].rc].ma);
	}

	tp find_greater_lt(tp rt, tp c, tp p) {//从rt向左找比c大的第一个值,0为不存在
		if (tree[p].lr == tree[p].rr) {
			if (tree[p].ma > c) {
				return tree[p].lr;
			}
			else {
				return 0;
			}
		}
		tp m = tree[p].lr + ((tree[p].rr - tree[p].lr) >> 1), ans = 0;
		if (rt > m && tree[tree[p].rc].ma > c) {
			ans = find_greater_lt(rt, c, tree[p].rc);
		}
		if (ans) {
			return ans;
		}
		return find_greater_lt(rt, c, tree[p].lc);
	}

	tp find_greater_rt(tp lt, tp c, tp p) {//从lt向右找比c大的第一个值，0为不存在
		if (tree[p].lr == tree[p].rr) {
			if (tree[p].ma > c) {
				return tree[p].lr;
			}
			else {
				return 0;
			}
		}
		tp m = tree[p].lr + ((tree[p].rr - tree[p].lr) >> 1), ans = 0;
		if (lt <= m && tree[tree[p].lc].ma > c) {
			ans = find_greater_rt(lt, c, tree[p].lc);
		}
		if (ans) {
			return ans;
		}
		return find_greater_rt(lt, c, tree[p].rc);
	}

};
