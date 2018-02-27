#include <iostream>
#include <string>
#include <vector>
#include <algorithm>
using namespace std;

//在str首尾以及字符中间加入相同字符，解决偶数回文情况
string GetOddString(string str)
{
	string res;
	res.resize(2 * str.length() + 1);
	for (unsigned int i = 0; i < res.length(); ++i) {
		res[i] = (i & 1) == 0 ? '#' : str[i / 2];
	}
	return res;
}
//求字符串最大回文串，返回最大回文的长度及首字符位置
int maxLcpsLength(string st,int &pos) 
{
	if (st.length() < 1) {
		pos = -1;
		return 0;
	}

	string str = GetOddString(st);
	vector<int> vec(str.length());	//	存回文半径

	int res_max_len = 0;	//扩充后的最大半径
	pos = 0;				//扩充后最大半径时，圆心的位置

	int C = -1;	//达到最大回文右边界时，圆心的位置
	int R = -1;	//最大会问右边界，最右面的下标
	for (int i = 0; i < str.length(); ++i) {
		vec[i] = R > i ? (min(vec[2 * C - i],R - i)) : 1;
		while (i - vec[i] > -1 && vec[i] + i < vec.size()) {
			if (str[i - vec[i]] == str[vec[i] + i]) {
				++vec[i];
			}
			else {
				break;
			}
		}
		--vec[i];
		if (vec[i] > res_max_len) {
			res_max_len = vec[i];
			pos = i;
		}
	}
	pos -= res_max_len;
	pos /= 2;
	return res_max_len;
}

int main()
{
	string str = "";
	int pos = 0;
	int len = maxLcpsLength(str, pos);
	cout << pos << " " << len << endl;

	return 0;
}
