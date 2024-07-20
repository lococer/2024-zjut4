#include<bits/stdc++.h>
typedef long long ll;
#define int ll
#define lp (p<<1)
#define rp (p<<1|1)
const int N = 1e5 + 100 , M = 2e5 + 100;
const int INF = 1e9,MOD = 998244353;
ll qpow(ll x,ll p){ll res=1;while(p){if(p&1)res=res*x%MOD;x=x*x%MOD;p>>=1;}return res;}
ll inv(ll x){return qpow(x,MOD-2);}
int a[ N ];
struct{
    int v,max;
    int l,r;
}tr[ N << 2 ];

void pushup( int p ){
    tr[ p ].max = std::max( tr[ lp ].max, tr[ rp ].max );
    tr[ p ].v = tr[ lp ].v + tr[ rp ].v;
}

void build( int l, int r, int p){
    tr[ p ].l = l;tr[ p ].r = r;
    if( l == r ){
        tr[ p ].max = a[ l ];
        tr[ p ].v = a[ l ];
        return;
    }
    int mid = l + r >> 1;
    build( l, mid, lp );
    build( mid+1, r, rp );
    pushup(p);
}

void change( int l, int r, int p ){
    if( tr[ p ].max <= 1 ) return;
    if( tr[ p ].l == tr[ p ].r ){
        tr[ p ].max = std::sqrt( tr[ p ].max );
        tr[ p ].v = std::sqrt( tr[ p ].v );
        return;
    }
    int mid = tr[ p ].l + tr[ p ].r >> 1;
    if( l <= mid ) change( l, r, lp );
    if( r > mid ) change( l, r, rp );
    pushup( p );
}

int query( int l, int r, int p ){
    if( l <= tr[ p ].l && r >= tr[ p ].r ){
        return tr[ p ].v;
    }
    int mid = tr[ p ].l + tr[ p ].r >> 1;
    int ans = 0;
    if( l <= mid ) ans += query( l, r, lp );
    if( r > mid ) ans += query( l, r, rp );
    return ans; 
}

void solve(){
    int n;std::cin>>n;
    for( int i = 1 ; i <= n ; i ++ ) std::cin>>a[ i ];
    build( 1 , n , 1 );
    int m;std::cin>>m;
    while( m -- ){
        int o,l,r;std::cin>>o>>l>>r;
        if( l > r ) std::swap( l , r );
        if( o == 0 ){
            change( l , r , 1 );
        }else{
            std::cout<<query( l , r , 1 )<<'\n';
        }
    }
}


signed main(){
    std::ios::sync_with_stdio(0);std::cin.tie(0);std::cout.tie(0);
    // int t;std::cin>>t;
    // while(t--)
        solve();
}