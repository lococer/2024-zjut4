#include<bits/stdc++.h>
typedef long long ll;
#define lp (p<<1)
#define rp (p<<1|1)
const int N = 5e5 + 100 , M = 3e5 + 100;
const int INF = 1e9,MOD = 998244353;
ll qpow(ll x,ll p){assert(p>=0);ll res=1;while(p){if(p&1)res=res*x%MOD;x=x*x%MOD;p>>=1;}return res;}
ll inv(ll x){return qpow(x,MOD-2);}
namespace Fread {
	const int SIZE=1<<21;char buf[SIZE],*S,*T;
	inline char getchar() {if(S==T){T=(S=buf)+fread(buf,1,SIZE,stdin);if(S==T)return '\n';}return *S++;}
}
namespace Fwrite {
	const int SIZE=1<<21;
	char buf[SIZE],*S=buf,*T=buf+SIZE;
	inline void flush(){fwrite(buf,1,S-buf,stdout);S=buf;}
	inline void putchar(char c){*S++=c;if(S==T)flush();}
	struct POPOSSIBLE{~POPOSSIBLE(){flush();}}ztr;
}
#define getchar Fread :: getchar
#define putchar Fwrite :: putchar
namespace Fastio{
	struct Reader{
	    template<typename T>
    	Reader& operator >> (T& x) {
        	char c=getchar();T f=1;
        	while(c<'0'||c>'9'){if(c=='-')f=-1;c=getchar();}x=0;
        	while(c>='0'&&c<='9'){x=x*10+(c-'0');c=getchar();}x*=f;
	        return *this;
    	}
	    Reader(){}
	}cin;
	struct Writer{
	    template<typename T>
	    Writer& operator << (T x) {
	        if(x==0){putchar('0');return *this;}
	        if(x<0){putchar('-');x=-x;}
	        static int sta[45];int top=0;
	        while(x){sta[++top]=x%10;x/=10;}
	        while(top){putchar(sta[top]+'0');--top;}
	        return *this;
    	}
    	Writer& operator << (char c) {putchar(c);return *this;}
    	Writer(){}
	}cout;
}
#define endl '\n' 
#define cin Fastio::cin
#define cout Fastio::cout

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
int size[ N ], son[ N ], dfn[ N ], dfncnt, redfn[ N ], top[ N ], dep[ N ], fa[ N ], indfn[ N ], outdfn[ N ];
int sd[ N ];// node stand for edge
void dfs0( int x, int dfsfa ){
    dep[ x ] = dep[ dfsfa ] + 1;
    size[ x ] = 1;
    for( int i = g.head[ x ]; i; i = g.e[ i ].next ){
        int y = g.e[ i ].to;
        if( y == dfsfa ) continue;
        sd[ y ] = g.e[ i ].w;
        dfs0( y, x );
        size[ x ] += size[ y ]; 
        if( size[ y ] > size[ son[ x ] ] ) son[ x ] = y;
    }
}
void dfs1( int x, int dfsfa, int linktop ){
    dfn[ x ] = ++dfncnt;
    indfn[ x ] = dfn[ x ];
    redfn[ dfncnt ] = x;
    top[ x ] = linktop;
    fa[ x ] = dfsfa;
    if( son[ x ] ) dfs1( son[ x ], x, linktop);
    for( int i = g.head[ x ]; i; i = g.e[ i ].next ){
        int y = g.e[ i ].to;
        if( y == dfsfa || y == son[ x ] ) continue;
        dfs1( y, x, y );
    }
    outdfn[ x ] = dfncnt;
} 
int LCA( int x, int y ){
    while( top[ x ] != top[ y ] ){
        if( dep[ top[ x ] ] < dep[ top[ y ] ] ) std::swap( x, y );
        x = fa[ top[ x ] ];
    }
    if( dep[ x ] < dep[ y ] ) std::swap( x, y );
    return y;
}

int m,s;
void solve(){
    cin>>n>>m>>s;
    g.ini( n );
    for( int i = 1 ; i < n ; i ++ ){
        int x, y;cin>>x>>y;
        g.add_e( x, y, i );
        g.add_e( y, x, i );
    }

    dfs0( s, s );
    dfs1( s, s, s );
    for( int i = 1 ; i <= m ; i ++ ){
        int x, y;cin>>x>>y;
        cout<<LCA( x, y )<<'\n';
    }

}


signed main(){
        solve();
}