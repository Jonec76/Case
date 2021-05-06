#include "matrix_node.h"
#include<iostream>
#include<fstream>
using namespace std;

int main(){
    ifstream cin_m("input.txt");
    Matrix m;
    cin_m >> m ;
    
    ifstream cin_n("input2.txt");
    Matrix n;
    cin_n >> n;
    
    cout<<m+n;

    ifstream cin_mul("input3.txt");
    Matrix mplier;
    cin_mul >> mplier;
    cout<<m*mplier;
    
    cout<<m.transpose();

    Matrix copy_m(n);
    cout<<copy_m;

}