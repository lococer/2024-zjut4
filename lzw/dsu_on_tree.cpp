#include<bits/stdc++.h>
typedef unsigned long long ll;
// #define int ll
#define lp (p<<1)
#define rp (p<<1|1)
const int N = 5e5 + 100 , M = 3e5 + 100;
const int INF = 1e9,MOD = 998244353;
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
template<typename T>
struct fenwicktree{
    std::vector<T> tr;
    fenwicktree(int n){tr.resize((n+10)<<1);}
    int lowbit(int x){return x&-x;}
    void add(int p,T x){for(;p<tr.size();p+=lowbit(p))tr[p]+=x;}
    ll ask(int p){T ans=0;for(;p;p-=lowbit(p))ans+=tr[p];return ans;}
    ll ask(int l,int r){ return ask(r)-ask(l-1);}
};
ll a[ N ];
fenwicktree<ll> tr1(1e6+10),tr2(1e6+10),tr3(1e6+10);
ll ans[ N ], nowans;
ll n;
ll size[ N ], bigson[ N ], dfnin[ N ], dfnout[ N ], dfn[ N ], dfncnt;
ll redfn[ N ];
void dfs0( int x, int dfsfa ){
    size[ x ] = 1;
    dfn[ x ] = ++dfncnt;
    redfn[ dfncnt ] = x;
    dfnin[ x ] = dfn[ x ];
    int maxson = 0;
    for( int i = g.head[ x ]; i; i = g.e[ i ].next ){
        int y = g.e[ i ].to;
        if( y == dfsfa ) continue;
        dfs0( y, x );
        size[ x ] += size[ y ];
        if( size[ y ] > size[ maxson ] ) maxson = y;
    }
    dfnout[ x ] = dfncnt;
    bigson[ x ] = maxson;
}

void add( ll x ){
    nowans += x * x * tr1.ask( x ) - x * tr2.ask( x );
    nowans += tr3.ask(x+1,1e6) - tr2.ask(x+1,1e6) * x;
    tr1.add( x, 1 );
    tr2.add( x, x );
    tr3.add( x, x * x );
}

void del( ll x ){
    tr1.add( x, -1 );
    tr2.add( x, -x );
    tr3.add( x, -x * x );
    nowans -= x * x * tr1.ask( x ) - x * tr2.ask( x );
    nowans -= tr3.ask(x+1,1e6) - tr2.ask(x+1,1e6) * x;
}

void dfs2( ll x, ll dfsfa, bool keep ){
    for( int i = g.head[ x ]; i; i = g.e[ i ].next ){
        int y = g.e[ i ].to;
        if( y == dfsfa || y == bigson[ x ] ) continue;
        dfs2( y, x, false );
    }
    if( bigson[ x ] ){
        dfs2( bigson[ x ], x, true );
    }
    for( int i = g.head[ x ]; i; i = g.e[ i ].next ){
        int y = g.e[ i ].to;
        if( y == dfsfa || y == bigson[ x ] ) continue;
        for( int j = dfnin[ y ]; j <= dfnout[ y ]; j ++ ){
            add( a[ redfn[ j ] ] );
        }
    }
    add( a[ x ] );
    ans[ x ] = nowans;
    if( keep == false ){
        for( int i = dfnin[ x ]; i <= dfnout[ x ]; i ++ ){
            del( a[ redfn[ i ] ] );
        }
    }
}

void solve(){
    std::cin>>n;
    g.ini( n );
    for( int i = 1 ; i < n ; i ++ ){
        int x, y;std::cin>>x>>y;
        g.add_e( x, y );
        g.add_e( y, x );
    }
    for( int i = 1 ; i <= n ; i ++ ) std::cin>>a[ i ];
    
    dfs0( 1, 1 );

    dfs2( 1, 1, true );

    for( int i = 1 ; i <= n ; i ++ ) ans[ i ] *= 2;

    ll res = 0;
    for( int i = 1; i <= n ; i ++ ) res ^= ans[ i ];

    std::cout<<res<<'\n';
}


signed main(){
    std::ios::sync_with_stdio(0);std::cin.tie(0);std::cout.tie(0);
        solve();
}