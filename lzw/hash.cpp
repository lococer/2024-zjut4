#include<bits/stdc++.h>
typedef long long ll;
#define int ll
#define lp (p<<1)
#define rp (p<<1|1)
const int N = 2e5 + 100 , M = 2e5 + 100;
const int INF = 1e9,MOD = 998244353 , P = 333337;
int n;

struct HASH{
    const int P1 = 13333337, P2 = 1337;
    std::vector<int> has1, bas1, has2, bas2;
    HASH(std::string s){
        int len = s.size() - 1;
        has1.resize( len + 1 );has2.resize( len + 1 );
        bas1.resize( len + 1 );bas2.resize( len + 1 );
        for( int i = 1 ; i <= len ; i ++ ){
            has1[ i ] = ( has1[ i - 1 ] * P1 % MOD + s[ i ] ) % MOD;
            has2[ i ] = ( has2[ i - 1 ] * P2 % MOD + s[ i ] ) % MOD;
        }
        bas1[ 0 ] = 1;bas2[ 0 ] = 1;
        for( int i = 1 ; i <= len ; i ++ ) bas1[ i ] = bas1[ i - 1 ] * P1 % MOD;
        for( int i = 1 ; i <= len ; i ++ ) bas2[ i ] = bas2[ i - 1 ] * P2 % MOD;
    }
    std::pair<int,int> query( int l , int r ){
        int ans1 = ( has1[ r ] - has1[ l - 1 ] * bas1[ r - l + 1 ] % MOD + MOD ) % MOD;
        int ans2 = ( has2[ r ] - has2[ l - 1 ] * bas2[ r - l + 1 ] % MOD + MOD ) % MOD;
        return {ans1, ans2};
    }
};

void solve(){
    std::string s;
    std::cin>>s;
    s = ' ' + s;
    HASH h( s );
    std::cout<<( h.query( 1 , 2 ) == h.query( 3 , 4 ) )<<'\n';
}


signed main(){
    std::ios::sync_with_stdio(0);std::cin.tie(0);std::cout.tie(0);
    // int t;std::cin>>t;
    // while(t--)
        solve();
}