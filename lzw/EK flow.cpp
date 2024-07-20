#include <bits/stdc++.h>
typedef long long ll;
#define int ll
const int N = 2e3 + 100 , M = 1e4 + 100;
const int INF = 1e9;
const int MOD = 998244353;
int n,m,s,t;
struct edge{
	int to,next,w;
}e[ M ];
int head[ N ],tot = 1 ;
void add_e( int x , int y , int w ){
	e[ ++tot ].to = y;
	e[ tot ].next = head[ x ];
	e[ tot ].w = w;
	head[ x ] = tot;
}
int mf[ N ],pre[ N ];
bool bfs(){
	for( int i = 1 ; i <= n ; i ++ ) mf[ i ] = 0;
	mf[ s ] = INF;
	std::queue< int > q;
	q.push( s );
	while( q.size() ){
		int x = q.front();q.pop();
		for( int i = head[ x ] ; i ; i = e[ i ].next ){
			int y = e[ i ].to;
			if( mf[ y ] != 0 || e[ i ].w == 0 ) continue;
			pre[ y ] = i;
			mf[ y ] = std::min( mf[ x ] , e[ i ].w );
			q.push( y );
			if( y == t ) return 1;
		}
	}
	return 0;
}
void solve(){
	std::cin>>n>>m>>s>>t;
	for( int i = 1 ; i <= m ; i ++ ){
		int x , y , w;std::cin>>x>>y>>w;
		add_e( x , y , w );
		add_e( y , x , 0 );
	}
	ll ans = 0;
	
	while( bfs() ){
		ans += mf[ t ];
		int y = t;
		while( y != s ){
			int i = pre[ y ];
			e[ i ].w -= mf[ t ];
			e[ i ^ 1 ].w += mf[ t ];
			y = e[ i ^ 1 ].to;
		}
	}

	std::cout<<ans<<'\n';;
}
signed main() {
	std::ios::sync_with_stdio(0);std::cin.tie(0);std::cout.tie(0);
	// ll t;std::cin>>t;
	// while( t-- )
	{
		solve();
	}
}