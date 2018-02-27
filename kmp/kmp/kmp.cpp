#include <iostream>
#include <string>
#include <vector>
#include <algorithm>
using namespace std;

vector<int> GetNext(string str1) {
	vector<int> vec(str1.length());
	if (vec.size() == 0) {
		return vec;
	}
	vec[0] = -1;

	if (vec.size() == 1) {
		return vec;
	}
	vec[1] = 0;

	for (int i = 2; i < vec.size(); ++i) {
		int j = vec[i - 1];
		while (j != -1 && str1[j] != str1[i - 1]) {
			j = vec[j];
		}
		vec[i] = j + 1;
	}
	return vec;
}

int SerchStr_KMP(const string &str1, const string &str2)
{
	if (str1.length() == 0 || str2.length() == 0 || str2.length() < 1 || str1.length() < str1.length()) {
		return -1;
	}
	auto next = GetNext(str2);

	int i = 0;
	int j = 0;
	while (i < str1.length() && j < str2.length()) {
		if (str1[i] == str2[j]) {
			++i;
			++j;
		}
		else {
			j = next[j];
			if (j == -1) {
				j = 0;
				++i;
			}
		}
	}
	return j == str2.length() ? i - j : -1;
}



int main()
{
	string str1 = "abcabcdabcabce";
	string str2 = "abcabce";
	cout << SerchStr_KMP(str1, str2) << endl;

	return 0;
}