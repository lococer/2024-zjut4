#include <bits/stdc++.h>

using namespace std;
using ll=long long;

class shash {
public:
	vector<ll> pres;
	vector<ll> epow;
	ll e, p;

	shash(string& s, ll e, ll p) {
		int n = s.size();
		this->e = e;
		this->p = p;
		pres = vector<ll>(n + 1);
		epow = vector<ll>(n + 1);
		epow[0] = 1;
		for (int i = 0; i < n; i++) {
			pres[i + 1] = (pres[i] * e + s[i]) % p;
			epow[i + 1] = (epow[i] * e) % p;
		}
	}

	ll operator()(int l, int r) {
		ll res = (pres[r + 1] - pres[l] * epow[r - l + 1] % p) % p;
		return (res + p) % p;
	}
};

int main(){
    string s ="0000";
    shash ss(s , 1331 , 1E9 + 7);
    cout << ss(0 , 1) << "\n";
}