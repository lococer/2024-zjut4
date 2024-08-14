template<class T>
struct set_array {//������,��Ϊ����ʱ�ǵ����±�0
    const ll INF = 0x7fffffff;//����set��˵�����ֵ
    int tot, mysize;
    vector<int>lc, rc, sz, nul;
    vector<T>vl;
    set_array(int n) {
        lc = rc = sz = nul = vector<int>(2 * n + 50);
        vl = vector<T>(2 * n + 50);
        mysize = 0;
        tot = 2 * n + 39;
        for (int i = 1; i < 2 * n + 40; i++) {
            nul[i] = 2 * n + 40 - i;
        }
        add(INF, 1, 0, 0);
    }

    void cp(int x, int y) {//���Ƶ�,���ܶ�
        lc[x] = lc[y];
        rc[x] = rc[y];
        sz[x] = sz[y];
        vl[x] = vl[y];
    }

    int add(tp v, int s, int l, int r) {//�ӵ�,���ܶ�
        int cnt = nul[tot--];
        lc[cnt] = l;
        rc[cnt] = r;
        sz[cnt] = s;
        vl[cnt] = v;
        return cnt;
    }

    int merge(int x, int y) { return add(max(vl[x], vl[y]), sz[x] + sz[y], x, y); }//�ϲ�,ע�������Ҫ���ĵ�һ��ֵ

    void upd(int x) {//���£����ܶ�
        if (!lc[x]) {
            sz[x] = 1;
            return;
        }
        sz[x] = sz[lc[x]] + sz[rc[x]];
        vl[x] = max(vl[lc[x]], vl[rc[x]]);
    }

    void rot(int x, int flag) {//��ת�����ܶ�
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

    void mat(int x) {//ά�������ܶ�
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

    void insert(T v, int x = 1) {//����,set
        if (!lc[x]) {
            lc[x] = add(min(v, vl[x]), 1, 0, 0);
            rc[x] = add(max(v, vl[x]), 1, 0, 0);
            upd(x);
            mat(x);
            mysize++;
            return;
        }
        if (vl[lc[x]] > v) {
            insert(v, lc[x]);
        }
        else if (vl[lc[x]] < v) {
            insert(v, rc[x]);
        }
        upd(x);
        mat(x);
        return;
    }

    void erase(T v, int x = 1, int fa = 0) {//����ֵɾ���ڵ�,set
        if (!lc[x]) {
            if (vl[lc[fa]] == v) {
                nul[++tot] = lc[fa];
                nul[++tot] = rc[fa];
                cp(fa, rc[fa]);
                mysize--;
            }
            else if (vl[rc[fa]] == v) {
                nul[++tot] = lc[fa];
                nul[++tot] = rc[fa];
                cp(fa, lc[fa]);
                mysize--;
            }
            return;
        }
        if (vl[lc[x]] >= v) {
            erase(v, lc[x], x);
        }
        else {
            erase(v, rc[x], x);
        }
        upd(x);
        mat(x);
        return;
    }

    int rnk(T v, int x = 1) {//��ֵ��ѯ����,set
        if (sz[x] == 1) {
            return 1;
        }
        if (vl[lc[x]] >= v) {
            return rnk(v, lc[x]);
        }
        else {
            return rnk(v, rc[x]) + sz[lc[x]];
        }
    }

    T kth(int k, int x = 1) {//��ѯ��kС,set
        if (sz[x] == k) {
            return vl[x];
        }
        if (sz[lc[x]] >= k) {
            return kth(k, lc[x]);
        }
        else {
            return kth(k - sz[lc[x]], rc[x]);
        }
    }

    T& operator[](int k) {//�±��ѯ,array
        return kth_order(k + 1);
    }

    T& kth_order(int k, int x = 1) {//�����±��ѯ,array
        if (!lc[x]) {
            return vl[x];
        }
        if (sz[lc[x]] >= k) {
            return kth_order(k, lc[x]);
        }
        else {
            return kth_order(k - sz[lc[x]], rc[x]);
        }
    }

    void insert_index(T v, int k) {//�����±����,array
        insert_index(v, k + 1, 1);
    }

    void insert_index(T v, int k, int x) {//��������,�����±����,array
        if (!lc[x]) {
            lc[x] = add(v, 1, 0, 0);
            rc[x] = add(vl[x], 1, 0, 0);
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

    void erase_index(int k) {//�����±�ɾ��,array
        if (k < mysize) erase_index(k + 1, 1);
    }

    void erase_index(int k, int x, int fa = 0) {//���������������±�ɾ��,array
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

    void pos_for(int s, int t) {//����forѭ��
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
                //�˴��޸�vl[now]���Ǹ�a[pos]
                if (ls1 < vl[now]) {
                    sum = ls2 + ls1;
                    wz1 = pos - 1;
                    break;
                }
                else {
                    ls1 = ls2; ls2 = vl[now];
                }
                while (wz && rc[tmp[wz]] == now) now = tmp[wz--];
                if (wz) now = rc[tmp[wz]];
            }
            else {
                tmp[++wz] = now;
                now = lc[now];
            }
        }
    }

    void rev_for(int s, int t) {//����forѭ��
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
                //�˴��޸�vl[now]���Ǹ�a[pos]
                if (vl[now] > sum) {
                    wz2 = pos;
                    break;
                }
                while (wz && lc[tmp[wz]] == now) now = tmp[wz--];
                if (wz) now = lc[tmp[wz]];
            }
            else {
                tmp[++wz] = now;
                now = rc[now];
            }
        }
    }

    int find_max(int k, T num, int x = 1) {//�����±��kС���ֱ�num�������±�
        if (vl[x] <= num) {
            return -1;
        }
        if (!lc[x]) {
            return 0;
        }
        int tmp = -1;
        if (sz[lc[x]]<k && vl[rc[x]]>num) {
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
