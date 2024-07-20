

#include <iostream>
#include <string>
#include <algorithm>
#include <vector>
using namespace std;
/*
dp[i][0]指小于数字n前i位数的个数
dp[i][1]指等于数组n前i位数的个数 为0或1
dp[i][0]=dp[i-1][0]*数字集大小+数字集大小(若数字集有0则不需要的，因为前导0可以消掉)+dp[i-1][1]*(num中小于n[i-1]的个数)
if(num中有s[i-1]）dp[i][1]=dp[i-1][1]
*/
int main()
{
    cout << "输入数字集:";
    string num;
    cin >> num;
    cout << "输入n:";
    string n;
    cin >> n;
    sort(num.begin(), num.end());
    vector<vector<int>> dp(n.size() + 1, vector<int>(2, 0));
    dp[0][1] = 1;
    int mm = num.size(), nn = n.size();
    for (int i = 1; i <= nn; i++) {
        for (int j = 1; j <= mm; j++) {
            if (n[i - 1] == num[j - 1])dp[i][1] = dp[i - 1][1];
            else if (n[i - 1] > num[j - 1])dp[i][0] += dp[i - 1][1];
            else break;
        }
        if(i>1)dp[i][0] += mm * dp[i - 1][0] + (num[0]=='0'?0:mm);
    }
    cout << "共有" << dp[nn][0]+dp[nn][1] << "个数字";
}


