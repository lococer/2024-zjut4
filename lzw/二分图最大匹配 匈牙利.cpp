#include <bits/stdc++.h>
typedef long long ll;
const int N = 1e3 + 100 , M = 5e4 + 100;
const int INF = 1e9;
const int MOD = 1;
int e,n,m;
struct Edge{
    int to,next;
}E[ M ];
int tot,head[ N ];
void add_E( int x , int y ){
    E[ ++tot ].to = y;
    E[ tot ].next = head[ x ];
    head[ x ] = tot;
}
int vis[ N ],match[ N ];
bool dfs( int x ){
    for( int i = head[ x ] ; i ; i = E[ i ].next ){
        int y = E[ i ].to;
        if( vis[ y ] ) continue;
        vis[ y ] = 1;
        if( !match[ y ] || dfs( match[ y ] ) ){
            match[ y ] = x;
            return 1;
        }
    }
    return 0;
}
int ans = 0;
void solve(){
    std::cin>>n>>m>>e;
    for( int i = 1 ; i <= e ; i ++ ){
        int x , y;std::cin>>x>>y;
        add_E( x , y );
    }
    for( int i = 1 ; i <= n ; i ++ ){
        memset( vis , 0 , sizeof( vis ) );
        if( dfs( i ) ) ans++;
    }
    std::cout<<ans;
}
int main() {
    std::ios::sync_with_stdio(0);std::cin.tie(0);std::cout.tie(0);
    // ll t;std::cin>>t;
    // while( t-- )
    {
        solve();
    }
}