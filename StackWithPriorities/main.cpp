#include "Stack.cpp"

int main()
{
    Stack<char> S;
    Element<char> Array[] = { {'A',3},{'B',2},{'C',12},{'D',0},{'E',2} };
    int length = sizeof(Array) / sizeof(Element<char>);
    for (int i = 0; i < length; i++)
    {
        S.Add(Array[i]);
    }
    S.PrintWithPriority();
    Element<char> exempl;
    exempl.data = 'F';
    exempl.priority = 11;
    S.Add(exempl);
    S.PrintWithPriority();
    return 0;
}
