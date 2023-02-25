#include <iostream>
#include <cstdlib>
#include <ctime>
#include <cstring>
#include <iomanip>

using namespace std;

void fn0(int a, char b){
    cout<<"fn0: "<<a<<" "<<b<<endl;
}

void fn1(int a, char b='a'){
    cout<<"fn1: "<<a<<" "<<b<<endl;
}

void fn2(int a=1, char b='a'){
    cout<<"fn2: "<<a<<" "<<b<<endl;
}

//Trieda Movie
//nazov, rok, rating
//konstruktory
//destruktor
//setters, getters
//print

//Trieda MovieDB
//pole objectov tzpu Movie
//add, search, print

class Movie{
private:
    char* title;
    int year;
    int rating;
public:
    Movie(const char* title = nullptr, const int year = -1, const int rating = -1):
        title(nullptr),
        year(year),
        rating(rating){
        if(title){
            this->title=new char[strlen(title)+1];
            strcpy(this->title,title);
        }
    }
    Movie(const Movie& other):
        title(nullptr),
        year(other.year),
        rating(other.rating){
            if(other.title){
                title=new char[strlen(other.title)+1];
                strcpy(this->title,other.title);
            }
    }
    ~Movie(){
        if(title){
            delete[] title;
        }
    }

    void setTitle(char *set_title) {
        if(!set_title){
            return;
        }
        if(this->title){
            delete[] this->title;
            this->title=nullptr;
        }
        this->title=new char[strlen(set_title)+1];
        strcpy(this->title,set_title);
    }

    void setYear(int set_year) {
        this->year = set_year;
    }

    void setRating(int set_rating) {
        this->rating = set_rating;
    }

    char *getTitle() const {
        return title;
    }

    int getYear() const {
        return year;
    }

    int getRating() const {
        return rating;
    }

    void print() const{
        cout<<left<<setw(25)<<(this->title ? this->title : "-----");
        cout<<setw(7)<<this->year;
        cout<<this->rating;
        cout<<endl;
    }
};

//testovanie
int main(){
    //1.cast
    fn0(1,'u');
    fn1(2);
    fn1(3,'A');
    fn2();
    fn2(2);
    fn2(3,'A');
    //2.cast
    Movie film1;
    Movie film2("Toy Story",1995,86);
    Movie film3 = film2;
    film2.setRating(96);
    film2.print();
    return 0;
}