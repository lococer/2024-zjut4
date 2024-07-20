#include<bits/stdc++.h>

using namespace std;
using ll=long long;
using ull=unsigned long long;
// using i128=__int128_t;
using pis=pair<ll,ll>;

const int N=1e6+100;
const ll mod=998244353;
const ll inf=1e18;
const int maxn=1e6+100;


struct SA{
    string s;
    vector<int> rk,sa,tmprk,cnt,tmpsa,height;
    int n,csize;
    SA(const string &ss){
        s=ss;
        n=s.length();csize=max(200,n);
        rk.resize(2*n+1);
        tmprk.resize(2*n+1);
        tmpsa.resize(n+1);
        sa.resize(n+1);
        height.resize(n+1);
        cnt.resize(csize+1);
        for(int i=1;i<=n;i++)sa[i]=i,rk[i]=s[i-1];
        if(n==1)rk[1]=1;
    }
    pis getrk(int a,int l){
        return pis{rk[a],rk[a+l]};
    }
    void stbsort(int l){
        for(int i=0;i<=csize;i++)cnt[i]=0;
        for(int i=1;i<=n;i++)cnt[getrk(i,l).second]++;
        for(int i=1;i<=csize;i++)cnt[i]+=cnt[i-1];
        for(int i=n;i>=1;i--)tmpsa[cnt[getrk(sa[i],l).second]--]=sa[i];
        sa=tmpsa;//第二关键词排序
        for(int i=0;i<=csize;i++)cnt[i]=0;
        for(int i=1;i<=n;i++)cnt[getrk(i,l).first]++;
        for(int i=1;i<=csize;i++)cnt[i]+=cnt[i-1];
        for(int i=n;i>=1;i--)tmpsa[cnt[getrk(sa[i],l).first]--]=sa[i];
        sa=tmpsa;//第一关键词排序
    }
    void work(){
        for(int w=1;w<n;w<<=1){
            stbsort(w);
            int nowrk=0;
            tmprk[sa[1]]=++nowrk;
            for(int i=2;i<=n;i++){
                if(getrk(sa[i],w)==getrk(sa[i-1],w))tmprk[sa[i]]=nowrk;
                else tmprk[sa[i]]=++nowrk;
            }
            for(int i=1;i<=n;i++)rk[i]=tmprk[i];
        }
        for(int i=1,k=0;i<=n;i++){
            int j=sa[rk[i]-1];
            if(k)k--;
            while(max(i,j)+k-1<n&&s[i+k-1]==s[j+k-1])k++;
            height[rk[i]]=k;
        }
    }
};

string s;

void solve(){
    cin>>s;
    SA sa(move(s));
    sa.work();
    for(int i=1;i<=s.length();i++)cout<<sa.sa[i]-1<<' ';
    cout<<'\n';
    for(int i=1;i<=s.length();i++)cout<<sa.height[i]<<' ';
}


signed main(){
    freopen("aa.in", "r", stdin);
    freopen("aa.out", "w", stdout);
    std::ios::sync_with_stdio(0);
    std::cin.tie(0);
    std::cout.tie(0);
    int t = 1;
    // std::cin>>t;  
    while (t--)
    solve();
}