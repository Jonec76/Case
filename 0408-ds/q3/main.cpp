#include<iostream>

using namespace std;

void Multiply(int **a,int **b, int **c, int m, int n, int p){
    int count_a = 0;
    int count_b = 0;
    int count_c = 0;
    int count_d = 0;
    int count_e = 0;

    for(int i=0;i<m;i++){
        count_a++;
        for(int j=0; j<p; j++){
            count_b++;
            c[i][j] = 0;count_c++;
            for(int k=0;k<n;k++){
                count_d++;
                c[i][j] += a[i][k] * b[k][j];count_e++;
            }
        }
    }

    cout<<"[Count analysis]"<<endl;
    cout<<"count_a: "<<count_a<<endl;
    cout<<"count_b: "<<count_b<<endl;
    cout<<"count_c: "<<count_c<<endl;
    cout<<"count_d: "<<count_d<<endl;
    cout<<"count_e: "<<count_e<<endl<<endl;
}

void allocSpace(int*** p, int row, int col){
    *p = new int*[row];
    for (int i = 0; i < row; ++i) {
        (*p)[i] = new int[col];
    }
}
void printMatrix(int** matrix, int row, int col){
    cout<<"(row: "<<row<<", col: "<<col<<")"<<endl;
    for (int i = 0; i < row; i++) {
        for (int j = 0; j < col; j++) {
            cout<<matrix[i][j]<<" ";
        }
        cout<<endl;
    }
    cout<<endl;
}

void allocValue(int*** p, int row, int col){
    allocSpace(p, row, col);
    for (int i = 0; i < row; ++i) {
        for (int j = 0; j < col; ++j) {
            (*p)[i][j] = i + j;
        }
    }
    printMatrix(*p, row, col);
}


int main(){
    int** a=NULL, **b=NULL, **c=NULL;
    int row=5, col=3;

    cout<<"[Matrix A]"<<endl;
    allocValue(&a, 5, 3);

    
    cout<<"[Matrix B]"<<endl;
    allocValue(&b, 3, 4);


    allocSpace(&c, 5, 4);
    Multiply(a, b, c, 5, 3, 4);
    cout<<"[Matrix A X B]"<<endl;
    printMatrix(c, 5, 4);

    free(a);
    free(b);
    free(c);
}