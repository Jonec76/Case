#ifndef INSERT_SORT_H
#define INSERT_SORT_H

template < class T>
void Insert(const T& e, T* a, int i) { // insert e into ordered a[1:i]
    a[0] = e; 
    while(e < a[i]) {
        a[i + 1] = a[i];
        i--; 
    }
    a[i + 1] = e; 
}

template < class T>
void InsertionSort(T* a, const int n)
{ // Sort a[1:n] into nondecreasing order
    for(int j = 1; j<=n;j++) {
        T temp = a[j];
        Insert(temp, a, j-1); 
    }
}
#endif