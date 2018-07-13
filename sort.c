#include <stdio.h>

void quick_sort(int *a, int left, int right) {
    if (left >= right) {
        return;
    }


    int i = left;
    int j = right;
    int key = a[left];

    while (i < j) {
        while(i < j && key <= a[j]) {
            j--;
        }
        a[i] = a[j];

        while (i < j && key >= a[i]) {
            i++;
        }
        a[j] = a[i];
    }

    a[i] = key;
    quick_sort(a, left, i - 1);
    quick_sort(a, i + 1, right);
}

void bubble_sort(int *a, int len) {
    int done = len;

    for (int i = 0; i < done; done--) {
        for (int j = 0; j < done; j++) {
            if (a[j] > a[j+1]) {
                int prev = a[j];
                a[j] = a[j+1];
                a[j+1] = prev;
            }
        }
    }
}

void insert_sort(int *a, int len) {
    for (int i = 0; i < len; i++) {
        for (int j = 0; j < i; j++) {
            if (a[j] > a[i]) {
                int tmp = a[j];
                a[j] = a[i];
                a[i] = tmp;
            }
        }
    }
}

void merge(int *a, int *tmp, int left, int middle, int right) {
    int i = left, j = middle + 1, k = left;
    while (i != middle + 1 && j != right + 1) {
        if (a[i] < a[j]) {
            tmp[k++] = a[i++];
        }
        if (a[i] > a[j]) {
            tmp[k++] = a[j++];
        }
    }
    while (i != middle + 1) {
        tmp[k++] = a[i++];
    }
    while (j != right + 1) {
        tmp[k++] = a[j++];
    }
    for (i = left; i <= right; i++) {
        a[i] = tmp[i];
    }
}

void merge_sort(int *a, int *tmp, int left, int right) {
    if (left >= right) {
        return;
    }
    int middle = (right + left)/2;
    merge_sort(a, tmp, left, middle);
    merge_sort(a, tmp, middle + 1, right);
    merge(a, tmp, left, middle, right);
}

int main() {
    int a[] = {10, 5, 99, 29, 95, 1, 959, 194, 1000, 3945, 100, 80, 23};
    int len = sizeof(a)/sizeof(int);

    for (int i = 0; i < len; i++) {
        printf("index: %d, value: %d\n", i, a[i]);
    }

    printf("after algorithm=======\n");

//    quick_sort(a, 0, len - 1);
//    bubble_sort(a, len);
//    insert_sort(a, len);

    int b[13];
    merge_sort(a, b, 0, len - 1);
    for (int i = 0; i < len; i++) {
        printf("index: %d, value: %d\n", i, a[i]);
    }

    return 0;
}