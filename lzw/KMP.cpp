#include<bits/stdc++.h>
typedef long long ll;
#define int ll
#define lp (p<<1)
#define rp (p<<1|1)
const int N = 1e6 + 100 , M = 2e5 + 100;
const int INF = 1e9,MOD = 998244353;
int next[ N ];
char s1[ N ],s2[ N ];
void solve(){
    // std::cin>>(s1+1)>>(s2+1);
    scanf("%s%s",s1+1,s2+1);
    int n = strlen(s1+1), m = strlen(s2+1);
    next[ 1 ] = 1;
    for( int i = 2, j = 1 ; i <= m ; i ++ ){
        while( j != 1 && s2[ i ] != s2[ j ] ) j = next[ j - 1 ];
        if( s2[ i ] == s2[ j ] ) j++;
        next[ i ] = j;
    }
    for( int i = 1, j = 1 ; i <= n ; i ++ ){
        while( j != 1 && s1[ i ] != s2[ j ] ) j = next[ j - 1 ];
        if( s1[ i ] == s2[ j ] ) j ++;
        if( j == m + 1 ){
            // std::cout<<i-m+1<<'\n';
            printf("%d\n",i-m+1);
            j = next[ j - 1 ];
        }
    }
    for( int i = 1 ; i <= m ; i ++ ){
        // std::cout<<next[ i ]-1<<' ';
        printf("%d ",next[ i ] - 1);
    }
}


signed main(){
    // std::ios::sync_with_stdio(0);std::cin.tie(0);std::cout.tie(0);
    // int t;std::cin>>t;
    // while(t--)
        solve();
}

