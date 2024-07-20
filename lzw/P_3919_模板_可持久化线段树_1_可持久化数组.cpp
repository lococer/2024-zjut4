#include<bits/stdc++.h>
typedef long long ll;
#define int ll
#define lp (p<<1)
#define rp (p<<1|1)
const int N = 1e6 + 100 , M = 3e5 + 100;
const int INF = 1e18,MOD = 998244353;
ll qpow(ll x,ll p){ll res=1;while(p){if(p&1)res=res*x%MOD;x=x*x%MOD;p>>=1;}return res;}
ll inv(ll x){return qpow(x,MOD-2);}

int a[ N ];
struct{
    int l,r,val;
}tr[ N << 5 ];
int tot;
int copy( int p ){
    tr[ ++tot ].l = tr[ p ].l;
    tr[ tot ].r = tr[ p ].r;
    tr[ tot ].val = tr[ p ].val;
    return tot;
}
int root[ N ];

int build( int l , int r , int p ){
    p = ++tot;
    if( l == r ){
        tr[ p ].val = a[ l ];
        return p;
    }
    int mid = l + r >> 1;
    tr[ p ].l = build( l , mid , tr[ p ].l );
    tr[ p ].r = build( mid + 1 , r , tr[ p ].r );
    return p;
}

int update( int l , int r , int p , int w , int pos ){
    p = copy( p );
    if( l == r ){
        tr[ p ].val = w;
        return p;
    }
    int mid = l + r >> 1;
    if( pos <= mid ) tr[ p ].l = update( l , mid , tr[ p ].l , w , pos );
    if( pos > mid ) tr[ p ].r = update( mid + 1 , r , tr[ p ].r , w , pos );
    return p;
}

int query( int l , int r , int p , int pos ){
    if( l == r ){
        return tr[ p ].val;
    }
    int mid = l + r >> 1;
    if( pos <= mid ) return query( l , mid , tr[ p ].l , pos );
    return query( mid + 1 , r , tr[ p ].r , pos );
}

int n,m;
void solve(){
    std::cin>>n>>m;
    for( int i = 1 ; i <= n ; i ++ ) std::cin>>a[ i ];
    root[ 0 ] = build( 1 , n , root[ 0 ] );
    for( int i = 1; i <= m ; i ++ ){
        int ver,op;
        std::cin>>ver>>op;
        if( op == 1 ){
            int pos,w;std::cin>>pos>>w;
            root[ i ] = update( 1 , n , root[ ver ], w , pos );
        }else{
            int pos;std::cin>>pos;
            std::cout<<query( 1, n, root[ ver ] , pos)<<'\n';
            root[ i ] = root[ ver ];
        }
    }
}


signed main(){
    std::ios::sync_with_stdio(0);std::cin.tie(0);std::cout.tie(0);
    // int t;std::cin>>t;
    // while(t--)
        solve();
}