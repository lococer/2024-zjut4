template<class T>
struct my_array {
    int tot, mysize;
    vector<int>lc, rc, nul, sz;
    vector<T>node;
    my_array(int n = 0) {
        init(n);
    }
    void init(int n) {
        int num = 2 * n + 5;
        lc = rc = sz = nul = vector<int>(num);
        node = vector<T>(num);
        mysize = 0;
        tot = num - 1;
        for (int i = 1; i < num; i++) {
            nul[i] = num - i;
        }
    }

    void cp(const int x, const int y) {//复制点,不能动
        lc[x] = lc[y];
        rc[x] = rc[y];
        sz[x] = sz[y];
        node[x] = node[y];
    }

    int add_node(const T v, const int s, const int l, const int r) {//加点,不能动
        int pos = nul[tot--];
        lc[pos] = l;
        rc[pos] = r;
        sz[pos] = s;
        node[pos] = v;
        return pos;
    }

    int merge(int x, int y) {//合并
        return add_node(max(node[x], node[y]), sz[x] + sz[y], x, y);
    }

    void upd(int x) {//更新
        if (!lc[x]) {
            //sz[x] = 1;
            return;
        }
        sz[x] = sz[lc[x]] + sz[rc[x]];
        node[x] = max(node[lc[x]], node[rc[x]]);
    }

    void rot(int x, int flag) {//翻转，不能动
        if (!flag) {
            rc[x] = merge(rc[lc[x]], rc[x]);
            nul[++tot] = lc[x];
            lc[x] = lc[lc[x]];
        }
        else {
            lc[x] = merge(lc[x], lc[rc[x]]);
            nul[++tot] = rc[x];
            rc[x] = rc[rc[x]];
        }
    }

    void mat(int x) {//维护，不能动
        if (sz[lc[x]] > sz[rc[x]] * 3) {
            if (sz[rc[lc[x]]] > sz[lc[lc[x]]] * 2) {
                rot(lc[x], 1);
            }
            rot(x, 0);
        }
        else if (sz[rc[x]] > sz[lc[x]] * 3) {
            if (sz[lc[rc[x]]] > sz[rc[rc[x]]] * 2) {
                rot(rc[x], 0);
            }
            rot(x, 1);
        }
    }

    T& operator[](int k) {//下标查询,array
        return kth_order(k + 1);
    }

    T& kth_order(int k, int x = 1) {//辅助下标查询,array
        if (!lc[x]) {
            return node[x];
        }
        if (sz[lc[x]] >= k) {
            return kth_order(k, lc[x]);
        }
        else {
            return kth_order(k - sz[lc[x]], rc[x]);
        }
    }

    void push_back(T v) {
        insert_index(v, mysize);
    }

    void pop_back() {
        erase_index(mysize - 1);
    }

    void insert_index(T v, int k) {//根据下标插入,array
        if (mysize == 0) {
            add_node(v, 1, 0, 0);
            mysize++;
            return;
        }
        insert_index(v, k + 1, 1);
    }

    void insert_index(const T& v, int k, int x) {//辅助函数,根据下标插入,array
        if (!lc[x]) {
            if (k > 1) {
                lc[x] = add_node(node[x], 1, 0, 0);
                rc[x] = add_node(v, 1, 0, 0);
            }
            else {
                lc[x] = add_node(v, 1, 0, 0);
                rc[x] = add_node(node[x], 1, 0, 0);
            }
            upd(x);
            mat(x);
            mysize++;
            return;
        }

        if (sz[lc[x]] >= k) {
            insert_index(v, k, lc[x]);
        }
        else {
            insert_index(v, k - sz[lc[x]], rc[x]);
        }
        upd(x);
        mat(x);
        return;
    }

    void erase_index(int k) {//根据下标删除,array
        if (k < mysize) {
            if (mysize == 1) {
                nul[++tot] = 1;
                mysize--;
            }
            else {
                erase_index(k + 1, 1);
            }
        }
    }

    void erase_index(int k, int x, int fa = 0) {//辅助函数，根据下标删除,array
        if (!lc[x]) {
            nul[++tot] = lc[fa];
            nul[++tot] = rc[fa];
            if (lc[fa] == x) {
                cp(fa, rc[fa]);
            }
            else {
                cp(fa, lc[fa]);
            }
            mysize--;
            return;
        }
        if (sz[lc[x]] >= k) {
            erase_index(k, lc[x], x);
        }
        else {
            erase_index(k - sz[lc[x]], rc[x], x);
        }
        upd(x);
        mat(x);
        return;
    }

    void pos_for(int s, int t) {//正向for循环
        vector<int>tmp(65);
        int wz = 0;
        int now = 1, hs = s + 1, pos = s - 1;
        while (lc[now]) {
            if (sz[lc[now]] >= hs) {
                tmp[++wz] = now;
                now = lc[now];
            }
            else {
                hs -= sz[lc[now]];
                tmp[++wz] = now;
                now = rc[now];
            }
        }
        while (wz && pos < t) {
            if (!lc[now]) {
                ++pos;
                //此处修改node[now]就是改a[pos]

                while (wz && rc[tmp[wz]] == now) now = tmp[wz--];
                if (wz) now = rc[tmp[wz]];
            }
            else {
                tmp[++wz] = now;
                now = lc[now];
            }
        }
    }

    void rev_for(int s, int t) {//逆向for循环
        vector<int>tmp(65);
        int wz = 0;
        int now = 1, hs = s + 1, pos = s + 1;
        while (lc[now]) {
            if (sz[lc[now]] >= hs) {
                tmp[++wz] = now;
                now = lc[now];
            }
            else {
                hs -= sz[lc[now]];
                tmp[++wz] = now;
                now = rc[now];
            }
        }
        while (wz && pos > t) {
            if (!lc[now]) {
                --pos;
                //此处修改node[now]就是改a[pos]

                while (wz && lc[tmp[wz]] == now) now = tmp[wz--];
                if (wz) now = lc[tmp[wz]];
            }
            else {
                tmp[++wz] = now;
                now = rc[now];
            }
        }
    }

    int find_max(int k, T num, int x = 1) {//查找下标比k小数字比num大的最大下标,与[]重载矛盾
        if (node[x] <= num) {
            return -1;
        }
        if (!lc[x]) {
            return 0;
        }
        int tmp = -1;
        if (sz[lc[x]]<k && node[rc[x]]>num) {
            tmp = find_max(k - sz[lc[x]], num, rc[x]);
        }
        if (~tmp) {
            return tmp + sz[lc[x]];
        }
        else {
            return find_max(k, num, lc[x]);
        }
    }

};
