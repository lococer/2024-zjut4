#include<bits/stdc++.h>
typedef long long ll;
#define int ll
const int N = 2e5 + 100 , M = 2e5 + 100;
const int INF = 1e9,MOD = 998244353;
int fa[ N ],dis[ N ];
int find_fa( int x ){
    if( x != fa[ x ] ){
        int t = find_fa( fa[ x ] );
        dis[ x ] += dis[ fa[ x ] ];
        fa[ x ] = t;
    }
    return fa[ x ];
}
int n , m;
void solve(){
    std::cin>>n>>m;
    for( int i = 1 ; i <= n ; i ++ ){
        fa[ i ] = i;
        dis[ i ] = 0;
    }
    int f = 1;
    while( m-- ){
        int x , y , z;std::cin>>x>>y>>z;
        int fx = find_fa( x ) , fy = find_fa( y );
        if( fx == fy ){
            if( dis[ y ] != z + dis[ x ] && dis[ x ] != dis[ y ] - z ) 
                f = 0;
        }
        else{
            fa[ fy ] = fx;
            dis[ fy ] = -dis[ y ] + z + dis[ x ];
        }
    }
    if( f ){
        std::cout<<"YES\n";
    }
    else{
        std::cout<<"NO\n";
    }
}


signed main(){
    std::ios::sync_with_stdio(0);std::cin.tie(0);std::cout.tie(0);
    int t;std::cin>>t;
    while(t--)
        solve();
}