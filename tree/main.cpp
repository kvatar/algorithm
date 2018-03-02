#include "binary_tree.hpp"
using namespace std;

int main()
{
	vector<int> vec = {1,2,3,0,0,0,0};
	Bintary_Tree<int> btree(vec,0);
	btree.Print_Prev();
	return 0;
}
