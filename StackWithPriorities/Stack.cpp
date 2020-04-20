#include "Stack.h"

template <typename T> Stack<T>::Stack()
{
    first = empty;
}

template <typename T> Stack<T>::~Stack()
{
    delete[] stack_;
}

template <typename T> void Stack<T>::Clear()
{
    first = empty;
}

template <typename T> bool Stack<T>::IsFull()
{
    return first == full;
}

template <typename T> bool Stack<T>::IsEmpty()
{
    return first == empty;
}

template <typename T> int Stack<T>::GetCount()
{
    return first + 1;
}

template <typename T> void Stack<T>::Add(const Element<T> & element)
{
    int i;
    for (i = first; i >= 0; i--)
        if (stack_[i].priority > element.priority)
            break;
    if (IsFull())
    {
        if (i != -1)
        {
            for (int j = 0; j < i; j++)
                stack_[j] = stack_[j + 1];
            stack_[i] = element;
        }
    }
    else
    {
        for (int j = first; j > i; j--)
            stack_[j + 1] = stack_[j];
        stack_[i + 1] = element;
        first++;
    }
}

template <typename T> Element<T> Stack<T>::Remove()
{
    if (IsEmpty())
        return Element<T>();
    return stack_[first--];
}

template <typename T> void Stack<T>::Print()
{
    if (IsEmpty())
        return;
    for (int i = first; i >= 0; i--)
        cout << stack_[i].data << "t";
    cout << endl;
}

template <typename T> void Stack<T>::PrintWithPriority()
{
    if (IsEmpty())
        return;
    for (int i = first; i >= 0; i--)
        cout << stack_[i].data << ", pr: " << stack_[i].priority << "\t";
    cout << endl;
}
