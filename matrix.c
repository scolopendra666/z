#include <stdio.h>
#include <stdlib.h>

#define MAX_SIZE 100

// Function prototypes
void printMatrix(int **matrix, int rows, int cols);
void freeMatrix(int **matrix, int rows, int allocationMethod);

int **allocateStaticMatrix(int rows, int cols);
int **allocateDynamicMatrixMalloc(int rows, int cols);
int **allocateDynamicMatrixCalloc(int rows, int cols);
int **allocateDynamicMatrixArray(int rows, int cols);

int main() {
    int choice;
    int rows, cols;
    int **matrix;

    if (scanf("%d", &choice) != 1) {
        printf("n/a");
        return 1;
    }

    // Read matrix dimensions
    if (scanf("%d %d", &rows, &cols) != 2) {
        printf("n/a");
        return 1;
    }

    // Allocate memory based on user choice
    switch (choice) {
        case 1:
            matrix = allocateStaticMatrix(rows, cols);
            break;
        case 2:
            matrix = allocateDynamicMatrixMalloc(rows, cols);
            break;
        case 3:
            matrix = allocateDynamicMatrixCalloc(rows, cols);
            break;
        case 4:
            matrix = allocateDynamicMatrixArray(rows, cols);
            break;
        default:
            printf("n/a");
            return 1;
    }

    // Read matrix elements
    for (int i = 0; i < rows; ++i) {
        for (int j = 0; j < cols; ++j) {
            if (scanf("%d", &matrix[i][j]) != 1) {
                printf("n/a");
                freeMatrix(matrix, rows, choice);
                return 1;
            }
        }
    }

    // Print the matrix
    printMatrix(matrix, rows, cols);

    // Free allocated memory
    freeMatrix(matrix, rows, choice);

    return 0;
}

// Function to print a matrix
void printMatrix(int **matrix, int rows, int cols) {
    for (int i = 0; i < rows; ++i) {
        for (int j = 0; j < cols; ++j) {
            printf("%d", matrix[i][j]);
            if (j < cols - 1) {
                printf(" ");
            }
        }
        if (i < rows - 1) {
            printf("\n");
        }
    }
}

// Function to free memory allocated for a matrix

void freeMatrix(int **matrix, int rows, int allocationMethod) {
    switch (allocationMethod) {
        case 1:  // static allocation
        case 2:  // dynamic allocation (malloc)
        case 3:  // dynamic allocation (calloc)
            for (int i = 0; i < rows; ++i) {
                free(matrix[i]);
            }
            free(matrix);
            break;
        case 4:  // dynamic allocation (array of pointers)
            free(matrix[0]);
            free(matrix);
            break;
        default:
            printf("n/a");
            exit(1);
    }
}

// Function to allocate a matrix using static allocation
int **allocateStaticMatrix(int rows, int cols) {
    if (rows > MAX_SIZE || cols > MAX_SIZE) {
        printf("n/a");
        exit(1);
    }

    int **matrix = (int **)malloc(rows * sizeof(int *));
    if (matrix == NULL) {
        printf("n/a");
        exit(1);
    }

    for (int i = 0; i < rows; ++i) {
        matrix[i] = (int *)malloc(cols * sizeof(int));
        if (matrix[i] == NULL) {
            printf("n/a");
            freeMatrix(matrix, i, 1);
            exit(1);
        }
    }

    return matrix;
}

// Function to allocate a matrix using dynamic allocation (malloc)
int **allocateDynamicMatrixMalloc(int rows, int cols) {
    int **matrix = (int **)malloc(rows * sizeof(int *));
    if (matrix == NULL) {
        printf("n/a");
        exit(1);
    }

    for (int i = 0; i < rows; ++i) {
        matrix[i] = (int *)malloc(cols * sizeof(int));
        if (matrix[i] == NULL) {
            printf("n/a");
            freeMatrix(matrix, i, 2);
            exit(1);
        }
    }

    return matrix;
}

// Function to allocate a matrix using dynamic allocation (calloc)
int **allocateDynamicMatrixCalloc(int rows, int cols) {
    int **matrix = (int **)calloc(rows, sizeof(int *));
    if (matrix == NULL) {
        printf("n/a");
        exit(1);
    }

    for (int i = 0; i < rows; ++i) {
        matrix[i] = (int *)calloc(cols, sizeof(int));
        if (matrix[i] == NULL) {
            printf("n/a");
            freeMatrix(matrix, i, 3);
            exit(1);
        }
    }

    return matrix;
}

// Function to allocate a matrix using dynamic allocation (array of pointers)
int **allocateDynamicMatrixArray(int rows, int cols) {
    int **matrix = (int **)malloc(rows * sizeof(int *));
    if (matrix == NULL) {
        printf("n/a");
        exit(1);
    }

    matrix[0] = (int *)malloc(rows * cols * sizeof(int));
    if (matrix[0] == NULL) {
        printf("n/a");
        freeMatrix(matrix, 0, 4);
        exit(1);
    }

    for (int i = 1; i < rows; ++i) {
        matrix[i] = matrix[0] + i * cols;
    }

    return matrix;
}