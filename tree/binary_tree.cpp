#include "binary_tree.hpp"
#include <cassert>


void Bintary_Tree::create_tree_help_func(Node *&p,const std::vector<data_type> &vec,data_type sign,int &pos)
{
    if (p != nullptr || pos > vec.size()){
        printf("creatr_tree_help_fun invaild parameter\n");
        return;
    }

    if (pos == vec.size()){
        return;
    }

    if (vec[pos] == sign){
        p = nullptr;
    }else{
        p->data = vec[pos];
    }
    pos++;

    if (p != nullptr){
        create_tree_help_func(p->leftchild,vec,sign,pos);
        create_tree_help_func(p->rightchild,vec,sign,pos);
    }

}


BBintary_Tree::Bintary_Tree(const std::vector<data_type> &vec,data_type sign)
{
    int pos = 0;
    create_tree_help_func(root,vec,sign,pos);
}
