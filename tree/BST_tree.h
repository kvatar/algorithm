#ifndef SEARCH_TREE_H
#define SEARCH_TREE_H

#include <iostream>
using namespace std;

template<typename T>
class BSTree
{
	typedef T value_type;
	typedef value_type * pointer;
	typedef value_type & reference;
	typedef int size_type;
	typedef unsigned int difference_type;
	
	struct BstNode 
	{
		value_type data;
		BstNode * leftchild;
		BstNode * rightchild;
		BstNode * parent;
	};
private:
	BstNode *root;

	static BstNode *_BuyNode()
	{
		BstNode * s = (BstNode *)malloc(sizeof(BstNode));
		if(s  == NULL) exit(1);
		memset(s,0,sizeof(BstNode));
		return s;
	}
	
	void _DestroyLeafNode(BstNode *&s)
	{
		if(s != NULL)
		{
			if(s->parent == NULL)
				root = NULL;
			else if(s == s->parent->leftchild)
				s->parent->leftchild = NULL;
			else if(s == s->parent->rightchild)
				s->parent->rightchild = NULL;
			free(s);
			s = NULL;
		}
	}
	
public:
	BSTree() : root(NULL){}

	//Ñ­»·
	BstNode *Find(T kx)
	{
		return _Findvalue(root,kx);
	}
	
	//µÝ¹é
	BstNode *Search(T kx)
	{
		return _Searchvalue(root,kx);
	}

	bool Insert_rec(const T &x)
	{
		return Insert_rec(root,NULL,x);
	}

	bool Insert(const T &x)
	{
		BstNode * s = _BuyNode();
		s->data = kx;
		if(root == NULL)
		{
			root = s;
			s->parent = NULL;
			return true;
		}
		BstNode *p = root;
		BstNode *pa = NULL;
		while(p != NULL)
		{
			if(kx == p->data)
				return false;
			pa = p;
			p = p->data > kx ? p->leftchild : p->rightchild;		
		}
		if(pa->data > kx)
		{
			pa->leftchild = s;
			s->parent = pa;
		}
		else
		{
			pa->rightchild = s;
			s->parent = pa;
		}
		return true;
	}

	bool Delete_Node(BstNode *s)
	{
		if(s == NULL)
			return false;
		if(s->== NULL && s->rightchild == NULL)
		{
			_DestroyLeafNode(s);
			return true;
		}
		else if(s->leftchild != NULL)
		{
			BstNode *p = Pre_Node(s);
			s->data = p->data;
			Delete_Node(p);
			return true;
		}
		else 
		{
			BstNode *p = Suc_Node(s);
			s->data = p->data;
			Delete_Node(p);
			return true;
		}

	}

	/*bool Remove_rec(const T &x)
	{
		Remove_rec(root,x);
	}*/


	void Print()
	{
		InOrder(root);
		cout<<endl;
	}
	
	BstNode * Min_Value_Node()
	{
		return Min_Value_Node(root);
	}

	BstNode * Max_Value_Node()
	{
		return Max_Value_Node(root);
	}

	static BstNode * Pre_Node(BstNode *p)
	{
		if(p->leftchild != NULL)
			return Max_Value_Node(p->leftchild);
		else
		{
			BstNode *pa = p->parent;
			while(pa != NULL && p != pa->rightchild)
			{				
				p = pa;
				pa = p->parent;	
			}
			if(pa == NULL)
				return false;
			return pa;
		}
	}
	static BstNode *Suc_Node(BstNode *p)
	{
		if(p == NULL)	return ;
		if(p->rightchild != NULL)
			return Min_Value_Node(p->rightchild);
		else
		{
			BstNode *pa = p->parent;
			while(pa != NULL && p != pa->leftchild)
			{				
				p = pa;
				pa = p->parent;	
			}
			return pa;
		}
	}
private:
	/*static bool Remove_rec(BstNode *&ptr,const T &x)
	{
		bool res = false;
		if(ptr == NULL)	return res;
		if(x < ptr->data)
		{
			Remove_rec(ptr->leftchild,x);
		}
		else if(x > ptr->data)
		{
			Remove_rec(ptr->rightchild,x);
		}
		else 
		{
		
		}
		return res;
	}*/


	static bool Insert_rec(BstNode *&ptr,BstNode *pa,const T &x)
	{
		if(ptr == NULL)
		{
			ptr = _BuyNode();
			ptr->data = x;
			ptr->parent = pa;
			return true;
		}
		if(ptr->data == x)
			return false;
		if(x > ptr->data)
		{
			return Insert_rec(ptr->rightchild,ptr,x);
		}
		else
		{
			return Insert_rec(ptr->leftchild,ptr,x);
		}

		
	}


	static BstNode * Min_Value_Node(BstNode *p)
	{
		while(p->leftchild != NULL)
		{
			p = p->leftchild;
		}
		return p;
	}

	static BstNode * Max_Value_Node(BstNode *p)
	{
		while(p->rightchild != NULL)
		{
			p = p->rightchild;
		}
		return p;
	}

	static BstNode * _Findvalue(BstNode *ptr,T kx)
	{
		while(ptr != NULL && ptr->data != kx)
		{
			if(kx > ptr->data)
			{
				ptr = ptr->rightchild;
			}
			else
			{
				ptr = ptr->leftchild;
			}

		}
		return ptr;
	}

	static BstNode * _Searchvalue(BstNode *ptr,T kx)
	{
		if(ptr->data == kx || ptr == NULL)
			return ptr;
		else if(ptr->data < kx)
		{
			return _Searchvalue(ptr->rightchild,kx);
		}
		else 
		{
			return _Searchvalue(ptr->leftchild,kx);
		}

	}

	static void InOrder(BstNode *p)
	{
		if(p != NULL)
		{
			InOrder(p->leftchild);
			cout<<p->data<<" ";
			InOrder(p->rightchild);
		}

	}

};


#endif

