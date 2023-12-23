#include <stdio.h>
#include <limits.h>
#include <stdlib.h>

enum Direction
{
    LEFT = 0,
    DOWN = 1,
    RIGHT = 2,
    UP = 3
};

int main()
{
    int mx_size;
    printf("Enter matrix size: ");
    scanf("%d", &mx_size);
    int **mx = (int **)malloc(mx_size * sizeof(int *));
    if (!mx)
    {
        printf("Failed to allocate memory!");
        return -1;
    }
    
    for (int i = 0; i < mx_size; ++i)
    {
        mx[i] = malloc(mx_size);
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
    
    printf("\n");
    enum Direction current_direction = RIGHT;
    int left_border = 0;
    int right_border = mx_size - 1;
    int top_border = 0;
    int bot_border = mx_size - 1;
    int current_border = right_border;
    int row_ind = 0;
    int col_ind = 0;
    while (1)
    {
        if (current_direction == RIGHT)
        {
            if (col_ind <= current_border)
            {
                printf("%d ", mx[row_ind][col_ind]);
                ++col_ind;
            }
            else
            {
                col_ind = right_border;
                current_border = bot_border;
                current_direction = DOWN;
                if (row_ind >= current_border)
                {
                    break;
                }
                
                ++row_ind;
                ++top_border;
            }
        }
        else if (current_direction == DOWN)
        {
            if (row_ind <= current_border)
            {
                printf("%d ", mx[row_ind][col_ind]);
                ++row_ind;
            }
            else
            {
                row_ind = bot_border;
                current_border = left_border;
                current_direction = LEFT;
                if (col_ind <= current_border)
                {
                    break;
                }
                
                --col_ind;
                --right_border;
            }
        }
        else if (current_direction == LEFT)
        {
            if (col_ind >= current_border)
            {
                printf("%d ", mx[row_ind][col_ind]);
                --col_ind;
            }
            else
            {
                col_ind = left_border;
                current_border = top_border;
                current_direction = UP;
                if (row_ind <= current_border)
                {
                    break;
                }
                
                --row_ind;
                --bot_border;
            }
        }
        else
        {
            if (row_ind >= current_border)
            {
                printf("%d ", mx[row_ind][col_ind]);
                --row_ind;
            }
            else
            {
                row_ind = top_border;
                current_border = right_border;
                current_direction = RIGHT;
                if (col_ind >= current_border)
                {
                    break;
                }
                
                ++col_ind;
                ++left_border;
            }
        }
    }
    
    return 0;
}