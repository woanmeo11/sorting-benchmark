#ifndef QUICKSORT_H_INCLUDED
#define QUICKSORT_H_INCLUDED

#include <algorithm>
#include "rewritten_random.h"

using namespace std;

void call_quicksort(long long arr[], int L, int H) {
    int i = L, j = H;
    int pivot = arr[random(L, H)];

    do {
        while (arr[i] < pivot)
            ++i;
        while (arr[j] > pivot)
            --j;
        if (i <= j) {
            swap(arr[i], arr[j]);
            ++i;
            --j;
        }
    }
    while (i <= j);

    if (L < j)
        call_quicksort(arr, L, j);
    if (i < H)
        call_quicksort(arr, i, H);
}

void quicksort(long long arr[], int n) {
    call_quicksort(arr, 0, n - 1);
}

#endif // QUICKSORT_H_INCLUDED
