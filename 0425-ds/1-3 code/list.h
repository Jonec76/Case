#include<iostream>
using namespace std;

template <class T> class List;
template <class T> class stack;
template <class T> class queue;

template <class T>
class Node{
    friend class List<T>;
    friend class stack<T>;
    friend class queue<T>;
    private:  
        T data;
        Node* link;
};

template <class T>
class List{
    friend class stack<T>;
    friend class queue<T>;
    public: 
        List(){first = 0;}
        void InsertBack(const T& e);
        void Concatenate(List<T>& b);
        void Reverse();

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
        Node<T>* tail;
};

template <class T>
void List<T>::InsertBack(const T& e){
    Node<T>* new_node = new Node<T>();
    new_node->data = e;
    new_node->link = NULL;
    tail = new_node;

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
class stack: public List<T>{
    public:
        void PopBack();

};

template <class T>
void stack<T>::PopBack(){
    Node<T>* cur = this->first;
    while(cur->link != this->tail){
        cur = cur->link;
    }
    free(this->tail);
    this->tail = cur;
    cur->link = NULL;
}




template <class T>
class queue: public List<T>{
    public:
        void Pop();

};

template <class T>
void queue<T>::Pop(){
    Node<T>* cur = this->first;
    if(cur->link){
        cur = cur->link;
    }
    free(this->first);
    this->first = cur;
}


