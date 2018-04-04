#fndef HEAP_H
#define HEAP_H

#include <algorithm>
#include <function>
#include <vector>
#include <initializer_list>

namespace kvatar{

template <typename T,typename Compare>
class heap
{
public:
    heap() = default;
    heap(const vector<T> &v) : vec(v) {}
    heap(vector<T> &&v) : vec(std::move(v)) {}
    heap(std::initializer_list<T> list) : vec(list) {}
private:

    static int parent(int pos){
        return (pos - 1) / 2; 
    }
    static int leftchild(int pos){
        return pos * 2 + 1;
    }
    static int rightchild(int pos){
        return pos * 2 + 2;
    }

    void make_heap();
    void heap_up();
    void heap_down();
    bool compare_three(int pos);

private:
    vector<int> vec;
    Compare compare;
};

template <typename T,typename C>
void heap<T,C>::make_heap()
{
    if(vec.size() <= 1){
        return ;
    }
    
    for(int i = parent(vec.size() - 1);i >= 0; --i){
        
    }
    
}

template <typename T,typename C>
void heap<T,C>::heap_up()
{
    int pos = parent(vec.size() - 1);

    bool iscontinue = true;
    whle(pos >= 0 && iscontinue){
        iscontinue = compare_three(pos);
        pos = parent(pos);
    }
}

template <typename T,typename C>
void heap<T,C>::heap_down()
{
    int pos = 
}


template <typename T,typename C>
bool heap<T,C>::compare_three(int pos)
{
    bool res = false;
    if(leftchild(pos) >= vec.size()){
        return res;
    }

    int &min = (rightchild(pos) >= vec.size()) ? vec[leftchild(pos)] :
        (compare(vec[leftchild(pos)],vec[rightchild(pos)]) ? 
         vec[leftchild(pos)] : vec[rightchild(pos)]);
    if(compare(min,vec[pos])){
        std::swap(min,vec[pos]);
        res = true;
    }
    return res;
}

};




#endif




