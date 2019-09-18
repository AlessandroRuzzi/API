#ifndef PROGETTO_API_RELATIONS_RB_H
#define PROGETTO_API_RELATIONS_RB_H

#include "rel.h"

//defining all the rb-tree structures and the relations structure

typedef struct rb_Tree_relations{
    char color;
    char *entities;
    struct rb_Tree_relations *right,*left,*p;
    struct T3 *cont;
    struct T *max_tree;
    int max_cont;
}rb_Tree_relations;

typedef struct T1 {

    struct rb_Tree_relations *root,*nil;


}T1;

//end of structures




//defining functions of the rb-tree of the relations

T1 *left_rotate1(T1 *ent_t,rb_Tree_relations *x);

T1 * right_rotate1(T1 *ent_t,rb_Tree_relations *x);

T1 *rb_insert_fixup1(T1 *ent_t , rb_Tree_relations *z);

rb_Tree_relations *create_element1(rel relations,T1 *ent_t);

T1 *rb_insert1(T1 *ent_t,rel relations);

T1 *create_rb1();

rb_Tree_relations *tree_minimum1(rb_Tree_relations *x,rb_Tree_relations *nil);

rb_Tree_relations *tree_successor1(rb_Tree_relations *x,rb_Tree_relations *nil);

T1 *rb_delete_fixup1(T1 *ent_t,rb_Tree_relations *x);

T1 *delete_rb1(T1 *ent_t,rb_Tree_relations *z);

void print_rb1(rb_Tree_relations *root,rb_Tree_relations *nil);

rb_Tree_relations *rb_search1(rb_Tree_relations *root,rb_Tree_relations *nil,char *value);

//end of functions



#endif //PROGETTO_API_RELATIONS_RB_H
