template<class T>
struct my_map {
    int tot, mysize;
    vector<int>lc, rc, nul, sz;
    vector<T>node;
    vector<tp>cnt;
    my_map(int n) {
        tp num = 2 * n + 50;
        lc = rc = sz = nul = vector<int>(num);
        node = vector<T>(num);
        cnt = vector<tp>(num);
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
        cnt[x] = cnt[y];
        node[x] = node[y];
    }

    int add_node(const T v, const tp num, const int s, const int l, const int r) {//加点,不能动
        int pos = nul[tot--];
        lc[pos] = l;
        rc[pos] = r;
        sz[pos] = s;
        cnt[pos] = num;
        node[pos] = v;
        return pos;
    }

    int merge(int x, int y) {//合并
        return add_node(max(node[x], node[y]), cnt[x] + cnt[y], sz[x] + sz[y], x, y);
    }

    void upd(int x) {//更新
        if (!lc[x]) {
            //sz[x] = 1;
            return;
        }
        sz[x] = sz[lc[x]] + sz[rc[x]];
        cnt[x] = cnt[lc[x]] + cnt[rc[x]];
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

    int find(const T v) {
        if (mysize == 0) {
            return 0;
        }
        int one = 1;
        if (node[one] < v) {//说明不存在
            return 0;
        }
        return find_help(v, one);
    }

    int find_help(const T& v, const int& x) {//节点从1开始
        if (!lc[x]) {
            if (node[x] == v) {
                return x;
            }
            else {
                return 0;
            }
        }
        if (node[lc[x]] >= v) {
            return find_help(v, lc[x]);
        }
        else {
            return find_help(v, rc[x]);
        }
    }

    void add(T v, tp num) {//增删操作
        if (mysize == 0) {
            add_node(v, num, 1, 0, 0);
            mysize++;
            return;
        }
        int one = 1;
        add_help(v, num, one);
    }

    void add_help(const T& v, const tp& num, const int& x) {
        if (!lc[x]) {
            if (node[x] == v) {
                cnt[x] += num;
            }
            else {
                lc[x] = add_node(node[x], cnt[x], 1, 0, 0);
                rc[x] = add_node(v, num, 1, 0, 0);
                if (node[x] > v) {
                    swap(lc[x], rc[x]);
                }
                upd(x);
                mat(x);
                mysize++;
            }
            return;
        }
        if (node[lc[x]] >= v) {
            add_help(v, num, lc[x]);
        }
        else if (node[lc[x]] < v) {
            add_help(v, num, rc[x]);
        }
        upd(x);
        mat(x);
        return;
    }

    void assign(T v, tp num) {//赋值操作
        if (mysize == 0) {
            add_node(v, num, 1, 0, 0);
            mysize++;
            return;
        }
        int one = 1;
        assign_help(v, num, one);
    }

    void assign_help(const T& v, const tp& num, const int& x) {
        if (!lc[x]) {
            if (node[x] == v) {
                cnt[x] = num;
            }
            else {
                lc[x] = add_node(node[x], cnt[x], 1, 0, 0);
                rc[x] = add_node(v, num, 1, 0, 0);
                if (node[x] > v) {
                    swap(lc[x], rc[x]);
                }
                upd(x);
                mat(x);
                mysize++;
            }
            return;
        }
        if (node[lc[x]] >= v) {
            assign_help(v, num, lc[x]);
        }
        else if (node[lc[x]] < v) {
            assign_help(v, num, rc[x]);
        }
        upd(x);
        mat(x);
        return;
    }

    void erase(T v) {
        if (mysize == 0) {
            return;
        }
        if (mysize == 1) {
            if (node[1] == v) {
                nul[++tot] = 1;
                mysize--;
            }
            return;
        }
        int one = 1, zero = 0;
        erase_help(v, one, zero);
    }

    void erase_help(const T& v, const int& x, const int& fa) {//根据值删除节点,set
        if (!lc[x]) {
            if (node[lc[fa]] == v) {
                nul[++tot] = lc[fa];
                nul[++tot] = rc[fa];
                cp(fa, rc[fa]);
                mysize--;
            }
            else if (node[rc[fa]] == v) {
                nul[++tot] = lc[fa];
                nul[++tot] = rc[fa];
                cp(fa, lc[fa]);
                mysize--;
            }
            return;
        }
        if (node[lc[x]] >= v) {
            erase_help(v, lc[x], x);
        }
        else {
            erase_help(v, rc[x], x);
        }
        upd(x);
        mat(x);
        return;
    }

    int rk(T v) {
        if (mysize == 0) {
            return 0;
        }
        int one = 1;
        return rk_help(v, one);
    }

    int rk_help(const T& v, const int& x) {//按值查询排名,按sz来,不存在时返回第一个比其大的排名
        if (sz[x] == 1) {
            return 1;
        }
        if (node[lc[x]] >= v) {
            return rk_help(v, lc[x]);
        }
        else {
            return rk_help(v, rc[x]) + sz[lc[x]];
        }
    }

    tp& operator[](const T& v) {//与按cnt来的第k小矛盾。
        int x = find(v);
        if (x == 0) {
            add(v, 0);
        }
        return cnt[x];
    }

    T kth(int k) {
        assert(mysize != 0);
        assert(cnt[1] >= k);
        int one = 1;
        return kth_help(k, one);
    }

    T kth_help(const int& k, const int& x) {//查询第k小,map
        if (!lc[x]) {
            return node[x];
        }
        if (cnt[lc[x]] >= k) {
            return kth_help(k, lc[x]);
        }
        else {
            return kth_help(k - cnt[lc[x]], rc[x]);
        }
    }

    tp getcnt(T v) {
        return cnt[find(v)];
    }

};
