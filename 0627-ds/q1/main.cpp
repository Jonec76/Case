#include<iostream>
#include <random>
#include <string>
#include <iomanip>
#include "insert_sort.h"
#include "mid_of_three.h"
#include "r_merge_sort.h"
#include "i_merge_sort.h"
#include "heap_sort.h"
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

void gen_random(char *s, size_t len) {
     for (size_t i = 0; i < len; ++i) {
        int randomChar = rand()%(26);
        s[i] = 'a' + randomChar;
     }
     s[len] = 0;
 }

template < class T>
void gen_string_data(T** arr, int len){

    for(int i=1;i<=len;i++){
        char* tmp = new char[5];
        gen_random(tmp, 5);
        string str(tmp);
        (*arr)[i] = tmp;
    }
}

template < class T>
void print_arr(T* arr, int len){
    for(int i=1;i<len;i++)
        cout<<arr[i]<<" ";
    puts("");
}

int main(){
    int len=6;
    int* link = new int[len+1];
    int idx=0;
    memset(link, 0, (len+1)*sizeof(int));

    srand(time(0));
    

    // generate random data
    int* i_arr = new int[len];
    gen_int_data(&i_arr, len);

    char* c_arr = new char[len];
    gen_char_data(&c_arr, len);

    float* f_arr = new float[len];
    gen_float_data(&f_arr, len);

    string* s_arr = new string[len];
    gen_string_data(&s_arr, len);



    // sort 
    cout<<setw(22)<<"Insertion sort: ";
    InsertionSort(i_arr, len);
    print_arr(i_arr, len);

    cout<<setw(22)<<"Heap sort: ";
    int* i_arr_2 = new int[len];
    gen_int_data(&i_arr_2, len);
    HeapSort(i_arr_2, len);
    print_arr(i_arr_2, len);

    cout<<"Midian-of-three sort: ";
    mid_of_three(c_arr, 1, len);
    print_arr(c_arr, len);

    cout<<"Recursive merge sort: ";
    rMergeSort(f_arr, link, 1, len);
    while(link[idx]!=0){// link 裡面記錄的是 sorted list 的 next node index，從 link[0] 開始 
        cout<<f_arr[link[idx]]<<" ";
        idx = link[idx];
    }
    puts("");

    cout<<"Iterative merge sort: ";
    iMergeSort(s_arr, len);
    print_arr(s_arr, len);
}