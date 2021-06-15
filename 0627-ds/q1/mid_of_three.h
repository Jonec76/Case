#ifndef MID_OF_THREE_H
#define MID_OF_THREE_H

template < class T>
void swap( T* a, T* b)
{
	int tmp = *a;
	*a = *b;
	*b = tmp;
}

template < class T>
int partition(T a[],int p, int r) {
    T x=a[p],y=a[(r-p)/2+p],z=a[r-1],i=p-1,j=r;
    if ((y>x && y<z) || (y>z && y<x) ) 
        x=y;
    else if ((z>x && z<y) || (z>y && z<x )) 
        x=z;
    while (1) {
        do  {j--;} while (a[j] > x);
        do  {i++;} while (a[i] < x);
        if  (i < j) swap(&a[i],&a[j]);
        else return j+1;
    }
}

template < class T>
void mid_of_three(T a[],int start,int end) {
    int q;
    if (end-start<2) return;
    q=partition(a,start,end);
    mid_of_three(a,start,q);
    mid_of_three(a,q,end);
}

#endif