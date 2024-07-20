#include<bits/stdc++.h>

using namespace std;
using ll=long long;

const int maxn=1000005;
int n,p[maxn+100],s[maxn+100],phi[maxn+100],tot;


/*
比n小且与n互质的数的和为phi[n]*n/2
*/


/*
p为质数
p|n&&p^2|n -> phi[n]=phi[n/p]*p
p|n&&!(p^2|n) -> phi[n]=phi[n/p]*(p-1)
=>
对于每一个i,枚举质数p,更新phi[i*p]
p^2|i*p即p|i以此更新
*/
void Phi(){
    phi[1]=1;
    for(int i=2;i<=maxn;i++){
        if(!s[i])p[++tot]=i,phi[i]=i-1;
        for(int j=1;j<=tot&&i*p[j]<=maxn;j++){
            s[i*p[j]]=1,phi[i*p[j]]=(p[j]-1)*phi[i];
            if(i%p[j]==0){
                phi[i*p[j]]=phi[i]*p[j]; 
                break;
            }
        }
    }
}

/*
求单个欧拉函数
*/
int getphi(int x){
    int ret=x;
    for(int i=2;i*i<=x;i++){
        if(x%i==0)ret=ret/i*(i-1);
        while(x%i==0)x/=i;
    }
    if(x>1)ret=ret/x*(x-1);
    return ret;
}
/*
正确
*/
void solve(){
    Phi();
    for(int i=1;i<100;i++)cout<<i<<" "<<phi[i]*i/2<<'\n';
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