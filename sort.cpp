//Type of sorts
//Author: Vincent Pálfy

#include <iostream>
#include <cstdlib>
#include <ctime>
#include <cstring>
#include <bits/stdc++.h>

#define SIZE 20
using namespace std;

void genArray(int* data,const size_t n, const size_t hmin, const size_t hmax){
    for (size_t i=0;i<n;i++){
        data[i]=rand()%(hmax-hmin+1)+hmin;
    }
}

void copyArray(const int* originalList, int* newList, const int length){
    for (int i=0;i<length;i++){
        newList[i]=originalList[i];
    }
}

void printArray(int* data, const int length){
    for (int i=0;i<length;cout<<data[i]<<" ",i++);
    cout<<std::endl;
}

void resetArray(int* data, int* original, const int length){
    for (int i=0;i<length;i++){
        data[i]=original[i];
    }
}

void numSwap(int* num_1, int* num2){
    int tmp=*num_1;
    *num_1=*num2;
    *num2=tmp;
}

size_t getPivotIndex(const int *data, const size_t low, const size_t high)
{
    const size_t middle = (low+high)/2;
    if((data[middle]<=data[low] && data[high-1]>=data[low])||(data[middle]>=data[low] && data[high-1]<=data[low])){
        return low;
    }
    else if ((data[low]<=data[middle] && data[high-1]>=data[middle])||(data[low]>=data[middle] && data[high-1]<=data[middle])){
        return middle;
    }
    else{
        return high-1;
    }
}

size_t partition(int* data, const size_t pivot, const size_t low, const size_t high)
{
    numSwap(&data[pivot], &data[high-1]);
    size_t j = low;
    for (size_t i=low;i<=high-1;i++) {
        if (data[i] <= data[high-1]) {
            numSwap(&data[j], &data[i]);
            j++;
        }
    }
    return j-1;
}

void merge(int* data,const int low, const int middle, const int high){
    int arrayA[middle-low+1], arrayB[high-middle];
    for (int i = 0; i < (middle-low+1); i++)
        arrayA[i] = data[low + i];
    for (int j = 0; j < (high-middle); j++)
        arrayB[j] = data[middle + 1 + j];
    int i=0, j=0, k=low;
    while (i < (middle-low+1) && j < (high-middle)) {
        if (arrayA[i] <= arrayB[j]) {
            data[k] = arrayA[i];
            i++;
        } else {
            data[k] = arrayB[j];
            j++;
        }
        k++;
    }
    while (i < (middle-low+1)) {
        data[k] = arrayA[i];
        i++;
        k++;
    }
    while (j < (high-middle)) {
        data[k] = arrayB[j];
        j++;
        k++;
    }
}

void siftDown(int* data, const size_t root_index, const size_t n){
    size_t iLeftChild=2*root_index+1;
    size_t iRightChild=2*root_index+2;
    size_t iSwap=root_index;
    if(iLeftChild >= n){
        return;
    }
    if(data[iLeftChild] > data[root_index]){
        iSwap=iLeftChild;
    }
    if(data[iRightChild] > data[iSwap] && iRightChild<n){
        iSwap=iRightChild;
    }
    if(iSwap != root_index){
        swap(data[root_index],data[iSwap]);
        siftDown(data,iSwap,n);
    }
}

void buildHeap(int* data, const size_t n){
    for(size_t i=(n/2)-1;i!=SIZE_MAX;i--){
        siftDown(data,i,n);
    }
}

void bubbleSort(int* data,const int length){
    for (int i=1;i<length;i++){
        for(int j=0;j<length-i;j++){
            if(data[j]>data[j+1]){
                numSwap(&data[j],&data[j+1]);
            }
        }
    }
}

void quickSort(int* data, const size_t low, const size_t high)
{
    if(low<high){
        size_t pivot = getPivotIndex(data,low,high);
        pivot=partition(data,pivot,low,high);
        quickSort(data,low,pivot);
        quickSort(data,pivot+1,high);
    }
}

void insertionSort(int* data, const int length) {
    int current,j;
    for (int i=1;i<length;i++){
        current=data[i];
        j=i-1;
        while(j>=0 && data[j]>current){
            numSwap(&data[j+1],&data[j]);
            j=j-1;
        }
        data[j+1]=current;
    }
}

void mergeSort(int* data,const int low, const int high){
    if(high<=low){
        return;
    }
    int middle=(low+high)/2;
    mergeSort(data,low,middle);
    mergeSort(data,middle+1,high);
    merge(data,low,middle,high);
}

void heapSort(int* data,const size_t n){
    buildHeap(data,n);
    for(size_t i=1;i<n;i++){
        swap(data[0],data[n-i]);
        siftDown(data,0,n-i);
    }
}

int main(){

    srand(time(NULL));
    int* data=new int[SIZE];
    int* data_copy=new int[SIZE];
    genArray(data,SIZE,-50,50);
    copyArray(data,data_copy,SIZE);
    int c;

    cout<<"List before: ";
    c=26;
    c=c-(strlen("List before: "));
    for(int i=0;i<c;i++){
        cout<<" ";
    }
    printArray(data, SIZE);

    cout<<"List after mergeSort: ";
    mergeSort(data,0,SIZE-1);
    c=26;
    c=c-(strlen("List after mergeSort: "));
    for(int i=0;i<c;i++){
        cout<<" ";
    }
    printArray(data, SIZE);
    resetArray(data, data_copy, SIZE);

    cout<<"List after insertionSort: ";
    insertionSort(data,SIZE);
    c=26;
    c=c-(strlen("List after insertionSort: "));
    for(int i=0;i<c;i++){
        cout<<" ";
    }
    printArray(data, SIZE);
    resetArray(data, data_copy, SIZE);

    bubbleSort(data,SIZE);
    cout<<"List after bubbleSort: ";
    c=26;
    c=c-(strlen("List after bubbleSort: "));
    for(int i=0;i<c;i++){
        cout<<" ";
    }
    printArray(data, SIZE);
    resetArray(data, data_copy, SIZE);

    stable_sort(data,data+SIZE);
    cout<<"List after stableSort: ";
    c=26;
    c=c-(strlen("List after stableSort: "));
    for(int i=0;i<c;i++){
        cout<<" ";
    }
    printArray(data, SIZE);
    resetArray(data, data_copy, SIZE);

    quickSort(data,0,SIZE);
    cout<<"List after quickSort: ";
    c=26;
    c=c-(strlen("List after quickSort: "));
    for(int i=0;i<c;i++){
        cout<<" ";
    }
    printArray(data, SIZE);
    resetArray(data, data_copy, SIZE);

    heapSort(data,SIZE);
    cout<<"List after heapSort: ";
    c=26;
    c=c-(strlen("List after heapSort: "));
    for(int i=0;i<c;i++){
        cout<<" ";
    }
    printArray(data, SIZE);
    resetArray(data, data_copy, SIZE);

    delete[] data;
    delete[] data_copy;
    
    cout<<"\n";
    cout<<"Write Enter to quit..."<<endl;
    cin.ignore(10,'\n');
    cin.get();
    return 0;
}
