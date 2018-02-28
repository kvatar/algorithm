#include <iostream>
#include <vector>
#include <algorithm>
using namespace std;

//************************partition************************
//包含begin，不包含end
pair<int, int> partition(vector<int> &vec, int begin, int end, int pivot)
{
	if (vec.size() <= 0 || begin < 0 || end > vec.size()) {
		return pair<int, int>(-1, -1);
	}
	int left = begin;	//小于pivot将要替换的位置
	int right = --end;	//大于pivot将要替换的位置
	int i = begin;
	while (i != right + 1) {
		if (vec[i] < pivot) {
			swap(vec[i++], vec[left++]);
		}
		else if (vec[i] > pivot) {
			swap(vec[i], vec[right--]);
		}
		else {
			i++;
		}
	}
	return pair<int, int>(left, right + 1);
}

int Process_GetMinKNumsByPartition(vector<int> &vec, int begin, int end, int k)
{
	if (begin == end) {
		return -1;
	}
	auto res = partition(vec, begin, end, vec[begin]);
	if (k >= res.first && k < res.second) {
		return vec[res.first];
	}
	else if (k < res.first) {
		return Process_GetMinKNumsByPartition(vec, begin, res.first,k);
	}
	else {
		return Process_GetMinKNumsByPartition(vec, res.second, end,k);
	}
}

int GetMinKNumsByPartition(vector<int> &vec, int k)
{
	if (k >= vec.size() || k < 0 || vec.size() < 0) {
		return -1;
	}
	vector<int> vectmp = vec;
	return Process_GetMinKNumsByPartition(vectmp, 0, vec.size(), k - 1);
}

int main() 
{
	vector<int> vec = { 6, 9, 1, 3, 1, 2, 2, 5, 6, 1, 3, 5, 9, 7, 2, 5, 6, 1, 9 };

	cout << GetMinKNumsByPartition(vec,4) << endl;
	return 0;
}