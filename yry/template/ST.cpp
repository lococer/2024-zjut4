#include <iostream>
#include <cmath>

using namespace std;
typedef long long ll;
int st[10000][100];

int main(){
    //freopen("aa.in","r",stdin);
    //freopen("aa.out","w",stdout);
    ios::sync_with_stdio(false);
    cin.tie(0);
    int l,ll,rr;
    cin>>l;
    for(int i=0;i<l;i++)cin>>st[i][0];
    int n=ceil(log(l));
    for(int i=1;i<=n;i++){
        for(int j=0;j+(1<<i)<=l;j++){
            st[j][i]=max(st[j][i-1],st[j+(1<<(i-1))][i-1]);
        }
    }
    while(cin>>ll>>rr){
        int tmp=log(rr-ll+1);
        cout<<max(st[ll][tmp],st[rr-(1<<tmp)+1][tmp])<<endl;
    }
    
}