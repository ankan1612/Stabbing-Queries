int main()
{  
    int i, j, x, y, l,m; 
    rect_list_t rectangles[50000];
    rect_list_t * tmp;
    seg_tree_2d_t *tr;
    for( i=0; i<50000; i++)
    {  
        rectangles[(17*i)%50000 ].next = rectangles + ((17*(i+1))%50000);  
    }
    rectangles[(17*49999)%50000 ].next = NULL;
    i=0; tmp = rectangles;
    while(tmp->next != NULL )
    {  
        tmp = tmp->next; i+=1; 
    }
    printf("List of %d rectangles\n",i);
    for(i=0; i<12500; i++)
    {  
        rectangles[i].x_min = 500000 + 40*i;
        rectangles[i].x_max = 500000 + 40*i + 20;
        rectangles[i].y_min = 0;
        rectangles[i].y_max = 1000000;
    }
    for(i=12500; i<25000; i++)
    {  
        rectangles[i].x_min = 500000 + 40*(i-12500) + 10;
        rectangles[i].x_max = 500000 + 40*(i-12500) + 20;
        rectangles[i].y_min = 0;
        rectangles[i].y_max = 1000000;
    }
    for(i=25000; i<37500; i++)
    {  
        rectangles[i].x_min = 20*(i-25000);
        rectangles[i].x_max = 20*(i-25000) + 250000;
        rectangles[i].y_min = 20*(i-25000);
        rectangles[i].y_max = 20*(i-25000) + 250000;
    }
    for(i=37500; i<50000; i++)
    {  
        rectangles[i].x_min = 40*(i-37500);
        rectangles[i].x_max = 500000;
        rectangles[i].y_min = 300000;
        rectangles[i].y_max = 500000 + 40*(i-37500);
    }
    printf("Defined the 50000 rectangles\n"); fflush(stdout);
    tr = create_seg_tree_2d( rectangles );
    printf("Created 2d segment tree\n"); fflush(stdout);
    /* test 1 */
    for( i= 0; i<1000; i++ )
    {  
        x = 500000 + 400*i +30;
        y = ((1379*i)%400000) + 10;
        tmp = query_seg_tree_2d( tr, x,y);
        if( tmp != NULL )
        {  
            printf("point %d,%d should not be covered by any rectangle.\n",x,y);
            printf(" instead reported as covered by [%d,%d]x[%d,%d]\n",tmp->x_min, tmp->x_max, tmp->y_min, tmp->y_max); 
            fflush(stdout);
            exit(0);
        }
    }
    printf("Passed Test 1.\n");
    /* test 2 */
    for( i= 0; i<1000; i++ )
    {  
        x = 500000 + 400*i +5;
        y = ((3791*i)%400000) + 10;
        tmp = query_seg_tree_2d( tr, x,y);
        if( tmp == NULL )
        {  
            printf("point %d,%d should be covered by a rectangle, not found\n",x,y);
            fflush(stdout);
            exit(0);
        }
        if( x< tmp->x_min || x > tmp->x_max || y< tmp->y_min || y > tmp->y_max )
        {  
            printf("rectangle [%d,%d]x[%d,%d] does not cover point %d,%d\n",tmp->x_min, tmp->x_max, tmp->y_min, tmp->y_max,x,y); 
            fflush(stdout); 
            exit(0);
        } 
    }
    printf("Passed Test 2.\n");
    /* test 3 */
    for( i= 0; i<10; i++ )
    {  
        x = 300000 + 20000*i + 3;
        y = 400001;
        tmp = query_seg_tree_2d( tr, x,y);
        if( tmp == NULL )
        {  
            printf("point %d,%d should be covered by a rectangle, not found\n",x,y);
            exit(0);
        }
        while( tmp != NULL )
        {  
            if( x< tmp->x_min|| x > tmp->x_max|| y< tmp->y_min|| y > tmp->y_max )
            { 
                printf("rectangle [%d,%d]x[%d,%d] does not cover point %d,%d\n", tmp->x_min, tmp->x_max, tmp->y_min, tmp->y_max,x,y); 
                exit(0);
            }
            tmp = tmp->next;
        }
    }
    printf("Passed Test 3.\n");
    /* test 4 */
    for( i= 0; i<10; i++ )
    {  
        x = 10* (rand()%100000) +4;
        y = 10* (rand()%100000) +4;
        m=0;
        for(j=0; j<50000; j++ )
        {  
            if( rectangles[j].x_min < x && rectangles[j].x_max > x &&
            rectangles[j].y_min < y && rectangles[j].y_max > y )
            m +=1;
        }
        tmp = query_seg_tree_2d( tr, x,y);
        l=0;
        while( tmp != NULL )
        {  
            if( x< tmp->x_min|| x > tmp->x_max|| y< tmp->y_min|| y > tmp->y_max )
            {  
                printf("rectangle [%d,%d]x[%d,%d] does not cover point %d,%d\n",
                tmp->x_min, tmp->x_max, tmp->y_min, tmp->y_max,x,y); 
                exit(0);
            }
            l+= 1;
            tmp = tmp->next;
        }
        if( l!= m )
        {  
            printf("test 4.%d: Point %d,%d should be in %d rectangles, but %d found\n", i, x, y, m, l);
            fflush(stdout); 
        }     
    }
    printf("End of tests\n");
}