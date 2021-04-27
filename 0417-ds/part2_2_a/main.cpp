#include "stack.h"
#include <iostream>
using namespace std;


int main(){
    cout<<"Int stack: \n";
    Stack<int> s_int(5) ;
    s_int.Push(4);
    s_int.Push(3);
    s_int.Push(2);
    s_int.Push(1);
    s_int.Pop();
    cout<<"Size: "<<s_int.Size();


    cout<<"\n\nFloat stack: \n";
    Stack<float> s_float(5) ;
    s_float.Push(3.2);
    s_float.Push(2.12);
    s_float.Push(1.56);
    s_float.Pop();
    cout<<"Size: "<<s_float.Size();




}