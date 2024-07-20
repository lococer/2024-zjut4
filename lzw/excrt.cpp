#include<bits/stdc++.h>
typedef long long ll;
#define int ll
const int N = 2e5 + 100;
const int MOD = 998244353;
int mod[ N ],ANS[ N ];
int n;
ll qmul( ll x , ll p , ll mo ){
    ll ans = 0;
    while( p ){
        if( p & 1 ) ans = (ans + x) % mo;
        x = ( x + x ) % mo;
        p >>= 1;
    }
    return ans;
}
ll exgcd( ll A , ll B , ll &x , ll&y ){
    if( B == 0 ){ x = 1 ; y = 0 ; return A ;}
    int tx , ty;
    int gcd = exgcd( B , A % B , tx , ty );
    x = ty;
    y = tx - (A/B)*ty;
    return gcd;
}
void solve(){
    std::cin>>n;
    for( int i = 1 ; i <= n ; i ++ ){
        std::cin>>mod[ i ]>>ANS[ i ];
    }
    for( int i = 2 ; i <= n ; i ++ ){
        int A = mod[ 1 ] , B = mod[ i ] , C = ANS[ i ] - ANS[ 1 ];
        C = ( C % B + B ) % B;
        int x , y;
        int gcd = exgcd( A , B , x , y );
        x = qmul( x , C / gcd , B );
        // x = x * ( C / gcd );
        x = ( x % B + B ) % B;
        ANS[ 1 ] = ANS[ 1 ] + qmul( mod[ 1 ] , x , mod[ 1 ] * ( mod[ i ] / gcd ) );
        // ANS[ 1 ] = ANS[ 1 ] + mod[ 1 ] * x;
        mod[ 1 ] = mod[ 1 ] * ( mod[ i ] / gcd );
        ANS[ 1 ] = ( ANS[ 1 ] % mod[ 1 ] + mod[ 1 ] ) % mod[ 1 ];
    }
    std::cout<<ANS[ 1 ]<<'\n';
}

signed main(){
    std::ios::sync_with_stdio(0);std::cin.tie(0);std::cout.tie(0);
    // int t;std::cin>>t;
    // while( t-- )
        solve();
}