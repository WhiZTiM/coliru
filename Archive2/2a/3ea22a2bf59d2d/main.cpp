#include <iostream>
#include <algorithm>
#include <memory>
#include <list>
typedef unsigned int uint;


template <typename keyT,typename varT> class priority_list_based_non_ranged_queue:public std::list<std::pair<keyT,varT>> //9.8
{
    void insert(const keyT &k,const varT &v)
    {
        push_back(pair<keyT,varT>(k,v));
    }
    varT remove(uint i)
    {
        varT out = (*this)[i];
        list::erase(i);
        return out;
    }
    varT extractMin()
    {
        uint min;
        for(uint i = 0;i<size();i++)
            if((*this)[i]<(*this)[min]) min = i;
        return remove(min);
    }
    void changePriority(uint i,keyT k)
    {
        if(i>=count) return;
        (*this)[i].fst = k;
    }
    priority_list_based_non_ranged_queue join(const priority_list_based_non_ranged_queue &right)
    {
        list::insert(end(),right.begin(),right.end());
        return (*this);
    }
};

template <typename keyT,typename varT> class priority_array_based_ranged_qeue //9.7
{
    struct Node{
        keyT key;
        varT var;
        Node(const keyT &k,const varT &v):key(k),var(v){}

        bool operator<(const Node &right)
        {
            return (key<right.key);
        }

    } *head;
    uint count,max_count;
public:
    ~priority_array_based_ranged_qeue()
    {
        delete[] head;
    }

    priority_array_based_ranged_qeue():head(nullptr){}

    priority_array_based_ranged_qeue(const uint &_max_count): head(new Node[_max_count]),max_count(_max_count),count(0){}


    Node* insert(const keyT &k,const varT &v)
    {
        if(count>=max_count) return nullptr;
        head[count++] = Node(k,v);
        std::qsort(head,count,sizeof(Node),[](const Node &a,const Node &b)
        {
            return(a.key<b.key);
        });
    }

    varT remove(uint i)
    {
        if(i>=count) return Node();
        Node out = head[i];
        memcpy(&head[i],&head[i+1],--count-i);
        return out.var;
    }

    varT extractMin()
    {
        return remove(0);
    }

    void changePriority(uint i,keyT k)
    {
        if(i>=count) return;
        head[i].key = k;
        std::qsort(head,count,sizeof(Node),[](const Node &a,const Node &b)
        {
            return(a.key<b.key);
        });
    }

    priority_array_based_ranged_qeue(keyT *keys,varT *vars,uint c):priority_array_based_ranged_qeue(c)
    {
        for(uint i = 0;i<c;i++)
            insert(keys[i],vars[i]);

    }
    priority_array_based_ranged_qeue &join(const priority_array_based_ranged_qeue &right)
    {
        priority_array_based_ranged_qeue temp(max_count+right.max_count);
        for(int i = 0;i<count;i++)
            temp.insert(head[i].key,head[i].var);
        for(int i = 0;i<right.count;i++)
            temp.insert(right.head[i].key,right.head[i].var);
        delete this;
        *this = temp;
        return *this;
    }


};


int main(int argc, char *argv[])
{

    return 0;
}
