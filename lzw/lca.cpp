#include <bits/stdc++.h>
typedef long long ll;
const int N = 5e5 + 100 , M = 5e5 + 100;
const int INF = 1e9;
const int MOD = 1;
int n,m,s;
struct{
    int to , next;
}e[ M * 2 ];
int head[ N ],tot;
void add_e( int x , int y ){
    e[ ++tot ].to = y;
    e[ tot ].next = head[ x ];
    head[ x ] = tot;
}
int fa[ N ][ 31 ];
int dep[ N ];
void dfs( int p , int f ){
    fa[ p ][ 0 ] = f;
    dep[ p ] = dep[ f ] + 1;
    for( int i = head[ p ] ; i ; i = e[ i ].next ){
        int y = e[ i ].to;
        if( y == f ) continue; 
        dfs( y , p );
    }
}
int lca( int x , int y ){
    if( dep[ x ] < dep[ y ] ) std::swap( x , y );//x是深的
    for( int i = 30 ; i >= 0 ; i -- ){
        if( dep[ fa[ x ][ i ] ] >= dep[ y ] ) x = fa[ x ][ i ];
    }
    if( x == y ) return x;
    for( int i = 30 ; i >= 0 ; i -- ){
        if( fa[ x ][ i ] != fa[ y ][ i ] ){
            x = fa[ x ][ i ];
            y = fa[ y ][ i ];
        }
    }
    return fa[ x ][ 0 ];
}
void solve(){
    std::cin>>n>>m>>s;
    for( int i = 1 ; i <= n - 1 ; i ++ ){
        int x , y;std::cin>>x>>y;
        add_e( y , x );add_e( x , y );
    }
    dep[ s ] = 1;
    dfs( s , 0 );
    for( int i = 1 ; i <= 30 ; i ++ ){
        for( int j = 1 ; j <= n ; j ++ ){
            fa[ j ][ i ] = fa[ fa[ j ][ i - 1 ] ][ i - 1 ];
        }
    }
    for( int i = 1 ; i <= m ; i ++ ){
        int x , y;std::cin>>x>>y;
        std::cout<<lca( x , y )<<'\n';
    }
    // for( int i = 1 ; i <= n ; i ++ ) std::cout<<fa[ i ][ 0 ]<<' ';
}
int main() {
    std::ios::sync_with_stdio(0);std::cin.tie(0);std::cout.tie(0);
    // ll t;std::cin>>t;
    // while( t-- )
    {
        solve();
    }
}