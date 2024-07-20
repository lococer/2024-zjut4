#include<bits/stdc++.h>
typedef long long ll;
const int N = 1e4 + 100 , M = 5e4 + 100;
const int INF = 1e9;
struct Edge
{
    int to,next;
}e[ M ];
int tot,head[ N ];
int n,m;
void add_edge( int x , int y ){
    e[ ++tot ].to = y;
    e[ tot ].next = head[ x ];
    head[ x ] = tot;
}
int dfn[ N ],low[ N ],dfnnum;
std::stack< int > st;
int ins[ N ],scc[ N ],scccnt,size[ N ];
void tarjan( int x ){
    st.push( x );
    ins[ x ] = 1;
    dfn[ x ] = low[ x ] = ++dfnnum;
    for( int i = head[ x ] ; i ; i = e[ i ].next ){
        int y = e[ i ].to;
        if( !dfn[ y ] ){
            tarjan( y );
            low[ x ] = std::min( low[ x ] , low[ y ] );
        }
        else{
            if( ins[ y ] )  low[ x ] = std::min( low[ x ] , dfn[ y ] );
        }
    }

    if( dfn[ x ] == low[ x ] ){
       int y ; ++scccnt;
       do{
            y = st.top();ins[ y ] = 0;
            st.pop();
            scc[ y ] = scccnt;
            size[ scccnt ]++;
       }while( x != y );
    }

}
void solve(){
    std::cin>>n>>m;
    for( int i = 1 ; i <= m ; i ++ ){
        int x , y;std::cin>>x>>y;
        add_edge( x , y );
    }
    for( int i = 1 ; i <= n ; i ++ ){
        if( !dfn[ i ] ) tarjan( i );
    }
    int ans = 0;
    for( int i = 1 ; i <= scccnt ; i ++ ){
        if( size[ i ] > 1 ) ans++;
    }
    std::cout<<ans;
}
int main(){
    std::ios::sync_with_stdio(0);std::cin.tie(0);std::cout.tie(0);
    // ll t;std::cin>>t;
    // while( t-- )
    {
        solve();
    }
}