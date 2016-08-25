/* 
---------------------------------------------------------------------------------------------------------
Solution to the 2nd Project of Advanced Data Structures I9600
City College of New York, CUNY 

AUTHOR : ANKAN KUMAR GIRI

Email : agiri000@citymail.cuny.edu / ankangiri@gmail.com
---------------------------------------------------------------------------------------------------------
*/
#include <stdlib.h>
#include <stdio.h>
#include <iostream>
using namespace std;
#define MINUS_INFINITY -9999999
class rect_list_t 
{
    public:
        rect_list_t  *next;
        int x_min,x_max,y_min,y_max;
};
class YSegmentTree
{
    public:
        int key;
        YSegmentTree *left;
        YSegmentTree *right;
        rect_list_t  *rectangle_list;
};
class seg_tree_2d_t
{
    public:
        int key;
        seg_tree_2d_t *left;
        seg_tree_2d_t *right;
        YSegmentTree *y_tree;
        rect_list_t  *rectangle_list;
};
class Stack_XItem
{
    public:
        seg_tree_2d_t  *node1;
        seg_tree_2d_t  *node2;
        int number;
};
class Stack_YItem
{
    public:
        YSegmentTree  *node1;
        YSegmentTree  *node2;
        int number;
};
class Stack
{
    public:
        Stack_XItem *tree;
        Stack *next;
};
class YStack
{
    public:
        Stack_YItem *tree;
        YStack *next;
};
Stack *create_stack()
{
    Stack *stack = new Stack();
    stack->next = NULL;
    return stack;
}
void push(Stack_XItem *&node, Stack *&stack)
{
    Stack *tmp_stack = new Stack();
    tmp_stack->tree = node;
    tmp_stack->next = stack->next;
    stack->next = tmp_stack;
}
bool stack_empty(Stack *&stack)
{
    if (stack->next == NULL)
    {
        return true;
    }
    return false;
}
Stack_XItem *pop(Stack *&stack)
{
    Stack *tmp_stack = stack->next;
    Stack_XItem *node = tmp_stack->tree;
    stack->next = tmp_stack->next;
    delete tmp_stack;
    return node;
}
void remove_stack(Stack *&stack)
{
    Stack *temp_stack;
    do
    {
        temp_stack = stack->next;
        delete stack;
        stack = temp_stack;
    } while (temp_stack != NULL);
}
YStack *create_ystack()
{
    YStack *stack = new YStack();
    stack->next = NULL;
    return stack;
}
void push(Stack_YItem *&node, YStack *&stack)
{
    YStack *tmp_stack = new YStack();
    tmp_stack->tree = node;
    tmp_stack->next = stack->next;
    stack->next = tmp_stack;
}
bool stack_empty(YStack *&stack)
{
    if (stack->next == NULL)
    {
        return true;
    }
    return false;
}
Stack_YItem *pop(YStack *&stack)
{
    YStack *tmp_stack = stack->next;
    Stack_YItem *node = tmp_stack->tree;
    stack->next = tmp_stack->next;
    delete tmp_stack;
    return node;
}
void remove_ystack(YStack *&stack)
{
    YStack *temp_stack;
    do
    {
        temp_stack = stack->next;
        delete stack;
        stack = temp_stack;
    } while (temp_stack != NULL);
}
void quickSort(int arr[], int left, int right)
{
      int i = left;
      int j = right;
      int tmp;
      int pivot = arr[(left + right) / 2];
      while (i <= j)
      {
            while (arr[i] < pivot)
                  i++;
            while (arr[j] > pivot)
                  j--;
            if (i <= j)
            {
                  tmp = arr[i];
                  arr[i] = arr[j];
                  arr[j] = tmp;
                  i++;
                  j--;
            }
      };
      if (left < j)
            quickSort(arr, left, j);
      if (i < right)
            quickSort(arr, i, right);
}
void empty_tree(seg_tree_2d_t *&stree)
{
    stree->rectangle_list  = NULL;
    if( stree->right != NULL )
    {
        empty_tree( stree->left );
        empty_tree( stree->right );
    }
}
void check_tree(seg_tree_2d_t *&tr, int depth, int lower, int upper )
{
    if( tr->left == NULL )
    {
        cout << "Tree Empty\n";
        return;
    }
    if( tr->key < lower || tr->key >= upper )
        cout <<"Wrong Key Order \n";
    if( tr->right == NULL )
    {
        if( *( (int *) tr->left) == 42 )
        {
            cout << tr->key<<"("<< depth <<")";
        }
        else
            cout <<"Wrong Object \n";
    }
    else
    {
        check_tree(tr->left, depth+1, lower, tr->key );
        check_tree(tr->right, depth+1, tr->key, upper );
    }
}
void empty_tree(YSegmentTree *&stree)
{
    stree->rectangle_list  = NULL;
    if( stree->right != NULL )
    {
        empty_tree( stree->left );
        empty_tree( stree->right );
    }
}
void check_tree(YSegmentTree *&tr, int depth, int lower, int upper )
{
    if( tr->left == NULL )
    {
        cout << "Tree Empty\n";
        return;
    }
    if( tr->key < lower || tr->key >= upper )
        cout << "Wrong Key Order \n";
    if( tr->right == NULL )
    {
        if( *( (int *) tr->left) == 42 )
        {
            cout << tr->key<<"("<< depth <<")";
        }
        else
            cout <<"Wrong Object \n";
    }
    else
    {
        check_tree(tr->left, depth+1, lower, tr->key );
        check_tree(tr->right, depth+1, tr->key, upper );
    }
}
void attach_xintv_rectangle(seg_tree_2d_t *&tree_node, int a, int b,int c, int d)
{
    rect_list_t  *new_node = new rect_list_t ();
    new_node->next = tree_node->rectangle_list;
    new_node->x_min = a;
    new_node->x_max = b;
    new_node->y_min = c;
    new_node->y_max = d;
    tree_node->rectangle_list = new_node;
}
void attach_yintv_rectangle(YSegmentTree *&tree_node, int a, int b,int c, int d)
{
    rect_list_t  *new_node = new rect_list_t ();
    new_node->next = tree_node->rectangle_list;
    new_node->x_min = a;
    new_node->x_max = b;
    new_node->y_min = c;
    new_node->y_max = d;
    tree_node->rectangle_list = new_node;
}
void insert_rectangle_xinterval(seg_tree_2d_t *&tree, int a, int b, int c, int d)
{
    if(tree->left == NULL)
        return;
    else
    {
        seg_tree_2d_t *current_node = tree;
        seg_tree_2d_t *right_path = new seg_tree_2d_t();
        seg_tree_2d_t *left_path = new seg_tree_2d_t();
        while( current_node->right != NULL )
        {
            if( b < current_node->key )
                current_node = current_node->left;
            else if( current_node->key < a)
                current_node = current_node->right;
            else if( a < current_node->key && current_node->key < b )
            {
                right_path = current_node->right;
                left_path  = current_node->left;
                break;
            }
            else if( a == current_node->key )
            {
                right_path = current_node->right;
                break;
            }
            else
            {
                left_path  = current_node->left; /* no right */
                break;
            }
        }
        if( left_path != NULL )
        {
            while( left_path->right != NULL )
            {
                if( a < left_path->key )
                {
                    attach_xintv_rectangle(left_path->right, a,b,c,d);
                    left_path = left_path->left;
                }
                else if ( a == left_path->key )
                {
                    attach_xintv_rectangle(left_path->right, a,b,c,d);
                    break;
                }
                else
                    left_path = left_path->right;
            }
            if( left_path->right == NULL && left_path->key == a )
                attach_xintv_rectangle(left_path, a,b,c,d);
        }
        if( right_path != NULL )
        {
            while( right_path->right != NULL )
            {
                if( right_path->key < b )
                {
                    attach_xintv_rectangle(right_path->left, a,b,c,d);
                    right_path = right_path->right;
                }
                else if ( right_path->key == b)
                {
                    attach_xintv_rectangle(right_path->left, a,b,c,d);
                    break;
                }
                else
                    right_path = right_path->left;
            }
        }
    }
}
void insert_rectangle_yinterval(YSegmentTree *&tree, int a, int b, int c, int d)
{
    if(tree->left == NULL)
        return;
    else
    {
        YSegmentTree *current_node = tree;
        YSegmentTree *right_path = new YSegmentTree();
        YSegmentTree *left_path = new YSegmentTree();
        while( current_node->right != NULL )
        {
            if( d < current_node->key )
                current_node = current_node->left;
            else if( current_node->key < c)
                current_node = current_node->right;
            else if( c < current_node->key && current_node->key < d )
            {
                right_path = current_node->right;
                left_path  = current_node->left;
                break;
            }
            else if( c == current_node->key )
            {
                right_path = current_node->right;
                break;
            }
            else
            {
                left_path  = current_node->left;
                break;
            }
        }
        if( left_path != NULL )
        {
            while( left_path->right != NULL )
            {
                if( c < left_path->key )
                {
                    attach_yintv_rectangle(left_path->right, a,b,c,d);
                    left_path = left_path->left;
                }
                else if ( c == left_path->key )
                {
                    attach_yintv_rectangle(left_path->right, a,b,c,d);
                    break;
                }
                else
                    left_path = left_path->right;
            }
            if( left_path->right == NULL && left_path->key == c )
                attach_yintv_rectangle(left_path, a,b,c,d);
        }
        if( right_path != NULL )
        {
            while( right_path->right != NULL )
            {
                if( right_path->key < d )
                {
                    attach_yintv_rectangle(right_path->left, a,b,c,d);
                    right_path = right_path->right;
                }
                else if ( right_path->key == d)
                {
                    attach_yintv_rectangle(right_path->left, a,b,c,d);
                    break;
                }
                else
                    right_path = right_path->left;
            }
        }
    }
}
rect_list_t  *query_seg_tree_2d(seg_tree_2d_t *&tree, int x, int y)
{
    if( tree->left == NULL )
        return(NULL);
    else
    {
        seg_tree_2d_t *current_xtree_node = tree;
        rect_list_t  *result_list = NULL;
        rect_list_t  *current_list;
        while( current_xtree_node->right != NULL )
        {
            if( x < current_xtree_node->key )
                current_xtree_node = current_xtree_node->left;
            else
                current_xtree_node = current_xtree_node->right;

            if(current_xtree_node->y_tree!=NULL)
            {
                YSegmentTree *yroot = current_xtree_node->y_tree;
                while(yroot->right!=NULL)
                {
                    if( y < yroot->key )
                        yroot = yroot->left;
                    else
                        yroot = yroot->right;
                    current_list = yroot->rectangle_list;
                    while( current_list != NULL )
                    {
                        rect_list_t  *new_result = new rect_list_t();
                        new_result->next = result_list;
                        new_result->x_min = current_list->x_min;
                        new_result->x_max = current_list->x_max;
                        new_result->y_min = current_list->y_min;
                        new_result->y_max = current_list->y_max;
                        result_list = new_result;
                        current_list = current_list->next;
                    }
                }
            }
        }
        return( result_list );
    }
}
void y_inorder(YSegmentTree *&ytxt)
{
    if(ytxt->right == NULL)
    {
        cout << ytxt->key << "->";
        if(ytxt->rectangle_list!=NULL)
        {
            cout << "\n";
            for(rect_list_t  *r=ytxt->rectangle_list; r!=NULL; r=r->next)
            {
                cout << r->x_min << "," <<r->x_max << "  " << r->y_min <<"," << r->y_max <<"\n";
            }
        }
        return;
    }
    y_inorder(ytxt->left);
    cout << ytxt->key << "->";
    if(ytxt->rectangle_list!=NULL)
    {
        cout << "\n";
        for(rect_list_t  *r=ytxt->rectangle_list; r!=NULL; r=r->next)
        {
            cout << r->x_min << "," <<r->x_max << "  " << r->y_min <<"," << r->y_max <<"\n";
        }
    }
    y_inorder(ytxt->right);
}
YSegmentTree *make_y_tree(rect_list_t  *rectangles,int n_rec)
{
    int keys[2*n_rec], prev_key;
    int i,j;
    for(i=0;i<n_rec;i++)
    {
        keys[2*i] = rectangles[i].y_min;
        keys[2*i+1] = rectangles[i].y_max;
    }
    quickSort(keys,0,2*n_rec-1);
    YSegmentTree *ulists = new YSegmentTree();
    ulists->right = NULL;
    prev_key = ulists->key = keys[2*n_rec-1];
    int tmpno = 42;
    int *tmpob  = &tmpno;
    ulists->left = (YSegmentTree *) tmpob;
    int length = 1;
    for( j = 2*n_rec-2; j>= 0; j-- )
    {
        if( keys[j] != prev_key )
        {
            YSegmentTree *temp = new YSegmentTree();
            prev_key = temp->key = keys[j];
            temp->right = ulists;
            ulists = temp;
            ulists->left = (YSegmentTree *) tmpob;
            length++;
        }
    }
    YSegmentTree *tmp = new YSegmentTree();
    tmp->key = MINUS_INFINITY;
    tmp->right = ulists;
    tmp->left = (YSegmentTree *) tmpob;
    ulists = tmp;
    length++;
    YSegmentTree *root = new YSegmentTree();
    Stack_YItem *current = new Stack_YItem();
    current->node1 = root;
    current->node2 = NULL;
    current->number = length;
    YStack *st = create_ystack();
    push(current, st);
    while( !stack_empty(st) )
    {
        current = pop(st);
        YSegmentTree *nd;
        if( current->number > 1 )
        {
            nd = new YSegmentTree();
            Stack_YItem *left = new Stack_YItem();
            Stack_YItem *right = new Stack_YItem();
            left->node1 = nd;
            left->node2 = current->node2;
            left->number = current->number/2;
            nd = new YSegmentTree();
            right->node1 = nd;
            right->node2 = current->node1;
            right->number = current->number - left->number;
            current->node1->left  = left->node1;
            current->node1->right = right->node1;
            push(right, st);
            push(left, st);
        }
        else
        {
            current->node1->left  = ulists->left;
            current->node1->key   = ulists->key;
            current->node1->right = NULL;
            if( current->node2 != NULL )
                current->node2->key   = ulists->key;
            YSegmentTree *tmp = ulists;
            ulists = ulists->right;
            delete tmp;
        }
    }
    empty_tree(root);
    for(  j = 0; j<n_rec; j++ )
    {
        insert_rectangle_yinterval( root, rectangles[j].x_min, rectangles[j].x_max, rectangles[j].y_min, rectangles[j].y_max);
    }
    return root;
}
void inorder(seg_tree_2d_t *&txt)
{
    if(txt->right == NULL)
    {
        if(txt->rectangle_list!=NULL)
        {
            int no_of_rectangles=0;
            for(rect_list_t  *rect = txt->rectangle_list; rect!=NULL; rect=rect->next)
            {
                no_of_rectangles++;
            }
            rect_list_t  rt[no_of_rectangles];
            int i=0;
            for(rect_list_t  *rect = txt->rectangle_list; rect!=NULL; rect=rect->next)
            {
                rt[i].x_min=rect->x_min;
                rt[i].x_max=rect->x_max;
                rt[i].y_min=rect->y_min;
                rt[i].y_max=rect->y_max;
                i++;
            }
            txt->y_tree = make_y_tree(rt,no_of_rectangles);
        }
        return;
    }
    inorder(txt->left);
    if(txt->rectangle_list!=NULL)
    {
        int no_of_rectangles=0;
        for(rect_list_t  *rect = txt->rectangle_list; rect!=NULL; rect=rect->next)
        {
           no_of_rectangles++;
        }
        rect_list_t  rt[no_of_rectangles];
        int i=0;
        for(rect_list_t  *rect = txt->rectangle_list; rect!=NULL; rect=rect->next)
        {
            rt[i].x_min=rect->x_min;
            rt[i].x_max=rect->x_max;
            rt[i].y_min=rect->y_min;
            rt[i].y_max=rect->y_max;
            i++;
        }
        txt->y_tree = make_y_tree(rt,no_of_rectangles);
    }
    inorder(txt->right);
}
void inorder_complete(seg_tree_2d_t *&txt)
{
    if(txt->right==NULL)
    {
        cout << txt->key << "->\n";
        if(txt->y_tree!=NULL)
        {
            y_inorder(txt->y_tree);
        }
        return;
    }
    inorder_complete(txt->left);
    cout << txt->key << "->\n";
    if(txt->y_tree!=NULL)
    {
        y_inorder(txt->y_tree);
    }
    inorder_complete(txt->right);
}
seg_tree_2d_t *create_seg_tree_2d(rect_list_t  *rectangles)
{
    int no_of_rec = 0;
    for(rect_list_t  *rect = rectangles; rect!=NULL; rect=rect->next)
    {
        no_of_rec++;
    }
    cout <<  "No of rect_list_t s are : " << no_of_rec <<"\n";
    int keys[2*no_of_rec], prev_key;
    int i,j;
    for(i=0;i<no_of_rec;i++)
    {
        keys[2*i] = rectangles[i].x_min;
        keys[2*i+1] = rectangles[i].x_max;
    }
    quickSort(keys,0,2*no_of_rec-1);
    seg_tree_2d_t *ulists = new seg_tree_2d_t();
    ulists->right = NULL;
    prev_key = ulists->key = keys[2*no_of_rec-1];
    int tmpno = 42;
    int *tmpob  = &tmpno;
    ulists->left = (seg_tree_2d_t *) tmpob;
    int length = 1;
    for( j = 2*no_of_rec-2; j>= 0; j-- )
    {
        if( keys[j] != prev_key )
        {
            seg_tree_2d_t *temp = new seg_tree_2d_t();
            prev_key = temp->key = keys[j];
            temp->right = ulists;
            ulists = temp;
            ulists->left = (seg_tree_2d_t *) tmpob;
            length++;
        }
    }
    seg_tree_2d_t *tmp = new seg_tree_2d_t();
    tmp->key = MINUS_INFINITY;
    tmp->right = ulists;
    tmp->left = (seg_tree_2d_t *) tmpob;
    ulists = tmp;
    length++;
    seg_tree_2d_t *root = new seg_tree_2d_t();
    Stack_XItem *current = new Stack_XItem();
    current->node1 = root;
    current->node2 = NULL;
    current->number = length;
    Stack *st = create_stack();
    push(current, st);
    while( !stack_empty(st) )
    {
        current = pop(st);
        seg_tree_2d_t *nd;
        if( current->number > 1 )
        {
            nd = new seg_tree_2d_t();
            Stack_XItem *left = new Stack_XItem();
            Stack_XItem *right = new Stack_XItem();
            left->node1 = nd;
            left->node2 = current->node2;
            left->number = current->number/2;
            nd = new seg_tree_2d_t();
            right->node1 = nd;
            right->node2 = current->node1;
            right->number = current->number - left->number;
            current->node1->left  = left->node1;
            current->node1->right = right->node1;
            push(right, st);
            push(left, st);
        }
        else
        {
            current->node1->left  = ulists->left;
            current->node1->key   = ulists->key;
            current->node1->right = NULL;
            if( current->node2 != NULL )
                current->node2->key   = ulists->key;
            seg_tree_2d_t *tmp = ulists;
            ulists = ulists->right;
            delete tmp;
        }
    }
    empty_tree(root);
    for(  j = 0; j<no_of_rec; j++ )
    {
        insert_rectangle_xinterval( root, rectangles[j].x_min, rectangles[j].x_max, rectangles[j].y_min, rectangles[j].y_max);
    }
    inorder(root);
    return(root);
}

#include "test_file.cpp"