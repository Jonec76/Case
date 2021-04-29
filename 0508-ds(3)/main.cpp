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
    Triple* table = new Triple[m.value];
    vector<Triple> m_table = m.get_triple_table();

    // Matrix sum = (m+n);
    // cout<<sum;

    // sum = sum.transpose();
    // cout<<sum;

    Matrix test(m);
    cout<<test;

    // cout<<m;
    // cout<<n;
}