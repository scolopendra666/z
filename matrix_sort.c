#include <stdio.h>
#include <stdlib.h>

void printMatrix(int **matrix, int rows, int cols);
void freeMatrix(int **matrix, int rows, int allocationMethod);
int **allocateDynamicMatrixMalloc(int rows, int cols);
int **allocateDynamicMatrixCalloc(int rows, int cols);
int **allocateDynamicMatrixArray(int rows, int cols);

void sortMatrixByRowSums(int **matrix, int rows, int cols);

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
            matrix = allocateDynamicMatrixMalloc(rows, cols);
            break;
        case 2:
            matrix = allocateDynamicMatrixCalloc(rows, cols);
            break;
        case 3:
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

    // Sort matrix by row sums
    sortMatrixByRowSums(matrix, rows, cols);

    // Print the sorted matrix
    printMatrix(matrix, rows, cols);

    // Free allocated memory
    freeMatrix(matrix, rows, choice);

    return 0;
}

void sortMatrixByRowSums(int **matrix, int rows, int cols) {
    // Calculate row sums
    int *rowSums = (int *)malloc(rows * sizeof(int));
    if (rowSums == NULL) {
        printf("n/a");
        exit(1);
    }

    for (int i = 0; i < rows; ++i) {
        rowSums[i] = 0;
        for (int j = 0; j < cols; ++j) {
            rowSums[i] += matrix[i][j];
        }
    }

    // Sort rows based on row sums
    for (int i = 0; i < rows - 1; ++i) {
        for (int j = 0; j < rows - i - 1; ++j) {
            if (rowSums[j] > rowSums[j + 1]) {
                // Swap rows
                int *tempRow = matrix[j];
                matrix[j] = matrix[j + 1];
                matrix[j + 1] = tempRow;

                // Swap row sums
                int tempSum = rowSums[j];
                rowSums[j] = rowSums[j + 1];
                rowSums[j + 1] = tempSum;
            }
        }
    }

    // Free row sums array
    free(rowSums);
}

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

void freeMatrix(int **matrix, int rows, int allocationMethod) {
    switch (allocationMethod) {
        case 1:  // dynamic allocation (malloc)
        case 2:  // dynamic allocation (calloc)

        case 3:  // dynamic allocation (array of pointers)
            for (int i = 0; i < rows; ++i) {
                free(matrix[i]);
            }
            free(matrix);
            break;
        default:
            printf("n/a");
            exit(1);
    }
}

int **allocateDynamicMatrixMalloc(int rows, int cols) {
    int **matrix = (int **)malloc(rows * sizeof(int *));
    if (matrix == NULL) {
        printf("n/a");
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
            freeMatrix(matrix, i, 2);
            exit(1);
        }
    }

    return matrix;
}

int **allocateDynamicMatrixArray(int rows, int cols) {
    int **matrix = (int **)malloc(rows * sizeof(int *));
    if (matrix == NULL) {
        printf("n/a");
        exit(1);
    }

    for (int i = 0; i < rows; ++i) {
        matrix[i] = (int *)malloc(cols * sizeof(int));
        if (matrix[i] == NULL) {
            printf("n/a");
            freeMatrix(matrix, i, 3);
            exit(1);
        }
    }

    return matrix;
}
