#include<bits/stdc++.h>// O mlogn
typedef long long ll;
const int N = 5e5 + 100 ;
const int MOD = 1000003;
const int INF = 0x4f4f4f4f;
int n,m,s,dis[ N ],tot,head[ N ],vis[ N ];
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
void read(){
    std::cin>>n>>m;
    g.ini( n );
    s=1;
    for( int i = 1 ; i <= m ; i ++ ){
        int u,v,w;std::cin>>u>>v;
        g.add_e(u,v,1);
        g.add_e(v,u,1);
    }
}
std::priority_queue< std::pair< int , int > > q;//维护待遍历的节点的最短路径与节点编号
void solve(){
    std::memset( dis , 0x4f , sizeof( dis ) );
    dis[ s ] = 0;
    q.push( std::make_pair( 0 , s ) );//压初始节点
    while(!q.empty()){
        while( !q.empty() && (-q.top().first) > dis[ q.top().second] ) q.pop();//之前维护的信息过时
        if( q.empty() ) break;
        int x = q.top().second;
        q.pop();
        vis[ x ] = 1;
        for( int i = g.head[ x ] ; i ; i = g.e[ i ].next ){
            int y = g.e[ i ].to;
            if( vis[ y ] ) continue;
            if( dis[ x ] + g.e[ i ].w < dis[ y ] ){
                dis[ y ] = dis[ x ] + g.e[ i ].w;
                q.push(std::make_pair( -dis[ y ] , y) );
            }
        }
    }
}
void print(){
    for( int i = 1 ; i <= n ; i ++ ){
        if( dis[ i ] == INF ) std::cout<<((1<<31)-1)<<' ';
        else    std::cout<<dis[ i ]<<' ';
    }
}
int main(){
    std::ios::sync_with_stdio(0);std::cin.tie(0);std::cout.tie(0);
    // ll t;std::cin>>t;
    // while( t-- )
    {
        read();
        solve();
        print();
    }
}
