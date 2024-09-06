namespace my_hash {
    int hash_num;
    static const ll hash_p[] = { (ll)1e9 + 7,(ll)1e9 + 9,(ll)1e9 + 21,(ll)1e9 + 33,(ll)1e9 + 87,(ll)1e9 + 93,(ll)1e9 + 97,(ll)1e9 + 123,(ll)1e9 + 181,(ll)1e9 + 207 };

    vector<tp> operator*(vector<tp> v, tp x) {
        for (int i = 0; i < v.size(); i++) {
            v[i] *= x;
        }
        return v;
    }

    vector<tp> operator+(vector<tp> v, tp x) {
        for (int i = 0; i < v.size(); i++) {
            v[i] += x;
        }
        return v;
    }

    vector<tp> operator-(vector<tp> v, tp x) {
        for (int i = 0; i < v.size(); i++) {
            v[i] -= x;
        }
        return v;
    }

    vector<tp> operator*(vector<tp> v, const vector<tp>& x) {
        for (int i = 0; i < v.size(); i++) {
            v[i] *= x[i];
        }
        return v;
    }

    vector<tp> operator+(vector<tp> v, const vector<tp>& x) {
        for (int i = 0; i < v.size(); i++) {
            v[i] += x[i];
        }
        return v;
    }

    vector<tp> operator-(vector<tp> v, const vector<tp>& x) {
        for (int i = 0; i < v.size(); i++) {
            v[i] -= x[i];
        }
        return v;
    }

    vector<tp>& qm(vector<tp>& v) {
        for (int i = 0; i < v.size(); i++) {
            v[i] %= hash_p[i];
            v[i] += (v[i] >> 63 & hash_p[i]);
        }
        return v;
    }

    // �����ϣ����
    struct VectorHash {
        size_t operator()(const vector<ll>& v) const {
            size_t seed = v.size();
            for (auto& i : v) {
                seed ^= i + 0x9e3779b9 + (seed << 6) + (seed >> 2);
            }
            return seed;
        }
    };

    // ������ȱȽϺ���
    struct VectorEqual {
        bool operator()(const vector<ll>& lhs, const vector<ll>& rhs) const {
            return lhs == rhs;
        }
    };

    umap<vector<ll>, tp, VectorHash, VectorEqual> hash_mp;

    void hash_init(int n) {
        hash_num = n;
    }

    template<typename T>
    vector<ll> tohash(const T obj) {
        vector<ll> lsans(hash_num);

        //�Զ���ṹ��
        //vector<unsigned char> bytes(sizeof(T));
        //memcpy(bytes.data(), &obj, sizeof(T));

        //����begin��end��stl
        vector<unsigned char> bytes(obj.begin(), obj.end());

        for (unsigned char& byte : bytes) {
            int t = hash_num;
            while (t--) {
                ((lsans[t] <<= 8) += byte) %= hash_p[t];
            }
        }

        //������
        //int t = hash_num;
        //while (t--) {
        //    ((lsans[t] = obj) %= hash_p[t];
        //}

        return lsans;
    }
}
