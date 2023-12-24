#include <stdio.h>
#include <stdbool.h>

void InputLine(int *m, int *n){
    long long r = 0;
    long long a = 0;
        
    a = getchar();
    while (1){
        if (a == ' ' || a == '\n'){
            m[*n] = r;
            *n += 1;
            r = 0;
        }
        else{
            r = r * 10 + (a - '0');
        }
        if (a == '\n'){
            break;
        }

        a = getchar();
    }
    
}

int InputMatrix(int *m){
    // считываем первую строку
    int n = 0;
    InputLine(m, &n);
    int size = n;
    for (int i = 0; i < size - 1; i++){
        InputLine(m, &n);
    }
    return size;
}

void PrintMatrix(int *m, int size){
    int curr_i = 0;
    int curr_j = 0;
    int left_border = 0;
    int right_border = size - 1;
    int up_border = 0;
    int down_border = size - 1;
    int element_counter = 0;

    int step_side = 0;
    int step_vertical = 0;
    
    while (element_counter < size * size){
        curr_i += step_vertical;
        curr_j += step_side;
        printf("%d ", m[curr_i * size + curr_j]);

        if (curr_i == up_border && curr_j == left_border){
            if (!(curr_i == 0 && curr_j == 0)){
                down_border -= 1;
            }
            step_side = 1;
            step_vertical = 0;
        }
        else if (curr_i == up_border && curr_j == right_border){
            if (curr_i != 0){
                left_border += 1;
            }
            step_side = 0;
            step_vertical = 1;
        }
        else if (curr_i == down_border && curr_j == right_border){
            up_border += 1;
            step_side = -1;
            step_vertical = 0;
        }
        else if (curr_i == down_border && curr_j == left_border){
            right_border -= 1;
            step_side = 0;
            step_vertical = -1;
        }
        element_counter += 1;
    }
}

int main() {
    int m[50];

    int n = 0;
    int size = InputMatrix(m);

    PrintMatrix(m, size);
}
