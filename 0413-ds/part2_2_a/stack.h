#include "bag.h"
#include <iostream>

using namespace std;

template<class T>
class Stack : public Bag
{
    public:
        Stack (int stackCapacity = 10);
        void Push(const T&);
        T Pop();
    private:
        T* array;
};

template<class T>
Stack<T>::~Stack ( ) 
{ 
    delete [] array; 
}

template<class T>
Stack<T>::Stack(int stackCapacity) : Bag(stackCapacity) {
    // explicitly call to the Bag constructor that has arguments{
    // here is code specifically for creating a stack, if any
    if ( stackCapacity < 1 ) 
        throw "Capacity must be > 0";	
    array = new T [ stackCapacity ];	
    top = -1;
}

template<class T>
void Stack<T>::Push(const T& x)
{
    if (IsFull())
    {
        cout << "Overflow\nProgram Terminated\n";
        exit(EXIT_FAILURE);
    }
 
    cout << "Inserting " << x << endl;
    array[++top] = x;
}

template<class T>
T Stack<T>::Pop()
{
    // check for stack underflow
    if (IsEmpty())
    {
        cout << "Underflow\nProgram Terminated\n";
        exit(EXIT_FAILURE);
    }
 
    cout << "Removing " << array[top] << endl;
 
    // decrease stack size by 1 and (optionally) return the popped element
    return array[top--];
}
