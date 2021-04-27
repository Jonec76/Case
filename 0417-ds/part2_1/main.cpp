#include "queue.h"
#include <iostream>
using namespace std;

void merge(Queue<int> q1, Queue<int> q2){
    int q1_size = q1.get_size();
    int q2_size = q2.get_size();
    int p1=0, p2=0;
    int* list1 = new int[q1.get_size()];
    int* list2 = new int[q2.get_size()];
    
    Queue<int> res(q1_size + q2_size);
    q1.get_queue(&list1);
    q2.get_queue(&list2);
    
    while(p1 < q1_size && p2 < q2_size){
        if(((p1 + p2)%2) == 0){
            res.Push(list1[p1]);
            p1++;
        }else{
            res.Push(list2[p2]);
            p2++;
        }
    }

    while(p1 < q1_size){
        res.Push(list1[p1]);
        p1++;
    }

    while(p2 < q2_size){
        res.Push(list2[p2]);
        p2++;
    }

    int* p_res = new int [res.get_size()];
    res.get_queue(&p_res);
    for(int i=0;i<res.get_size();i++){
        cout<<p_res[i]<<" ";
    }
}

int main(){
    int* q;
    q = new int[6];

    Queue<int> q1(3);
    q1.Push(2);
    q1.Push(3);
    q1.Push(5);
    q1.Push(7);
    cout<<"Part 2-1(a)"<<endl;
    cout<<"Size: "<<q1.get_size()<<endl;
    cout<<"Capacity: "<<q1.get_capacity()<<endl;
    cout<<"Queue: ";
    q1.get_queue(&q);
    for(int i=0;i<6;i++){
        cout<<q[i]<<" ";
    }
    cout<<endl;

    cout<<"\nPart 2-1(b)"<<endl;
    cout<<"Queue: ";
    Queue<int> q2(10);
    q2.Push(8);
    q2.Push(6);

    merge(q1, q2);
    
    

}