#include<bits/stdc++.h>
typedef long long ll;
#define int ll
#define lp (p<<1)
#define rp (p<<1|1)
const int N = 2e5 + 100 , M = 2e5 + 100;
const int INF = 1e9,MOD = 998244353;
std::vector< int > bs;
void insert( int x ){//插入
    for( auto i : bs ){
        x = std::min( x ^ i , x );
    }
    for( auto &i : bs ){
        i = std::min( x ^ i , i );
    }
    if( x ){
        bs.push_back( x );
    }
}
void solve(){
    int n;std::cin>>n;
    std::vector< int > a;
    for( int i = 1 ; i <= n ; i ++ ){
        int x;std::cin>>x;
        a.push_back( x );
    }   
    for( auto i : a ) insert( i );

    int max = 0;// 最大异或值
    for( auto i : bs ){
        max ^= i;
    }
    
    std::sort(bs.begin(),bs.end());
    int k = 3;// 求第k大异或值 对bs排序 将k分解为二进制，第i位为1则选取第i个数，特判bs.size()<n 则k-- 因为原集合能表示0
    int value = 0 , p=0;
    if( bs.size() < n ) k--;
    while( k ){
        if( k >> p & 1 ) value^=bs[ p ];
    }

    int cnt = 0 , target = 5;// 计算有多少种方法异或得出target
    // 首先判断target能否被线性基表示出来 若能 则cnt = 1 << ( n - bs.size());

}


signed main(){
    std::ios::sync_with_stdio(0);std::cin.tie(0);std::cout.tie(0);
    // int t;std::cin>>t;
    // while(t--)
        solve();
}