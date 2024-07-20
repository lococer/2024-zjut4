#include<bits/stdc++.h>// O mlogn
typedef long long ll;
const int N = 5e5 + 100 ;
const int MOD = 1000003;
const int INF = 0x4f4f4f4f;
int n,m,s,dis[ N ],tot,head[ N ],vis[ N ];
struct Edge
{
    int to,w,next;  
};
Edge edge[ N ];
void add(int u ,int v , int w ){
    edge[ ++tot ].to = v;
    edge[ tot ].w = w;
    edge[ tot ].next = head[ u ];
    head[ u ] = tot;
}
void read(){
    std::cin>>n>>m;
    s=1;
    for( int i = 1 ; i <= m ; i ++ ){
        int u,v,w;std::cin>>u>>v;
        add(u,v,1);
        add(v,u,1);
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
        for( int i = head[ x ] ; i!= 0 ; i = edge[ i ].next ){
            int y = edge[ i ].to;
            if( vis[ y ] ) continue;
            if( dis[ x ] + edge[ i ].w < dis[ y ] ){
                dis[ y ] = dis[ x ] + edge[ i ].w;
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
