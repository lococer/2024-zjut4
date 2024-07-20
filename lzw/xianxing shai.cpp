#include<bits/stdc++.h>
typedef long long ll;
#define int ll
#define lp (p<<1)
#define rp (p<<1|1)
const int N = 2e5 + 100 , M = 2e5 + 100;
const int INF = 1e9,MOD = 998244353;
std::vector< int > pri;
int vis[ N + 100 ];
void ini(){
    for( int i = 2 ; i <= N ; i ++ ){
        if( !vis[ i ] ) pri.push_back( i );
        for( auto j : pri ){
            if( j * i > N ) break;
            vis[ j * i ] = 1;
            if( i % j == 0 ) break;
        }
    }
}
void solve(){
    ini();
    for( auto i : pri ) std::cout<<i<<' ';std::cout<<'\n';   
}


signed main(){
    std::ios::sync_with_stdio(0);std::cin.tie(0);std::cout.tie(0);
    // int t;std::cin>>t;
    // while(t--)
        solve();
}