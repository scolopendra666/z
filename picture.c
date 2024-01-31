#include <stdio.h>

#define N 15
#define M 13

void transform(int *buf, int **matr, int n, int m);
void make_picture(int **picture, int n, int m);
void reset_picture(int **picture, int n, int m);

int main() {
    int picture_data[N][M];
    int *picture[N];
    transform(&picture_data[0][0], picture, N, M);

    make_picture(picture, N, M);

    // Print the resulting picture
    for (int i = 0; i < N; i++) {
        for (int j = 0; j < M; j++) {
            printf("%d ", picture[i][j]);
        }
        printf("\n");
    }

    return 0;
}

void make_picture(int **picture, int n, int m) {
    int frame_w[] = {1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1};
    int frame_h[] = {1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1};
    int tree_trunk[] = {7, 7, 7, 7};
    int tree_foliage[] = {3, 3, 3, 3};
    int sun_data[6][5] = {{0, 6, 6, 6, 6}, {0, 0, 6, 6, 6}, {0, 0, 6, 6, 6},
                          {0, 6, 0, 0, 6}, {0, 0, 0, 0, 0}, {0, 0, 0, 0, 0}};

    reset_picture(picture, n, m);

    // Draw the frame_w
    for (int i = 0; i < n; i++) {
        for (int j = 0; j < m; j++) {
            if (i < 1 || i >= n - 1 || j < 1 || j >= m - 1) {
                picture[i][j] = frame_w[j];
            }
        }
    }

    // Draw the tree_foliage
    for (int i = 1; i < 6; i++) {
        for (int j = 6; j < 10; j++) {
            picture[i][j] = tree_foliage[j - 6];
        }
    }

    // Draw the tree_trunk
    for (int i = 6; i < 10; i++) {
        for (int j = 10; j < 14; j++) {
            picture[i][j] = tree_trunk[j - 10];
        }
    }

    // Draw the sun_data
    for (int i = 1; i < 7; i++) {
        for (int j = 1; j < 6; j++) {
            picture[i][j] = sun_data[i - 1][j - 1];
        }
    }
}

void reset_picture(int **picture, int n, int m) {
    for (int i = 0; i < n; i++) {
        for (int j = 0; j < m; j++) {
            picture[i][j] = 0;
        }
    }
}

void transform(int *buf, int **matr, int n, int m) {
    for (int i = 0; i < n; i++) {
        matr[i] = buf + i * m;
    }
}
