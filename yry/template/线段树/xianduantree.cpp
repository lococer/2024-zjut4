/*************************************************************************
	* @Author: Ye Ruiyang
	* @Version: 1.0
	* @Other: none
	* @Created Time:2022年10月28日03:16:57
	* @Change Time:2022年10月30日00:09:33
************************************************************************/






#include <iostream>
#include <vector>
using namespace std;
void creat(vector<int>& num, vector<int>& qujian, int l = -1, int r = -1, int now = 0);
void updata(int l, int r, int d, vector<int>& num, vector<int>& qujian, int l_ = -1, int r_ = -1, int now = 0);
long long query(int l, int r, vector<int>& num, vector<int>& qujian, int l_ = -1, int r_ = -1, int now = 0);

int mark[100000];
int main()
{
	int n;
	cout << "输入大小:";
	cin >> n;
	vector<int> num(n),qujian(10000);
	for (int i = 0; i < n; i++)cin >> num[i];
	creat(num, qujian);
	cout << "输入数组（1更新 2查询 0退出):";
	int op;
	while (cin >> op) {
		if (!op)break;
		if (op == 1) {
			int d, l,r;
			cin >> l >> r>>d;
			updata(l, r, d, num, qujian);
		}
		if (op == 2) {
			int l, r;
			cin >> l >> r;
			cout << query(l, r, num, qujian)<<endl;
		}
	}
    
}

void creat(vector<int> &num,vector<int> &qujian, int l, int r, int now) {
	if (l == -1 && r == -1)l = 0, r = num.size() - 1;
	if (l == r) {
		qujian[now] = num[l];
		return;
	}
	int m = (r-l) / 2 + l;
	creat( num, qujian, l, m, 2 * now + 1);
	creat( num, qujian, m + 1, r, 2 * now + 2);
	qujian[now] = qujian[now * 2 + 1] + qujian[now * 2 + 2];


}
void updata(int l, int r, int d, vector<int>& num, vector<int>& qujian,int l_,int r_,int now) {
	if (l_ == -1 && r_ == -1)l_ = 0, r_ = num.size() - 1;
	if (l > r_ || r < l_)return;
	if (l <= l_ && r >= r_) {
		mark[now] += d;
		return;
	}
	qujian[now] += (min(r_, r) - max(l_, l)+1) * d;
	if (l_ == r_)return;
	int m= (r_ - l_) / 2 + l_;
	updata(l, r, d, num, qujian, l_, m, now * 2 + 1);
	updata(l, r, d, num, qujian, m+1, r_, now * 2 + 2);
}
long long query(int l, int r, vector<int>& num, vector<int>& qujian, int l_ , int r_ , int now) {
	if (l_ == -1 && r_ == -1)l_ = 0, r_ = num.size() - 1;
	if (mark[now]) {
		qujian[now] += (r_-l_+1)*mark[now];
		mark[now * 2 + 1]+= mark[now];
		mark[now * 2 + 2]+= mark[now];
		mark[now] = 0;
	}
	if (l <= l_ && r >= r_)return qujian[now];
	if (l > r_ || r < l_)return 0;
	int m = (r_ - l_) / 2 + l_;
	return query(l, r, num, qujian, l_, m, now * 2 + 1)+ query(l, r, num, qujian, m+1, r_, now * 2 + 2);

}


