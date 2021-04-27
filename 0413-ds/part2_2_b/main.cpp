#include "queue.h"
#include <iostream>
using namespace std;


int main(){
    cout<<"Int queue: \n";
    Queue<int>q_int(5);
    q_int.Push(5);
    q_int.Push(3);
    q_int.Push(2);
    q_int.Push(2);
    q_int.Push(2);
    q_int.Push(1);
    cout<<"\nsize: "<<q_int.get_size()<<endl;
    // cout<<"\n\nFloat stack: \n";
    // Queue<float>q_float(5);
    // q_float.Push(5.234);
    // q_float.Push(3.45);
    // q_float.Push(2.67);
    // q_float.Pop();
    // cout<<"\nsize: "<<q_float.get_size()<<endl;
}