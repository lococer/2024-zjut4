

#include <iostream>
#include <string>
#include <vector>

using namespace std;
int main()
{
	cout << "主串:";
	string s, target;
	cin >> s;
	cout << "模式串:";
	cin >> target;
	int m = s.length(), n = target.length();
	vector<int> next(n+1, 0);
	int i = 1, j = 0;
	next[0] = -1;
	if (n > 1)next[1] = 0;
	int cs = 0;
	/*
	求next数组
	*/
	while (i < n) {
		while (i<n && target[i] == target[j]) {
			i++;
			j++;
			if (target[i] == target[next[j]])next[i] = next[j];//相等的跳过,
			else next[i] = j;
			
		}
		if (j == 0 && i<n)next[i + 1] = 0,i++;
		else j = next[j];

	}
	i = 0;
	j = 0;
	while (i < m && j<n) {
		cs++;
		if (j==-1 || s[i] == target[j]) {
			i++;
			j++;
		}
		else {
			j = next[j];
		}
		if (j == n)cout << i-j << endl,j=next[j];
	}
	cout << "执行了" << cs << "次";
	return 0;
}

/*
#include <bits/stdc++.h>
using namespace std;
typedef long long ll;
typedef pair<ll,ll> pis;



int main() {
    ios::sync_with_stdio(0);
    cin.tie();
    string s1,s2;
    cin>>s1>>s2;
    int d[s2.length()+1]={0};
    d[0]=-1;
    //预处理
    int p1=0,p2=-1;
    while(p1<s2.length()){
        if(p2==-1||s2[p1]==s2[p2]){
            p1++;
            p2++;
            d[p1]=p2;
        }else p2=d[p2];
    }
    for(auto a:d)cout<<a<<" ";
    cout<<'\n';
    //kmp
    p1=0,p2=0;
    while(p1<s1.length()){
        if(p2==-1||s1[p1]==s2[p2]){
            p1++;
            p2++;
        }else p2=d[p2];
        if(p2==s2.length()){
            cout<<p1-p2<<" ";
            p2=d[p2];
        }
    }
    

    return 0;
}*/



