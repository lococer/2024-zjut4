#include<bits/stdc++.h>
typedef long long ll;
const int N = 1e5 + 100 , M = 5e2 + 100;
const int INF = 1e9;
ll t;
void read(){
    std::cin>>t;
}
ll inv( ll a , ll p , ll mod){
    ll ans = 1;
    while( p ){
        if( p & 1 ){
            ans = ans * a % mod;
        }
        a *= a;
        a %= mod;
        p>>=1;
    }
    return ans;
}
ll fact[ 2 * N ];
ll C( ll n , ll m , ll p ){
    // return m < n ? 0 : fact[m] * inv[fact[n], p] % p * inv[fact[m - n], p] % p;
    if( n > m ) return 0;
    return (fact[ m ] * inv( fact[ n ] , p - 2 , p ) % p * inv( fact[ m - n ] , p - 2 , p)) % p;
}
ll lucas( ll n , ll m , ll p ){
    // return n == 0 ? 1 % p : lucas(m / p, n / p, p) * C(m % p, n % p, p) % p;
    if( n == 0 ) return 1;
    return lucas( n / p , m / p , p ) * C( n % p , m % p , p ) % p;
}
void solve(){
    ll n , m , p;
    for( ll j = 1 ; j <= t ; j ++ ){
        std::cin>>n>>m>>p;
        fact[ 0 ] = 1;
        for( ll i = 1 ; i <= n + m ; i ++ ){
            fact[ i ] = (fact[ i - 1 ] * i) % p ; 
        }
        std::cout<<lucas( n , m + n , p )<<'\n';
    }
}
int main(){
    std::ios::sync_with_stdio(0);std::cin.tie(0);std::cout.tie(0);
    // ll t;std::cin>>t;
    // while( t-- )
    {
        read();
        solve();
    }
}   