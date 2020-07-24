/*******************************************************************************
 * Item Stock
 ******************************************************************************/
#include <stdio.h> 
#include <stdlib.h>

//  N-1        Item     1 ≤ N ≤ 100,000
//  M           Stock   1 ≤ M ≤ 1,000,000,000

// NOTE Sample input

// Input N M
//  N 5
//  M  15

// 5 15                                         
// 1 1 2                                        
// 2 1 3 1                                     
// 1 2 1                                        
// 2 4 3 1                                      

int arr1 [] = {5,15};
int arr2 [] = {1,1,2};
int arr3 [] = {2,1,3,1};
int arr4 [] = {1,2,1};
int arr5 [] = {2,4,3,1};

int *arr[] = { (int *)&arr1, (int *)&arr2, (int *)&arr3, (int *)&arr4 ,(int *)&arr5};
/*******************************************************************************
 * Type Structure
 ******************************************************************************/
typedef enum 
{
    DYNAMIC = 1,
    FIXED = 2
}Stock_Type;

char *stock_type[] = { "Dynamic", "Fixed"};

int _Index = 1;
typedef struct
{
    int index;
    int type;
    int qty;
    int stock;
    int parent;

} Tree_Type;


/*******************************************************************************
 * Function
 ******************************************************************************/
void Tree_Init(Tree_Type* t, int stock)
{
    if(t == NULL)
    {
        t = calloc(0,sizeof(Tree_Type));
    }

    t->index  = _Index;
    _Index ++;
    t->type = FIXED;
    t->qty = 0;
    t->stock = stock;
    t->parent = 0;
}

void Print_Tree(Tree_Type* t)
{
    printf("---\r\n");
    
    printf( "index\t%i\r\n",t->index);
    printf( "type\t%s\r\n", stock_type[t->type-1]);
    printf( "qty\t%i\r\n",t->qty);
    printf( "stock\t%i\r\n",t->stock);
    printf( "parent\t%i\r\n",t->parent);
}

int Get_Total_Qty(Tree_Type *t, int index)
{
    int total_qty = t[index].stock;
    
    int qty_index  = index;
    while (t[qty_index].parent !=0 )
    {
        total_qty *= t[qty_index].qty;
        qty_index = t[qty_index].parent-1;
    }
    

    return total_qty;
}

void Change_Tree(Tree_Type* t, int index)
{
    Stock_Type stock_type = t[index].type;
    int parent = t[index].parent -1;

    switch (stock_type)
    {
        case DYNAMIC:
            t[index].stock = t[parent].stock / t[index].qty;
            
            // printf("stock - %i\r\n",t[index].stock);
            
            break;
        case FIXED:
            if (t[index].parent  != 0)
            {
                // Get Total Qty to Change Item 1's Stock
                int total_qty =  Get_Total_Qty(t,index);
                // printf("total qty: %i\r\n",total_qty);
                
                t[0].stock -=  total_qty* t[index].stock; 
                
                //  Fix Dynamic Item's Stock
                for(int i = 1;i<index;i++)
                {
                    if (t[i].type == DYNAMIC)
                    {
                        Change_Tree(t,i);
                    }                        
                }
                
            }
            break;
    }
}

void Print_Answer(Tree_Type* t, int count)
{
    printf("---\r\n");
    
    for(int i = 0;i<count;i++)
    {
        printf("%i\r\n",t[i].stock);
    }
}

/*******************************************************************************
 * Main
 ******************************************************************************/

int main(int argc, char *argv[])
{
    // n = 5
    // m = 15
    int n = arr[0][0];
    int m = arr[0][1];

    Tree_Type* tree_node = calloc(n,sizeof(Tree_Type));
    Tree_Init(tree_node, m);

 // NOTE Debug
    n = 5;

    for(int i = 1;i<n;i++)
    {
        tree_node[i].index =  _Index;
        
        Stock_Type stock_type = arr[i][0];

        tree_node[i].type = stock_type;
        tree_node[i].parent = arr[i][1];
        tree_node[i].qty = arr[i][2];

        switch(stock_type)
        {
            case DYNAMIC:
                tree_node[i].stock = -1;
                break;
            case FIXED:
                tree_node[i].stock = arr[i][3];
                break;
        }

        Change_Tree(tree_node , i);


        _Index ++;
    }
    



    for(int i = 0;i<n;i++)
    {
        Print_Tree((Tree_Type*)(tree_node+i));
    }

    Print_Answer(tree_node,n);

    // Sample output
    // 6
    // 3
    // 1
    // 3
    // 1

    free(tree_node);
    
    return 0;
}