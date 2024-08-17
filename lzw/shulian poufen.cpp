#include<bits/stdc++.h>
typedef long long ll;
#define int ll
#define lp (p<<1)
#define rp (p<<1|1)
const int N = 1e5 + 100 , M = 1e5 + 100;
const int INF = 1e9,MOD = 998244353;
int a[ N ],n,m,r,P;
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

int top[ N ],son[ N ],dfn[ N ],dfncnt,dep[ N ],fa[ N ],siz[ N ],rdfn[ N ];
void dfs1( int x , int f ){
    siz[ x ] = 1;
    int maxsiz = 0;
    for( int i = g.head[ x ] ; i ; i = g.e[ i ].next ){
        int y = g.e[ i ].to;
        if( y == f || siz[ y ] ) continue;
        fa[ y ] = x;
        dep[ y ] = dep[ x ] + 1;
        dfs1( y , x );
        siz[ x ] += siz[ y ];
        if( siz[ y ] > maxsiz ){
            maxsiz = siz[ y ];
            son[ x ] = y;
        }
    }
}
void dfs2( int x , int t ){
    dfn[ x ] = ++dfncnt;
    rdfn[ dfncnt ] = x;
    top[ x ] = t;
    if( son[ x ] == 0 ) return;
    dfs2( son[ x ] , t );
    for( int i = g.head[ x ] ; i ; i = g.e[ i ].next ){
        int y = g.e[ i ].to;
        if( dfn[ y ] || y == son[ x ] ) continue;
        else dfs2( y , y );
    }
}
struct{
    int l , r , sum;
    int lazy;
}tr[ N << 2 ];
void build( int l , int r , int p ){
    tr[ p ].l = l;tr[ p ].r = r;
    if( l == r ){
        tr[ p ].sum = a[ rdfn[ l ] ] % P;
        return;
    }
    int mid = ( l + r ) >> 1;
    build( l , mid , lp );
    build( mid + 1 , r , rp );
    tr[ p ].sum = (tr[ lp ].sum + tr[ rp ].sum) % P;
}
void pushdown( int p ){
    if( tr[ p ].lazy ){
        int t = tr[ p ].lazy % P;
        tr[ p ].lazy = 0;
        tr[ lp ].sum += ( tr[ lp ].r - tr[ lp ].l + 1 ) * t % P;
        tr[ rp ].sum += ( tr[ rp ].r - tr[ rp ].l + 1 ) * t % P;
        tr[ lp ].sum %= P;
        tr[ rp ].sum %= P;
        tr[ lp ].lazy += t;
        tr[ rp ].lazy += t;
    }
}
void change( int l , int r , int p , int x ){
    if( tr[ p ].l >= l && tr[ p ].r <= r ){
        tr[ p ].lazy += x;
        tr[ p ].sum += ( tr[ p ].r - tr[ p ].l + 1 ) * x % P;
        tr[ p ].sum %= P;
        return;
    }
    pushdown( p );
    int mid = ( tr[ p ].l + tr[ p ].r ) >> 1;
    if( l <= mid ) change( l , r , lp , x );
    if( r > mid ) change( l , r , rp , x );
    tr[ p ].sum = tr[ lp ].sum + tr[ rp ].sum;
    tr[ p ].sum %= P;
}
int query( int l , int r , int p ){
    if( tr[ p ].l >= l && tr[ p ].r <= r ){
        return tr[ p ].sum;
    }
    pushdown( p );
    int mid = ( tr[ p ].l + tr[ p ].r ) >> 1;
    int sum = 0;
    if( l <= mid ) sum += query( l , r , lp );
    if( r > mid ) sum += query( l , r , rp );
    return sum % P;
}
void treeadd( int x , int y , int z ){
    while( top[ x ] != top[ y ] ){
        if( dep[ top[ x ] ] < dep[ top[ y ] ] ) std::swap( x , y );
        change( dfn[ top[ x ] ] , dfn[ x ] , 1 , z );
        x = fa[ top[ x ] ];
    }
    if( dep[ x ] < dep[ y ] ) std::swap( x , y );
    change( dfn[ y ] , dfn[ x ] , 1 , z );
}
int treesum( int x , int y ){
    int sum = 0;
    while( top[ x ] != top[ y ] ){
        if( dep[ top[ x ] ] < dep[ top[ y ] ] ) std::swap( x , y );
        sum += query( dfn[ top[ x ] ] , dfn[ x ] , 1 );
        x = fa[ top[ x ] ];
    } 
    if( dep[ x ] < dep[ y ] ) std::swap( x , y );
    sum += query( dfn[ y ] , dfn[ x ] , 1 );
    return sum % P;
}
void subtreeadd( int x , int z ){
    change( dfn[ x ] , dfn[ x ] + siz[ x ] - 1 , 1 , z );
}
int subtreequery( int x ){
    return query( dfn[ x ] , dfn[ x ] + siz[ x ] - 1 , 1 ) % P;
}
void solve(){
    std::cin>>n>>m>>r>>P;
    g.ini( n );
    for( int i = 1 ; i <= n ; i ++ ) std::cin>>a[ i ];
    for( int i = 1 ; i < n ; i ++ ){
        int x , y;std::cin>>x>>y;
        g.add_e( x , y );
        g.add_e( y , x );
    }
    dfs1( r , r );
    dfs2( r , r );
    // for( int i = 1 ; i <= n ; i ++ ) std::cout<<dfn[ i ]<<' ';std::cout<<"\n";
    build( 1 , n , 1 );
    while( m-- ){
        int o;std::cin>>o;
        if( o == 1 ){
            int x , y , z;std::cin>>x>>y>>z;
            treeadd( x , y , z );
        }
        if( o == 2 ){
            int x , y;std::cin>>x>>y;
            std::cout<<treesum( x , y )<<'\n';
        }   
        if( o == 3 ){
            int x , z;std::cin>>x>>z;
            subtreeadd( x , z );
        }
        if( o == 4 ){
            int x;std::cin>>x;
            std::cout<<subtreequery( x )<<'\n';
        }
    }
}


signed main(){
    // freopen("c.in","r",stdin);
    // freopen("c.out","w",stdout);
    std::ios::sync_with_stdio(0);std::cin.tie(0);std::cout.tie(0);
    // int t;std::cin>>t;
    // while(t--)
        solve();
}