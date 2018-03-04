#ifndef B_H
#define B_H

#include <iostream>
#include <queue>
#include <cassert>
using namespace std;

template<typename K,typename R,int M>
class BMTree
{
public:
	typedef K KeyType;
	typedef R Record;
	
	struct ElemType 
	{
		KeyType key;
		Record *Recptr;
		
		//for text
		ElemType(KeyType x = 0):key(x),Recptr(NULL){}
	};
	struct BNode		//可以加一个域来存储节点在父节点的位置
	{
		int num;
		ElemType data[M+1];
		BNode *sub[M+1];
		BNode *parent;
		BNode(ElemType kx,BNode *left = NULL,BNode *right = NULL,BNode *parent = NULL)
		{
			memset(this,0,sizeof(BNode));
			data[1] = kx;
			num = 1;
			sub[0] = left;
			sub[1] = right;
		}
		BNode()
		{
			memset(this,0,sizeof(BNode));
		}

	};
	struct Result
	{
		BNode *pnode;
		int index;
		Result(BNode *ptr = NULL,int k = 0):pnode(ptr),index(k) {}

		bool operator==(BNode *p)
		{
			return p == pnode;
		}
		bool operator!=(BNode *p)
		{
			return !(*this == p);
		}

	};

public:

	BMTree():root(NULL){}

	bool FindValue(KeyType kx,Result &res)//循环
	{
		BNode *ptr = root;
		while(ptr != NULL)
		{
			ptr->data[0].key = kx;//
			int i = ptr->num;
			while(kx < ptr->data[i].key)
				--i;
			res.pnode = ptr;
			res.index = kx == ptr->data[i].key ? i : i + 1;
			if(i > 0 && ptr->data[i].key == kx)
			{		
				return true;
			}
			ptr = ptr->sub[i];
		}
		return false;

	}

	bool SearchValue(KeyType kx,Result &res)
	{
		SearchValue(root,kx,res);
	}

	bool Insert(ElemType x)
	{
		if(root == NULL)
			root = new BNode(x);
		Result res;
		if(FindValue(x.key,res))	
			return false;
		BNode *ptr = res.pnode;
		int pos = res.index;
		Insert_Item(ptr,x,NULL,pos);
		while(ptr->num > M-1)
		{
			BNode *newnode = Splice(ptr);
			ElemType kx = newnode->data[0];
			BNode *pa = NULL;
			if(ptr == root)
			{
				pa = new BNode(kx,ptr,newnode);
				root = ptr->parent = newnode->parent = pa;
				break;
			}
			else
			{
				pa = ptr->parent;
				newnode->parent = pa;
				Insert_Item(pa,kx,newnode);
			}
			ptr = pa;
		}
		return true;
	}

	void Print()//error
	{
		queue<BNode *> qu;
		qu.push(root);
		qu.push(NULL);
		int sz_now = 1;
		int sz_next = 0;
		while(!qu.empty())
		{
			BNode *ptr = qu.front();
			qu.pop();
			if(ptr == NULL)
			{
				if(--sz_now == 0)
				{
					cout<<endl;
				}
			}
			else
			{
				Print_Node(ptr);
				if(ptr->sub[0] == NULL)
					continue;
				for(int i = 0;i <= ptr->num;i++)
				{
					qu.push(ptr->sub[i]);
				}
				++sz_next;
				qu.push(NULL);
			}
			sz_now = sz_next;
			sz_next = 0;
		}
		cout<<endl;
	}

	bool Delete(KeyType kx)
	{
		Result res;
		if(!FindValue(kx,res))
			return false;
		BNode *ptr = res.pnode;
		int pos = res.index;
		Delete(ptr,pos);
		return true;
	}

	void InOrder()
	{
		for(Result res = First(root);res != NULL;res = Next(res))
		{
			cout<<res.pnode->data[res.index].key<<" ";
		}

	}


private:

	static Result First(BNode *ptr)
	{
		Result res;
		while(ptr->sub[0] != NULL)
		{
			ptr = ptr->sub[0];
		}
		res.pnode = ptr;
		res.index = 1;
		return res;
	}

	static Result Last(BNode *ptr)
	{
		Result res;
		while(ptr->sub[ptr->num] != NULL)
		{
			ptr = ptr->sub[ptr->num];
		}
		res.pnode = ptr;
		res.index = ptr->num
		return res;
	}

	static Result Next(Result res)
	{
		Result r;
		BNode *ptr = res.pnode;
		int pos = res.index;
		if(ptr->sub[pos] != NULL)
		{
			r = First(ptr->sub[pos]);
		}
		else
		{
			pos++;
			while(ptr != NULL && pos > ptr->num)
			{
				pos = ptr->parent == NULL ? 0 : Getpos(ptr->parent,ptr->data[1].key);
				ptr = ptr->parent;
			}
			r = Result(ptr,pos);
		}
		return r;

	}

	void Delete(BNode *ptr,int pos)
	{
		assert(ptr != NULL);
		if(ptr->sub[0] != NULL)
		{
			ptr->data[pos] = ptr->sub[pos]->data[1];
			Delete(ptr->sub[pos],1);
		}
		else
		{
			Delete_Item(ptr,pos);
			if(ptr->num < Min_num && ptr != root)
			{
				Get_balance(ptr);
				if(root->num == 0)
				{
					BNode *r = root;
					root = root->sub[0];
					delete r;
					root->parent = NULL;
				}
			}

		}

	}


	static void Get_balance(BNode *ptr)
	{
		BNode *pa = ptr->parent;
		BNode *Leftbrother = Getbrother(ptr,true);
		BNode *Rightbrother = Getbrother(ptr,false);
		int papos = Getpos_in_parent(ptr);
		if(pa == NULL)	//是根结点不用调整
			return ;
		else if(Leftbrother != NULL && Leftbrother->num > Min_num)
		{
			LendNode(ptr,Leftbrother);
		}
		else if(Rightbrother != NULL && Rightbrother->num > Min_num)
		{
			LendNode(ptr,Rightbrother);
		}
		else
		{
			if(Leftbrother != NULL)
			{
				Merge(Leftbrother,ptr);
			}
			else
			{
				Merge(ptr,Rightbrother);
			}
			if(pa->num < Min_num)
			{
				Get_balance(pa);
			}

		}


	}
	
	static void Delete_Item(BNode *ptr,int pos)
	{
		for(int i = pos;i <= ptr->num;i++)
		{
			ptr->data[i] = ptr->data[i+1];
			ptr->sub[i] = ptr->sub[i+1];
		}
		--ptr->num;
	}

	static void Merge(BNode *p1,BNode *p2)
	{
		assert(p1->num + p2->num + 1 <= Max_num);
		BNode *pa = p1->parent;
		int papos = Getpos_in_parent(p1);
		p2->data[0] = pa->data[papos+1];
		Delete_Item(pa,papos+1);
		for(int i = 0;i <= p2->num;i++)
		{
			if(p2->sub[i] != NULL)
				p2->sub[i]->parent = p1;
			Insert_Item(p1,p2->data[i],p2->sub[i]);
		}
		delete p2;
	}


	static void LendNode(BNode *p1,BNode *p2)//p1往p2借
	{
		int papos = Getpos_in_parent(p1);
		BNode *pa = p1->parent;
		bool IsLeft = ((p1->data[1].key) > (p2->data[1].key));
		if(IsLeft)
		{
			ElemType d = pa->data[papos];
			BNode *pnode = p1->sub[0];
			if(p2->sub[p2->num] != NULL)
				p2->sub[p2->num]->parent = p1;
			p1->sub[0] = p2->sub[p2->num];
			pa->data[papos] = p2->data[p2->num];
			Delete_Item(p2,p2->num);
			Insert_Item(p1,d,pnode,1);
		}
		else
		{
			ElemType d = pa->data[papos+1];
			BNode *pnode = p2->sub[0];
			if(p2->sub[0] != NULL)
				p2->sub[0]->parent = p1;
			p2->sub[0] = p2->sub[1];
			pa->data[papos+1] = p2->data[1];
			Delete_Item(p2,1);
			Insert_Item(p1,d,pnode,p1->num+1);
		}

	}


	static BNode *Getbrother(BNode *ptr,bool Isleft)
	{
		
		BNode *pa = ptr->parent;
		if(pa == NULL)	return NULL;
		int papos = Getpos_in_parent(ptr);
		if(Isleft)
		{
			return papos != 0 ? pa->sub[papos-1] : NULL;
		}
		else
		{
			return papos != ptr->num ? pa->sub[papos+1] : NULL;
		}

	}

	static int Getpos_in_parent(BNode *ptr)
	{
		if(ptr->parent != NULL)
			return Getpos(ptr->parent,ptr->data[1].key) - 1;
		else
			return 0;
	}

	static void Print_Node(BNode *ptr)
	{
		for(int i = 0;i<ptr->num;i++)
		{
			cout<<ptr->data[i+1].key<<",";
		}
		cout<<" ";
	}


	static BNode *Splice(BNode *ptr)
	{
		BNode *newnode = new BNode;

		//movedata
		for(int i = 0;i < Splice_new_num;i++)
		{
			newnode->data[Splice_new_num-i-1] = ptr->data[M-i];
			newnode->sub[Splice_new_num-i-1] = ptr->sub[M-i];
			if(ptr->sub[M-i])
				ptr->sub[M-i]->parent = newnode;
		}

		ptr->num = Splice_old_num - 1;
		newnode->num = Splice_new_num - 1; 
		return newnode;
	}

	

	static int Getpos(BNode *ptr,KeyType x)//返回插入时要插入的位置，即：pos位置的值要比x值高
	{
		int pos = ptr->num;
		while(pos > 0 && ptr->data[pos].key >= x)
			--pos;
		return pos + 1;
	}


	static void Insert_Item(BNode *ptr,ElemType x,BNode *right,int pos = -1)
	{
		if(pos == -1)	pos = Getpos(ptr,x.key);
		int i = ptr->num;
		while(i >= pos)
		{
			ptr->data[i+1] = ptr->data[i];
			ptr->sub[i+1] = ptr->sub[i];
			--i;
		}
		ptr->data[i+1] = x;
		ptr->sub[i+1] = right;
		ptr->num += 1;
	
	}
	static bool SearchValue(BNode *ptr,KeyType kx,Result &res)//递归
	{
		if(ptr == NULL)
			return false;
		ptr->data[0].key = kx;//
		int i = ptr->num;
		while(kx < ptr->data[i].key) 
			--i;
		res.pnode = ptr;
		res.index = kx == ptr->data[i].key ? i : i + 1;
		if(i > 0 && ptr->data[i].key == kx)
		{			
			return true;
		}
		else
		{
			return FindValue(ptr->sub[i],kx,res);
		}

	}



private:
	BNode *root;

	static const int Min_num = (M-1)/2;//数据数量
	static const int Max_num = M-1;

	static const int Splice_old_num = (M+1)/2;//节点数量
	static const int Splice_new_num = M+1-Splice_old_num;//节点数量

};

#endif