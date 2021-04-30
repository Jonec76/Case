#include"list.h"
using namespace std;

int main(){
    cout<<"Stack: "<<endl;

    stack<int> s;
    s.InsertBack(5);
    s.InsertBack(6);
    s.InsertBack(7);
    s.PopBack();
    s.InsertBack(9);
    
    for(auto it = s.begin();it!=s.end();it++){
        cout<<*it;
    }


    cout<<"\n\nQueue: "<<endl;
    queue<int> q;
    q.InsertBack(5);
    q.InsertBack(6);
    q.InsertBack(7);
    q.Pop();
    q.InsertBack(9);
    
    for(auto it = q.begin();it!=q.end();it++){
        cout<<*it;
    }

    cout<<"\n\nSum (i * i+5): "<<endl;
    List<int> l;
    l.InsertBack(0);
    l.InsertBack(1);
    l.InsertBack(2);
    l.InsertBack(3);
    l.InsertBack(4);
    l.InsertBack(5);
    l.InsertBack(6);
    l.InsertBack(7);
    l.InsertBack(8);
    l.InsertBack(9);
    l.InsertBack(10);


    auto begin = l.begin();
    auto tail = l.begin();
    tail += 5;
    int sum = 0;
    for(tail;tail!=q.end();tail++){
        sum += (*begin * *tail);
        // cout<<"begin: "<<*begin<<endl;
        // cout<<"tail: "<<*tail<<endl;
        begin++;
    }
    cout<<"Sum: "<<sum<<endl;

}