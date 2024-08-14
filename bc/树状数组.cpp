namespace tree_array {
	tp lowbit(tp x) {
		return x & (-x);
	}

	void update(vector<tp>& ar, tp pos, tp n, tp val) {
		while (pos <= n) {
			ar[pos] += val;
			pos += lowbit(pos);
		}
	}

	tp getsum(vector<tp>& ar, tp pos) {
		tp sum = 0;
		while (pos >= 1) {
			sum += ar[pos];
			pos -= lowbit(pos);
		}
		return sum;
	}

	tp getsum(vector<tp>& ar, tp lt, tp rt) {
		return getsum(ar, rt) - getsum(ar, lt - 1);
	}

	void build(vector<tp>& ar, vector<tp>& br, tp n) {
		for (int i = 1; i <= n; i++) {
			update(ar, i, n, br[i]);
		}
	}
};
