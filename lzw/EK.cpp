#include<bits/stdc++.h>
typedef long long ll;
#define int ll
const int N = 2e5 + 100 , M = 2e5 + 100;
const int INF = 1e9,MOD = 998244353;
int n , m , s , t;
struct{
    int to , next , w;
}e[ M << 1 ];
int head[ N ],tot = 1;
void add_e( int x , int y , int w ){
    e[ ++tot ].to = y;
    e[ tot ].w = w;
    e[ tot ].next = head[ x ];
    head[ x ] = tot;
}
int mf[ N ],pre[ N ];
bool bfs(){
    for( int i = 1 ; i <= n ; i ++ ) mf[ i ] = 0;
    std::queue< int > q;
    q.push( s );mf[ s ] = INF;
    while( q.size() ){
        int x = q.front();q.pop();
        for( int i = head[ x ] ; i ; i = e[ i ].next ){
            int y = e[ i ].to;
            if( mf[ y ] || e[ i ].w == 0 ) continue;
            mf[ y ] = std::min( mf[ x ] , e[ i ].w );
            q.push( y );
            pre[ y ] = i;
            if( y == t ) return 1;

        }
    }
    return 0;
}
int EK(){
    int MF = 0;
    while( bfs() ){
        int p = t;
        MF += mf[ t ];
        while( p != s ){
            int edge = pre[ p ];
            e[ edge ].w -= mf[ t ];
            e[ edge ^ 1 ].w += mf[ t ];
            p = e[ p ^ 1 ].to;
        }
    }
    return MF;
}
void solve(){
    std::cin>>n>>m>>s>>t;
    for( int i = 1 ; i <= m ; i ++ ){
        int x , y , w;
        std::cin>>x>>y>>w;
        add_e( x , y , w );
        add_e( y , x , 0 );
    }
    std::cout<<EK()<<'\n';
}


signed main(){
    std::ios::sync_with_stdio(0);std::cin.tie(0);std::cout.tie(0);
    // int t;std::cin>>t;
    // while(t--)
        solve();
}