#include<bits/stdc++.h>
typedef long long ll;
#define int ll
const int N = 5e3 + 100 , M = 2e5 + 100;
const int INF = 1e9,MOD = 998244353;
int n , m , S , T;
struct{
	int to , next , w;
}e[ N << 1 ];
int head[ N ],tot = 1 ;
void add_e( int x , int y , int w ){
	e[ ++tot ].to = y;
	e[ tot ].w = w;
	e[ tot ].next = head[ x ];
	head[ x ] = tot;
}
int layer[ N ];
bool bfs(){
	for( int i = S ; i <= T ; i ++ ) layer[ i ] = 0;
	std::queue< int > q;
	q.push( S );layer[ S ] = 1;
	while( q.size() ){
		int x = q.front();q.pop();
		for( int i = head[ x ] ; i ; i = e[ i ].next ){
			int y = e[ i ].to;
			if( layer[ y ] || e[ i ].w == 0 ) continue;
			layer[ y ] = layer[ x ] + 1;
			q.push( y );
			if( y == T ) return 1;  
		}
	}
	return 0;
}
int cur[ N ];
int dfs( int x , int mf ){
	if( x == T ) return mf;
	int sum = 0;
	for( int i = cur[ x ] ; i ; i = e[ i ].next ){
		cur[ x ] = i;
		int y = e[ i ].to;
		if( layer[ y ] != layer[ x ] + 1 || e[ i ].w == 0 ) continue;
		int f = dfs( y , std::min( e[ i ].w , mf ) );
		sum += f;
		mf -= f;
		e[ i ].w -= f;
		e[ i ^ 1 ].w += f;
		if( mf == 0 ) break; 
	}
	if( sum == 0 ) layer[ x ] = 0;
	return sum;
}
int dinic(){
	int mf = 0;
	while( bfs() ){
		memcpy( cur , head , sizeof head );
		mf += dfs( S , INF );
	}
	return mf;
}
void solve(){
	std::cin>>n>>m>>S>>T;
	for( int i = 1 ; i <= m ; i ++ ){
		int x , y , w;std::cin>>x>>y>>w;
		add_e( x , y , w );
		add_e( y , x , 0 );
	}
	std::cout<<dinic()<<'\n';
}


signed main(){
	std::ios::sync_with_stdio(0);std::cin.tie(0);std::cout.tie(0);
	// int t;std::cin>>t;
	// while(t--)
		solve();
}