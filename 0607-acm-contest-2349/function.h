#ifndef FUNCTION_H_
#define FUNCTION_H_
#include <cstdlib>
#include <stddef.h>
#include <iostream>
using namespace std;

struct Node{
    int value;
    char side;
};
// TODO: Implement the sorting algorithm
template < class T >
void merge(T arr[], int l, int m, int r)
{
    int n1 = m - l + 1;
    int n2 = r - m;
 
    T L[n1], R[n2];
 
    for (int i = 0; i < n1; i++)
        L[i] = arr[l + i];
    for (int j = 0; j < n2; j++)
        R[j] = arr[m + 1 + j];
 
    int i = 0;
 
    int j = 0;
 
    int k = l;
 
    while (i < n1 && j < n2) {
        if (L[i].value <= R[j].value) {
            arr[k] = L[i];
            i++;
        }
        else {
            arr[k] = R[j];
            j++;
        }
        k++;
    }
 
    while (i < n1) {
        arr[k] = L[i];
        i++;
        k++;
    }
 
    while (j < n2) {
        arr[k] = R[j];
        j++;
        k++;
    }
}

template < class T >
void mysort(T arr[],int l,int r){
    if(l>=r){
        return;//returns recursively
    }
    int m =l+ (r-l)/2;
    mysort(arr,l,m);
    mysort(arr,m+1,r);
    merge(arr,l,m,r);
}



// TODO: Implement the funtion to read input, process data, and output answers.
void solve(){
    int N, left, right;
    long ans = 0, cost;
    std::cin >> N >> left >> right >> cost;
    struct Node* arr = new struct Node[N];
    int ctr = 0;
    for(int i=0;i<N;i++){
        std::cin >> arr[i].value;
        arr[i].side = (ctr < left)?'l':'r';
        ctr ++;
    }

    // 先依照數字去跑 merge sort
    mysort(arr, 0, N-1);


    int left_total = 0;
    int left_set = 0;
    // int left_single = 0;

    int right_total = 0;
    int right_set = 0;
    // int right_single = 0;
    

    // 這演算法蠻麻煩的（自己也想很久ＸＤ）
    // 1. 先找出同字異邊的 set(或說 pair 也行，但我的 code 是寫成 set)，然後就不要管他們
    // 2. 把兩邊都先抓出來，這時抓出來的組合只剩下 同邊同字、同邊異字、異邊異字（異邊同字不用管）
    // 3. 接著看兩邊那邊比較多，就處理多的那一邊
    // 3-1. 假如右邊比較多，那就去看右邊有多少個 set(同邊同字，譬如 666677 這樣可以組出 3 組就是 right_set=3)
    // 3-2. 用這些 set 去變色，以 66 為例就把它變成 6'6，而且能變的組數不能高於 (右邊總數 - 左邊總數)
    // 應該看不太懂，因為真的蠻難解釋的哈哈，直接看例子

    // 左:1234559 右:66789 來看(以下右邊會用 ' 表示)
    // 1. 先扣掉 99' ，因為他們已經組好了
    // 2. left_set=1, left_total=6, right_set=1, right_total=4
    // 3. 比較 total 那邊多，就處理那邊 。left_total > right_total 所以處理左邊
    // 3-1. 左邊 6 最多只能降到 4 (right_total)，再降下去成本會變高，至於怎麼降？
    // 3-2. 看 set
    //      因為 left_set=1   ->   6-2 >= 4   -> 變色 1 cost(55 變成 55')
    //      左邊剩下 1234 右邊 6678  -> 最好的 cost 就是 max(4, 4)=4
    // 總結：演算法最終目的是希望兩邊相同 (左 6 右 4 想辦法變成: 左 4 右 4)，而且只有在多出來的那邊還有 set 時，才能向下調整
    //      假如是 左 123456 右 7788 的話，因為左邊沒有 set 所以不能向下調整，這時最好的 cost 就是 max(6, 4)=6


    for(int i=0;i<N;){
        int cur_value = arr[i].value;
        int end_idx =0;
        int tmp_left_ctr  =0, tmp_right_ctr =0;
        do{ // 找出連續的一段數字之結尾 index
            end_idx++;
        }while(arr[i+end_idx].value==cur_value);

        for(int k=i;k<i+end_idx;k++){
            if(arr[k].side == 'l')
                tmp_left_ctr++;
            else
                tmp_right_ctr++;
        }

        if(tmp_left_ctr < tmp_right_ctr){
            right_total += (tmp_right_ctr - tmp_left_ctr); // 假如這段連續的 5 是 5555555，那 total 就是 7
            right_set += (tmp_right_ctr - tmp_left_ctr)>>1; // 假如這段連續的 5 是 5555555，那 set 就是 7/2 就是 3
            // right_single += (tmp_right_ctr - tmp_left_ctr) & 1; // single 沒用到
        }else{
            left_total += (tmp_left_ctr - tmp_right_ctr);
            left_set += (tmp_left_ctr - tmp_right_ctr)>>1;
            // left_single += (tmp_left_ctr - tmp_right_ctr) & 1;
        }

        i += end_idx;
    }
    // std::cout<<left_total<<" -- "<<right_total<<std::endl;
    // std::cout<<left_set<<" == "<<right_set<<std::endl;
    // std::cout<<left_single<<" ~~ "<<right_single<<std::endl;

    if(left_total > right_total){
        int capacity = (left_total - right_total)>>1; // 左 6 右 4 最多只能降到 4，再往下成本會上升
        int merge_set;
        if(capacity < left_set){
            merge_set = capacity;
        }else{
            merge_set = left_set;
        }
        ans = left_total - merge_set;
    }else if(left_total < right_total){
        int capacity = (right_total - left_total)>>1;
        int merge_set;
        if(capacity < right_set){
            merge_set = capacity;
        }else{
            merge_set = right_set;
        }
        ans = right_total - merge_set;
    }else{
        ans = left_total;
    }
    std::cout<<ans*cost<<std::endl;
};




// The codes bellow prevent you from using bulit-in sorting function and from importing C++ containers.
// Nothing needed to be implemented below.
// Do not modify the codes below.

void qsort(void* , std::size_t , std::size_t , void*);

template <class RandomAccessIterator> 
void sort (RandomAccessIterator , RandomAccessIterator );

template <class RandomAccessIterator, class Compare> 
void sort (RandomAccessIterator , RandomAccessIterator , Compare );

#endif
#ifndef vector
#define vector
#endif
#ifndef list
#define list
#endif
#ifndef forward_list
#define forward_list
#endif
#ifndef deque
#define deque
#endif
#ifndef array
#define array
#endif
#ifndef set
#define set
#endif
#ifndef multiset
#define multiset
#endif
#ifndef map
#define map
#endif
#ifndef multimap
#define multimap
#endif
#ifndef unordered_set
#define unordered_set
#endif
#ifndef unordered_multiset
#define unordered_multiset
#endif
#ifndef unordered_map
#define unordered_map
#endif
#ifndef unordered_multimap
#define unordered_multimap
#endif
#ifndef bitset
#define bitset
#endif
#ifndef valarray
#define valarray
#endif
#ifndef stack
#define stack
#endif
#ifndef queue
#define queue
#endif
#ifndef priority_queue
#define priority_queue
#endif
