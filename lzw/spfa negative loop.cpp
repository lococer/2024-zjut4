#include<bits/stdc++.h>
typedef long long ll;
const int N = 5e2 + 100 , M = 6e3 + 100;
const int MOD = 100003;
const int INF = 1e9;
struct gra{
    struct data{ int to,next,w; };
    std::vector<int> head;
    std::vector<data> e;
    int tot;
    void ini( int n ){
        head.clear();e.clear();
        head.resize(n+1); e.resize(1);
        tot = 0;
    }
    void add_e( int x, int y, int w = 1 ){
        e.push_back({y,head[x],w});
        head[x]=++tot;
    }
}g;

int n,m;
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
        for( int i = g.head[ x ] ; i != 0 ; i = g.e[ i ].next ){
            int y = g.e[ i ].to;
            if( dis[ x ] + g.e[ i ].w < dis[ y ] ){
                dis[ y ] = dis[ x ] + g.e[ i ].w;
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
    std::cin>>n>>m;
    g.ini( n );
    for( int i = 1 ; i <= m; i ++ ){
        int x,y,c;std::cin>>x>>y>>c;
            g.add_e( x , y , c ); //有向图
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