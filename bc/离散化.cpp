void discrete(vector<tp>a, tp n, unordered_map<tp, tp>& f, unordered_map<tp, tp>& h) {
	tp cnt = 0;
	sort(a.begin() + 1, a.begin() + n + 1);
	f[a[1]] = ++cnt;
	h[1] = a[1];
	for (tp i = 2; i <= n; i++) {
		if (a[i] == a[i - 1]) {
			continue;
		}
		f[a[i]] = ++cnt;
		h[cnt] = a[i];
	}
}
