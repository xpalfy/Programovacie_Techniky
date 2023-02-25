#include <iostream>
#include <string>
#include <vector>

using namespace std;

template <typename T>
const T& maximum(const T& a, const T& b){
    return a > b ? a : b;
}

template <typename T, typename U>
struct MyPair{
    T first;
    U second;
    void about(){
        cout<<"Primary Template"<<endl;
    }
};

template <typename T>
struct MyPair<T,char>{
    T first;
    char second;
    void about(){
        cout<<"Partially specialized template"<<endl;
    }
};

template<typename T,int v>
void print(T a){
    cout<<a<<" "<<v<<endl;
}

int main(){
    cout<<maximum<int>(5,6)<<maximum<string>("ahoj","today")<<maximum<char>('a','u')<<endl;
    MyPair<string,vector<int>> mp1{"ahoj",{1,2,3,4,5}};
    MyPair<int,char> mp2{5,'a'};
    mp1.about();
    mp2.about();
    print<string,56>("ahoj");
    return 0;
}