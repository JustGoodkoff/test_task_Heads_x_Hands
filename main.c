#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h.>


struct two_dim_arr {
    int **arr;
    int len;
    int *arr_of_lengths;
};

void swap_items(int *a, int *b) {
    int temp = *a;
    *a = *b;
    *b = temp;
}

int partition(int *data, int length, int order) {
    int pivot = data[length / 2];
    int i = 0;
    int j = length - 1;
    while (i <= j) {
        while (((data[i] < pivot) - order) && data[i] != pivot) {
            ++i;
        }
        while (((data[j] > pivot) - order) && data[j] != pivot) {
            --j;
        }
        if (i >= j) {
            break;
        }
        swap_items(&data[i++], &data[j--]);
    }
    return i;
}

void quicksort(int *data, int length, int order) {
    if (length > 1) {
        int p = partition(data, length, order);
        quicksort(data, p, order);
        quicksort(&data[p], length - p, order);
    }
}

bool is_len_exist(const int *arr_of_len, int len, int new_len) {
    for (int i = 0; i < len; ++i) {
        if (arr_of_len[i] == new_len) {
            return true;
        }
    }
    return false;
}

struct two_dim_arr test_task(int n) {
    int **two_dimensional_array = (int **) malloc(n * sizeof(int *));
    struct two_dim_arr twoDimArr;
    int *arr_of_lengths = (int *) calloc(n, sizeof(int));
    for (int i = 0; i < n; ++i) {
        int len = rand() % (n + 100) + 1;
        while (is_len_exist(arr_of_lengths, n, len)) {
            len = rand() % (n + 100) + 1;
        }
        arr_of_lengths[i] = len;
        int *arr = (int *) malloc(len * sizeof(int));
        for (int j = 0; j < len; ++j) {
            arr[j] = rand();
        }
        quicksort(arr, len, i % 2);
        two_dimensional_array[i] = arr;;
    }
    twoDimArr.arr = two_dimensional_array;
    twoDimArr.len = n;
    twoDimArr.arr_of_lengths = arr_of_lengths;
    return twoDimArr;
}

void free_two_dim_arr(struct two_dim_arr tda) {
    for (int i = 0; i < tda.len; ++i) {
        free(tda.arr[i]);
    }
    free(tda.arr);
    free(tda.arr_of_lengths);
}

int main() {
    struct two_dim_arr tda = test_task(6);
    for (int i = 0; i < tda.len; ++i) {
        for (int j = 0; j < tda.arr_of_lengths[i]; ++j) {
            printf("%i ", tda.arr[i][j]);
        }
        printf("\n");
    }
    free_two_dim_arr(tda);
    return 0;
}
