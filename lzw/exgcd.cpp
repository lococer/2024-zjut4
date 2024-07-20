#include<bits/stdc++.h>
typedef long long ll;
const int N = 1e5 + 100 , M = 5e2 + 100;
const int INF = 1e9;
ll exgcd( ll A , ll B , ll &x , ll&y ){
    if( B == 0 ){ x = 1 ; y = 0 ; return A ;}
    ll tx , ty;
    ll gcd = exgcd( B , A % B , tx , ty );
    x = ty;
    y = tx - (A/B)*ty;
    return gcd;
}
void solve(){
    ll A,B,x,y;
    std::cin>>A>>B;
    exgcd( A , B , x , y );
    std::cout<<( x % B + B ) % B;
}
int main(){
    std::ios::sync_with_stdio(0);std::cin.tie(0);std::cout.tie(0);
    // ll t;std::cin>>t;
    // while( t-- )
        solve();
}   