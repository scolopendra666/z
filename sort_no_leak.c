#include <stdio.h>
#include <stdlib.h>

// Function prototypes
int readArray(int **arr, int *size);
void bubbleSort(int *arr, int size);
void printArray(const int *arr, int size);

int main() {
    int *data;
    int size;

    if (readArray(&data, &size) == 0) {
        bubbleSort(data, size);
        printArray(data, size);
        free(data);  // Освобождаем память после использования
    } else {
        printf("n/a");
    }

    return 0;
}

// Function to read an array from stdin
int readArray(int **arr, int *size) {
    if (scanf("%d", size) != 1) {
        return -1;
    }

    *arr = (int *)malloc(*size * sizeof(int));  // Выделяем память для массива

    if (*arr == NULL) {
        return -1;
    }

    for (int i = 0; i < *size; ++i) {
        if (scanf("%d", &(*arr)[i]) != 1) {
            free(*arr);  // Освобождаем память в случае ошибки ввода элемента массива
            return -1;
        }
    }

    return 0;  // Возвращаем 0 при успешном вводе массива
}

// Function to perform bubble sort on an array
void bubbleSort(int *arr, int size) {
    for (int i = 0; i < size - 1; ++i) {
        for (int j = 0; j < size - i - 1; ++j) {
            if (arr[j] > arr[j + 1]) {
                // Swap arr[j] and arr[j + 1]
                int temp = arr[j];
                arr[j] = arr[j + 1];
                arr[j + 1] = temp;
            }
        }
    }
}

// Function to print an array to stdout
void printArray(const int *arr, int size) {
    for (int i = 0; i < size; ++i) {
        printf("%d ", arr[i]);
    }
}
