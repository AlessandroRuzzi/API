#ifndef PROGETTO_API_ENTITY_RB_H
#define PROGETTO_API_ENTITY_RB_H

#include "rel.h"

//defining all the rb-tree structures and the relations structure

typedef struct rb_Tree_entities{
    char color;
    char *entities;
    struct rb_Tree_entities *right,*left,*p;
}rb_Tree_entities;

typedef struct T {

    struct rb_Tree_entities *root,*nil;


}T;

//end of structures




// defining functions of the rb-tree of the entities

T *left_rotate(T *ent_t,rb_Tree_entities *x);

T* right_rotate(T *ent_t,rb_Tree_entities *x);

T *rb_insert_fixup(T *ent_t , rb_Tree_entities *z);

rb_Tree_entities *create_element(rel relations,T *ent_t);

T *rb_insert(T *ent_t,rel relations);

T *create_rb();

rb_Tree_entities *tree_minimum(rb_Tree_entities *x,rb_Tree_entities *nil);

rb_Tree_entities *tree_successor(rb_Tree_entities *x,rb_Tree_entities *nil);

T *rb_delete_fixup(T *ent_t,rb_Tree_entities *x);

T *delete_rb(T *ent_t,rb_Tree_entities *z);

void print_rb(rb_Tree_entities *root,rb_Tree_entities *nil);

rb_Tree_entities *rb_search(rb_Tree_entities *root,rb_Tree_entities *nil,char *value);

//end of functions

#endif //PROGETTO_API_ENTITY_RB_H
