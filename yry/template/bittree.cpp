#include<bits/stdc++.h>

using namespace std;
using ll=long long;

const int N=2e6+10;

int s[N+10];


constexpr inline int lowbit(int x){
    return x&-x;
}

void update(int p,int k){
    for(;p<=N;p+=lowbit(p))s[p]+=k;
}

int sum(int p){
    int ret=0;
    for(;p;p-=lowbit(p))ret+=s[p];
    return ret;
}

int query(int l,int r){
    return sum(r)-sum(l-1);
}


void solve(){


}
int main(){
    freopen("aa.in","r",stdin);
    freopen("aa.out","w",stdout);
    std::ios::sync_with_stdio(0);std::cin.tie(0);std::cout.tie(0);
    int t=1;//cin>>t;
    while(t--)
        solve();
        
}