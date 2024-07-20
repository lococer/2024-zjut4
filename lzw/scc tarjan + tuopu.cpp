#include<bits/stdc++.h>
typedef long long ll;
const int N = 1e4 + 100 , M = 1e5 + 100;
const int INF = 1e9;
struct Edge{
    int to , next , w;
}e[ M ],E[ M ];
int head[ N ],Head[ N ],tot,w[ N ];
int n , m;
void add_e( int x , int y , int w ){
    e[ ++ tot ].to = y;
    e[ tot ].w = w;
    e[ tot ].next = head[ x ];
    head[ x ] = tot;
}
int dfn[ N ],low[ N ],scc[ N ],scccnt,dfncnt,ins[ N ],sccw[ N ];
std::stack< int > st;
void tarjan( int x ){
    dfn[ x ] = low[ x ] = ++dfncnt;
    st.push( x );
    ins[ x ] = 1;
    for( int i = head[ x ] ; i ; i = e[ i ].next ){
        int y = e[ i ].to;
        if( !dfn[ y ] ){
            tarjan( y );
            low[ x ] = std::min( low[ x ] , low[ y ] ); 
        }
        else{
            if( ins[ y ] ) low[ x ] = std::min( low[ x ] , dfn[ y ] );
        }
    }
    if( low[ x ] == dfn[ x ] ){
        int y ; ++scccnt;
        do{
            y = st.top();st.pop();
            ins[ y ] = 0;
            scc[ y ] = scccnt;
            sccw[ scc[ y ] ] += w[ y ];
        }while( y != x );
    }
}
int in[ N ],out[ N ],ans[ N ],vis[ N ],inq[ N ];
void add_E( int x , int y , int w ){
    E[ ++tot ].to = y;
    E[ tot ].w = w;
    E[ tot ].next = Head[ x ];
    Head[ x ] = tot;
}
void solve(){
    std::cin>>n>>m;
    for( int i = 1 ; i <= n ; i ++ ) std::cin>>w[ i ];
    for( int i = 1 ; i <= m ; i ++ ){
        int x , y;std::cin>>x>>y;
        add_e( x , y , 1 );
    }
    for( int i = 1 ; i <= n ; i ++ ){
        if( dfn[ i ] == 0 ) tarjan( i );
    }
    tot = 0;
    
    for( int x = 1 ; x <= n ; x ++ ){
        for( int i = head[ x ] ; i ; i = e[ i ].next ){
            int y = e[ i ].to;
            if( scc[ x ] != scc[ y ] ){
                add_E( scc[ x ] , scc[ y ] , 1 );
                in[ scc[ y ] ]++;
            }
        }
    }
    std::queue< int > q;
    for( int i = 1 ; i <= scccnt ; i ++ ){
        if( !in[ i ] ){
            ans[ i ] = sccw[ i ];
            q.push( i );
        }
    }
    while( !q.empty() ){
        int x = q.front();q.pop();
        for( int i = Head[ x ] ; i ; i = E[ i ].next ){
            int y = E[ i ].to;
            in[ y ] --;
            if( in[ y ] == 0 ) q.push( y );
            ans[ y ] = std::max( ans[ y ] , ans[ x ] + sccw[ y ] );
        }
    }
    int max = 0;
    for( int i = 1 ; i <= scccnt ; i ++ ){
        max = std::max( max , ans[ i ] );
    }
    std::cout<<max;
}
int main(){
    std::ios::sync_with_stdio(0);std::cin.tie(0);std::cout.tie(0);
    // ll t;std::cin>>t;
    // while( t-- )
    {
        solve();
    }
}