#include <iostream>
#include <vector>
using namespace std;

template <typename T>
void Printsubset(const vector<T> &vec)
{
	for (int i = 0; i < pow(2, vec.size()); ++i) {
		int mask = 1;
		for (int j = 0; j < vec.size(); ++j) {
			if ((mask & i) != 0) {
				cout << vec[j] << " ";
			}
			mask <<= 1;
		}
		cout << endl;
	}
}


int main()
{
	vector<int> vec = { 1,2,3,4,5 };
	Printsubset(vec);
	return 0;
}