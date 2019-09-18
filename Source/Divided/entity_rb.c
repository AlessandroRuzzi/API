#include "entity_rb.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>


// defining functions of the rb-tree of the entities

T *left_rotate(T *ent_t,rb_Tree_entities *x){
    rb_Tree_entities *y;

    y = x->right;
    x->right = y->left;

    if(y->left != ent_t->nil){
        y->left->p = x;
    }
    y->p = x->p;

    if(x->p == ent_t->nil){
        ent_t->root = y;
    }
    else if(x == x->p->left){
        x->p->left =y;
    }
    else{
        x->p->right = y;
    }
    y->left = x;
    x->p = y;

    return ent_t;
}

T* right_rotate(T *ent_t,rb_Tree_entities *x){
    rb_Tree_entities *y;

    y = x->left;
    x->left = y->right;

    if(y->right != ent_t->nil){
        y->right->p = x;
    }
    y->p = x->p;

    if(x->p == ent_t->nil){
        ent_t->root = y;
    }
    else if(x == x->p->right){
        x->p->right =y;
    }
    else{
        x->p->left= y;
    }
    y->right = x;
    x->p = y;

    return ent_t;
}

T *rb_insert_fixup(T *ent_t , rb_Tree_entities *z){
    rb_Tree_entities *x,*y;

    if(z == ent_t->root){
        ent_t->root->color='b';

    }
    else{
        x = z->p;

        if(x->color == 'r'){
            if(x == x->p->left){
                y = x->p->right;
                if(y->color == 'r'){
                    x->color= 'b';
                    y->color = 'b';
                    x->p->color = 'r';
                    ent_t = rb_insert_fixup(ent_t,x->p);
                }
                else{

                    if(z == x->right){
                        z = x;
                        ent_t = left_rotate(ent_t,z);
                        x = z->p;
                    }


                    x->color = 'b';
                    x->p->color='r';
                    ent_t = right_rotate(ent_t,x->p);
                }
            }
            else{
                y = x->p->left;
                if(y->color == 'r'){
                    x->color= 'b';
                    y->color = 'b';
                    x->p->color = 'r';
                    ent_t = rb_insert_fixup(ent_t,x->p);
                }
                else {
                    if(z == x->left){
                        z = x;
                        ent_t = right_rotate(ent_t,z);
                        x = z->p;
                    }


                    x->color = 'b';
                    x->p->color='r';
                    ent_t = left_rotate(ent_t,x->p);


                }

            }
        }
    }

    return ent_t;
}

rb_Tree_entities *create_element(rel relations,T *ent_t){
    rb_Tree_entities *punt;

    punt = malloc(sizeof(rb_Tree_entities));
    punt->p = ent_t->nil;
    punt->right = ent_t->nil;
    punt->left = ent_t->nil;
    punt->entities = malloc((strlen(relations.first) + 1) *sizeof(char));
    strcpy(punt->entities,relations.first);
    return punt;


}

T *rb_insert(T *ent_t,rel relations){
    rb_Tree_entities *z;
    z = create_element(relations,ent_t);

    rb_Tree_entities *y=ent_t->nil;
    rb_Tree_entities *x=ent_t->root;

    while (x != ent_t->nil){

        y = x;

        if(strcmp(z->entities,x->entities)<0){
            x=x->left;

        }
        else{
            x = x->right;

        }
    }

    z->p = y;

    if(y ==ent_t->nil){
        ent_t->root = z;

    }
    else{
        if(strcmp(z->entities,y->entities)<0){

            y->left = z;

        }
        else{
            y->right =z;
        }
    }
    z->left = ent_t->nil;
    z->right = ent_t->nil;
    z->color = 'r';


    ent_t = rb_insert_fixup(ent_t,z);

    return ent_t;
}

T *create_rb(){

    T *t;
    t=malloc(sizeof(T));
    t->nil=malloc(sizeof(rb_Tree_entities));
    t->root=malloc(sizeof(rb_Tree_entities));
    t->nil->left = t->nil;
    t->nil->right = t->nil;
    t->nil->p = t->nil;
    t->nil->color = 'b';
    t->root = t->nil;
    return t;

}

rb_Tree_entities *tree_minimum(rb_Tree_entities *x,rb_Tree_entities *nil){
    while(x->left != nil)
        x = x->left;
    return x;
}

rb_Tree_entities *tree_successor(rb_Tree_entities *x,rb_Tree_entities *nil){

    rb_Tree_entities *y;

    if (x->right != nil)
        return tree_minimum(x->right,nil);
    y = x->p;
    while( y != nil && x == y->right){

        x = y;
        y = y->p;
    }
    return y;
}

T *rb_delete_fixup(T *ent_t,rb_Tree_entities *x){

    rb_Tree_entities *w;

    if(x->color == 'r' || x->p == ent_t->nil)
        x->color = 'b';
    else if(x == x->p->left){
        w = x->p->right;
        if(w->color == 'r'){
            w->color = 'b';
            x->p->color = 'r';
            ent_t = left_rotate(ent_t,x->p);
            w = x->p->right;
        }
        if(w->left->color == 'b' && w->right->color == 'b'){
            w->color = 'r';
            ent_t = rb_delete_fixup(ent_t,x->p);
        }
        else{
            if(w->right->color == 'b'){
                w->left->color = 'b';
                w->color = 'r';
                ent_t = right_rotate(ent_t,w);
                w = x->p->right;
            }
            w->color = x->p->color;
            x->p->color = 'b';
            w->right->color = 'b';
            ent_t = left_rotate(ent_t,x->p);

        }
    }
    else{
        w = x->p->left;

        if(w->color == 'r'){
            w->color = 'b';
            x->p->color = 'r';
            ent_t = right_rotate(ent_t,x->p);
            w = x->p->left;
        }
        if(w->right->color == 'b' && w->left->color == 'b'){
            w->color = 'r';
            ent_t = rb_delete_fixup(ent_t,x->p);
        }
        else{
            if(w->left->color == 'b'){
                w->right->color = 'b';
                w->color = 'r';
                ent_t = left_rotate(ent_t,w);
                w = x->p->left;
            }
            w->color = x->p->color;
            x->p->color = 'b';
            w->left->color = 'b';
            ent_t = right_rotate(ent_t,x->p);

        }

    }
    return ent_t;
}

T *delete_rb(T *ent_t,rb_Tree_entities *z){

    int cont = 0;

    rb_Tree_entities *x,*y;

    if(z->left == ent_t->nil || z->right == ent_t->nil)
        y = z;
    else
        y = tree_successor(z,ent_t->nil);
    if(y->left != ent_t->nil)
        x = y->left;
    else
        x = y->right;

    x->p = y->p;
    if(y->p == ent_t->nil)
        ent_t->root = x;
    else if(y == y->p->left)
        y->p->left = x;
    else
        y->p->right = x;
    if(y != z){
        if(strlen(z->entities) < strlen(y->entities)){
            z->entities = realloc(z->entities,(strlen(y->entities) + 1) *sizeof(char));

        }
        strcpy(z->entities,y->entities);
        cont =1;
    }
    if(y->color == 'b')
        ent_t = rb_delete_fixup(ent_t,x);

    if(cont == 1){
        free(y->entities);
        free(y);
    }
    else{
        free(z->entities);
        free(z);

    }

    return ent_t;
}

void print_rb(rb_Tree_entities *root,rb_Tree_entities *nil){

    if(root != nil){

        print_rb(root->left,nil);
        fputs(" ",stdout);
        fputs(root->entities,stdout);
        print_rb(root->right,nil);

    }
}

rb_Tree_entities *rb_search(rb_Tree_entities *root,rb_Tree_entities *nil,char *value){

    while(root != nil){

        if(strcmp(value,root->entities) == 0)
            return root;
        else if(strcmp(value,root->entities) < 0)
            root = root->left;
        else
            root = root->right;
    }

    return NULL;

}

//end of functions

