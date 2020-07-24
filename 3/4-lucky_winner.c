/*******************************************************************************
 * Lucky Winner
 ******************************************************************************/
#include <stdio.h>
#include <stdlib.h>

// N                    Rows                   1<= N <= 1000
// K                    Tokens                1<= K <= 1000 
// 3 Columns

// Sample Input
// 5 3
// 100 -9 -1
// -1 3 2
// -9 2 3
// 2 5 1
// 3 3 4


int arr1 [] = {5, 3};
int arr2 [] = {100, -9, -1};
int arr3 [] = {-1, 3, 2};
int arr4 [] = {-9, 2, 3};
int arr5 [] = {2, 5, 1};
int arr6 [] = {3, 3, 4};

int *arr[] = { (int *)&arr1, (int *)&arr2, (int *)&arr3, (int *)&arr4 ,(int *)&arr5, (int *)&arr6};

/*******************************************************************************
 * Type Structure
 ******************************************************************************/
typedef struct
{
    int val[3];
    int max_sum;
} _Lucky_Type;


/*******************************************************************************
 * Function
 ******************************************************************************/
void Print_Lucky_Type(_Lucky_Type* l_t)
{
    for(int i = 0;i<3;i++)
    {
        printf("val - %i:\t%i\r\n",i,l_t->val[i]);
    }
    printf("max_sum:\t%i\r\n\r\n",l_t->max_sum);
    
}

int Get_Max(int* arr,  int count)
{
    int max = arr[0];
    for(int i = 0;i<count;i++)
    {
        if(arr[i]>max)
        {
            max = arr[i];
        }
    }

    return max;
}

int Get_Max_Sum(int* arr, int count)
{
    int small_index = 0;
    for(int i = 0;i<count;i++)
    {
        if(arr[i]<arr[small_index])
        {
            small_index = i;
        }
    }

    int max_sum = 0;
    for(int i = 0;i<count;i++)
    {
        if (i == small_index)
        {
            continue;
        }/* code */
        max_sum += arr[i];
    }
    
    return max_sum;
}

int Get_Lucky_Winner(int * arr,  int count, int token)
{
    int* index = calloc(count,sizeof(int));
    for(int i = 0;i<count;i++)
    {
        index[i] = 1;
    }
    
    int lucky_winner = 0;
    int max = 0;
    int zero_index = 0;
    for(int i = 0;i<token;i++)
    {
        for(int j = 0;j<count;j++)
        {
            if(arr[j]*index[j]>max)
            {
                max = arr[j]*index[j];
                zero_index = j;
            }
        }
        index[zero_index] = 0;
        lucky_winner += max;
        max = 0;
    }
    
    return lucky_winner;
}

/*******************************************************************************
 * Main
 ******************************************************************************/
int main(int argc, char *argv[])
{
    int N = arr[0][0];
    int K = arr[0][1];
    
    _Lucky_Type* l_type = calloc(N,sizeof(_Lucky_Type));
    for(int i = 0;i<N;i++)
    {
        l_type[i].val[0] = arr[1+i][0];
        l_type[i].val[1] = arr[1+i][1];
        l_type[i].val[2] = arr[1+i][2];
    }
    
    // for(int i = 0;i<N;i++)
    // {
    //     Print_Lucky_Type(l_type+i);
    // }

    int max_sum = 0;
    int *max_sum_arr = calloc(N,sizeof(int));
    for(int i = 0;i<N;i++)
    {
        max_sum =  Get_Max_Sum((l_type+i)->val,3);
        printf("max_sum:\t%i\r\n",max_sum);
        
        l_type[i].max_sum = max_sum;
        max_sum_arr[i] = max_sum;
    }
    
    int lucky_winner = 0;
    lucky_winner = Get_Lucky_Winner(max_sum_arr,N,K);
    printf("%i\r\n",lucky_winner);



    free(max_sum_arr);
    free(l_type);

    return 0;
}