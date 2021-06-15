#ifndef R_MERGE_SORT_H
#define R_MERGE_SORT_H
using namespace std;
#include<iostream>

template <class T>
int ListMerge(T* a, int* link, const int start1, const int start2) {// 兩個排序好的鏈分別從start1及start2開始，將它們合併
// 將link[0]當作一個暫時的標頭。回傳合併好的鏈的開頭。 int iResult = 0; // 結果鏈的最後一筆記錄
    int i1=start1, i2 =start2;
    int iResult = 0;
    for (; i1 && i2; ){
        if (a[i1] <= a[i2]) { 
            link[iResult] = i1;
            iResult = i1; 
            i1 = link[i1];
        }else {
            link[iResult] = i2;
            iResult = i2; 
            i2 =link[i2]; 
        }
    }

    // 將其餘的記錄附接至結果鏈
    if (i1 == 0) 
        link[iResult] = i2; 
    else 
        link[iResult] = i1;
    return link[0];
}


template <class T>
int rMergeSort(T* a, int* link, const int left, const int right)
{// 要排序的是a[left:right]。對於所有i，link[i] 初始化為0。
// rMerge回傳排序好的鏈的第一個元素之索引值。
    if (left >= right) return left; //base case int mid = (left + right) /2;
    int mid = (left + right) /2;

    return ListMerge(a, link,
        rMergeSort(a, link, left, mid),
        rMergeSort(a, link, mid+1, right)); // 排序左半邊 rMergeSort(a, link, mid + 1, right));
}

#endif