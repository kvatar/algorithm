#ifndef BINTARY_TREE_H

#include <vector>

template <typename T>
class Bintary_Tree
{
public:
    typedef T           data_type;
    struct Node{
        Node            *leftchild;
        Node            *rightchild;
        data_type       data;
    }

public:
    Bintary_Tree(const std::vector<data_type> &vec = "",data_type sign);

private:
    static void create_tree_help_func(Node *&p,const std::vector<data_type> &vec,data_type sign,int &pos);

private:
    Node *root;
};



#endif
