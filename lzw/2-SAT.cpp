#include <bits/stdc++.h>
typedef long long ll;
const int N = 2e6 + 100 , M = 1e6 + 100;
const int INF = 1e9;
const int MOD = 1;
int n,m;
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
int dfn[ N ],scc[ N ],dfncnt,scccnt,low[ N ],ins[ N ];
std::stack< int > st;
void tarjan( int x ){
    dfn[ x ] = low[ x ] = ++dfncnt;
    ins[ x ] = 1;
    st.push( x );
    for( int i = g.head[ x ] ; i ; i = g.e[ i ].next ){
        int y = g.e[ i ].to;
        if( !dfn[ y ] ){
            tarjan( y );
            low[ x ] = std::min( low[ x ] , low[ y ] );
        }
        else{
            if( ins[ y ] ) low[ x ] = std::min( low[ x ] , dfn[ y ] );
        }
    }

    if( dfn[ x ] == low[ x ] ){
        int y;++scccnt;
        do{
            y = st.top();st.pop();
            ins[ y ] = 0;
            scc[ y ] = scccnt;
        }while( x != y );
    }
}
void solve(){
    std::cin>>n>>m;
    g.ini( n << 1 );
    for( int i = 1 ; i <= m ; i ++ ){
        int a,b,x,y;std::cin>>a>>x>>b>>y;
        if( x == 1 && y == 1 ){
            g.add_e( a + n , b );
            g.add_e( b + n , a );
        }
        if( x == 0 && y == 1 ){
            g.add_e( a , b );
            g.add_e( b + n , a + n );
        }
        if( x == 1 && y == 0 ){
            g.add_e( a + n , b + n );
            g.add_e( b , a );
        }
        if( x == 0 && y == 0 ){
            g.add_e( a , b + n );
            g.add_e( b , a + n );
        }
    }   
    for( int i = 1 ; i <= n * 2 ; i ++ ){
        if( dfn[ i ] == 0 ) tarjan( i );
    }
    for( int i = 1 ; i <= n ; i ++ ){
        if( scc[ i ] == scc[ i + n ] ){
            std::cout<<"IMPOSSIBLE\n";
            return;
        }
    } 
    std::cout<<"POSSIBLE\n";
    for( int i = 1 ; i <= n ; i ++ ){
        std::cout<<(scc[ i ] < scc[ i + n ])<<' ';
    }
}
int main() {
    std::ios::sync_with_stdio(0);std::cin.tie(0);std::cout.tie(0);
    // ll t;std::cin>>t;
    // while( t-- )
    {
        solve();
    }
}