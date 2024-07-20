#include <bits/stdc++.h>
using namespace std;
using ll = long long;
using pis = pair<ll, ll>;
using pisi = pair<int, int>;
using tup = tuple<ll, int, int>;
const ll mod=1000000007;
const int N=1e6+5;
ll tree[N<<1];
ll L[N<<1],R[N<<1],n,lazy[N<<1];


int build(){
    for(int i=n-1;i<2*n-1;i++)L[i]=R[i]=i-n+1;
    for(int i=n-2;i>=0;i--){
        tree[i]=tree[(i<<1)+1]+tree[(i<<1)+2];
        L[i]=L[(i<<1)+1];R[i]=R[(i<<1)+2];
    }
}

void down(int now){
    if(!lazy[now])return;
    int ls=(now<<1)+1,rs=ls+1;
    tree[ls]+=(R[ls]-L[ls]+1)*lazy[now];
    tree[rs]+=(R[rs]-L[rs]+1)*lazy[now];
    lazy[ls]+=lazy[now];lazy[rs]+=lazy[now];
    lazy[now]=0;
}

void update(int now,int l,int r,int k){
    if(L[now]==R[now]){
        tree[now]+=k;
        return;
    }
    if(l<=L[now]&&r>=R[now]){
        lazy[now]+=k;
        tree[now]+=1ll*(R[now]-L[now]+1)*k;
        return;
    }
    down(now);
    int l1=L[(now<<1)+1],r1=R[(now<<1)+1],l2=L[(now<<1)+2],r2=R[(now<<1)+2];
    if(max(l,l1)<=min(r,r1))update((now<<1)+1,l,r,k);
    if(max(l,l2)<=min(r,r2))update((now<<1)+2,l,r,k);
    tree[now]=tree[(now<<1)+1]+tree[(now<<1)+2];
}

void update_one(int p,int k){
    for(int i=n-1+p;i>=0;i=(i-1)>>1)tree[i]+=k;
}

ll query(int now,int l,int r){
    if(l<=L[now]&&r>=R[now])return tree[now];
    down(now);
    ll ret=0;
    int l1=L[(now<<1)+1],r1=R[(now<<1)+1],l2=L[(now<<1)+2],r2=R[(now<<1)+2];
    if(max(l,l1)<=min(r,r1))ret+=query((now<<1)+1,l,r);
    if(max(l,l2)<=min(r,r2))ret+=query((now<<1)+2,l,r);
    return ret;
}


int main()
{
    #ifndef ONLINE_JUDGE
    freopen("aa.in", "r", stdin);
    freopen("aa.out", "w", stdout);
    #endif 
    ios::sync_with_stdio(0);
    cin.tie(0);
    int t=1;
    //cin >> t;
    while (t--)
    {
        int m,p=0;
        cin>>n>>m;
        while((1<<p)<n)p++;
        int nn=n;
        n=1<<p;
        for(int i=n-1;i<n-1+nn;i++)cin>>tree[i];
        
        build();
        for(int i=0;i<m;i++){
            int a,b,c,d;
            cin>>a>>b>>c;
            if(a==1){
                cin>>d;
                update(0,b-1,c-1,d);
            }else{
                cout<<query(0,b-1,c-1)<<'\n';
            }
        }
        
        
    }
    return 0;
}