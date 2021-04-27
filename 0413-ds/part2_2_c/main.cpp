#include "deque.h"
#include <iostream>
using namespace std;


int main(){
    cout<<"Int queue: \n";
    DEqueue<int>d(4);
    d.insert_front(20);
    d.insert_front(30);
    d.insert_rear(30);
    d.delete_front();
    d.delete_front();
    d.insert_front(40);
    d.insert_front(50);
    d.delete_rear();
    d.delete_rear();
}