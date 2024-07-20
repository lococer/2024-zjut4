#include <bits/stdc++.h>
typedef long long ll;
const int N = 1e5 + 100 , M = 1e5 + 100;
const int INF = 1e9;
const int MOD = 1;
int n,m;
int in[ N ],pre[ N ];
struct{
    int v,l,r;
}tree[ N ];
void build( int lin , int rin , int lpre , int rpre , int p ){
    for( int i = lin ; i <= rin ; i ++ ){
        if( in[ i ] == pre[ lpre ] ){
            tree[ p ].v = pre[ lpre ];
            tree[ p ].l = 2 * p;
            tree[ p ].r = 2 * p + 1;
            build( lin , i - 1 , lpre + 1 , lpre + i - lin , 2 * p );
            build( i + 1 , rin , lpre + i - lin + 1 , rpre , 2 * p + 1 );
            break;
        }
    }
}
void solve(){
    std::cin>>n;
    for( int i = 1 ; i <= n ; i ++ ) std::cin>>pre[ i ];
    for( int i = 1 ; i <= n ; i ++ ) std::cin>>in[ i ];
    build( 1 , n , 1 , n , 1 );
    // for( int i = 1 ; i <= n * 2 ; i ++ ) std::cout<<tree[ i ].v<<' ';
    std::queue< int > q;
    q.push(1);
    while(!q.empty()){
        int p = q.front();q.pop();
        if( p != 1 )    std::cout<<' '<<tree[ p ].v;
        else std::cout<<tree[ p ].v;
        if( tree[tree[ p ].r].v != 0 ) q.push( tree[ p ].r );
        if( tree[tree[ p ].l].v != 0 ) q.push( tree[ p ].l );
    }
}
int main() {
    std::ios::sync_with_stdio(0);std::cin.tie(0);std::cout.tie(0);
    // ll t;std::cin>>t;
    // while( t-- )
    {
        solve();
    }
}