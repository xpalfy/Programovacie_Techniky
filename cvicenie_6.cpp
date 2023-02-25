// Tema: Heap sort
// Autor: Pavol Marak

#include <iostream>
#include <cstdlib>
#include <ctime>

using namespace std;

// Funkcia na vypis pola
void printArray(const int *data, const size_t n) {
    for (int i = 0; i < n; i++) {
        std::cout << data[i] << " ";
    }
    std::cout << std::endl;
}

// Funkcia na vygenerovanie prvkov pola v rozsahu <hmin,hmax>
void genArray(int *data, const size_t n, const size_t hmin, const size_t hmax) {
    for (size_t i = 0; i < n; i++) {
        data[i]=rand()%(hmax-hmin+1)+hmin;
    }
}

// Funkcia na vymenu hodnot na danych adresach.
void swap(int *a, int *b) {
    int tmp = *a;
    *a = *b;
    *b = tmp;
}

// Operacia siftDown
// Predstavuje "plavanie" s vrcholom smerom nadol
// pokial nie je splnena vlastnost Max-heap resp. Min-heap.
void siftDown(int *data, const size_t root_index, const size_t n) {
    size_t iSwap = root_index;
    size_t iLeftChild = root_index * 2 + 1;
    size_t iRightChild = root_index * 2 + 2;

    // neexistuje lavy potomok?
    if (iLeftChild >= n) {
        return;
    }
    // je lavy potomok vacsi ako data[root_index]?
    if (data[iLeftChild] > data[root_index]) {
        iSwap = iLeftChild;
    }
    // existuje pravy potomok a je vacsi ako data[iSwap]?
    if (iRightChild < n && data[iRightChild] > data[iSwap]) {
        iSwap = iRightChild;
    }
    // "plavanie" smerom nadol
    if (iSwap != root_index) {
        swap(&data[root_index], &data[iSwap]);
        siftDown(data, iSwap, n);
    }
}

// Funkcia na vytvorenie Max-Heapu pomocou operacie siftDown.
void buildHeapSiftDown(int *data, const size_t n) {
    for (size_t i = (n / 2) - 1; i != SIZE_MAX; i--) {
        siftDown(data, i, n);
    }
}

// Operacia siftUp
// Predstavuje "plavanie" s vrcholom smerom nahor pokial nie je
// splnena vlastnost Max-Heap resp. Min-heap.
void siftUp(int *data, const size_t i) {
    size_t iParent;
    if (i > 0) {
        iParent = (i - 1) / 2;
        if (data[iParent] < data[i]) {
            swap(&data[iParent], &data[i]);
            siftUp(data, iParent);
        }
    }
}

// Funkcia na vytvorenie Max-Heapu pomocou operacie siftUp.
void buildHeapSiftUp(int *data, const size_t n) {
    for (size_t i = 1; i < n; i++) {
        siftUp(data, i);
    }
}

// Funkcia, ktora vykona algoritmus Heap sort (triedime vzostupne)
void heapSort(int *data, const size_t n) {
    // 1. Vytvorime z pola Max-Heap
    buildHeapSiftDown(data, n);
    // alebo buildHeapSiftUp(data, n);

    // 2. Triedenie
    for (size_t i = 1; i < n; i++) {
        // 2a. Extrakcia maxima
        swap(&data[0], &data[n - i]);
        // 2b. Rekonstrukcia Max-Heapu
        siftDown(data, 0, n - i);
        // alebo buildHeapSiftUp(data, n - i);
    }
}

// testovanie
int main() {
    srand(time(NULL));
    //int data[] = {51, 3, 14, 9, 3, 0, 0, 24, 1};
    int data[20];
    size_t n = sizeof(data) / sizeof(data[0]);
    genArray(data,n,-20,20);
    printArray(data, n);
    heapSort(data, n);
    printArray(data, n);
    return 0;
}

