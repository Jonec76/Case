#include<iostream>
#include<string>
#include<vector>
#include<math.h>
#define RED     "\033[31m"
#define GREEN   "\033[32m"
#define RESET   "\033[0m"
using namespace std;

template < class T > class Chain;  // 前向宣告
template < class T > class CircularList;  // 前向宣告
class Polynomial;

struct Term { 
    double coef;
    int exp;
    Term Set(double c, int e) { coef=c; exp=e; return *this; }
};

template < class T >
class ChainNode {
    // Chain 可以 access 到 ChainNode 的 private/protected variable
    friend class CircularList <T>;
    friend class Polynomial;
    public:
        ChainNode(){link=NULL;}
        void set_data(T data){this->data = data;};
        T get_data(){return this->data;};
    private:
        T data;
        ChainNode<T>* link;
};

template <class T>
class CircularList {
    friend class Polynomial;
    public: 
        CircularList();
        ~CircularList(){};
        ChainNode<T>* GetNode();
        void RetNode(ChainNode<T>*& );
        void Insert(ChainNode<T> *x);
        void print_list(ostream& out);
        int size;
    private:
        ChainNode<T>* first;
        ChainNode<T>* last;
        ChainNode<T>* av;
};

class Polynomial{ 
    public:
        friend istream& operator>>(istream&, Polynomial&); // (a)
        friend ostream& operator<<(ostream&, Polynomial&); // (b)
        Polynomial(const Polynomial&);// (c)
        Polynomial& operator=(const Polynomial& b); // (D)
        ~Polynomial(); // (E)
        Polynomial& operator+(const Polynomial& b) const; // (F)
        Polynomial& operator-(const Polynomial& b) const; // (G)
        Polynomial& operator*(const Polynomial& b) const; // (H)
        Polynomial& operator+=(const Polynomial& b); // function for supporting operator *
        double Evaluate(double) const; //(i)
        Polynomial(){};
    private: 
        CircularList<struct Term> poly;
};


template <class T>
void CircularList<T>::print_list(ostream& out){
    if(last == NULL){
        out<<"Empty polynomial\n";
        return;
    }
    ChainNode<T>* tmp = first->link;
    while(tmp!=first){
        Term t = tmp->get_data();
        out<<GREEN<<t.coef<<" "<<t.exp<<RESET<<"\n";
        tmp = tmp->link;
    }
}

template <class T>
ChainNode<T>* CircularList<T>::GetNode() { // Provide a node for use
    ChainNode<T>* x; 
    if (av){
        x = av;
        av = av->link;
    }else{ // out of available nodes
        x = new ChainNode<T>; 
    }
    return x; 
}

template <class T>
void CircularList<T>::Insert(ChainNode<T> *x){
    // insert the node pointed at by x at the rear of the circular
    // list *this, where last points to the last node in the list
    size++;
    if (last==NULL) { // empty list
        last = x; 
        x -> link = first;
        first->link = x;
    } else {
        ChainNode<T> *cur = first;
        Term n = x->get_data();
        while(cur->link != first){
            Term c = (cur->link)->get_data();

            if(c.exp > n.exp ){
                break;
            }
            cur = cur->link;
        }


        if(cur->link == first)
            last = x;

        x->link = cur->link;
        cur->link = x;
    }
}



template <class T> 
CircularList<T>::CircularList() {
    size=0;
    last = NULL;
    av = NULL;
    first = new ChainNode<T>();
    ChainNode<T>* cur;
    for(int i =0;i<100;i++){
        ChainNode<T>* tmp = new ChainNode<T>();
        tmp->link = NULL;
        if(!av){
            av = tmp;
            cur = av;
            continue;
        }
        cur->link = tmp;
        cur = cur->link;
    }
}

template <class T>
void CircularList<T>::RetNode(ChainNode<T>*& x) {// Free the node pointed to by x
    x->link = av;
    av = x;
    x = 0; // not delete x
}




istream& operator>>(istream& is, Polynomial& p)
{
    cout<<"Read input file and construct Polynomial\n";
    int len;
    is >> len;
    for(int i=0;i<len;i++){
        ChainNode<Term>* x = p.poly.GetNode();
        Term t;
        is >> t.coef >> t.exp;

        x->set_data(t);
        p.poly.Insert(x);
    }
    return is; 
}

ostream& operator<<(ostream& out, Polynomial& p){
    p.poly.print_list(out);
    return out;
}

Polynomial::Polynomial(const Polynomial& a){
    cout<<"Copy constructor\n";
    int len = a.poly.size;
    ChainNode<Term>* cur = a.poly.first->link;
    for(int i=0;i<len;i++){
        ChainNode<Term>* x = this->poly.GetNode();

        x->set_data(cur->get_data());
        this->poly.Insert(x);
        cur = cur->link;
    }
 }


Polynomial& Polynomial::operator+=(const Polynomial& b){
    Polynomial* c = new Polynomial(*this + b);
    this->~Polynomial();
    int len = c->poly.size;
    ChainNode<Term>* cur = c->poly.first->link;
    for(int i=0;i<len;i++){
        ChainNode<Term>* x = this->poly.GetNode();
        x->set_data(cur->get_data());
        this->poly.Insert(x);
        cur = cur->link;
    }
    return *this;
}


Polynomial& Polynomial::operator=(const Polynomial& a){
    cout<<"Assign polynomial\n";
    cout<<"(Create and copy a new polynomial)";
    Polynomial* c = new Polynomial(a);
    cout<<"(Deconstruct the original polynomial)";
    this->~Polynomial();
    int len = c->poly.size;
    ChainNode<Term>* cur = c->poly.first->link;
    for(int i=0;i<len;i++){
        ChainNode<Term>* x = this->poly.GetNode();
        x->set_data(cur->get_data());
        this->poly.Insert(x);
        cur = cur->link;
    }
    return *this;
}

Polynomial& Polynomial::operator+(const Polynomial& b) const {
    cout<<"Add polynomial\n";

    Polynomial* c = new Polynomial();
    if(b.poly.size == 0){
        Polynomial* ret = new Polynomial(*this);
        return *ret;
    }else if(this->poly.size == 0){
        Polynomial* ret = new Polynomial(b);
        return *ret;
    }else if(this->poly.size == 0 && b.poly.size == 0){
        return *c;
    }

    ChainNode<Term>* cur1 = (*this).poly.first->link;
    ChainNode<Term>* cur2 = b.poly.first->link;
    int c1=0, c2=0;

    while(cur1 != (*this).poly.first && cur2 != b.poly.first){
        Term t1 = cur1->get_data();
        Term t2 = cur2->get_data();
        ChainNode<Term>* n = c->poly.GetNode();
        if(t1.exp < t2.exp){
            n->set_data(t1);
            cur1 = cur1->link;
        }else if(t1.exp > t2.exp){
            n->set_data(t2);
            cur2 = cur2->link;
        }else{
            Term s;
            s.coef = t1.coef + t2.coef;
            s.exp = t1.exp;
            n->set_data(s);
            cur1 = cur1->link;
            cur2 = cur2->link;
        }
        c->poly.Insert(n);
    }

    while(cur1 != (*this).poly.first){
        Term t1 = cur1->get_data();
        ChainNode<Term>* n = c->poly.GetNode();
        n->set_data(t1);
        cur1 = cur1->link;
        c->poly.Insert(n);
    }

    while(cur2 != b.poly.first){
        Term t2 = cur2->get_data();
        ChainNode<Term>* n = c->poly.GetNode();
        n->set_data(t2);
        cur2 = cur2->link;
        c->poly.Insert(n);
    }
    return *c;
}

Polynomial& Polynomial::operator-(const Polynomial& b) const {
    cout<<"Subtract polynomial\n";

    Polynomial* c = new Polynomial();

    ChainNode<Term>* cur1 = (*this).poly.first->link;
    ChainNode<Term>* cur2 = b.poly.first->link;
    int c1=0, c2=0;

    while(cur1 != (*this).poly.first && cur2 != b.poly.first){
        Term t1 = cur1->get_data();
        Term t2 = cur2->get_data();
        ChainNode<Term>* n = c->poly.GetNode();
        if(t1.exp < t2.exp){
            n->set_data(t1);
            cur1 = cur1->link;
        }else if(t1.exp > t2.exp){
            t2.coef *= -1;
            n->set_data(t2);
            cur2 = cur2->link;
        }else{
            Term s;
            s.coef = t1.coef - t2.coef;
            s.exp = t1.exp;
            n->set_data(s);
            cur1 = cur1->link;
            cur2 = cur2->link;
        }
        c->poly.Insert(n);
    }

    while(cur1 != (*this).poly.first){
        Term t1 = cur1->get_data();
        ChainNode<Term>* n = c->poly.GetNode();
        n->set_data(t1);
        cur1 = cur1->link;
        c->poly.Insert(n);
    }

    while(cur2 != b.poly.first){
        Term t2 = cur2->get_data();
        ChainNode<Term>* n = c->poly.GetNode();
        t2.coef *= -1;
        n->set_data(t2);
        cur2 = cur2->link;
        c->poly.Insert(n);
    }
    return *c;
}

Polynomial& Polynomial::operator*(const Polynomial& b) const {
    cout<<"Multiply polynomial\n";

    Polynomial* c = new Polynomial();

    ChainNode<Term>* cur1 = this->poly.first->link;
    int c1=0, c2=0;

    while(cur1 != this->poly.first){
        Polynomial* tmp = new Polynomial();
        ChainNode<Term>* cur2 = b.poly.first->link;

        Term t1 = cur1->get_data();
        double coef_a = t1.coef;
        int exp_a = t1.exp;
        while(cur2 != b.poly.first){
            Term t2 = cur2->get_data();
            double coef_b = t2.coef;
            int exp_b = t2.exp;

            double coef_prod = coef_a * coef_b;
            int exp_prod = exp_a + exp_b;

            Term prod;
            prod.coef = coef_prod;
            prod.exp = exp_prod;

            ChainNode<Term>* n = c->poly.GetNode();
            n->set_data(prod);
            tmp->poly.Insert(n);
            cur2 = cur2->link;
        }
        *c += *tmp;
        cur1 = cur1->link;
    }
    return *c;
}

Polynomial::~Polynomial() {
    cout<<"Deconstruct polynomial\n";

    if(poly.last) {
        ChainNode<Term>* x = poly.last->link;
        poly.last->link = poly.av; // last node linked to av av = x;
        poly.av = x->link;
        poly.last = NULL; 
        poly.size = 0;
    }
}

double Polynomial::Evaluate(double x) const{
    cout<<"Evaluate polynomial\n";

    ChainNode<Term>* cur = poly.first->link;
    
    double value = 0;
    char c = '+';
    while(cur != poly.first){
        Term t = cur->get_data();
        if(cur->link == poly.first)
            c = '=';
        printf("(%.2f * %.2f ^ %d) %c ", t.coef, x, t.exp, c);
        value += t.coef * pow(x, t.exp);
        cur = cur->link;
    }
    return value;
}