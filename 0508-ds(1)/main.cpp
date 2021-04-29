#include "list.h"

int main(){
    List<int> tmp_list = List<int>();
    List<int> list = List<int>();

    list.InsertFront(1);
    cout<<list;

    list.DeleteFront();
    cout<<list;
    
    list.InsertFront(5);
    list.InsertFront(4);
    list.InsertFront(3);
    list.InsertFront(2);
    list.InsertFront(1);
    cout<<list;
    
    list.DeleteBack(); 
    cout<<list;
    
    cout<<GREEN<<"List Front: "<<list.Front()<<RESET<<endl;
    cout<<GREEN<<"List Back: "<<list.Back()<<RESET<<endl;
    cout<<GREEN<<"List Get(2): "<<list.Get(2)<<RESET<<endl;
    
    list.Delete(2);
    cout<<list;
    
    list.Insert(3, 10);
    cout<<list;

    tmp_list.InsertBack(15);
    tmp_list.InsertBack(16);
    tmp_list.InsertBack(17);  
    tmp_list.InsertBack(18);
    
    list.Concatenate(tmp_list);
    cout<<GREEN<<"Concated_"<<tmp_list;
    cout<<list;

    list.Reverse();
    cout<<list;
}