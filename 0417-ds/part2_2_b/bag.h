#include <algorithm>
#include <iostream>

using namespace std;
class Bag
{ 
    public:
        Bag (int bagCapacity = 10);
        virtual ~Bag( );
        virtual int Size( ) const;
        virtual bool IsEmpty( ) const;
        virtual bool IsFull( ) const;
        virtual int Element( ) const;
        virtual int Top( )const;
        void Push(const int);
        void Pop( );

        int get_capacity() const;
    protected:
        int *array;
        int capacity, size=0;
        int top;
};

Bag::Bag (int bagCapacity)
:capacity ( bagCapacity ) 
{	
    if ( capacity < 1 ) 
        throw "Capacity must be > 0";	
    array = new int [ capacity ];	
    top = -1; // empty 
}

Bag::~Bag ( ) 
{ 
    delete [] array; 
}

inline int Bag::Size( ) const 
{ 
    return top + 1; 
}

inline int Bag::Element ( ) const 
{
    if ( IsEmpty ( ) ) 
        throw "Bag is empty";	

    return array [0]; // always return 0th element 
}

bool Bag::IsEmpty() const {
    return top == -1;               // or return size() == 0;
}

bool Bag::IsFull() const {
    return top == capacity - 1;     // or return size() == capacity;
}

void Bag::Pop () 
{
    if (IsEmpty()) throw "Bag is empty, cannot delete";
    int deletePos = top/2; // always delete top/2th element 
    copy(array + deletePos + 1, array + top + 1, 
                       array + deletePos);
    top--;
}

int Bag::Top( ) const
{
	if (IsEmpty( )) throw "Stack is empty.";
	return array[top];
}

int Bag::get_capacity() const{
    return capacity;
}



