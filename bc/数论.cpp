namespace my_math {

    tp gcd(tp a, tp b) {
        if (a < b) {
            swap(a, b);
        }
        while (b) {
            a %= b;
            swap(a, b);
        }
        return a;
    }

    inline tp exgcd(const tp a, const tp b, tp& x, tp& y) {
        if (b == 0) return x = 1, y = 0, a;
        tp d = exgcd(b, a % b, y, x);
        y -= a / b * x; return d;
    }

    tp ksm(tp a, tp b, tp p) {
        tp lsans = 1;
        while (b) {
            if (b & 1ll) {
                lsans = ((__int128)lsans * a) % p;
            }
            a = ((__int128)a * a) % p;
            b >>= 1;
        }
        return lsans;
    }

    inline tp inv(tp a, tp p) {
        return ksm(a, p - 2, p);
    }

    inline tp mul(tp a, tp b, const tp MOD) {
        tp Ret = 0;
        while (b) {
            if (b & 1) Ret = (Ret + a) % MOD;
            a = (a + a) % MOD, b >>= 1;
        }
        return Ret;
    }

    inline tp excrt(vector<tp>& p, vector<tp>& r, const int n) {
        tp m = 1, t = 0, k = 0, s = 0, x, y, ap = p[1], ar = r[1];

        for (int i = 2; i <= n; ++i) {
            t = exgcd(ap, p[i], x, y), s = ((r[i] - ar) % p[i] + p[i]) % p[i];
            if (s % t) return -1;
            m = s / t, k = p[i] / t, x = mul(x, m, k), y = mul(y, m, k);
            ar = ((ar + x * ap) % (ap * k) + ap * k) % (ap * k), ap = ap * k;
        }

        return (ar % ap + ap) % ap;
    }

    void prime_init(tp n, vector<tp>& prime) {
        vector<tp>not_prime(n + 5);
        for (int i = 2; i <= n; ++i) {
            if (!not_prime[i]) {
                prime.push_back(i);
            }
            for (int pri_j : prime) {
                if (i * pri_j > n) break;
                not_prime[i * pri_j] = true;
                if (i % pri_j == 0) {
                    break;
                }
            }
        }
    }

    void inv_init(tp n, vector<tp>& inv, tp p) {
        inv = vector<tp>(n + 5);
        inv[1] = 1;
        for (tp i = 2; i <= n; ++i) {
            inv[i] = (p - p / i) * inv[p % i] % p;
        }
    }

    inline tp qm(tp x, tp y) {//�����xҪ������(-y,y)֮�䣬����λ����λ�ƣ�intΪ31,llΪ63
        return x + (x >> 63 & y);
    }

    bool Miller_Rabin(long long p) {  // �ж�����
        if (p < 2) return 0;
        if (p == 2) return 1;
        if (p == 3) return 1;
        long long d = p - 1, r = 0;
        while (!(d & 1)) ++r, d >>= 1;  // ��d����Ϊ����
        //vector<tp>test = { 2,7,61 };//[1,2^32)
        vector<tp>test = { 2,325,9375,28178,450775,9780504,1795265022 };//[1,2^64)
        for (long long k = 0; k < test.size(); ++k) {
            long long a = test[k] % (p - 2) + 2;
            long long x = ksm(a, d, p);
            if (x == 1 || x == p - 1) continue;
            for (int i = 0; i < r - 1; ++i) {
                x = (__int128)x * x % p;
                if (x == p - 1) break;
            }
            if (x != p - 1) return 0;
        }
        return 1;
    }

    ll Pollard_Rho(ll x) {
        ll s = 0, t = 0;
        ll c = (ll)rand() % (x - 1) + 1;
        int step = 0, goal = 1;
        ll val = 1;
        for (goal = 1;; goal *= 2, s = t, val = 1) {  // �����Ż�
            for (step = 1; step <= goal; ++step) {
                t = ((__int128)t * t + c) % x;
                val = (__int128)val * abs(t - s) % x;
                if ((step % 127) == 0) {
                    long long d = gcd(val, x);
                    if (d > 1) return d;
                }
            }
            long long d = gcd(val, x);
            if (d > 1) return d;
        }
    }

    void find_prime_factor(set<tp>& s, tp x) {//����Щ��������
        if (x < 2) {
            return;
        }
        if (Miller_Rabin(x)) {              // ���xΪ����
            s.insert(x);
            return;
        }
        ll p = x;
        while (p >= x) p = Pollard_Rho(x);  // ʹ�ø��㷨
        while ((x % p) == 0) x /= p;
        find_prime_factor(s, x), find_prime_factor(s, p);  // �������·ֽ�x��p
    }

    void get_prime_factor(map<tp, tp>& mp, tp x) {
        set<tp>s;
        find_prime_factor(s, x);
        for (auto it : s) {
            while (x % it == 0) {
                mp[it]++;
                x /= it;
            }
        }
    }

    tp euler_phi(tp n) {
        tp ans = n;
        for (tp i = 2; i * i <= n; i++) {
            if (n % i == 0) {
                ans = ans / i * (i - 1);
                while (n % i == 0) n /= i;
            }
        }
        if (n > 1) ans = ans / n * (n - 1);
        return ans;
    }

    tp get_g(tp n) {
        tp g = 0;
        tp phi = euler_phi(n);
        set<tp>s;
        find_prime_factor(s, phi);
        for (tp i = 1;; i++) {
            bool flag = 1;
            if (__gcd(i, n) != 1)continue;
            for (auto& j : s) {
                if (ksm(i, phi / j, n) == 1) {
                    flag = 0;
                    break;
                }
            }
            if (flag) {
                g = i;
                break;
            }
        }
        return g;
    }
}
