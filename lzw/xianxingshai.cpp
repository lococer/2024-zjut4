#include<bits/stdc++.h>
typedef long long ll;
#define int ll
#define lp (p<<1)
#define rp (p<<1|1)
const int N = 2e5 + 100 , M = 2e5 + 100;
const int INF = 1e18,MOD = 998244353;
ll qpow(ll x,ll p){ll res=1;while(p){if(p&1)res=res*x%MOD;x=x*x%MOD;p>>=1;}return res;}
ll inv(ll x){return qpow(x,MOD-2);}
std::vector<int> prime;
bool isprime[N];
void getp(){
    for(int i=2;i<=N;i++){
        if( !isprime[i] ) prime.push_back(i);
        for( auto j : prime ){
            if( j * i > N ) break;
            isprime[ j * i ] = 1;
            if( i % j == 0 ) break;
        }
    }
}
void solve(){
    
}
signed main(){
    std::ios::sync_with_stdio(0);std::cin.tie(0);std::cout.tie(0);
    int t;std::cin>>t;
    while(t--)
        solve();
}