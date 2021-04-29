#include<iostream>
using namespace std;
#define RED     "\033[31m"
#define GREEN   "\033[32m"
#define RESET   "\033[0m"

template <class T> class List;

template <class T>
class Node{
    friend class List<T>;
    private:  
        T data;
        Node* link;
};

template <class T>
class List{
    public: 
        List();// (a)
        ~List();// (b)
        void InsertFront(const T& e);// (c)
        void DeleteFront();// (d)
        void DeleteBack();// (d)
        T Front();// (e)
        T Back();// (e)
        T Get(int i);// (f)
        void Delete(int i);// (g)
        void Insert(int i, const T& e);// (h)
        friend ostream &operator<<(ostream &out, const List &l){// (i)
            Node<T>* tmp = l.first;
            out<<GREEN<<"List => ";
            while(tmp){
                out<<tmp->data<<" ";
                tmp = tmp->link;
            }
            out<<"\n"<<RESET;
            return out;
        };

        void InsertBack(const T& e);// (j)
        void Concatenate(List<T>& b);// (j)
        void Reverse();// (j)

        class Iterator {
            friend class List;
            private:
                Node<T> *nodePtr;
                // The constructor is private, so only our friends
                // can create instances of iterators.
                Iterator(Node<T> *newPtr) : nodePtr(newPtr) {}
            public:
                Iterator() : nodePtr(nullptr) {} 

                // Overload for the comparison operator !=
                bool operator!=(const Iterator& itr) const {
                    return nodePtr != itr.nodePtr;
                }

                // Overload for the dereference operator *
                T& operator*() const {
                    if(nodePtr)
                        return nodePtr->data;
                }

                // Overload for the postincrement operator ++
                Iterator operator++(int) {
                    Iterator temp = *this;
                    nodePtr = nodePtr->link;
                    return temp;
                }

                Iterator operator+=(int i) {
                    Iterator temp = *this;
                    int ctr = 1;
                    while(nodePtr->link && ctr < i){
                        nodePtr = nodePtr->link;
                        ctr++;
                    }
                    return temp;
                }
        }; // End of inner class Iterator

        Iterator begin() const {
            return Iterator(first);
        }

        Iterator end() const {
            Node<T>* cur = first;
            while(cur!=NULL){
                cur = cur->link;
            }
            return Iterator(cur);
        }

    private:
        Node<T>* first;
};

template <class T>
List<T>::List(){
    first = 0;
}

template <class T>
List<T>::~List(){
    Node<T>* delete_node = first;
    
    while(first){
        first = first->link;
        free(delete_node);
        delete_node = first;
    }
}

template <class T>
void List<T>::InsertBack(const T& e){
    cout<<"Insert Back: "<<e<<endl;

    Node<T>* new_node = new Node<T>();
    new_node->data = e;
    new_node->link = NULL;

    if(first==0){
        first = new_node;
    }else{
        Node<T>* cur = first;
        while(cur->link!=NULL){
            cur = cur->link;
        }
        cur->link = new_node;
    }
}

template <class T>
void List<T>::InsertFront(const T& e){
    cout<<"Insert Front: "<<e<<endl;

    Node<T>* new_node = new Node<T>();
    new_node->data = e;
    new_node->link = NULL;

    if(first==0){
        first = new_node;
    }else{
        new_node->link = first;
        first = new_node;
    }
}

template <class T>
void List<T>::DeleteFront(){
    Node<T>* delete_node = first;
    first = first->link;
    cout<<"Delete Front: "<<delete_node->data<<endl;
    free(delete_node);
}

template <class T>
void List<T>::DeleteBack(){
    Node<T>* cur = first;
    if(cur->link == NULL)
        free(cur);
    
    while (cur->link->link){
        cur = cur->link;
    }
    Node<T>* delete_node = cur->link;
    cur->link = NULL;
    cout<<"Delete Back: "<<delete_node->data<<endl;
    free(delete_node);
}

template <class T>
T List<T>::Front(){
    return first->data;
}

template <class T>
T List<T>::Back(){
    Node<T>* cur = first;
    while(cur->link!=NULL){
        cur = cur->link;
    }
    return cur->data;
}

template <class T>
T List<T>::Get(int i){
    if(i<1){
        cout<<"Wrong index"<<endl;
        return 0;
    }

    Node<T>* cur = first;
    int ctr = 1;

    while(cur->link && ctr < i){
        ctr++;
        cur = cur->link;
    }
    return cur->data;
}

template <class T>
void List<T>::Delete(int i){
    cout<<"Delete index: "<<i<<endl;
    if(i<1){
        cout<<"Wrong index"<<endl;
        return;
    }

    if(i==1){
        DeleteFront();
        return;
    }

    Node<T>* cur = first;
    int ctr = 1;

    while(cur->link && ctr < i-1){
        ctr++;
        cur = cur->link;
    }
    Node<T>* delete_node = cur->link;
    cur->link = delete_node->link;
    free(delete_node);
}

template <class T>
void List<T>::Insert(int i, const T& e){
    cout<<"Insert index: "<<i<<"\nValue: "<<e<<endl;
    if(i<1){
        cout<<"Wrong index"<<endl;
        return;
    }
    if(i == 1){
        InsertFront(e);
        return;
    }
    
    Node<T>* cur = first;
    Node<T>* new_node = new Node<T>();
    new_node->data = e;
    new_node->link = NULL;
    int ctr = 1;

    while(ctr < i-1 && cur){
        cur = cur->link;
        ctr++;
    }
    new_node->link = cur->link;
    cur->link = new_node; 
}

template <class T>
void List<T>::Concatenate(List<T>& b){
    cout<<"\nConcate list"<<endl;
    Node<T>* cur = first;
    while(cur->link)
        cur = cur->link;
    
    Node<T>* c_cur = b.first;
    while(c_cur){
        Node<T>* new_node = new Node<T>();
        new_node->data = c_cur->data;
        new_node->link = NULL;
        cur->link = new_node;
        cur = cur->link;
        c_cur = c_cur->link;
    }
}
template <class T>
void List<T>::Reverse(){
    cout<<"\nReverse list\n";
    Node<T>* prev = NULL;
    Node<T>* cur = first;
    
    while(first){
        first = first->link;
        cur->link = prev;
        prev = cur;
        cur = first;
    }
    first = prev;
};