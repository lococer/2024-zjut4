#include<bits/stdc++.h>
typedef long long ll;
#define int ll
const int N = 2e5 + 100 , M = 2e5 + 100;
const int INf = 1e9,MOD = 998244353;
int a[ N ];
struct{
    int l , r;
    int lazy;
    int v;
}st[ N << 1 ];

void build( int l , int r , int p ){
    st[ p ].l = l , st[ p ].r = r;
    if( l == r ){
        st[ p ].v = a[ l ];
        return;
    }        
    int mid = ( l + r ) >> 1;
    build( l , mid , p << 1 );
    build( mid + 1 , r , p << 1 | 1 );
    st[ p ].v = st[ p << 1 ].v + st[ p << 1 | 1 ].v;
}

void pushdown( int p ){
    if( st[ p ].lazy ){
        st[ p << 1 ].v += ( st[ p << 1 ].r - st[ p << 1 ].l + 1 ) * st[ p ].lazy;
        st[ p << 1 ].lazy += st[ p ].lazy;
        st[ p << 1 | 1 ].v += ( st[ p << 1 | 1 ].r - st[ p << 1 | 1 ].l + 1 ) * st[ p ].lazy;
        st[ p << 1 | 1 ].lazy += st[ p ].lazy; 
        st[ p ].lazy = 0;
    }
}

void change( int l , int r , int p , int k ){
    if( st[ p ].l >= l && st[ p ].r <= r ){
        st[ p ].lazy += k;
        st[ p ].v += ( st[ p ].r - st[ p ].l + 1 ) * k;
        return;
    }
    pushdown( p ); 
    int mid = ( st[ p ].l + st[ p ].r ) >> 1;
    if( l <= mid ) change( l , r , p << 1 , k );
    if( r > mid ) change( l , r , p << 1 | 1 , k );
    st[ p ].v = st[ p << 1 ].v + st[ p << 1 | 1 ].v;
}

int query( int l , int r , int p ){
    if( st[ p ].l >= l && st[ p ].r <= r ){
        return st[ p ].v;
    }
    pushdown( p );
    int mid = ( st[ p ].l + st[ p ].r ) >> 1;
    int sum = 0;
    if( l <= mid ) sum += query( l , r , p << 1 );
    if( r > mid ) sum += query( l , r , p << 1 | 1 );
    return sum;
}

int n,m;
void solve(){
    std::cin>>n;
    std::cin>>m;
    
    for( int i = 1 ; i <= n ; i++ ) std::cin>>a[ i ];
    build( 1 , n , 1 );
    
    while( m -- ){
        int o;std::cin>>o;
        if( o == 1 ){
            int x , y , k;std::cin>>x>>y>>k;
            change( x , y , 1 , k );
        }
        else{
            int x , y;std::cin>>x>>y;
            std::cout<<query( x , y , 1 )<<'\n';
        }
    }
}


signed main(){
    std::ios::sync_with_stdio(0);std::cin.tie(0);std::cout.tie(0);
    // int t;std::cin>>t;
    // while(t--)
        solve();
}