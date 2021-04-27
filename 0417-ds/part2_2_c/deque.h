#include <iostream>
#define RED "\033[31m"
#define GREEN "\033[32m"
#define RESET "\033[0m"
using namespace std;

template < class T>
class Queue{ 
    public:
        Queue (int queueCapacity=10);
        bool IsEmpty( ) const;
        bool IsFull( ) const;
        void Push(const T& item);
        // add an item into the queue
        void Pop( );
        // delete an item 
        int get_capacity();
        int get_size();
        void get_queue(T** p);
        T& Front() const;
        // return top element of stack
        T& Rear() const;
        // return top element of stack
        void print_queue();
    protected:
        T* queue;
        int front,
            rear,
            capacity,
            size=0;
} ;



template < class T>
Queue<T>::Queue(int queueCapacity):capacity(queueCapacity)
{ 
    if (capacity < 1) throw "Queue capacity must be > 0";
    queue= new T[capacity];
    for(int i=0;i<capacity;i++)
        queue[i] = -100;
    front = rear = -1; // indicate empty stack
}

template < class T>
void Queue<T>::print_queue(){
    cout<<"==> ";
    for(int i=0;i<capacity;i++)
        cout<<queue[i]<<" ";
    cout<<endl;
}

template < class T>
inline bool Queue<T>::IsEmpty() const
{
    return size==0;
}

template < class T>
inline T& Queue<T>::Front() const
{
   if ( IsEmpty() ) throw "Queue is empty. No front element.";
   return queue[(front + 1) % capacity];
}

template < class T>
inline T& Queue<T>::Rear() const
{
   if ( IsEmpty() ) throw "Queue is empty. No rear element.";
   return queue[rear];
}

template < class T>
void Queue<T>::Push(const T& x) 
{// add x to stack
    cout<<GREEN<<"Push: "<<x<<RESET<<" \n";
    if ((rear + 1) % capacity == front) 
    {   T* newQu = new T[2*capacity];
        int start = (front+1) % capacity;
        if(start<2)
           copy(queue	+start, queue+start+capacity-1, newQu);
        else{
           copy(queue	+start, queue+capacity, newQu);
           copy(queue, queue+rear+1,newQu+capacity-start);
        }
        front = 2*capacity - 1;
        rear = capacity - 2;
        delete[] queue;
        queue = newQu;
    }
    rear = (rear+1)%capacity;  queue[rear] = x;

    size++;
    print_queue();
}

template < class T>
void Queue<T>::Pop( ) 
{
    if ( IsEmpty() ) throw "Queue is empty, cannot delete";	
    front = (front + 1) % capacity;
    cout<<RED<<"Pop: "<<queue[front]<<RESET<<endl;
    queue[front].~T(); // destructor for T

    size--;
    print_queue();
}

template < class T>
int Queue<T>::get_capacity(){
    return capacity;
}

template < class T>
int Queue<T>::get_size(){
    return size;
}

template < class T>
void Queue<T>::get_queue(T** p){
    int front_idx = front;
    for(int i=0;i<size;i++){
        (*p)[i] = queue[front_idx];
        front_idx = (front_idx + 1) % capacity;
    }
}

template < class T>
bool Queue<T>::IsFull() const{
   if(size == capacity )
      return true;
   else
      return false;
}

template <class T> 
class DEqueue : public Queue<T>{
  public:
    DEqueue(int queueCapacity = 10) : Queue<T>(queueCapacity) {};
    void insert_front(T x);
    void insert_rear(T x);
    void delete_front();
    void delete_rear();
};

template <class T> 
void DEqueue<T>::insert_front(T key) {
    cout<<GREEN<<"Push front: "<<key<<RESET<<" \n";
    if (this->IsFull()) {
        cout << "Overflow!!\n" << endl;
        return;
    }
    // If queue is initially empty,set front=rear=0; start of deque
    if (this->front == -1){
        this->front = 0;
        this->rear = 0;
    }else if (this->front == 0) {
        this->front = this->capacity - 1;
    } else // decrement front 1 position
        this->front = this->front - 1;

    this->queue[this->front] = key; // insert current element into DEqueue
    this->size++;
    this->print_queue();
}

// // insert element at the rear end of deque
template <class T> void DEqueue<T>::insert_rear(T key) {
    cout<<GREEN<<"Push rear : "<<key<<RESET<<" \n";

    if (this->IsFull()) {
        cout << "Overflow";
        return;
    }

    //  If queue is initially empty,set front=rear=0; start of deque
    if (this->front == -1) {
        this->front = 0;
        this->rear = 0;
    } else if (this->rear == this->capacity - 1) // rear is at last position of queue
        this->rear = 0;
    else // increment rear by 1 position
        this->rear = this->rear + 1;
    this->queue[this->rear] = key; // insert current element into DEqueue
    this->size++;
    this->print_queue();

}

// // Delete element at front of DEqueue
template <class T> void DEqueue<T>::delete_front() {
    cout<<RED<<"Pop front: "<<this->queue[this->front]<<RESET<<endl;
    if (this->IsEmpty()) {
        cout << "Queue Underflow!!\n";
        return;
    }
    this->queue[this->front] = -100;
    // DEqueue has only one element
    if (this->size==1) {
        this->front = -1;
        this->rear = -1;
    } else if (this->front == this->capacity - 1){
		this->front = 0;
    }else {
        this->front = this->front + 1;
    }
    this->size--;
    this->print_queue();

}

// // Delete element at rear end of DEqueue
template <class T> void DEqueue<T>::delete_rear() {
    cout<<RED<<"Pop rear : "<<this->queue[this->rear]<<RESET<<endl;
    if (this->IsEmpty()) {
        cout << "Underflow\n";
        return;
    }
    this->queue[this->rear] = -100;;

    // DEqueue has only one element
    if (this->size==1) {
        this->front = -1;
        this->rear = -1;
    } else if (this->rear == 0)
        this->rear = this->capacity - 1;
    else
        this->rear = this->rear - 1;
    this->size--;
    this->print_queue();
}