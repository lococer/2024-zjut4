#include<bits/stdc++.h>
typedef long long ll;
#define int ll
const int N = 2e5 + 100 , M = 2e5 + 100;
const int INF = 1e9,MOD = 998244353;
struct POINT{
    double x , y;
}point[ N ],st[ N ];
bool cmp( POINT x , POINT y ){
    if( x.x != y.x ) return x.x<y.x;
    return x.y<y.y;
}
double cross( POINT x , POINT y , POINT z ){
    double x1 = y.x - x.x , x2 = z.x - x.x;
    double y1 = y.y - x.y , y2 = z.y - x.y;
    return x1*y2 - y1*x2;
}
double dis( POINT x , POINT y ){
    return std::sqrt( pow( abs( x.x - y.x ) , 2 ) + pow( abs( x.y - y.y ) , 2 ) );
}
void solve(){
    int n;std::cin>>n;
    for( int i = 1 ; i <= n ; i ++ ){
        std::cin>>point[ i ].x>>point[ i ].y;
    }
    std::sort( point + 1 , point + 1 + n , cmp );
    int stp = 0;
    st[ ++stp ] = point[ 1 ];
    st[ ++stp ] = point[ 2 ];
    for( int i = 3 ; i <= n ; i ++ ){ // 下凸包
        while( stp >= 2 && cross( st[ stp-1 ] , st[ stp ] , point[ i ] ) < 0 ) stp--; // while
        st[ ++stp ] = point[ i ];
    }
    int t = stp;
    for( int i = n - 1 ; i >= 1 ; i -- ){ // 上凸包
        while( stp > t && cross( st[ stp-1 ] , st[ stp ] , point[ i ] ) < 0 ) // while
        stp--;
        st[ ++stp ] = point[ i ]; 
    }
    double cnt = 0;
    for( int i = 1 ; i < stp ; i ++ ){
        cnt += dis( st[ i ] , st[ i + 1 ] );
    }
    std::cout<<std::fixed<<std::setprecision(2)<<cnt<<'\n';
}


signed main(){
    std::ios::sync_with_stdio(0);std::cin.tie(0);std::cout.tie(0);
    // int t;std::cin>>t;
    // while(t--)
        solve();
}