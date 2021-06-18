#ifndef I_MERGE_SORT_H
#define I_MERGE_SORT_H

template<class T>
void Merge(T *a, T *b, const int k, const int m, const int n)
{ // a[k:m], a[m+1:n] are sorted, merged to b[k:n] for (int i1 = k, i2 = m+1, i3 = k;
    int i1 = k, i2 = m+1, i3 = k; 
    for (;i1 <= m && i2 <= n;i3++) {
        if (a[i1] <= a[i2]) { 
            b[i3] = a[i1]; 
            i1++;
        } else {
            b[i3] = a[i2];
            i2++; 
        }
    }
    // copy remaining records, if any, of 1st sublist
    if(i2>n) copy(a+i1, a+m+1, b+i3);
    // copy remaining records, if any, of 2nd sublist
    if(i1>m) copy(a+i2, a+n+1, b+i3);
}


template<class T>
void MergePass(T *a, T *b, const int n, const int s) {//adjacent pairs of sublist of size s are merged from a to b. n = # records in a
    int i = 1;
    for (;i <= n-(2*s)+1;i+= 2*s){
        Merge(a, b, i, i+s-1, i+(2*s)-1); 
    } 
    // merge remaining lists of size < 2*s
    if ((i + s-1) < n) //one full and one partial lists
        Merge(a, b, i, i+s-1, n);
    else //only one partial lists remained copy(a+i, a+n+1, b+i);
        copy(a+i, a+n+1, b+i);
}


template<class T>
void iMergeSort(T *a, const int n)
{ // sort a[1:n] into non-decreasing order
    T *tempList = new T[n+1];
    // s is the length of the currently merged sublist
    for (int s = 1; s < n; s *= 2) {
        MergePass(a, tempList, n, s);
        s *= 2;
        MergePass(tempList, a, n, s); 
    }
    delete [] tempList; 
}
#endif