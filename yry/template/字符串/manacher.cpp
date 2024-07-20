#include <bits/stdc++.h>
using namespace std;
typedef long long ll;
 
/*
加上哨兵 判断边界
*/
char* getnewstr(const char* str,int l){
    char* news=(char*)malloc(l*2+3);
    int p=0;
    news[p++]='!';news[p++]='#';
    for(int i=0;i<l;i++){
        news[p++]=str[i];
        news[p++]='#';
    }
    news[p++]='\0';
    return news;
}
/*
manacher
*/
int manacher(const char* str){
    int l=strlen(str);
    int len[l],p=0,ans=0;
    len[0]=1;
    for(int i=1;i<l;i++){
        len[i]=1;
        if(i<p+len[p]-1)len[i]=min(len[2*p-i],p+len[p]-i);
        while(str[i-len[i]]==str[i+len[i]])len[i]++;
        if(i+len[i]>p+len[p])p=i;
        ans=max(ans,len[i]-1);
    }
    return ans;
}

/*
原始方法
*/
int mid(const char* str){
    int l=strlen(str);
    int len[l],ans=0;
    for(int i=1;i<l;i++){
        len[i]=1;
        while(str[i-len[i]]==str[i+len[i]])len[i]++;
        ans=max(ans,len[i]-1);
    }
    return ans;
}



int main() {
    ios::sync_with_stdio(0);
    cin.tie();
    string s;
    cin>>s;
    cout<<manacher(getnewstr(s.c_str(),s.length()));
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