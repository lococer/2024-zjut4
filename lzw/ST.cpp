 #include<iostream>
#include<cmath>
typedef long long ll; 
const int N = 1e4 + 100 , M = 5e5 +100;
const int MOD = 998244353;
const int INF = 1e9;
int n,a[ N ];
int ST[ N ][ 21 ];
void ST_prework(){
    for( int i = 1 ; i <= n ; i ++ ){
        ST[ i ][ 0 ] = a[ i ];
    }
    int t = log( n ) / log( 2 ) + 1 ;
    for( int j = 1 ; j < t ; j ++ ){
        for( int i = 1 ; i <= n - ( 1 << j ) + 1 ; i ++ ){
            ST[ i ][ j ] = std::max( ST[ i ][ j - 1 ] , ST[ i + (1<<(j-1)) ][ j - 1 ] );
        }
    }
}
int ST_query( int l , int r ){
    int k = log( r - l + 1 ) / log( 2 );
    return std::max( ST[ l ][ k ] , ST[ r - ( 1 << k ) + 1 ][ k ] );
}
void solve(){
    std::cin>>n;
    for( int i = 1 ; i <= n ; i ++ ) std::cin>>a[ i ];
    ST_prework();
    int l , r; std::cin>>l>>r;
    std::cout<<ST_query( l , r );
}
int main(){
    std::ios::sync_with_stdio(0);std::cin.tie(0);std::cout.tie(0);
    // ll t;std::cin>>t;
    // while( t-- )
    {
        solve();
    }
}