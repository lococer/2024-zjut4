#include<bits/stdc++.h>
typedef long long ll;
// #define int ll
#define lp (p<<1)
#define rp (p<<1|1)
const int N = 3e5 + 100 , M = 3e5 + 100;
const int INF = 1e9,MOD = 998244353;
ll qpow(ll x,ll p){ll res=1;while(p){if(p&1)res=res*x%MOD;x=x*x%MOD;p>>=1;}return res;}
ll inv(ll x){return qpow(x,MOD-2);}
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
int n,maxlen;
template<typename T>
struct fenwicktree{
    std::vector<T> tr;
    fenwicktree(int n){tr.resize((n+10)<<1);}
    int lowbit(int x){return x&-x;}
    void add(int p,T x){p++; for(;p<tr.size();p+=lowbit(p))tr[p]+=x;}
    int ask(int p){p++;T ans=0;for(;p;p-=lowbit(p))ans+=tr[p];return ans;}
    int ask(int l,int r){ return ask(r)-ask(l-1);}
};
fenwicktree<int> ft( 2E4 + 10 );

// =======================
std::vector<int> size,vis,maxp,gcd,dis;
int root,sum;

void findroot( int x , int fa ){
    size[ x ] = 1;maxp[ x ] = 0;
    for( int i = g.head[ x ]; i; i = g.e[ i ].next ){
        int y = g.e[ i ].to;
        if( y == fa || vis[ y ] ) continue;
        findroot( y , x );
        maxp[ x ] = std::max( maxp[ x ], size[ y ] );
        size[ x ] += size[ y ];
    }
    maxp[ x ] = std::max( maxp[ x ], sum - size[ x ] );
    if( maxp[ x ] < maxp[ root ] ) root = x;
}

// 
std::vector<int> has;

int ans = 0;

// void futhercal(){
//     has.push_back();
// }

void caldis( int x , int fa ){
    if( dis[ x ] > maxlen ) return;
    has.push_back( x );
    for( int i = g.head[ x ]; i; i = g.e[ i ].next ){
        int y = g.e[ i ].to;
        if( y == fa || vis[ y ] ) continue;
        dis[ y ] = dis[ x ] + g.e[i].w;
        caldis( y , x );
    }
}
void cal( int x , int fa ){ // calculate ans on this subtree
    // init sth
    dis[ x ] = 0;
    std::vector<int> needclear;
    needclear.push_back( 0 );
    ft.add( 0 , 1 );
    for( int i = g.head[ x ]; i; i = g.e[ i ].next ){
        int y = g.e[ i ].to;
        if( vis[ y ] || y == fa ) continue;
        // update subtree root
        dis[ y ] = dis[ x ] + g.e[i].w;
        // cal subtree        
        // furthercal()
        caldis( y , x );

        for( auto j : has ){
            ans += ft.ask( maxlen - dis[ j ] );
            // if( j == 5 ){
            //     std::cerr<<ft.ask( 3 )<<'\n';
            // }
        }

        for( auto j : has ){
            ft.add( dis[ j ] , 1 );
            needclear.push_back( dis[ j ] );
        }

        // dont forget to clear
        has.clear();

    }

    for( auto i : needclear ){
        ft.add( i , -1 );
    }

    // clear if exist sth only in this subtree
}

void dfs( int x , int fa ){
    vis[ x ] = 1;cal( x , fa );
    for( int i = g.head[ x ]; i; i = g.e[ i ].next ){
        int y = g.e[ i ].to;
        if( y == fa || vis[ y ] ) continue;
        root = 0;
        sum = size[ y ];
        findroot( y , x );
        dfs( root , x );
    }
}
// =======================

void solve(){
    std::cin>>n;
    g.ini( n );
    size.resize( n + 1 );vis.resize( n + 1 );maxp.resize( n + 1 );gcd.resize( n + 1 );dis.resize( n + 1 );
    // for( int i = 1 ; i <= n ; i ++ ) std::cin>>a[ i ];
    for( int i = 1 ; i < n ; i ++ ){
        int x,y,w;std::cin>>x>>y>>w;
        g.add_e( x , y , w );
        g.add_e( y , x , w );
    }
    std::cin>>maxlen;
    // =======================
    sum = n;
    maxp[ root = 0 ] = INF;
    findroot( 1 , 1 );
    dfs( root , root );
    // =======================
    // std::cout<<root<<'\n';



    std::cout<<ans<<'\n';

}


signed main(){
    std::ios::sync_with_stdio(0);std::cin.tie(0);std::cout.tie(0);
    // int t;std::cin>>t;
    // while(t--)
        solve();
        // std::cout<<std::__gcd( 0 , 2 );
}