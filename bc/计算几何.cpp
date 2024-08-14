namespace geometry_pack {
#define ptt ptp
#define tt tp
	ptt operator+(const ptt& a, const ptt& b) { return{ a.first + b.first,a.second + b.second }; }
	ptt operator-(const ptt& a, const ptt& b) { return{ a.first - b.first,a.second - b.second }; }
	tt operator*(const ptt& a, const ptt& b) { return a.first * b.first + a.second * b.second; }
	tt operator%(const ptt& a, const ptt& b) { return a.first * b.second - a.second * b.first; }//计算几何全家桶//顺时针序
	ptt rotate2(ptt a, tt sita) { ptt ans; ans.first = cos(sita) * a.first - sin(sita) * a.second; ans.second = sin(sita) * a.first + cos(sita) * a.second; return ans; }
	db point2_dis(ptt u, ptt v) { db lsans = sqrtl((u.first - v.first) * (u.first - v.first) + (u.second - v.second) * (u.second - v.second)); return lsans; }
	db len(ptt p) { return sqrtl(p.first * p.first + p.second * p.second); }//求距离

	vector<ptt> getconvex_hull(vector<ptt>& point) {//Andrew求凸包
		vector<ptt>hull[3];
		int sz = int(point.size()), siz[3] = { 0,0,0 };
		sort(point.begin(), point.end());
		for (int i = 0; i < sz; hull[0].push_back(point[i++]), siz[0]++) {
			while (siz[0] > 1 && (hull[0][siz[0] - 1] - hull[0][siz[0] - 2]) % (point[i] - hull[0][siz[0] - 1]) >= 0) {
				hull[0].pop_back(); siz[0]--;
			}
		}
		for (int i = sz - 1; i >= 0; hull[1].push_back(point[i--]), siz[1]++) {
			while (siz[1] > 1 && (hull[1][siz[1] - 1] - hull[1][siz[1] - 2]) % (point[i] - hull[1][siz[1] - 1]) >= 0) {
				hull[1].pop_back(); siz[1]--;
			}
		}
		for (int j = 0; j < 2; j++)
			for (int i = 0; i < siz[j] - 1; i++)
				hull[2].push_back(hull[j][i]);
		return hull[2];
	}

	vector<ptt> merge(vector<ptt>& a, vector<ptt>& b) {//闵可夫斯基和(b需提前绕原点翻转)
		int sa = a.size(), sb = b.size(), pa = 1, pb = 1;
		auto dot = a[0] + b[0];
		vector<ptt>res{ dot };
		while (pa <= sa && pb <= sb) {
			auto d_a = a[pa % sa] - a[pa - 1], d_b = b[pb % sb] - b[pb - 1];
			if (d_a % d_b < 0)dot = dot + d_a, res.push_back(dot), pa++;
			else dot = dot + d_b, res.push_back(dot), pb++;
		}
		while (pa <= sa) { auto d_a = a[pa % sa] - a[pa - 1]; dot = dot + d_a, res.push_back(dot), pa++; }
		while (pb <= sb) { auto d_b = b[pb % sb] - b[pb - 1]; dot = dot + d_b, res.push_back(dot), pb++; }
		res.pop_back();
		return getconvex_hull(res);
	}//去重

	bool jud_in(vector<ptt>& v, ptt dot) {//判点在凸包内
		int sz = v.size(); dot = dot - v[0];
		if ((v[1] - v[0]) % dot > 0 || (v[sz - 1] - v[0]) % dot < 0)return 0;
		int l = 1, r = sz - 1;
		while (r - l > 1) {
			int mid = (l + r) / 2;
			((v[mid] - v[0]) % dot > 0) ? r = mid : l = mid;
		}
		return((v[r] - v[l]) % (dot + v[0] - v[l]) <= 0);
	}

	tt get_longest(vector<ptt>& point) {  // 求凸包直径的平方
		tt ma = 0;
		int j = 2;
		tp sz = point.size();
		if (sz < 3) {
			ma = (point[0] - point[1]) * (point[0] - point[1]);
			return ma;
		}
		for (int i = 0; i < sz; ++i) {
			while (abs((point[j] - point[i]) % (point[j] - point[(i + 1) % sz])) <= abs((point[(j + 1) % sz] - point[i]) % (point[(j + 1) % sz] - point[(i + 1) % sz]))) {
				j = (j + 1) % sz;
			}
			ma = max(ma, max((point[(i + 1) % sz] - point[j]) * (point[(i + 1) % sz] - point[j]), (point[i] - point[j]) * (point[i] - point[j])));
		}
		return ma;
	}
}
