#include<bits/stdc++.h>
typedef long long ll;
#define int ll
#define lp (p<<1)
#define rp (p<<1|1)
const int N = 2e5 + 100 , M = 3e5 + 100;
const int INF = 1e18,MOD = 998244353;
ll qpow(ll x,ll p){ll res=1;while(p){if(p&1)res=res*x%MOD;x=x*x%MOD;p>>=1;}return res;}
ll inv(ll x){return qpow(x,MOD-2);}
int n,m,a[ N ];
std::map<int,int> map,rmap;

struct{
    int l,r,sum;
}tr[ N << 5 ];
int tot,root[ N ];

int copy( int p ){
    tr[ ++tot ].l = tr[ p ].l;
    tr[ tot ].r = tr[ p ].r;
    tr[ tot ].sum = tr[ p ].sum;
    return tot;
}

void pushup( int p ){
    tr[ p ].sum = tr[ tr[ p ].l ].sum + tr[ tr[ p ].r ].sum;
}

int build( int l , int r , int p ){
    p = ++tot;
    if( l == r ){
        tr[ p ].sum = 0;
        return p;
    }
    int mid = l + r >> 1;
    tr[ p ].l = build( l , mid , tr[ p ].l );
    tr[ p ].r = build( mid + 1 , r , tr[ p ].r );
    pushup( p );
    return p;
}

int change( int l , int r , int p , int w , int pos ){
    p = copy( p );
    if( l == r ){
        tr[ p ].sum ++;
        return p;
    }
    int mid = l + r >> 1;
    if( pos <= mid ) tr[ p ].l = change( l , mid , tr[ p ].l , w , pos );
    if( pos > mid ) tr[ p ].r = change( mid + 1 , r , tr[ p ].r , w , pos );
    pushup( p );
    return p;
}

int query( int l , int r , int pl , int pr , int k ){
    if( l == r ) 
        return rmap[ l ];
    int mid = l + r >> 1;
    int num = tr[ tr[ pr ].l ].sum - tr[ tr[ pl ].l ].sum;
    if( k <= num ) return query( l , mid , tr[ pl ].l , tr[ pr ].l , k );
    return query( mid + 1 , r , tr[ pl ].r , tr[ pr ].r , k - num );
}

void solve(){
    std::cin>>n>>m;
    std::set<int> set;
    for( int i = 1 ; i <= n ; i ++ ){
        std::cin>>a[ i ];
        set.insert( a[ i ] );
    }
    int setcnt = 0;
    for( auto i : set ){
        map[ i ] = ++setcnt;
        rmap[ setcnt ] = i;
    }
    for( int i = 1 ; i <= n ; i ++ ){
        a[ i ] = map[ a[ i ] ];
    }

    root[ 0 ] = build( 1 , n , root[ 0 ] ); 

    for( int i = 1 ; i <= n ; i ++ ){
        root[ i ] = change( 1 , n , root[ i - 1 ], 1, a[ i ] );
    }

    while( m-- ){
        int l , r , k;std::cin>>l>>r>>k;
        std::cout<<query( 1 , n , root[ l - 1 ], root[ r ] , k )<<'\n';
    }
        

}


signed main(){
    std::ios::sync_with_stdio(0);std::cin.tie(0);std::cout.tie(0);
    // int t;std::cin>>t;
    // while(t--)
        solve();
}