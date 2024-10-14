struct disjoint_set {
    int n;
    vector<int>father;

    disjoint_set(const int& n) {
        init(n);
    }

    void init(const int& n) {
        this->n = n;
        father = vector<int>(n);
        for (int i = 0; i < n; i++) {
            father[i] = i;
        }
    }

    int find(const int& x) {
        if (x == father[x]) {
            return x;
        }
        else {
            father[x] = find(father[x]);  //���ڵ���Ϊ���ڵ�
            return father[x];         //���ظ��ڵ�
        }
    }

    void merge(const int& u, const int& v) {
        father[find(u)] = find(v);
    }

    bool isbind(const int& u, const int& v) {
        return find(u) == find(v);
    }

};
