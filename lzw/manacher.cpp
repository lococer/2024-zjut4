#include<iostream>
#include<cstring>
typedef long long ll;
const int N=12e6;
char s[N],temp[N<<1];
ll p[N<<1],len,ans;
void read(){
    std::cin>>s;
}
void ini(){
    len=strlen(s);
    temp[0]='!';
    for( ll i = 1 ; i <= len << 1 ; i +=2){
        temp[ i ] = '#';
        temp[ i + 1 ] = s[ i >> 1 ];
    }
    temp[ 2 * len + 1 ] = '#';
    temp[ 2 * len + 2 ] = '$';
    temp[ 2 * len + 3 ] = 0;
    len = len * 2 + 1 ;
}
void solve(){
    ll r=0,c=0;
    for( ll i = 1 ; i <= len ; i ++){
        if( i > r ) p[ i ] = 1;
        else p[ i ] = std::min( r-i,p[ (c<<1) - i ] );
        while( temp[ i + p[ i ] ] == temp[ i - p[ i ] ] ) p[ i ]++;
        if( p[ i ] + i > r ){
            r = i + p[ i ];
            c = i;
        }
        ans = std::max(ans,p[ i ]-1);
    }
}
void print(){
    std::cout<<ans<<'\n';
}
int main(){
    // std::ios::sync_with_stdio(0);std::cin.tie(0);std::cout.tie(0);
    // ll t;std::cin>>t;
    // while( t-- )
    {
        read();
        ini();
        solve();
        print();
    }
}