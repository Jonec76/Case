/*
 * matrix.cpp
 */

#include <stdexcept>
#include <iostream>
#include "matrix.h"

#define EPS 1e-10

using namespace std;
using std::ostream;  using std::istream;  using std::endl;
using std::domain_error;

void allocSpace(double*** p, int n){
    *p = new double*[n];
    for (int i = 0; i < n; ++i) {
        (*p)[i] = new double[n];
    }
}

Matrix add(Matrix a, Matrix b){
    double** m_sum_res;
    double** m_a = a.getMatrix();
    double** m_b = b.getMatrix();
    int n = a.rows_;

    allocSpace(&m_sum_res, n);
    
    for(int i=0;i<n;i++){
        for(int j=0;j<n;j++){
            m_sum_res[i][j] = m_a[i][j] + m_b[i][j];
        }
    }
    Matrix sum_res = Matrix(m_sum_res, n, n);
    return sum_res;
}

Matrix sub(Matrix a, Matrix b){
    double** m_sub_res;
    double** m_a = a.getMatrix();
    double** m_b = b.getMatrix();
    int n = a.rows_;

    allocSpace(&m_sub_res, n);
    
    for(int i=0;i<n;i++){
        for(int j=0;j<n;j++){
            m_sub_res[i][j] = m_a[i][j] - m_b[i][j];
        }
    }
    Matrix sub_res = Matrix(m_sub_res, n, n);
    return sub_res;
}

Matrix mul(Matrix a, Matrix b){
    double** m_mul_res;
    double** m_a = a.getMatrix();
    double** m_b = b.getMatrix();
    int n = a.rows_;

    allocSpace(&m_mul_res, n);
    
    for(int i=0;i<n;i++){
        for(int j=0;j<n;j++){
            int prod = 0;
            for(int k=0;k<n;k++){
                prod += m_a[i][k] * m_b[k][j];
            }
            m_mul_res[i][j] = prod;
        }
    }
    Matrix mul_res = Matrix(m_mul_res, n, n);
    return mul_res;
}


/* PUBLIC MEMBER FUNCTIONS
 ********************************/
double** Matrix::getMatrix(){
    return p;
};

Matrix::Matrix(int rows, int cols) : rows_(rows), cols_(cols)
{
    allocSpace();
    for (int i = 0; i < rows_; ++i) {
        for (int j = 0; j < cols_; ++j) {
            p[i][j] = i+j;
        }
    }
}

Matrix::Matrix(double** a, int rows, int cols) : rows_(rows), cols_(cols)
{
    allocSpace();
    for (int i = 0; i < rows_; ++i) {
        for (int j = 0; j < cols_; ++j) {
            p[i][j] = a[i][j];
        }
    }
}

Matrix::Matrix() : rows_(1), cols_(1)
{
    allocSpace();
    p[0][0] = 0;
}

Matrix::~Matrix()
{
    for (int i = 0; i < rows_; ++i) {
        delete[] p[i];
    }
    delete[] p;
}

Matrix::Matrix(const Matrix& m) : rows_(m.rows_), cols_(m.cols_)
{
    allocSpace();
    for (int i = 0; i < rows_; ++i) {
        for (int j = 0; j < cols_; ++j) {
            p[i][j] = m.p[i][j];
        }
    }
}

Matrix& Matrix::operator=(const Matrix& m)
{
    if (this == &m) {
        return *this;
    }

    if (rows_ != m.rows_ || cols_ != m.cols_) {
        for (int i = 0; i < rows_; ++i) {
            delete[] p[i];
        }
        delete[] p;

        rows_ = m.rows_;
        cols_ = m.cols_;
        allocSpace();
    }

    for (int i = 0; i < rows_; ++i) {
        for (int j = 0; j < cols_; ++j) {
            p[i][j] = m.p[i][j];
        }
    }
    return *this;
}

Matrix& Matrix::operator+=(const Matrix& m)
{
    for (int i = 0; i < rows_; ++i) {
        for (int j = 0; j < cols_; ++j) {
            p[i][j] += m.p[i][j];
        }
    }
    return *this;
}

Matrix& Matrix::operator-=(const Matrix& m)
{
    for (int i = 0; i < rows_; ++i) {
        for (int j = 0; j < cols_; ++j) {
            p[i][j] -= m.p[i][j];
        }
    }
    return *this;
}

Matrix& Matrix::operator*=(const Matrix& m)
{
    Matrix temp(rows_, m.cols_);
    for (int i = 0; i < temp.rows_; ++i) {
        for (int j = 0; j < temp.cols_; ++j) {
            for (int k = 0; k < cols_; ++k) {
                temp.p[i][j] += (p[i][k] * m.p[k][j]);
            }
        }
    }
    return (*this = temp);
}

Matrix& Matrix::operator*=(double num)
{
    for (int i = 0; i < rows_; ++i) {
        for (int j = 0; j < cols_; ++j) {
            p[i][j] *= num;
        }
    }
    return *this;
}

Matrix& Matrix::operator/=(double num)
{
    for (int i = 0; i < rows_; ++i) {
        for (int j = 0; j < cols_; ++j) {
            p[i][j] /= num;
        }
    }
    return *this;
}


/* STATIC CLASS FUNCTIONS
 ********************************/

Matrix Matrix::createIdentity(int size)
{
    Matrix temp(size, size);
    for (int i = 0; i < temp.rows_; ++i) {
        for (int j = 0; j < temp.cols_; ++j) {
            if (i == j) {
                temp.p[i][j] = 1;
            } else {
                temp.p[i][j] = 0;
            }
        }
    }
    return temp;
}

void Matrix::allocSpace()
{
    p = new double*[rows_];
    for (int i = 0; i < rows_; ++i) {
        p[i] = new double[cols_];
    }
}

/* NON-MEMBER FUNCTIONS
 ********************************/

Matrix operator+(const Matrix& m1, const Matrix& m2)
{
    Matrix temp(m1);
    return (temp += m2);
}

Matrix operator-(const Matrix& m1, const Matrix& m2)
{
    Matrix temp(m1);
    return (temp -= m2);
}

Matrix operator*(const Matrix& m1, const Matrix& m2)
{
    Matrix temp(m1);
    return (temp *= m2);
}

Matrix operator*(const Matrix& m, double num)
{
    Matrix temp(m);
    return (temp *= num);
}

Matrix operator*(double num, const Matrix& m)
{
    return (m * num);
}

Matrix operator/(const Matrix& m, double num)
{
    Matrix temp(m);
    return (temp /= num);
}

ostream& operator<<(ostream& os, const Matrix& m)
{
    for (int i = 0; i < m.rows_; ++i) {
        os << m.p[i][0];
        for (int j = 1; j < m.cols_; ++j) {
            os << " " << m.p[i][j];
        }
        os << endl;
    }
    return os;
}

istream& operator>>(istream& is, Matrix& m)
{
    for (int i = 0; i < m.rows_; ++i) {
        for (int j = 0; j < m.cols_; ++j) {
            is >> m.p[i][j];
        }
    }
    return is;
}
