#include<iostream>
using namespace std;

template <typename T> struct Element
{
    T data;
    int priority;
};

template <typename T> class Stack
{
public:
    Stack();
    ~Stack();
    void Add(const Element<T> &element);
    Element<T> Remove();
    int GetCount();
    void Print();
    void PrintWithPriority();
    bool IsFull();
    bool IsEmpty();
    void Clear();
private:
    enum {empty=-1, full=999};
    Element<T> stack_[full + 1];
    int first;
};
