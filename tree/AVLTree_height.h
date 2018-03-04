#ifndef AVLTREE_H
#define AVLTREE_H

#include <iostream>
#include <queue>
#include <cmath>
using namespace std;

template <typename T>
class AVLTree
{
public:
	typedef T _Ty;
	struct AVLNode
	{
		_Ty data;
		AVLNode *leftchild;
		AVLNode *rightchild;
		AVLNode *parent;
		int height;
		AVLNode(_Ty x,AVLNode *pa = NULL):leftchild(NULL),rightchild(NULL),parent(pa),data(x),height(1){}
	};
private:
	AVLNode *root;

	static void RotateRight(AVLNode *&ptr)
	{
		AVLNode *newroot = ptr->rightchild;
		ptr->rightchild = newroot->leftchild;
		if(newroot->leftchild != NULL)	newroot->leftchild->parent = ptr;
		newroot->leftchild = ptr;
		newroot->parent = ptr->parent;
		ptr->parent = newroot;
		
		ptr->height = Max(height(ptr->leftchild),height(ptr->rightchild)) + 1;
		newroot->height = Max(height(newroot->leftchild),height(newroot->rightchild)) + 1;
		
		ptr = newroot;
	}

	static void RotateLeft(AVLNode *&ptr)
	{
		AVLNode * newroot = ptr->leftchild;
		ptr->leftchild = newroot->rightchild;
		if(newroot->rightchild != NULL)	newroot->rightchild->parent = ptr;
		newroot->rightchild = ptr;
		newroot->parent = ptr->parent;
		ptr->parent = newroot;		
		
		ptr->height = Max(height(ptr->leftchild),height(ptr->rightchild)) + 1;
		newroot->height = Max(height(newroot->leftchild),height(newroot->rightchild)) + 1;
		
		ptr = newroot;
	}

	static void DoubleLeft(AVLNode *&ptr)
	{
		RotateRight(ptr->leftchild);
		RotateLeft(ptr);	
	}

	static void DoubleRight(AVLNode *&ptr)
	{
		RotateLeft(ptr->rightchild);
		RotateRight(ptr);
	}

	static int Insert(AVLNode *&ptr,AVLNode *pa,_Ty kx)
	{
		int res = 1;
		if(ptr == NULL)
		{
			ptr = new AVLNode(kx,pa);
			return res;
		}
		if(kx < ptr->data)
		{
			res = Insert(ptr->leftchild,ptr,kx);
			if(res == 1)
			{
				int height_beg = ptr->height;
				ptr->height = Max(height(ptr->leftchild),height(ptr->rightchild)) + 1;
				if(ptr->height == height_beg)
					res = 2;
				if(balance(ptr) == -2)
				{
					Get_balance(ptr,1);
					res = 2;
				}

			}
		}
		else if(kx > ptr->data)
		{
			res = Insert(ptr->rightchild,ptr,kx);
			if(res == 1)
			{
				int height_beg = ptr->height;
				ptr->height = Max(height(ptr->leftchild),height(ptr->rightchild)) + 1;
				if(ptr->height == height_beg)
					res = 2;
				if(balance(ptr) == 2)
				{
					Get_balance(ptr,0);
					res = 2;
				}
			}
		}
		else if(kx == ptr->data)
			res = 0;
		return res;
	}

	static void Get_balance(AVLNode *&ptr,bool Isleft)//1: 左边节点多
	{
		if(Isleft)
		{
			if(balance(ptr->leftchild) <= 0)
			{
				RotateLeft(ptr);
			}
			else
			{
				DoubleLeft(ptr);
			}
		}
		else
		{
			
			if(balance(ptr->rightchild) >= 0)
			{
				RotateRight(ptr);
			}
			else
			{
				DoubleRight(ptr);
			}
		}

	}

	static int Remove(AVLNode *&ptr,_Ty kx)	//返回值：0：失败。1：成功并且还要调整。2：成功并且不用调整。
	{
		if(ptr == NULL)
			return false;
		int res = 1;
		bool Iscontinue = 0;
		if(ptr->data == kx)
		{
			if(ptr->leftchild != NULL && ptr->rightchild != NULL)
			{
				AVLNode *s = Prev(ptr);
				ptr->data = s->data;
				kx = s->data;
				Iscontinue = 1;
			}
			else
			{
				AVLNode *child = ptr->leftchild != NULL ? ptr->leftchild : ptr->rightchild;
				if(child != NULL)	child->parent = ptr->parent;
				delete ptr;
				ptr = child;		
				return 1;
			}
		}
		if(kx < ptr->data || Iscontinue)
		{
			res = Remove(ptr->leftchild,kx);
			if(res == 1)
			{
				int height_beg = ptr->height;
				ptr->height = Max(height(ptr->leftchild),height(ptr->rightchild)) + 1;
				if(ptr->height == height_beg)
					res = 2;
				if(balance(ptr) == 2)
				{
					Get_balance(ptr,0);
					res = 2;
				}
			}
			return res;
		}
		else 
		{
			res = Remove(ptr->rightchild,kx);
			if(res == 1)
			{
				int height_beg = ptr->height;
				ptr->height = Max(height(ptr->leftchild),height(ptr->rightchild)) + 1;
				if(ptr->height == height_beg)
					res = 2;
				if(balance(ptr) == -2)
				{
					Get_balance(ptr,1);
					res = 2;
				}

			}
			return res;	
		}
}

	static AVLNode * First(AVLNode *ptr)
	{
		while(ptr != NULL && ptr->leftchild != NULL)
		{
			ptr = ptr->leftchild;
		}
		return ptr;
	}

	static AVLNode * Last(AVLNode *ptr) 
	{
		while(ptr != NULL && ptr->rightchild != NULL)
		{
			ptr = ptr->rightchild;
		}
		return ptr;
	}

	static AVLNode * Next(AVLNode *ptr)
	{
		if(ptr == NULL) return NULL;
		if(ptr->rightchild != NULL)
		{
			return First(ptr->rightchild);
		}else
		{
			AVLNode *pa = ptr->parent;
			while(pa != NULL && pa->leftchild != ptr)
			{
				ptr = pa;
				pa = pa->parent;
			}
			return pa;
		}
	}

	static AVLNode * Prev(AVLNode *ptr)
	{
		if(ptr == NULL) return NULL;
		if(ptr->leftchild != NULL)
		{
			return Last(ptr->leftchild);
		}
		else
		{
			AVLNode *pa = ptr->parent;
			while(pa != NULL && pa->rightchild != ptr)
			{
				ptr = pa;
				pa = pa->parent;
			}
			return pa;
		}
	}

	static int height(AVLNode *ptr)
	{
		if(ptr == NULL)
			return 0;
		else
			return ptr->height;
	}

	static int Max(int a,int b)
	{
		return a > b ? a : b;
	}

	static int balance(AVLNode *ptr)
	{
		return height(ptr->rightchild) - height(ptr->leftchild);
	}

	
public:
	AVLTree():root(NULL) {}
	~AVLTree() 
	{
		while(root != NULL)
		{
			Remove(root->data);
		}

	}

	bool Insert(_Ty kx)
	{			
		return Insert(root,NULL,kx) > 0;
	}

	bool NiceInsert(_Ty kx)
	{
		if(root == NULL)
		{
			root = new AVLNode(kx,NULL);
			return true;
		}
		AVLNode *p = root;
		AVLNode *pa = NULL;
		while(p != NULL && p->data != kx)
		{
			pa = p;
			p = kx > p->data ? p->rightchild : p->leftchild;
		}
		if(p != NULL)
			return false;
		bool IsLeft = kx < pa->data;
		if(IsLeft)	
		{
			pa->leftchild = new AVLNode(kx,pa);
			p = pa->leftchild;
		}
		else	
		{
			pa->rightchild = new AVLNode(kx,pa);
			p = pa->rightchild;
		}
		bool IsContinue = true;
		while(pa != NULL && IsContinue)
		{
			IsLeft = (p == pa->leftchild);
			if(IsLeft)
			{
				int height_beg = pa->height;
				pa->height = Max(height(pa->leftchild),height(pa->rightchild)) + 1;
				if(pa->height == height_beg)
					IsContinue = false;
				if(balance(pa) == -2)
				{
					if(pa->parent == NULL)	
						Get_balance(root,1);
					else
					{
						AVLNode *&ptr = 
							pa->parent->leftchild == pa ? pa->parent->leftchild : pa->parent->rightchild; 
						Get_balance(ptr,1);
					}
					IsContinue = false;
				}
			}
			else
			{
				int height_beg = pa->height;
				pa->height = Max(height(pa->leftchild),height(pa->rightchild)) + 1;
				if(pa->height == height_beg)
					IsContinue = false;
				if(balance(pa) == 2)
				{
					if(pa->parent == NULL)	
						Get_balance(root,0);
					else
					{
						AVLNode *&ptr = 
							pa->parent->leftchild == pa ? pa->parent->leftchild : pa->parent->rightchild; 
						Get_balance(ptr,0);
					}		
					IsContinue = false;
				}
			}
			p = pa;
			pa = pa->parent;
		}
		return true;
	}

	bool NiceRemove(_Ty kx)
	{
		AVLNode *p = root;
		while(p != NULL && p->data != kx)
		{
			p = p->data > kx ? p->leftchild : p->rightchild;
		}
		if(p == NULL)
			return false;
		if(p->leftchild != NULL && p->rightchild != NULL)
		{
			AVLNode *q = Prev(p);
			p->data = q->data;
			p = q;
		}
		//删节点
		AVLNode *child = p->leftchild != NULL ? p->leftchild : p->rightchild;
		if(p->parent == NULL)
		{
			delete(root);
			root = NULL;
			return true;
		}
		AVLNode *pa = p->parent;
		bool IsLeft = (pa->leftchild == p);
		delete p;
		if(IsLeft)
			pa->leftchild = child;
		else
			pa->rightchild = child;
		if(child != NULL)
			child->parent = pa;
		//调平衡
		bool IsContinue = true;
		while(pa != NULL && IsContinue)
		{
			int height_beg = pa->height;
			pa->height = Max(height(pa->leftchild),height(pa->rightchild)) + 1;
			if(pa->height == height_beg)
				IsContinue = false;
			if(IsLeft && balance(pa) == 2)
			{
				if(pa->parent == NULL)	
					Get_balance(root,0);
				else
				{
					AVLNode *&ptr = 
						pa->parent->leftchild == pa ? pa->parent->leftchild : pa->parent->rightchild; 
					Get_balance(ptr,0);
				}		
				IsContinue = false;
			}
			else if(!IsLeft && balance(pa) == -2)
			{
				if(pa->parent == NULL)	
					Get_balance(root,1);
				else
				{
					AVLNode *&ptr = 
						pa->parent->leftchild == pa ? pa->parent->leftchild : pa->parent->rightchild; 
					Get_balance(ptr,1);
				}
				IsContinue = false;
			}
			if(pa->parent != NULL)
				IsLeft = pa->parent->leftchild == pa;
			pa = pa->parent;
		}
		return true;
	}


	bool Remove(_Ty kx)
	{
		return Remove(root,kx) > 0;
	}

	void Print()
	{
		for(AVLNode *p = First(root);p != NULL;p = Next(p))
		{
			cout<<p->data<<" ";
		}
		cout<<endl;
	}

	int height()
	{
		return height(root);
	}

	void levelPrint()
	{
		queue<AVLNode *> qu;
		int h = height();
		int i = 1;
		qu.push(root);
		while(i <= h)
		{
			int size = (int)pow(2,i-1);
			int tmp = 0;
			while(tmp < size)
			{		
				AVLNode *s = qu.front();
				qu.push(s==NULL?NULL:s->leftchild);
				qu.push(s==NULL?NULL:s->rightchild);
				if(s == NULL)
					cout<<"#"<<" "; 
				else
					cout<<s->data<<" ";
				qu.pop();
				++tmp;
			}
			cout<<endl;
			++i;
		}
		cout<<endl;
	}

};



#endif