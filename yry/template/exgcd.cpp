#include <bits/stdc++.h>
using namespace std;
typedef long long ll;


/*
求ax0+by0=gcd(a,b)
已知bx1+(a%b)y1=gcd(b,a%b)
gcd(a,b)=gcd(b,a%b)
=>ax0+by0=bx1+(a-a\\b*b)y1
=>x0=y1 y0=x1-a\\b*y1
*/
ll exgcd(ll a,ll b,ll &x,ll &y){
    if(b==0){
        x=1;
        y=0;
        return a;
    }
    ll ret=exgcd(b,a%b,x,y);
    ll x1=x,y1=y;
    x=y1;y=x1-a/b*y1;
    return ret;
}
 
/*
满足gcd(a,mod)=1
ax+py=1
ax0+py0=1

x=x0+kp y=y0-ka
*/
ll inverse(ll a,ll mod){
    ll x,y;
    exgcd(a,mod,x,y);
    return (x+mod)%mod;
}
 
int main() {
    ios::sync_with_stdio(0);
    cin.tie();
    ll x,y,m,n,l,x0,y0;
    cin>>x>>y>>m>>n>>l;
    if(n<m){
        swap(n,m);
        swap(x,y);
    }
    ll tmp=exgcd(n-m,l,x0,y0);
    if((x-y)%tmp)cout<<"Impossible";
    else cout<<(x0*(x-y)/tmp%(l/tmp)+(l/tmp))%(l/tmp);
    return 0;
}
 
/*#include <iostream>
#include <windows.h>
 
using namespace std;
 
int main(){
    int a;
    cin>>a;
    if(a==114514){
        MessageBoxW(NULL,L"成功了",L"ok",0);
    }else{
        MessageBoxW(NULL,L"失败了",L"ok",0);
    }
    return 0;
}*/