#include <iostream>
#include <vector>
#include <algorithm>
using namespace std;

//***************************快排*******************************

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

void process(vector<int> &vec, int begin, int end) 
{
	if (begin == end) {
		return;
	}
	auto res = partition(vec, begin, end, vec[begin]);
	process(vec, begin, res.first);
	process(vec, res.second, end);
	
}


void QucikSort(vector<int> &vec) 
{
	process(vec, 0, vec.size());
}

int main()
{
	vector<int> vec;
	QucikSort(vec);
	auto res = partition(vec, 0, 1, 0);

	for (int i = 0; i < vec.size(); ++i) {
		cout << vec[i] << " ";
	}
	cout << endl;

	return 0;
}