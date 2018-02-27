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



int main()
{
	string str1 = "ababcababck";
	vector<int> vec = GetNext(str1);
	for (auto it = vec.begin(); it != vec.end(); ++it) {
		cout << *it << " ";
	}
	cout << endl;

	return 0;
}