#include <iostream>
#include <string>
#include <vector>
#include <algorithm>
using namespace std;

//��str��β�Լ��ַ��м������ͬ�ַ������ż���������
string GetOddString(string str)
{
	string res;
	res.resize(2 * str.length() + 1);
	for (unsigned int i = 0; i < res.length(); ++i) {
		res[i] = (i & 1) == 0 ? '#' : str[i / 2];
	}
	return res;
}
//���ַ��������Ĵ������������ĵĳ��ȼ����ַ�λ��
int maxLcpsLength(string st,int &pos) 
{
	if (st.length() < 1) {
		pos = -1;
		return 0;
	}

	string str = GetOddString(st);
	vector<int> vec(str.length());	//	����İ뾶

	int res_max_len = 0;	//���������뾶
	pos = 0;				//��������뾶ʱ��Բ�ĵ�λ��

	int C = -1;	//�ﵽ�������ұ߽�ʱ��Բ�ĵ�λ��
	int R = -1;	//�������ұ߽磬��������±�
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
