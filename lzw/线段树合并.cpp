#include<bits/stdc++.h>
typedef long long ll;
#define int ll
#define lp (p<<1)
#define rp (p<<1|1)
const int N = 1e5 + 100 , M = 3e5 + 100;
const int INF = 1e18,MOD = 998244353;
ll qpow(ll x,ll p){assert(p>=0);ll res=1;while(p){if(p&1)res=res*x%MOD;x=x*x%MOD;p>>=1;}return res;}
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
int n, m;

struct setree{
	int ls, rs, max, maxp;
};
// setree tr[ N << 6 ];
std::vector<setree> tr(0);
int tot;
int root[ N ];
void pushup( int p ){
	if( tr[ tr[ p ].ls ].max >= tr[ tr[ p ].rs ].max ){
		tr[ p ].max = tr[ tr[ p ].ls ].max;
		tr[ p ].maxp = tr[ tr[ p ].ls ].maxp;
	}else{
		tr[ p ].max = tr[ tr[ p ].rs ].max;
		tr[ p ].maxp = tr[ tr[ p ].rs ].maxp;
	}
	if( tr[ p ].max == 0 ) tr[ p ].maxp = 0;
}

int merge( int ltr, int rtr, int l, int r ){
	if( !ltr || !rtr ) return ltr + rtr;
	if( l == r ){
		tr[ ltr ].max += tr[ rtr ].max;
		tr[ ltr ].maxp = l;
		return ltr;
	}
	int mid = l + r >> 1;
	tr[ ltr ].ls = merge( tr[ ltr ].ls, tr[ rtr ].ls, l, mid );
	tr[ ltr ].rs = merge( tr[ ltr ].rs, tr[ rtr ].rs, mid + 1, r );
	pushup( ltr ); 
	return ltr;
}

int change( int p, int l, int r, int target, int value ){
	if( p == 0 ){
		tr.push_back({0,0,0,0});
		p = ++tot;
	}
	if( l == r ){
		tr[ p ].max += value;
		tr[ p ].maxp = l;
		return p;
	}
	int mid = l + r >> 1;
	if( target <= mid ){
		int tp = change( tr[ p ].ls, l, mid, target, value );
		tr[ p ].ls = tp; 
	}
	if( target > mid ){
		int tp = change( tr[ p ].rs, mid + 1, r, target, value );
		tr[ p ].rs = tp;
	}
	pushup( p );
	return p;
}

int query( int &p ){
	return tr[ p ].maxp;
}

int fa[ N ][ 31 ];
int dep[ N ];
void dfs0( int p , int f ){
    fa[ p ][ 0 ] = f;
    dep[ p ] = dep[ f ] + 1;
    for( int i = g.head[ p ] ; i ; i = g.e[ i ].next ){
        int y = g.e[ i ].to;
        if( y == f ) continue; 
        dfs0( y , p );
    }
}
int lca( int x , int y ){
    if( dep[ x ] < dep[ y ] ) std::swap( x , y );//x是深的
    for( int i = 30 ; i >= 0 ; i -- ){
        if( dep[ fa[ x ][ i ] ] >= dep[ y ] ) x = fa[ x ][ i ];
    }
    if( x == y ) return x;
    for( int i = 30 ; i >= 0 ; i -- ){
        if( fa[ x ][ i ] != fa[ y ][ i ] ){
            x = fa[ x ][ i ];
            y = fa[ y ][ i ];
        }
    }
    return fa[ x ][ 0 ];
}

int ans[ N ];
void dfs( int x, int dfsfa ){
	for( int i = g.head[ x ]; i; i = g.e[ i ].next ){
		int y = g.e[ i ].to;
		if( y == dfsfa ) continue;
		dfs( y, x );
	}
	for( int i = g.head[ x ]; i; i = g.e[ i ].next ){
		int y = g.e[ i ].to;
		if( y == dfsfa ) continue;
		root[ x ] = merge( root[ x ], root[ y ], 1, 1e5 );
	} 
	ans[ x ] = query( root[ x ] );
}

void solve(){
	std::cin>>n>>m;
	g.ini( n );

	for( int i = 1 ; i < n ; i ++ ){
		int x, y;std::cin>>x>>y;
		g.add_e( x, y );
		g.add_e( y, x );
	}
	dep[ 1 ] = 1;
    dfs0( 1 , 0 );
    for( int i = 1 ; i <= 30 ; i ++ ){
        for( int j = 1 ; j <= n ; j ++ ){
            fa[ j ][ i ] = fa[ fa[ j ][ i - 1 ] ][ i - 1 ];
        }
    }

	for( int i = 1 ; i <= m ; i ++ ){
		int x, y, z;std::cin>>x>>y>>z;
		root[ x ] = change( root[ x ], 1, 1e5, z, 1 );
		root[ y ] = change( root[ y ], 1, 1e5, z, 1 );
	 	root[ lca( x, y ) ] = change( root[ lca( x, y ) ], 1, 1e5, z, -1 );
		root[ fa[ lca( x,y) ][ 0 ] ] = change( root[ fa[ lca( x, y ) ][ 0 ] ], 1, 1e5, z, -1 );
	}

	dfs( 1, 0 );

	for( int i = 1 ; i <= n ; i ++ ){
		std::cout<<ans[ i ]<<'\n';
	}

}


signed main(){
	std::ios::sync_with_stdio(0);std::cin.tie(0);std::cout.tie(0);
		solve();
}