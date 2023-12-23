#include <stdio.h>
#include <limits.h>
#include <stdlib.h>

enum Consts
{
    MAX_MX_SIZE = 8
};

int main()
{
    int mx_size;
    printf("Enter matrix size: ");
    scanf("%d", &mx_size);
    int **mx = (int **)malloc(sizeof(int *) * mx_size);
    if (!mx)
    {
        printf("Failed to allocate memory!");
        return -1;
    }
    
    for (int i = 0; i < mx_size; ++i)
    {
        mx[i] = (int *)malloc(sizeof(int) * mx_size);
        if (!mx[i])
        {
            printf("Failed to allocate memory!");
            return -1;
        }
        
        for (int j = 0; j < mx_size; ++j)
        {
            scanf("%d", &mx[i][j]);
        }
    }
    
    int col_min_num = -1;
    int col_max_num = -1;
    int min_sum = INT_MAX;
    int max_sum = INT_MIN;
    for (int i = 0; i < mx_size; ++i)
    {
        int sum = 0;
        for (int j = 0; j < mx_size; ++j)
        {
            sum += mx[j][i];
        }
        
        if (sum > max_sum)
        {
            max_sum = sum;
            col_max_num = i;
        }
        if (sum < min_sum)
        {
            min_sum = sum;
            col_min_num = i;
        }
    }
    
    for (int i = 0; i < mx_size; ++i)
    {
        int temp = mx[i][col_min_num];
        mx[i][col_min_num] = mx[i][col_max_num];
        mx[i][col_max_num] = temp;
    }
    
    printf("\n");
    for (int i = 0; i < mx_size; ++i)
    {
        for (int j = 0; j < mx_size; ++j)
        {
            printf("%d ", mx[i][j]);
        }
        
        printf("\n");
    }

    return 0;
}