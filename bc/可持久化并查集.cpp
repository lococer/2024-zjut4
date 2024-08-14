struct sustain_disjoint_set {
	struct node {
		int lr, rr;//��������
		int rk, father;//�Ⱥ͸��׵�ֵ
		int lc, rc;//���Ҷ���
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
	//���ؽڵ��±�
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
	//���ظ��ڵ���±�
	int find(int x, int p) {
		int p1 = find_place(x, p);
		if (x == tree[p1].father) {
			return p1;
		}
		return find(tree[p1].father, p);
	}
	//��x�ĸ��׵�ֵ��Ϊc
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
	//��x���ȸ�Ϊc
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
	//�ж������Ƿ�һ��
	int judge(int u, int v, int p) {
		return find(u, p) == find(v, p);
	}
	//�ϲ����㣬ע��ϲ�ʱ���ǰ�uָ��v���ǰ�u�ĸ�����ָ��v�ĸ�����
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
