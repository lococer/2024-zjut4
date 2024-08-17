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

    inline tp qm(tp x, tp y) {//导入的x要控制在(-y,y)之间，根据位数改位移，int为31,ll为63
        return x + (x >> 63 & y);
    }

    bool Miller_Rabin(long long p) {  // 判断素数
        if (p < 2) return 0;
        if (p == 2) return 1;
        if (p == 3) return 1;
        long long d = p - 1, r = 0;
        while (!(d & 1)) ++r, d >>= 1;  // 将d处理为奇数
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
        for (goal = 1;; goal *= 2, s = t, val = 1) {  // 倍增优化
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

    void find_prime_factor(set<tp>& s, tp x) {//找哪些是其素数
        if (x < 2) {
            return;
        }
        if (Miller_Rabin(x)) {              // 如果x为质数
            s.insert(x);
            return;
        }
        ll p = x;
        while (p >= x) p = Pollard_Rho(x);  // 使用该算法
        while ((x % p) == 0) x /= p;
        find_prime_factor(s, x), find_prime_factor(s, p);  // 继续向下分解x和p
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

}

