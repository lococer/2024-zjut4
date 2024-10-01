//string machine
struct sm{
    vector<int> nxt,z,s,top;
    int lst;
    sm(int n):nxt(n+1),z(n+1,-1),s(n+1),top(n+1){
        nxt[0]=-1;
        lst=0;
    }
    void ins(int x){
        int p=nxt[lst];
        while(p!=-1&&s[p+1]!=x)p=nxt[p];
        nxt[lst+1]=p+1;
        p=nxt[lst];
        if(s[p+1]==x)top[lst]=top[p];
        else top[lst]=lst;
        while(p!=-1){
            if(s[p+1]==x){
                p=nxt[top[p]];
                continue;
            }
            z[lst-p+1]=p;
            p=nxt[p];
        }
        s[++lst]=x;
    }
};