#include<bits/stdc++.h>
typedef long long ll;
#define int ll
#define lp (p<<1)
#define rp (p<<1|1)
const int N = 5e2 + 100 , M = 2e5 + 100;
const int INF = 1e9,MOD = 998244353;
struct{
    int c,v,num;
}a[ N ];
struct node{
    int c,v;
};
std::vector< node > ve;
int n,m;
int dp[ 7005 ];
void solve(){
    std::cin>>n>>m;
    for( int i = 1 ; i <= n ; i ++ ){
        std::cin>>a[ i ].c>>a[ i ].v>>a[ i ].num;
    }
    for( int i = 1 ; i <= n ; i ++ ){
        int t = a[ i ].num,c = a[ i ].c,v = a[ i ].v;
        int p = 1;
        while( t >= p ){
            ve.push_back({c*p,v*p});
            t-=p;
            p<<=1;
        }
        if( t > 0 ){
            ve.push_back({c*t,v*t});
        }
    }
    for( auto i : ve ){
        for( int j = m ; j >= i.c ; j -- ){
            dp[ j ] = std::max( dp[ j ] , dp[ j - i.c ] + i.v );
        }
    }
    std::cout<<dp[ m ];
}


signed main(){
    std::ios::sync_with_stdio(0);std::cin.tie(0);std::cout.tie(0);
    // int t;std::cin>>t;
    // while(t--)
        solve();
}