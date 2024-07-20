#include<bits/stdc++.h>
typedef long long ll;
const int N = 2e4 + 100 , M = 1e5 + 100;
const int INF = 1e9;
struct Edge{
    int to,next;
}e[ M * 2 ];
int tot,head[ N ];
int n,m;
void add_e( int x , int y ){
    e[ ++ tot ].to = y;
    e[ tot ].next = head[ x ];
    head[ x ] = tot;
}
int low[ N ],dfn[ N ],dfncnt,cut[ N ],root,ans;
void tarjan( int x ){
    low[ x ] = dfn[ x ] = ++dfncnt;
    int child = 0;
    for( int i = head[ x ] ; i ; i = e[ i ].next ){
        int y = e[ i ].to;
        if( !dfn[ y ] ){
            tarjan( y );
            low[ x ] = std::min( low[ x ] , low[ y ] );
            if( low[ y ] >= dfn[ x ] ){
                child++;
                if( x != root || child > 1 ){
                    cut[ x ] = 1;
                }
            }
        }
        else{
            low[ x ] = std::min( low[ x ] , dfn[ y ] );
        }
    }
}
void solve(){
    std::cin>>n>>m;
    for( int i = 1 ; i <= m ; i ++ ){
        int x , y;std::cin>>x>>y;
        if( x == y ) continue;
        add_e( x , y );
        add_e( y , x );
    }
    for( int i = 1 ; i <= n ; i ++ ){
        if( !dfn[ i ] ) {
            root = i;
            tarjan( i );
        }
    }
    for( int i = 1 ; i <= n ; i ++ ) ans += cut[ i ];
    std::cout<<ans<<'\n';
    for( int i = 1 ; i <= n ; i ++ ){
        if( cut[ i ] ) std::cout<<i<<' ';
    }
}
int main(){
    std::ios::sync_with_stdio(0);std::cin.tie(0);std::cout.tie(0);
    // ll t;std::cin>>t;
    // while( t-- )
    {
        solve();
    }
}