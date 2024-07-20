#include <bits/stdc++.h>

using namespace std;

using ll=long long;
using pis=pair<ll,ll>;

/*
1 5 4 2 3
2 6 5 3 3
2 12 10 6 3
2 12 15 11 8
*/
template <typename T>
class segementtree
{
private:
    /* data */
    vector<T> sum,mark,num,mark_;//mark用来给子区间用,自身保证正确
    ll n_,mod;
    
    void pushup(int now){
        sum[now]=(sum[2*now+1]+sum[2*now+2])%mod;
    }
    void pushdown(int now,int nl,int nr){
            mark_[now*2+1]*=mark_[now];
            mark_[now*2+2]*=mark_[now];
            mark[now*2+1]*=mark_[now];
            mark[now*2+2]*=mark_[now];
            sum[now*2+1]*=mark_[now];
            sum[now*2+2]*=mark_[now];
            sum[now*2+1]%=mod;
            sum[now*2+2]%=mod;
            mark_[now*2+1]%=mod;
            mark_[now*2+2]%=mod;
            mark[now*2+1]%=mod;
            mark[now*2+2]%=mod;
            mark_[now]=1;
            mark[now*2+1]+=mark[now];
            mark[now*2+2]+=mark[now];
            sum[now*2+1]+=mark[now]*nl;
            sum[now*2+2]+=mark[now]*nr;
            sum[now*2+1]%=mod;
            sum[now*2+2]%=mod;
            mark[now]=0;
        
    }
    void build(int l,int r,int now){
        int m=(l+r)/2;
        if(l==r){
            sum[now]=num[l]%mod;
            return;
        }
        build(l,m,2*now+1);
        build(m+1,r,2*now+2);
        pushup(now);
    }
    void update(int L,int R,ll d,int l,int r,int now){
        int m=(l+r)/2;
        if(L<=l&&R>=r){
            sum[now]+=(r-l+1)*d;
            sum[now]%=mod;
            mark[now]+=d;
            mark[now]%=mod;
            return;
        }
        pushdown(now,m-l+1,r-m);
        if(L<=m)update(L,R,d,l,m,2*now+1);
        if(R>m)update(L,R,d,m+1,r,2*now+2);
        pushup(now);//用来保证自身正确
    }
    void update_(int L,int R,ll d,int l,int r,int now){
        int m=(l+r)/2;
        if(L<=l&&R>=r){
            sum[now]*=d;
            sum[now]%=mod;
            mark[now]*=d;
            mark[now]%=mod;
            mark_[now]*=d;
            mark_[now]%=mod;
            return;
        }
        pushdown(now,m-l+1,r-m);
        if(L<=m)update_(L,R,d,l,m,2*now+1);
        if(R>m)update_(L,R,d,m+1,r,2*now+2);
        pushup(now);//用来保证自身正确
    }
    T query(int L,int R,int l,int r,int now){
        int m=(l+r)/2;
        if(L<=l&&R>=r){
            return sum[now]%mod;
        }
        pushdown(now,m-l+1,r-m);
        ll ret=0;
        if(L<=m)ret+=query(L,R,l,m,2*now+1);
        if(R>m)ret+=query(L,R,m+1,r,2*now+2);
        return ret%mod;
    }
public:
    segementtree(/* args */)=default;
    ~segementtree()=default;
    segementtree(int n,vector<T> &tmp,ll mod_){
        sum.resize(n<<2,0);
        mark.resize(n<<2,0);
        mark_.resize(n<<2,0);
        for(int i=0;i<(n<<2);i++)mark_[i]=1;
        num=tmp;
        n_=n;
        mod=mod_;
        build(0,n-1,0);
    }
    T _query(int l,int r){
        return query(l,r,0,n_-1,0);
    }
    void _update(int l,int r,ll d){
        update(l,r,d,0,n_-1,0);
    }
    void _update_(int l,int r,ll d){
        update_(l,r,d,0,n_-1,0);
    }


};









int main(){
    ios::sync_with_stdio(false);
    cin.tie(0);
    freopen("aa.in","r",stdin);
    freopen("aa.out","w",stdout);
    ll n,m,mo=100000000000;
    cin>>n>>m;
    vector<ll> nums(n);
    for(int i=0;i<n;i++)cin>>nums[i];
    segementtree<ll> sg(n,nums,mo);
    for(int i=0;i<m;i++){
        ll op,x,y;
        cin>>op>>x>>y;
        if(op==2){
            cout<<sg._query(x-1,y-1)<<'\n';
        }else{
            sg._update(x-1,x-1,y);
        }
    }
    return 0;
}


