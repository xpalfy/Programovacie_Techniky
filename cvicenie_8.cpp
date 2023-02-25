#include <iostream>

using namespace std;

int add(const int a, const int b){
    return a+b;
}

int substract(const int a, const int b){
    return a-b;
}

void op1(){
    cout<<"op1"<<endl;
}

void op2(){
    cout<<"op2"<<endl;
}


void runFunction(void (*op)()){
    op();
}

typedef void(*fn)();

//testovanie
int main(){
    fn functions[]={op1,op2,op1};
    for(fn f:functions){
        f();
    }

    int(*op)(int,int);
    runFunction(op1);
    runFunction(op2);

    op=add;
    cout<<op(2,6)<<endl;

    op=substract;
    cout<<op(10,6);

    return 0;
}