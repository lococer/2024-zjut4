#include<iostream>
#include<queue>
#include<vector>
#include<cstring>
typedef long long ll;
const int size = 1e6 + 100;
ll n,tot,ans;
ll ac[size][28];
ll end[size];
ll fail[size];
int get( char c ){
    return c-'a';
}
char s[size];
void insert(char *str){
    int p = 0,len = strlen(str);
    for( int i = 0 ; i < len ; i ++){
        int ch = get( str[ i ] );
        if( ac[ p ][ ch ] == 0 ) ac[ p ][ ch ] = ++tot;
        p = ac[ p ][ ch ];
    }
    end[ p ]++;
}
void build(){
    std::queue< int > que;
    for( int i = 0 ; i < 26 ; i ++){
        if( ac[ 0 ][ i ] ) que.push(ac[ 0 ][ i ] );
    }
    while( !que.empty() ){
        int p = que.front();
        que.pop();
        for( int i = 0 ; i < 26 ; i ++){
            if( ac[ p ][ i ] ){
                fail[ ac[ p ][ i ] ] = ac[ fail[ p ] ][ i ];
                que.push(ac[ p ][ i ]);
            }
            else{
                ac[ p ][ i ] = ac[ fail[ p ] ][ i ] ;
            }
        }
    }
}
void query(char *str){
    int p = 0,len = strlen( str );
    for( int i = 0 ; i < len ; i ++){
        int ch = get( str[ i ] );
        p = ac[ p ][ ch ];
        for( int j = p ; j && end[ j ] != -1 ; j = fail[ j ] ){
            ans += end[ j ];
            end[ j ] = -1;
        }
    }
}
void read(){
    std::cin>>n;
    for( int i = 1 ; i <= n ; i ++){
        std::cin>>s;
        insert(s);
    }
    build();
}
void ini(){
}    
void solve(){
    std::cin>>s;
    query(s);
}
void print(){
    std::cout<<ans<<'\n';
}
int main(){
    freopen("c.in","r",stdin);
    //freopen("c.out","w",stdout);
    std::ios::sync_with_stdio(0);std::cin.tie(0);std::cout.tie(0);
    // ll t;std::cin>>t;
    // while( t-- )
    {
        read();
        ini();
        solve();
        print();
    }
}