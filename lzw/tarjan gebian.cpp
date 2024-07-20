/*
    说明：求带重边的无向图割边
*/

#include <bits/stdc++.h>
typedef long long ll;
const int N = 1+ 100 , M = 1 + 100;
const int INF = 1e9;
const int MOD = 1;
int n,m;
struct{
    int to,next,num;
}e[ M ];
int head[ N ],tot;
void add_e( int x , int y ){
    e[ ++tot ].to = y;
    e[ tot ].next = head[ x ];
    head[ x ] = tot;
    e[ tot ].num = tot;
}
int dfn[ N ],dfncnt,low[ N ];
std::vector< std::pair< int , int > > bri;
void tarjan( int x , int fa ){
    dfn[ x ] = low[ x ] = ++dfncnt;
    int facnt = 0;//判断重边
    for( int i = head[ x ] ; i ;i = e[ i ].next ){
        int y = e[ i ].to;
        if( !dfn[ y ] ){
            tarjan( y , x );
            low[ x ] = std::min( low[ x ] , low[ y ] );
            if( low[ y ] > dfn[ x ] ){
                bri.push_back( { x , y } );
            }
        }
        else{
            if( y != fa || facnt++ ) low[ x ] = std::min( low[ x ] , dfn[ y ] );
        }
    }
}
void solve(){
    std::cin>>n>>m;
    for( int i = 1 ; i <= m ; i ++ ){
        int x , y ;std::cin>>x>>y;
        add_e( x , y );
        add_e( y , x );
    }

    for( int i = 1 ; i <= n ; i ++ ){
        if( !dfn[ i ] ){
            tarjan( i , i );
        }
    }

    for( auto i : bri ) std::cout<<i.first<<' '<<i.second<<'\n';
}
int main() {
    std::ios::sync_with_stdio(0);std::cin.tie(0);std::cout.tie(0);
    // ll t;std::cin>>t;
    // while( t-- )
    {
        solve();
    }
}