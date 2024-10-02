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


struct ST{
    vector<int> nums;
    vector<vector<int>> st;
    int n,logn;
    const int inf=1e9+100;
    // const int inf=-1;
    ST(const vector<int> &_nums){
        nums=_nums;
        n=nums.size()-1;
        logn=floor(log2(n));
        st.resize(n+1,vector<int>(logn+1,inf));
        for(int i=1;i<=n;i++)st[i][0]=nums[i];
        for(int j=1;j<=logn;j++){
            for(int i=1;i<=n;i++){
                if(i+(1<<(j-1))<=n)st[i][j]=min(st[i][j-1],st[i+(1<<(j-1))][j-1]);
            }
        }
    }
    int ask(int l,int r){
        int d=r-l+1;
        d=floor(log2(d));
        return min(st[l][d],st[r-(1<<d)+1][d]);
    }
};



void solve(){
    vector<int> a;
    int n,m;
    cin>>n>>m;
    a.resize(n+1);
    for(int i=1;i<=n;i++)cin>>a[i];
    ST st(move(a));
    for(int i=1;i<=m;i++){
        int l,r;
        cin>>l>>r;
        cout<<st.ask(l,r)<<'\n';
    }
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