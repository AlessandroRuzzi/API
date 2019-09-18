#ifndef PROGETTO_API_COUNTER_RB_H
#define PROGETTO_API_COUNTER_RB_H

#include "rel.h"
#include <stdio.h>



//defining all the rb-tree structures and the relations structure

typedef struct rb_Tree_cont{
    char color;
    char *entities;
    int contatore;
    struct rb_Tree_cont *right,*left,*p;
    struct T *received;
}rb_Tree_cont;

typedef struct T3 {

    struct rb_Tree_cont *root,*nil;


}T3;

//end of structures



//defining functions of the rb-tree of the counter

T3 *left_rotate3(T3 *ent_t,rb_Tree_cont *x);

T3* right_rotate3(T3 *ent_t,rb_Tree_cont *x);

T3 *rb_insert_fixup3(T3 *ent_t , rb_Tree_cont *z);

rb_Tree_cont *create_element3(rel relations,T3 *ent_t, int cont);

T3 *rb_insert3(T3 *ent_t,rel relations);

T3 *create_rb3();

rb_Tree_cont *tree_minimum3(rb_Tree_cont *x,rb_Tree_cont *nil);

rb_Tree_cont *tree_successor3(rb_Tree_cont *x,rb_Tree_cont *nil);

T3 *rb_delete_fixup3(T3 *ent_t,rb_Tree_cont *x);

T3 *delete_rb3(T3 *ent_t,rb_Tree_cont *z);

void print_rb3(rb_Tree_cont *root,rb_Tree_cont *nil);

rb_Tree_cont *rb_search3(rb_Tree_cont *root,rb_Tree_cont *nil,char *value);


//end of functions



#endif //PROGETTO_API_COUNTER_RB_H
