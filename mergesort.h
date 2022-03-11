#ifndef MERGESORT_H_INCLUDED
#define MERGESORT_H_INCLUDED

const int MAX_ARR_SIZE = 1e6;
long long merge_arr[MAX_ARR_SIZE];

void call_mergesort(long long arr[], int left, int right) {
    if (left == right)
        return;

    int mid = (left + right) >> 1;
    call_mergesort(arr, left, mid);
    call_mergesort(arr, mid + 1, right);

    int i = left, j = mid + 1;
    int cur = 0;

    while (i <= mid || j <= right) {
        // no element left on the left
        if (i > mid)
            merge_arr[cur++] = arr[j++];
        // no element left on the right
        else if (j > right)
            merge_arr[cur++] = arr[i++];
        else if (arr[i] < arr[j])
            merge_arr[cur++] = arr[i++];
        else
            merge_arr[cur++] = arr[j++];
    }

    for (int i = 0; i < cur; ++i)
        arr[left + i] = merge_arr[i];
}

void mergesort(long long arr[], int n) {
    call_mergesort(arr, 0, n - 1);
}

#endif // MERGESORT_H_INCLUDED


