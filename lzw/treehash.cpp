#include<bits/stdc++.h>
typedef long long ll;
#define int ll
#define lp (p<<1)
#define rp (p<<1|1)
#define ull unsigned long long
const int N = 3e5 + 100 , M = 3e5 + 100;
const int INF = 1e18,MOD = 998244353;
ll qpow(ll x,ll p){assert(p>=0);ll res=1;while(p){if(p&1)res=res*x%MOD;x=x*x%MOD;p>>=1;}return res;}
ll inv(ll x){return qpow(x,MOD-2);}


const ull mask = std::mt19937_64(time(nullptr))();
ull shift(ull x) {
    x ^= mask;
    x ^= x << 13;
    x ^= x >> 7;
    x ^= x << 17;
    x ^= mask;
    return x;
}

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

int n;
ull hash[ N ];

void getHash( int x, int dfsfa ){
    hash[ x ] = 1;
    for( int i = g.head[ x ]; i; i = g.e[ i ].next ){
        int y = g.e[ i ].to;
        if( y == dfsfa ) continue;
        getHash( y, x );
        hash[ x ] += shift( hash[ y ] );
        hash[ x ] %= MOD;// use mode version
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
}


signed main(){
    std::ios::sync_with_stdio(0);std::cin.tie(0);std::cout.tie(0);
    int t;std::cin>>t;
    while(t--)
        solve();
}