#include <stdio.h>

int main() {
    const int Max_Size = 8;
    int matrix[Max_Size][Max_Size];
    int arr[Max_Size * Max_Size];
    int size;
    int n;

    printf("Введите размерность матрицы: ");
    scanf("%d", &size);

    while (size <= 0 || size > 8) {
        printf("Размерность должна быть в пределах от 1 до 8\n");
        printf("Введите размерность матрицы: ");
        scanf("%d", &size);
    }

    printf("Введите элементы матрицы:\n");
    for (int i = 0; i < size; i++) {
        for (int j = 0; j < size; j++) {
            scanf("%d", &matrix[i][j]);
        }
    }

    printf("Введите шаг для сдвига: ");
    scanf("%d", &n);

    printf("Исходная матрица:\n");
    for (int i = 0; i < size; i++) {
        for (int j = 0; j < size; j++) {
            printf("%d ", matrix[i][j]);
        }
        printf("\n");
    }

    int q = 0;
    int top = 0, bottom = size - 1, left = 0, right = size - 1;
    int dir = 1;
    while (top <= bottom && left <= right) {
        if (dir == 1) {
            for (int i = left; i <= right; i++) {
                arr[q] = matrix[top][i];
                q++;
            }
            top++;
            dir = 2;
        } else if (dir == 2) {
            for (int i = top; i <= bottom; i++) {
                arr[q] = matrix[i][right];
                q++;
            }
            right--;
            dir = 3;
        } else if (dir == 3) {
            for (int i = right; i >= left; i--) {
                arr[q] = matrix[bottom][i];
                q++;
            }
            bottom--;
            dir = 4;
        } else if (dir == 4) {
            for (int i = bottom; i >= top; i--) {
                arr[q] = matrix[i][left];
                q++;
            }
            left++;
            dir = 1;
        }
    }

    int Arr_Size = size * size;
    int N_Opt = n % Arr_Size;
    for (int k = 0; k < N_Opt; k++) {
        int last = arr[Arr_Size - 1];
        for (int i = Arr_Size - 1; i > 0; i--) {
            arr[i] = arr[i - 1];
        }
        arr[0] = last;
    }

    q = 0;
    top = 0, bottom = size - 1, left = 0, right = size - 1;
    dir = 1;
    while (top <= bottom && left <= right) {
        if (dir == 1) {
            for (int i = left; i <= right; i++) {
                matrix[top][i] = arr[q];
                q++;
            }
            top++;
            dir = 2;
        } else if (dir == 2) {
            for (int i = top; i <= bottom; i++) {
                matrix[i][right] = arr[q];
                q++;
            }
            right--;
            dir = 3;
        } else if (dir == 3) {
            for (int i = right; i >= left; i--) {
                matrix[bottom][i] = arr[q];
                q++;
            }
            bottom--;
            dir = 4;
        } else if (dir == 4) {
            for (int i = bottom; i >= top; i--) {
                matrix[i][left] = arr[q];
                q++;
            }
            left++;
            dir = 1;
        }
    }

    printf("Преобразованная матрица:\n");
    for (int i = 0; i < size; i++) {
        for (int j = 0; j < size; j++) {
            printf("%d ", matrix[i][j]);
        }
        printf("\n");
    }
    return 0;
}

