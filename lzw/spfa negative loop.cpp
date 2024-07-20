#include<bits/stdc++.h>
typedef long long ll;
const int N = 5e2 + 100 , M = 6e3 + 100;
const int MOD = 100003;
const int INF = 1e9;
struct{
    int to,w,next;
}e[ M ];
int head[ N ],tot;int n,m,w;
void add_e( int x , int y , int c ){
    e[ ++tot ].to = y;
    e[ tot ].w = c;
    e[ tot ].next = head[ x ];
    head[ x ] = tot;
}   
int vis[ N ],dis[ N ],cnt[ N ];
bool spfa(){
    memset( vis , 0 , sizeof( vis ) );
    memset( cnt , 0 , sizeof( cnt ) );
    for( int i = 1 ; i <= n ; i ++ ) dis[ i ] = INF;
    std::queue< int > q;
    q.push( 1 );
    dis[ 1 ] = 0;
    vis[ 1 ] = 1;
    while( !q.empty() ){
        int x = q.front();
        q.pop();
        vis[ x ] = 0;
        for( int i = head[ x ] ; i != 0 ; i = e[ i ].next ){
            int y = e[ i ].to;
            if( dis[ x ] + e[ i ].w < dis[ y ] ){
                dis[ y ] = dis[ x ] + e[ i ].w;
                if( !vis[ y ] ){
                    vis[ y ] = 1;
                    cnt[ y ] ++;
                    q.push( y );
                    if( cnt[ y ] > n ) return true;
                }
            }
        }
    }
    return false;
}
void solve(){
    tot=0;
    memset( head , 0 , sizeof( head ) );
    memset( e , 0 , sizeof( e ) );
    std::cin>>n>>m;
    for( int i = 1 ; i <= m; i ++ ){
        int x,y,c;std::cin>>x>>y>>c;
            add_e( x , y , c ); //有向图
            // add_e( y , x , c ); // 无向图
    }

    if( spfa() ) std::cout<<"YES\n";
    else std::cout<<"NO\n";
}
int main(){
    std::ios::sync_with_stdio(0);std::cin.tie(0);std::cout.tie(0);
    // ll t;std::cin>>t;
    // while( t-- )
        solve();
}