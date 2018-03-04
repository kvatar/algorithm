#ifndef BINTARY_TREE_H
#define BINTARY_TREE_H

#include <vector>
#include <iostream>
#include <cassert>

template <typename T>
class Bintary_Tree
{
public:
    typedef T           data_type;
    struct Node{
        Node            *leftchild;
        Node            *rightchild;
        data_type       data;

		Node(data_type da = data_type()) : data(da), leftchild(nullptr), rightchild(nullptr) {}
	};

public:
	Bintary_Tree();

    Bintary_Tree(const std::vector<data_type> &vec,data_type sign);

	void Print_Prev()const;
private:
    static void create_tree_help_func(Node *&p,const std::vector<data_type> &vec,data_type sign,int &pos);

	static void Print_Prev(Node *p);
private:
    Node *root;
};

template <typename T>
Bintary_Tree<T>::Bintary_Tree()
{
	int pos = 0;
	create_tree_help_func(root, vec, sign, pos);
}

template <typename T>
void Bintary_Tree<T>::create_tree_help_func(Node *&p, const std::vector<data_type> &vec, data_type sign, int &pos)
{
	if (p != nullptr || pos >= static_cast<int>(vec.size())) {
		std::cout << "creatr_tree_help_fun invaild parameter" << std::endl;
		return;
	}

	if (vec[pos] == sign) {
		p = nullptr;
	}
	else {
		p = new Node(vec[pos]);
	}
	pos++;

	if (p != nullptr) {
		create_tree_help_func(p->leftchild, vec, sign, pos);
		create_tree_help_func(p->rightchild, vec, sign, pos);
	}

}

template <typename T>
Bintary_Tree<T>::Bintary_Tree(const std::vector<data_type> &vec, data_type sign)
{
	int pos = 0;
	create_tree_help_func(root, vec, sign, pos);
}

template <typename T>
void Bintary_Tree<T>::Print_Prev(Node *p)
{
	if (p != NULL) {
		std::cout << p->data << " ";
		Print_Prev(p->leftchild);
		Print_Prev(p->rightchild);
	}
	else {
		std::cout << "#" << " ";
	}
}

template <typename T>
void Bintary_Tree<T>::Print_Prev() const
{
	Print_Prev(root);
	std::cout << std::endl;
}

#endif
