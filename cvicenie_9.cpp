#include <iostream>
#include <functional>
#include <vector>
#include <string>
#include <algorithm>

using namespace std;
/*
struct S{
    int num;
};

class C{
    int num;
public:
    C(){}
    C(int a){}
};

C fn1(){
    return {6};
}

void fn2(C c){

}

int name(){
    int a;
    int b=3;
    int c(5);
    S s1;
    S s2 = {5};
    S s3[]={{1},{2},{3}};
    int pole[]= {5,5,5,5};
    int pole2[10]={5};
    C c1;
    C c2=3;
    C c3(c2);

    //nova syntax

    int n1{};
    int n2{5};

    S sn1{};
    S sn2{6};
    S sn3[]{{5},{6},{7}};
    int pole3[]{5,6,9,10};

    C r1{};
    C r2{5};
    C r3{r2};
    C r4[]{1,2,5};
    C* r5{new C[]{1,2,3}};
    C r6{fn1()};
    fn2({6});

    int tmp = 56;
    function<int(int)> lambda = [&tmp](int param){
        return tmp+5;
    };

    function<function<int(int)>(void)> lambda2 = []()->int(*)(int){
        return [](int param){
            return 4;
        };
    };

    lambda(5);
    lambda2()(5);
    return 0;
}
*/

bool isNonEmpty(const string& str){
    return !str.empty();
}

int main(){
    vector<string> v {"This","is","a","nice","day"};
    // 1. all_of
    all_of(v.crbegin(),v.crend(), isNonEmpty); //bool, True or False
    all_of(v.crbegin(),v.crend(), [](const string& str){return !str.empty();});
    // 2. for_each
    for_each(v.begin(),v.end(),[](const string& str){cout<<str<<" "<<endl;});
    // 3. count_if
    count_if(v.begin(),v.end(),[](const string& str){
        return isupper(str.at(0))!=0;
    });
    // 4.find
    vector<string>::iterator iter = find(v.begin(),v.end(),"is");
    if(iter!=v.end()){
        cout<<*iter<<endl;
    }
    else{
        cout<<"Nenaslo"<<endl;
    }
    // 5.copy_if
    int len=4;
    vector<string>v2{v.size()};
    copy_if(v.begin(),v.end(),v2.begin(),[len](const string& str){
        return str.length()== (decltype(str.length()))len;});
    // 6.remove_if
    vector<string> del {"is","This"};
    vector<string>::iterator iter2=remove_if(v.begin(),v.end(),[&del](const string& str){
        for(const string& d : del){
            if(d==str){
                return true;
            }
        }
        return false;
    });
    return 0;
}