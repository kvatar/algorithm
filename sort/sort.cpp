#include <iostream>
#include <vector>
#include <algorithm>
using namespace std;

//***************************����*******************************

//����begin��������end
pair<int, int> partition(vector<int> &vec, int begin, int end, int pivot)
{
	if (vec.size() <= 1 || begin < 0 || end > vec.size()) {
		return pair<int, int>(-1, -1);
	}
	int left = begin;	//С��pivot��Ҫ�滻��λ��
	int right = --end;	//����pivot��Ҫ�滻��λ��
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
	auto res = partition(vec, begin, end, vec[begin]);
	if (res.first != begin) {
		process(vec, begin, res.first);
	}
	if (res.second != end) {
		process(vec, res.second, end);
	}
}


void QucikSort(vector<int> &vec) 
{
	process(vec, 0, vec.size());
}

int main()
{
	vector<int> vec = { 6, 9, 1, 3, 1, 2, 2, 5, 6, 1, 3, 5, 9, 7, 2, 5, 6, 1, 9 };
	QucikSort(vec);

	for (int i = 0; i < vec.size(); ++i) {
		cout << vec[i] << " ";
	}
	cout << endl;

	return 0;
}