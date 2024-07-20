
#include <iostream>
using namespace std;


int main()
{

	int Mark[100000]{ 0 };
	int prime[100000]{ 0 };
	int index = 0;
	for (int i = 2; i < 100000; i++) {
		//如果未标记则得到一个素数  
		if (Mark[i] == 0) prime[++index] = i;
		//标记目前得到的素数的i倍为非素数  
		for (int j = 1; j <= index && prime[j] * i < 100000; j++) {
			Mark[i * prime[j]] = 1;
			if (i % prime[j] == 0) break;
		}
	}
	/*
	若i能整除prime[j]，说明i因数有prime[j]，那么i*prime[j+]一定整除prime[j],留给其他i
	*/
	return index;
}


