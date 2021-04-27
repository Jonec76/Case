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
    Queue<int> q1(10);
    q1.Push(2);
    

    Queue<int> q2(10);
    q2.Push(8);
    q2.Push(5);

    merge(q1, q2);
    // for(int i=0;i<ans.get_size();i++){
    //     cout<<p_res[i]<<" ";
    // }
    

}