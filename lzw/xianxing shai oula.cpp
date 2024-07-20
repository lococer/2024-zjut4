#include<bits/stdc++.h>
typedef long long ll;
#define int ll
#define lp (p<<1)
#define rp (p<<1|1)
const int N = 2e5 + 100 , M = 2e5 + 100;
const int INF = 1e9,MOD = 998244353;
std::vector< int > pri;
int vis[ N + 100 ],phi[ N + 100 ];
void ini(){
    phi[ 1 ] = 1;
    for( int i = 2 ; i <= N ; i ++ ){
        if( !vis[ i ] ) {
            pri.push_back( i );
            phi[ i ] = i - 1;
        }
        for( auto j : pri ){
            if( j * i > N ) break;
            vis[ j * i ] = 1;
            if( i % j == 0 ) {
                phi[ i * j ] = j * phi[ i ];
                break;
            }else{
                phi[ i * j ] = ( j - 1 ) * phi[ i ];
            }
        }
    }
}
void solve(){
    ini();
    // for( auto i : pri ) std::cout<<i<<' ';std::cout<<'\n';   
    for( int i = 1 ; i <= 100 ; i ++ ){
        std::cout<<i <<' ' << phi[ i ]<<'\n';
    }
}


signed main(){
    std::ios::sync_with_stdio(0);std::cin.tie(0);std::cout.tie(0);
    // int t;std::cin>>t;
    // while(t--)
        solve();
}