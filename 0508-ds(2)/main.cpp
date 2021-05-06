#include "polynomial.h"
#include<iostream>
#include<fstream>
#define RED     "\033[31m"
#define GREEN   "\033[32m"
#define RESET   "\033[0m"
int main(){
    ifstream cin_p("input.txt");
    Polynomial a;
    cin_p>>a;
    cout<<a;

    Polynomial copy(a);
    cout<<copy;

    Polynomial assign_p;
    assign_p = a;
    cout<<assign_p;
    
    Polynomial b;
    cin_p>>b;
    cout<<b;

    cout<<a+b;
    cout<<a-b;
    cout<<a*b;
    double value = a.Evaluate(3);
    cout<<GREEN<<value<<RESET<<"\n\n";
}