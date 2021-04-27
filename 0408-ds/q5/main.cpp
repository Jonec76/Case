#include "matrix.h"

using namespace std;

void prod_complex_matrix(Matrix& r_matrix, Matrix& i_matrix, Matrix A, Matrix B, Matrix C, Matrix D){
    r_matrix = sub(mul(A, C), mul(B, D));
    i_matrix = add(mul(A, D), mul(B, C));
    cout<<"相乘實數矩陣: "<<endl<<r_matrix<<endl;
    cout<<"相乘虛數矩陣: "<<endl<<r_matrix<<endl;
}


int main(){
    Matrix m1 = Matrix(2, 2);
    Matrix m2 = Matrix(2, 2);
    Matrix m3 = Matrix(2, 2);
    Matrix m4 = Matrix(2, 2);
    Matrix r_matrix = Matrix(2, 2);
    Matrix i_matrix = Matrix(2, 2);
    
    m1 += 2*m1.createIdentity(2);
    m2 += 3*m2.createIdentity(2);
    m3 += 4*m2.createIdentity(2);
    m4 += 5*m2.createIdentity(2);

    cout<<"實數矩陣 m1: "<<endl<<m1;
    cout<<"虛數矩陣 m1: "<<endl<<m2<<endl;
    cout<<"實數矩陣 m2: "<<endl<<m3;
    cout<<"虛數矩陣 m2: "<<endl<<m4<<endl;


    prod_complex_matrix(r_matrix, i_matrix, m1, m2, m3, m4);
}