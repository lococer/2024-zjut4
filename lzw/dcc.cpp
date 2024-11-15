// 点双
#include<bits/stdc++.h>
typedef long long ll;
#define int ll
#define lp (p<<1)
#define rp (p<<1|1)
const int N = 5e5 + 100 , M = 3e5 + 100;
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
int dfn[ N ], low[ N ], dfncnt, root, cut[ N ];
std::vector<int> st;
std::vector<std::vector<int>> dcc;
// 不能有自环
// 所有点双放在dcc中，要统计一个割点连接了几个点双，只要吧点双中所有点cnt+1,即可得到
void tarjan(int x) {
	dfn[x] = low[x] = ++dfncnt;
	// stack[++top] = x;
    st.push_back( x );
	if (x == root && g.head[x] == 0) { //孤立点
		// dcc[++cnt].push_back(x);
        dcc.push_back(std::vector<int>(1,x));
		return;
	}
	int flag = 0;
	for (int i = g.head[x]; i; i = g.e[i].next) {
		// int y = ver[i];
        int y = g.e[ i ].to;
		if (!dfn[y]) {
			tarjan(y);
			low[x] = std::min(low[x], low[y]);
			if (low[y] >= dfn[x]) {
				flag++;
				if (x != root || flag > 1)
					cut[x] = true;
				// cnt++;
                std::vector<int> nowdcc;   
				int z;
				do {
                    z = st.back();
                    st.pop_back();
					// dcc[cnt].push_back(z);
                    nowdcc.push_back(z);
				} while (z != y);
				// dcc[cnt].push_back(x);
				nowdcc.push_back(x);
                dcc.push_back(nowdcc);
			}
		} 
		else
			low[x] = std::min(low[x], dfn[y]);
	}
}
int n, m;
void solve(){
    std::cin>>n>>m;
    g.ini( n );
    for( int i = 1 ; i <= m ; i ++ ){
        int x, y;std::cin>>x>>y;
		if( x == y ) continue;
        g.add_e( x, y );
        g.add_e( y, x );
    }

    for( int i = 1 ; i <= n ; i ++ ){
        if( !dfn[ i ] ){
			root = i;
			tarjan( i );
		}
    }

    std::cout<<dcc.size()<<'\n';
    for( auto i : dcc ){
        std::cout<<i.size()<<' ';
        for( auto j : i ){
            std::cout<<j<<' ';
        }
        std::cout<<'\n';
    }

}


signed main(){
    std::ios::sync_with_stdio(0);std::cin.tie(0);std::cout.tie(0);
    // int t;std::cin>>t;
    // while(t--)
        solve();
}