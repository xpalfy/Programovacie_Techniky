#include <iostream>
#include <cstdlib>
#include <ctime>

using namespace std;

void printList(const int* data,const size_t length){
    for (int i=0;i<length;cout<<data[i]<<" ",i++);
    cout<<std::endl;
}

void numSwap(int* num_1, int* num2){
    int tmp=*num_1;
    *num_1=*num2;
    *num2=tmp;
}

void bubbleSort(int* data,const size_t length){
    for(int i=0;i<length;i++){
        for(int j=0;j<length-i-1;j++){
            if(data[j]>data[j+1]){
                numSwap(&data[j],&data[j+1]);
            }
        }
    }
}

size_t getPivotIndex(const int *data, const size_t low, const size_t high)
{
    return rand()%(high-low)+low;
}

size_t partition(int data[], const size_t pivot, const size_t low, const size_t high)
{
    numSwap(&data[pivot], &data[high-1]);
    size_t j = low;
    for (size_t i=low;i<high;i++) {
        if (data[i] <= data[high-1]) {
            numSwap(&data[j], &data[i]);
            j++;
        }
    }
    j--;
    return j;
}

void quickSort(int *data, const size_t low, const size_t high)
{
    if(low+1<high){
        size_t pivot = getPivotIndex(data,low,high);
        pivot=partition(data,pivot,low,high);
        quickSort(data,low,pivot);
        quickSort(data,pivot+1,high);
    }
}

int main()
{
    srand(time(NULL)); 
    int data[]={5,4,3,2,1};
    size_t n = sizeof(data)/sizeof(data[0]);
    printList(data,n);
    //bubbleSort(data,n);
    quickSort(data,0,n);
    printList(data,n);
    return 0;
}