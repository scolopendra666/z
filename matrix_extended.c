#include <stdio.h>
#include <stdlib.h>

#define MAX_SIZE 100

// Function prototypes
void printMatrix(int **matrix, int rows, int cols);
void freeMatrix(int **matrix, int rows, int allocationMethod);
void calculateRowMaxAndColMin(int **matrix, int rows, int cols);
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
    calculateRowMaxAndColMin(matrix, rows, cols);
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

void calculateRowMaxAndColMin(int **matrix, int rows, int cols) {
    int *maxRow = (int *)malloc(rows * sizeof(int));

    if (maxRow == NULL) {
        printf("n/a");
        freeMatrix(matrix, rows, 2);
        exit(1);
    }

    int *colMin = (int *)malloc(cols * sizeof(int));

    if (colMin == NULL) {
        printf("n/a");
        free(maxRow);
        freeMatrix(matrix, rows, 2);
        exit(1);
    }

    for (int i = 0; i < rows; i++) {
        int max = matrix[i][0];
        for (int j = 1; j < cols; j++) {
            if (matrix[i][j] > max) {
                max = matrix[i][j];
            }
        }
        maxRow[i] = max;
    }
    for (int j = 0; j < rows; j++) {
        int min = matrix[0][j];
        for (int i = 1; i < cols; i++) {
            if (matrix[i][j] < min) {
                min = matrix[i][j];
            }
        }
        colMin[j] = min;
    }
    printf("\n");
    for (int i = 0; i < rows; ++i) {
        printf("%d ", maxRow[i]);
    }
    printf("\n");

    // Print column minima
    for (int j = 0; j < cols; ++j) {
        printf("%d ", colMin[j]);
    }

    // Free allocated memory
    free(maxRow);
    free(colMin);
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
            printf("Invalid allocation method\n");
            exit(1);
    }
}

// Function to allocate a matrix using static allocation
int **allocateStaticMatrix(int rows, int cols) {
    if (rows > MAX_SIZE || cols > MAX_SIZE) {
        printf("n/a\n");
        exit(1);
    }

    int **matrix = (int **)malloc(rows * sizeof(int *));
    if (matrix == NULL) {
        printf("n/a\n");
        exit(1);
    }

    for (int i = 0; i < rows; ++i) {
        matrix[i] = (int *)malloc(cols * sizeof(int));
        if (matrix[i] == NULL) {
            printf("n/a\n");
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
        printf("n/a\n");
        exit(1);
    }

    for (int i = 0; i < rows; ++i) {
        matrix[i] = (int *)malloc(cols * sizeof(int));
        if (matrix[i] == NULL) {
            printf("n/a\n");
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
        printf("n/a\n");
        exit(1);
    }

    for (int i = 0; i < rows; ++i) {
        matrix[i] = (int *)calloc(cols, sizeof(int));
        if (matrix[i] == NULL) {
            printf("n/a\n");
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
        printf("n/a\n");
        exit(1);
    }

    matrix[0] = (int *)malloc(rows * cols * sizeof(int));
    if (matrix[0] == NULL) {
        printf("n/a\n");
        freeMatrix(matrix, 0, 4);
        exit(1);
    }

    for (int i = 1; i < rows; ++i) {
        matrix[i] = matrix[0] + i * cols;
    }

    return matrix;
}
