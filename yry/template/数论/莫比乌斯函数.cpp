#include<bits/stdc++.h>

using namespace std;
using ll=long long;

const int maxn=1000005;
int n,p[maxn+100],u[maxn+100],tot;
bool vis[maxn+100];

/*
对于m=p[j]*i,p[j]是m的最小质因子
如果i含p[j]，说明指数大于一，为0，否则m比i多出一个因子，取负
*/
void getu(){
    u[1]=1;
    for(int i=2;i<maxn;i++){
        if(!vis[i]){
            p[tot++]=i;
            u[i]=-1;
        }
        for(int j=0;j<tot&&p[j]*i<maxn;j++){
            int m=p[j]*i;
            vis[m]=1;
            if(i%p[j]==0){
                u[m]=0;
                break;
            }else{
                u[m]=-u[i];
            }
        }
    }
}



void solve(){
    getu();
    for(int i=0;i<100;i++){
        cout<<i<<" "<<u[i]<<'\n';
    }
}
int main(){
    #ifndef ONLINE_JUDGE
    freopen("aa.in", "r", stdin);
    freopen("aa.out", "w", stdout);
    #endif 
    std::ios::sync_with_stdio(0);std::cin.tie(0);std::cout.tie(0);
    int t=1;//cin>>t;
    while(t--)
        solve();
}