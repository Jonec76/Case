#include<iostream>
#include "insert_sort.h"
#include "mid_of_three.h"
#include "r_merge_sort.h"
using namespace std;


template < class T>
void gen_int_data(T** arr, int len){
    for(int i=1;i<=len;i++){
        (*arr)[i] = (rand() % 100) + 1;
    }
}

template < class T>
void gen_char_data(T** arr, int len){
    for(int i=1;i<=len;i++){
        int r = rand() % 26;
        (*arr)[i] = 'a' + r; 
    }
}

template < class T>
void gen_float_data(T** arr, int len){

    for(int i=1;i<=len;i++){
        (*arr)[i] = ((rand() % 100) + 1)/10.0;
    }
}

int main(){
    int len=5;
    int* link = new int[len+1];
    int idx=0;
    memset(link, 0, len*sizeof(int));

    srand(time(0));
    
    int* i_arr = new int[len+1];
    gen_int_data(&i_arr, len);

    char* c_arr = new char[len+1];
    gen_char_data(&c_arr, len);

    float* f_arr = new float[len+1];
    gen_float_data(&f_arr, len);

    // InsertionSort(i_arr, len);
    // mid_of_three(i_arr, 1, len);
    // rMergeSort(c_arr, link, 1, len);
    // while(link[idx]!=0){// link 裡面記錄的是 sorted list 的 next node index，從 link[0] 開始 
    //     cout<<c_arr[link[idx]]<<" ";
    //     idx = link[idx];
    // }

}