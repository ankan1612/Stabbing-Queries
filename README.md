# 2D Segment Tree for stabbing queries

Create a two-dimensional segment tree, that is, a structure which receives a list of axis-aligned rectangles, and builds a structure that allows for stabbing queries. For a given query point, you should return all those rectangles that contain the query point.

The rectangle list structure is deﬁnes as :

```sh
struct rect_list_t { 
struct rect list t *next;
int x min; 
int x max; 
int y min; 
int y max;
}
```

Then you deﬁne a structure:
```sh
struct seg_tree_2d_t
```
 and functions :
 ```sh
 struct seg_tree_2d_t *create_seg_tree_2d( struct rect_list_t *list) 
 ```
 and 
 ```sh
 struct rect_list_t *query_seg_tree_2d( struct seg_tree_2d_t *tree, int x, int y)
 ```
