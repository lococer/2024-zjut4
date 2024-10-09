#include<bits/stdc++.h>

using namespace std;
using ll=long long;
using pis=pair<ll,ll>;

const int N=3e5+100;



/*
所有操作的数必须存在，可以先插入再删除
*/
struct Splay{
    vector<vector<int>> ch;
    vector<int> fa,siz,cnt,val;
    int n,tot,root;
    Splay(int n_){
        n=n_;
        tot=root=0;
        ch.resize(n+1,vector<int>(2));
        val=fa=siz=cnt=vector<int>(n+1);
    }
    int getlr(int x){return x==ch[fa[x]][1];}
    void link(int x,int y,int lr){
        fa[x]=y;
        ch[y][lr]=x;
    }
    void maintain(int x){
        if(x==0)clear(x);
        else siz[x]=siz[ch[x][0]]+siz[ch[x][1]]+cnt[x];
    }
    void clear(int x){siz[x]=ch[x][0]=ch[x][1]=fa[x]=val[x]=cnt[x]=0;}
    void rorate(int x){
        int y=fa[x],z=fa[y],xid=getlr(x),yid=getlr(y);
        if(!y)return;
        link(ch[x][xid^1],y,xid);
        link(y,x,xid^1);
        link(x,z,yid);
        maintain(y);
        maintain(x);
    }
    void splay(int x){
        while(fa[x]){
            if(fa[x]==root)rorate(x);
            else if(getlr(x)==getlr(fa[x]))rorate(fa[x]),rorate(x);
            else rorate(x),rorate(x);
        }
        root=x;
    }
    int find_pre(){
        int cur = ch[root][0];
        if( cur == 0 )return -1;
        while( ch[cur][1] )cur = ch[cur][1];
        splay(cur);
        return cur;
    }
    int find_next(){
        int cur = ch[root][1];
        if( cur == 0 )return -1;
        while( ch[cur][0] )cur = ch[cur][0];
        splay(cur);
        return cur;
    }
    int find_rank(int v){
        int ans = 0,cur = root;
        while(1)
        {
            if(v<val[cur])cur=ch[cur][0];
            else{
                ans += siz[ch[cur][0]];
                if( v == val[cur] ){
                    splay(cur);
                    return ans + 1;
                }
                ans += cnt[cur];
                cur = ch[cur][1];
            }
        }
    }
    int find_num(int v){
        int cur = root;
        while(1){
            if(ch[cur][0]!=0&&v<=siz[ch[cur][0]])
                cur=ch[cur][0];
            else{
                v -=cnt[cur]+siz[ch[cur][0]];
                if(v<=0){
                    splay(cur);
                    return val[cur];
                }
                cur = ch[cur][1];
            }
        }
    }
    void ins(int v){
        if(!root){
            root=++tot;
            val[tot]=v;
            cnt[tot]++;
            maintain(tot);
            return;
        }
        int now=root,pre=0;
        while(1){
            if(now==0){
                ++tot;
                val[tot]=v;
                cnt[tot]++;
                link(tot,pre,v>val[pre]);
                maintain(tot);
                maintain(pre);
                splay(tot);
                break;
            }
            if(val[now]==v){
                cnt[now]++;
                maintain(now);
                maintain(pre);
                splay(now);
                break;
            }
            pre=now;
            now=ch[now][v>val[now]];
        }
    }
    void del(int v){
        find_rank(v);
        if(cnt[root]>1){
            cnt[root]--;
            maintain(root);
            return;
        }
        if(!ch[root][0]&&!ch[root][1]){
            clear(root);
            root=0;
            return;
        }
        if(!ch[root][0]){
            int x=root;
            root=ch[root][1];
            fa[root]=0;
            clear(x);
            return;
        }
        if(!ch[root][1]){
            int x=root;
            root=ch[root][0];
            fa[root]=0;
            clear(x);
            return;
        }
        int now = root;
        int x = find_pre();
        link(ch[now][1],x,1);
        clear(now);
        maintain(root);
    }
};


void solve(){
    int n;
    cin>>n;
    Splay st(n);
    for(int i=1;i<=n;i++){
        int op;
        cin>>op;
        if(op==1){
            int x;
            cin>>x;
            st.ins(x);
        }else if(op==2){
            int x;
            cin>>x;
            st.del(x);
        }else if(op==3){// rank
            int x;
            cin>>x;
            st.ins(x);
            cout<<st.find_rank(x)<<'\n';
            st.del(x);
        }else if(op==4){
            int x;
            cin>>x;
            cout<<st.find_num(x)<<'\n';
        }else if(op==5){
            int x;
            cin>>x;
            st.ins(x);
            cout<<st.val[st.find_pre()]<<'\n';
            st.del(x);
        }else{
            int x;
            cin>>x;
            st.ins(x);
            cout<<st.val[st.find_next()]<<'\n';
            st.del(x);
        }


    }

}

int main(){
    std::ios::sync_with_stdio(0);
    std::cin.tie(0);
    std::cout.tie(0);
    int t=1;
    // cin>>t;
    while(t--)solve();
    return 0;
}

/*
10
1 964673
5 968705
4 1
3 964673
5 965257
1 915269
1 53283
3 964673
3 53283
3 53283

4
1 1
1 2
3 1
3 1

*/