// Tema: Merge sort
// Autor: Vladislav Novak

#include <iostream>
#include <iomanip>
#include <cstring>
#include <algorithm>

//------------------------------------------------------------------------------
// Merge
//------------------------------------------------------------------------------

void merge(int *output, const int *input, const size_t low, const size_t middle, const size_t high)
{
    size_t in1 = low;
    size_t in2 = middle;
    size_t out = low;

    while (in1 < middle && in2 < high) {
        if (input[in1] <= input[in2]) { // stabilne triedenie
            output[out] = input[in1];
            ++ in1;
        }
        else {
            output[out] = input[in2];
            ++ in2;
        }
        ++ out;
    }
    while (in1 < middle) {
        output[out] = input[in1];
        ++ in1;
        ++ out;
    }
    while (in2 < high) {
        output[out] = input[in2];
        ++ in2;
        ++ out;
    }
}

//------------------------------------------------------------------------------
// Merge sort (top down)
//------------------------------------------------------------------------------

// Pri volani funkcie musi byt obsah poli 'dataA' a 'dataB' rovnaky!
void mergeSortTopDown(int *dataA, int *dataB, const size_t low, const size_t high)
{
    if (low + 1 >= high) {
        return;
    }

    const size_t middle = (high + low) / 2;

    mergeSortTopDown(dataB, dataA, low, middle); // dataA -> dataB
    mergeSortTopDown(dataB, dataA, middle, high);

    merge(dataA, dataB, low, middle, high); // dataB -> dataA
}

// Tato funkcia sluzi ako rozhranie pre zakrytie detailov rekurzivnej implementacie merge sort-u pri volani z main-u
void mergeSortTopDown(int *array, const size_t length)
{
    int* tmpArray = new int[length];
    std::memcpy(tmpArray, array, length * sizeof(int));
    mergeSortTopDown(array, tmpArray, 0, length);
    delete[] tmpArray;
}

//------------------------------------------------------------------------------
// Merge sort (bottom up)
//------------------------------------------------------------------------------

void swapPointers(int **a, int **b)
{
    int *c = (*a);
    (*a) = (*b);
    (*b) = c;
}

void mergeSortBottomUp(int *data, const size_t length)
{
    int* tmpData = new int [length];

    int * input = data;
    int * output = tmpData;
    bool needCopyToOrigin = false;
    for (size_t step = 1; step < length; step *= 2) {
        for (size_t i = 0; i < length; i += 2 * step) {
            size_t low = i;
            size_t middle = std::min(i + step, length);
            size_t high = std::min(i + 2 * step, length);
            merge(output, input, low, middle, high);
        }
        swapPointers(&input, &output);
        needCopyToOrigin = ! needCopyToOrigin;
    }

    if (needCopyToOrigin) {
        std::memcpy(data, tmpData, length * sizeof(int));
    }

    delete[] tmpData;
}

//-------------------------------------------------------------------------------------------------
// TESTOVANIE
//-------------------------------------------------------------------------------------------------

void println(const char *label, const int *data, const size_t length)
{
    std::cout << label << ": ";
    for(size_t i = 0; i < length; ++ i) {
        std::cout << std::setw(3) << data[i] << ' ';
    }
    std::cout << std::endl;
}

#define LENGTH(array) (sizeof(array)/sizeof((array)[0]))

int main()
{
    int in[]  = { 10, 20,  2,  4,  4,  8,  1,  4,  7,  9, 20,   30 };
    int out[] = {  0, -1, -2, -3, -4, -5, -6, -7, -8, -9, -10, -11 };
    merge(out, in, 2, 6, 10);
    println("merge in ", in, LENGTH(in));
    println("merge out", out, LENGTH(out));

    int dataTopDown[] = { 5, 3, 2, 1};
    mergeSortTopDown(dataTopDown, LENGTH(dataTopDown));
    println("merge sort (top down) ", dataTopDown, LENGTH(dataTopDown));

    int dataBottomUp[] = { 5, 3, 2, 1};
    mergeSortTopDown(dataBottomUp, LENGTH(dataBottomUp));
    println("merge sort (bottom up)", dataBottomUp, LENGTH(dataBottomUp));

    return 0;
}
