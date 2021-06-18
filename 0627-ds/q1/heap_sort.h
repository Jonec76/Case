#ifndef HEAP_SORT_H
#define HEAP_SORT_H

template<class T>
void Adjust(T *a, const int root, const int n) {
    T e=a[root];
    int j = 2*root;
    for (; j <= n; j *=2) {
        if (j < n && a[j] < a[j+1]) // j and j+1 are siblings 
            j++; // make j be the max child
        if (e >= a[j]) 
            break;
        a[j / 2] = a[j]; // move jth record up the path
    }
    a[j / 2] = e; 
}

template<class T>
void HeapSort(T *a, const int n) {// sort a[1..n] into non-decreasing order
// a[n/2] is the parent of the last node, a[n]
    for (int i = n/2; i >= 1; i--) // buttom-up heapification
        Adjust(a, i, n);// make the tree rooted at i be a max heap
    for (int i = n-1; i >= 1; i--) {
        swap(a[1], a[i+1]); // move one record from heap to list 
        Adjust(a, 1, i); // heapify
    } 
}

#endif