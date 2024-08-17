#include<bits/stdc++.h>
typedef long long ll;
#define int ll
#define lp (p<<1)
#define rp (p<<1|1)
const int N = 3e5 + 100 , M = 3e5 + 100;
const int INF = 1e18,MOD = 998244353;
ll qpow(ll x,ll p){assert(p>=0);ll res=1;while(p){if(p&1)res=res*x%MOD;x=x*x%MOD;p>>=1;}return res;}
ll inv(ll x){return qpow(x,MOD-2);}

struct DSU{
    std::vector<int> fa;
    DSU( int n ){
        fa.resize( n + 1 );
        for( int i = 1 ; i <= n ; i ++ ) fa[ i ] = i;
    }
    int find_fa( int x ){
        while( x != fa[ x ] ) x = fa[ x ] = fa[ fa[ x ] ];
        return x;
    }
    bool same( int x, int y ){
        return find_fa( x ) == find_fa( y );
    }
    bool merge( int x, int y ){
        int fx = find_fa( x ), fy = find_fa( y );
        if( fx == fy ) return false; 
        fa[ fx ] = fy;
        return true;
    }
};

void solve(){
    
}


signed main(){
    std::ios::sync_with_stdio(0);std::cin.tie(0);std::cout.tie(0);
    int t;std::cin>>t;
    while(t--)
        solve();
}