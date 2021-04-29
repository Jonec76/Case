#include<iostream>
#include<string>
#include<vector>
using namespace std;

#define RED     "\033[31m"
#define GREEN   "\033[32m"
#define RESET   "\033[0m"
struct Triple{int row, col, value;};
class Matrix; 
class MatrixNode {
    friend class Matrix;
    friend istream& operator>>(istream&, Matrix&); // 為了能夠讀進矩陣
    friend ostream& operator<<(ostream&, Matrix&);
    private:
        MatrixNode *down , *right;
        bool head;
        union {
            MatrixNode* next;
            Triple triple;
        };
        MatrixNode(bool, Triple*); // 建構子
    public:
        string print_triple();
        Triple get_triple();
};



MatrixNode::MatrixNode(bool b, Triple *t) // 建構子
{
    head = b;
    if (b) {right = down = this;} // 列/行的標頭節點
    else triple = *t; // 標頭節點串列的元素節點或標頭節點
}
Triple MatrixNode::get_triple(){
    return triple;
}
static MatrixNode* av = NULL;

class Matrix{
    friend istream& operator>>(istream&, Matrix&);
    friend ostream& operator<<(ostream&, Matrix&);
    friend Matrix& operator*(Matrix const &, Matrix const &);
    public:
        Matrix(){};
        Matrix(Matrix&);
        ~Matrix(); // 解構子
        int p, row, col, value;
        Matrix& operator+(Matrix const &);
        vector<Triple> get_triple_table() const;
        void build_matrix(vector<Triple>, Matrix& );
        Matrix transpose() const;
    private:
        MatrixNode* headnode;

};

Matrix::Matrix(Matrix& copy){
    vector<Triple> table = copy.get_triple_table();
    Triple t;
    t.row = copy.row;
    t.col = copy.col;
    t.value = copy.value;
    table.insert(table.begin(), t);
    
    build_matrix(table, *this);
}


Matrix Matrix::transpose() const{
    Matrix transpose_matrix;
    vector<Triple>table = get_triple_table();

    for(int i=0;i<value;i++){
        int tmp = table[i].col;
        table[i].col = table[i].row;
        table[i].row = tmp;
    }

    Triple t;
    t.col = row;
    t.row = col;
    t.value = value;
    table.insert(table.begin(), t);

    transpose_matrix.build_matrix(table, transpose_matrix);
    return transpose_matrix;
}

string MatrixNode::print_triple(){
    return to_string(triple.row)+" "+to_string(triple.col)+ " "+to_string(triple.value)+"\n";
}


Matrix& Matrix::operator+(Matrix const &b){
    Matrix sum;
    
    if(col!=b.col ||row!=b.row){
        cout<<"Mismatch dimension.";
        return *this;
    }

    vector<Triple>table_a = get_triple_table();
    vector<Triple>table_b = b.get_triple_table();

    vector<Triple> table_sum;
    int i_a=0, i_b=0;

    while(i_a < value && i_b < b.value){
        int one_dim_index_a = table_a[i_a].row*p + table_a[i_a].col;
        int one_dim_index_b = table_b[i_b].row*b.p + table_b[i_b].col;
        Triple t;
        if(one_dim_index_a < one_dim_index_b){
            t.col = table_a[i_a].col;
            t.row = table_a[i_a].row;
            t.value = table_a[i_a].value;
            i_a++;
        }else if(one_dim_index_a > one_dim_index_b){
            t.col = table_b[i_b].col;
            t.row = table_b[i_b].row;
            t.value = table_b[i_b].value;
            i_b++;
        }else{
            t.col = table_b[i_b].col;
            t.row = table_b[i_b].row;
            t.value = table_a[i_a].value + table_b[i_b].value;
            i_a++;
            i_b++;
        }
        table_sum.push_back(t);
    }

    if(i_a != value){
        while(i_a < value){
            Triple t;
            t.col = table_a[i_a].col;
            t.row = table_a[i_a].row;
            t.value = table_a[i_a].value;
            table_sum.push_back(t);
            i_a++;
        }
    }


    if(i_b != b.value){
        while(i_b < b.value){
            Triple t;
            t.col = table_b[i_b].col;
            t.row = table_b[i_b].row;
            t.value = table_b[i_b].value;
            table_sum.push_back(t);
            i_b++;
        }
    }

    Triple t;
    t.col = col;
    t.row = row;
    t.value = table_sum.size();
    table_sum.insert(table_sum.begin(), t);

    build_matrix(table_sum, *this);
    return *this;
};


vector<Triple> Matrix::get_triple_table() const{
    vector<Triple> table;
    MatrixNode* matrix_head = headnode;
    MatrixNode* cur_head = headnode;
    cur_head = matrix_head->right; // H[0]
    int i=0;
    while(cur_head != matrix_head){
        MatrixNode* tmp_element = cur_head->right; // row major
        while(tmp_element != cur_head){
            Triple tmp_triple = tmp_element->get_triple();
            table.push_back(tmp_triple);
            tmp_element = tmp_element->right;
            i++;
        }
        cur_head = cur_head->next;
    }
    return table;
}


ostream& operator<<(ostream& os, Matrix& matrix){
    MatrixNode* matrix_head = matrix.headnode;
    MatrixNode* cur_head = matrix.headnode;
    os<<GREEN<<"Head \n "<<RESET<<matrix_head->print_triple();
    os<<GREEN<<"\nElement \n"<<RESET;
    cur_head = matrix_head->right; // H[0]
    
    while(cur_head != matrix_head){
        MatrixNode* tmp_element = cur_head->right; // row major
        while(tmp_element != cur_head){
            os<<" "<<tmp_element->print_triple();
            tmp_element = tmp_element->right;
        }
        cur_head = cur_head->next;
    }
    return os;
};

void Matrix::build_matrix(vector<Triple> table_sum, Matrix& matrix)
{
    Triple s;
    s.row = table_sum[0].row;
    s.col = table_sum[0].col;
    s.value = table_sum[0].value;
    int p = max(s.row, s.col);
    matrix.p = p;
    matrix.row = s.row;
    matrix.col = s.col;
    matrix.value = s.value;
    // set up header node for list of header nodes 
    matrix.headnode = new MatrixNode(false, &s);

    if (p == 0) {
        matrix.headnode->right = matrix.headnode;
    }

    MatrixNode **head = new MatrixNode* [p]; 
    for (int i = 0; i < p; i++)
        head[i] = new MatrixNode(true, 0); // please continue on the next page
    
    MatrixNode **col = new MatrixNode* [p];     
    for (int i = 0; i < p; i++){
        col[i] = head[i];
    }

    int currentRow = 0;
    MatrixNode* last = head[0]; // last node in current row
    for (int i = 0; i < s.value; i++) {
        Triple t;
        t.row = table_sum[i+1].row;
        t.col = table_sum[i+1].col;
        t.value = table_sum[i+1].value;
        if (t.row > currentRow) { // end of current row
            last->right = head[currentRow]; // close current
            currentRow = t.row;
            last = head[currentRow]; 
        } // end of if
        last = last->right = new MatrixNode(false, &t); // link new node into row list
        
        col[t.col] = col[t.col]->down = last;
    }
    last->right = head[currentRow]; // close last row 
    for (int i = 0; i < s.col; i++)
        col[i]->down = head[i]; // close all column
    // link the header nodes together
    for (int i = 0; i < p; i++)
        head[i]->next = head[i + 1];
    head[p-1]->next = matrix.headnode;
    matrix.headnode->right = head[0];
    delete [] head;
}

istream& operator>>(istream& is, Matrix& matrix)
{
    Triple s;
    is >> s.row >> s.col >> s.value;
    int p = max(s.row, s.col);
    matrix.p = p;
    matrix.row = s.row;
    matrix.col = s.col;
    matrix.value = s.value;
    // set up header node for list of header nodes 
    matrix.headnode = new MatrixNode(false, &s);

    if (p == 0) {
        matrix.headnode->right = matrix.headnode;
        return is; // for supporting "cin >> mi >> mj;" }
    }

    MatrixNode **head = new MatrixNode* [p]; 
    for (int i = 0; i < p; i++)
        head[i] = new MatrixNode(true, 0); // please continue on the next page
    
    MatrixNode **col = new MatrixNode* [p];     
    for (int i = 0; i < p; i++){
        col[i] = head[i];
    }

    int currentRow = 0;
    MatrixNode* last = head[0]; // last node in current row
    for (int i = 0; i < s.value; i++) {
        Triple t;
        is >> t.row >> t.col >> t.value;
        if (t.row > currentRow) { // end of current row
            last->right = head[currentRow]; // close current
            currentRow = t.row;
            last = head[currentRow]; 
        } // end of if
        last = last->right = new MatrixNode(false, &t); // link new node into row list
        
        col[t.col] = col[t.col]->down = last;
    }
    last->right = head[currentRow]; // close last row 
    for (int i = 0; i < s.col; i++)
        col[i]->down = head[i]; // close all column
    // link the header nodes together
    for (int i = 0; i < p; i++)
        head[i]->next = head[i + 1];
    head[p-1]->next = matrix.headnode;
    matrix.headnode->right = head[0];
    delete [] head;
    return is; 
}

Matrix::~Matrix(){
//     if(!headnode)
//         return;
//     MatrixNode* x = headnode->right;

//     headnode->right = av;
//     av = headnode;

//     while(x != headnode){
//         MatrixNode* y = x->right;
//         x->right = av;
//         av = y;
//         x = x->next;
//     }

//     headnode = 0;
}