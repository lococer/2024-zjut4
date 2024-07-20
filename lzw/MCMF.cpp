#include<bits/stdc++.h>
typedef long long ll;
#define int ll
const int N =  5e4 + 100 , M = 5e4 + 100;
const int INF = 1e9,MOD = 998244353;
int n , m , S , T;
struct{
    int to , next , w , c;
}e[ M << 1 ];
int head[ N ],tot = 1;
void add_e( int x , int y , int w , int c){
    e[ ++tot ].to = y;
    e[ tot ].w = w;
    e[ tot ].c = c;
    e[ tot ].next = head[ x ];
    head[ x ] = tot;
}
int mf[ N ],pre[ N ];
int dis[ N ],vis[ N ];
bool spfa(){
    for( int i = S ; i <= T ; i ++ ){ 
        mf[ i ] = vis[ i ] = 0;
        dis[ i ] = INF;
    }
    std::queue< int > q;q.push( S );
    dis[ S ] = 0;vis[ S ] = 1;mf[ S ] = INF;
    while( !q.empty() ){
        int x = q.front();q.pop();
        vis[ x ] = 0;
        for( int i = head[ x ] ; i != 0 ; i = e[ i ].next ){
            int y = e[ i ].to;
            if( dis[ x ] + e[ i ].c < dis[ y ] && e[ i ].w ){
                dis[ y ] = dis[ x ] + e[ i ].c;
                mf[ y ] = std::min( mf[ x ] , e[ i ].w );
                pre[ y ] = i;
                if( !vis[ y ] ){
                    vis[ y ] = 1;
                    q.push( y );
                }
            }
        }
    }
    return mf[ T ] > 0;
}
int MF , MC;
void EK(){
    while( spfa() ){
        int p = T;
        MF += mf[ T ];
        MC += dis[ T ] * mf[ T ];
        while( p != S ){
            int i = pre[ p ];
            e[ i ].w -= mf[ T ];
            e[ i ^ 1 ].w += mf[ T ];
            p = e[ i ^ 1 ].to;
        }
    }
}
void solve(){
    std::cin>>n>>m>>S>>T;
    for( int i = 1 ; i <= m ; i ++ ){
        int x , y , w , c ;
        std::cin>>x>>y>>w>>c;
        add_e( x , y , w , c );
        add_e( y , x , 0 , -c );
    }
    EK();
    std::cout<<MF<<' '<<MC<<'\n';
}


signed main(){
    std::ios::sync_with_stdio(0);std::cin.tie(0);std::cout.tie(0);
    // int t;std::cin>>t;
    // while(t--)
        solve();
}