/***********************************************************************
* Project           : API PROJECT 2019 -> social network like
*
* Program name      : progetto_api.c
*
* Author            : Alessandro Ruzzi
*
* Date created      : 29/07/2019
*
* Purpose           : implement a mechanism for monitoring relationships between
                      entities (for example people) that change over time.
*
* Revision History  :
*
* Date          Author        Ref    Revision (25/08/2019)
* 15/09/2019    A. Ruzzi      2      changed dimension of char entities, deleted the useless code, changed the name of the variables the be more readable.
*
|***********************************************************************/


#include <stdio.h>
#include <stdlib.h>
#include <string.h>

//defining all the rb-tree structures and the relations structure

typedef struct rb_Tree_entities{
    char color;
    char *entities;
    struct rb_Tree_entities *right,*left,*p;
}rb_Tree_entities;

typedef struct rb_Tree_relations{
    char color;
    char *entities;
    struct rb_Tree_relations *right,*left,*p;
    struct T3 *cont;
    struct T *max_tree;
    int max_cont;
}rb_Tree_relations;

typedef struct rb_Tree_cont{
    char color;
    char *entities;
    int contatore;
    struct rb_Tree_cont *right,*left,*p;
    struct T *received;
}rb_Tree_cont;

typedef struct T {

    struct rb_Tree_entities *root,*nil;


}T;
typedef struct T1 {

    struct rb_Tree_relations *root,*nil;


}T1;

typedef struct puntatori {

    struct T *t;
    struct T1 *t1;


}puntatori;

typedef struct T3 {

    struct rb_Tree_cont *root,*nil;


}T3;

typedef struct rel {

    char function[7];
    char type[35];
    char first[35];
    char second[35];
}rel;

//end of structures





//defining global variables

int report_check = 0;
int end=0;
int verification =0;
rb_Tree_cont *search_pointer = NULL;
int max_number_relations_received = 0;

//end of global variables





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





//defining functions of the rb-tree of the relations

T1 *left_rotate1(T1 *ent_t,rb_Tree_relations *x){
    rb_Tree_relations *y;

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

T1 * right_rotate1(T1 *ent_t,rb_Tree_relations *x){
    rb_Tree_relations *y;

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
        x->p->right=y;
    }
    else{
        x->p->left = y;
    }
    y->right = x;
    x->p = y;

    return ent_t;
}

T1 *rb_insert_fixup1(T1 *ent_t , rb_Tree_relations *z){
    rb_Tree_relations *x,*y;

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
                    ent_t = rb_insert_fixup1(ent_t,x->p);
                }
                else{

                    if(z == x->right){
                        z = x;
                        ent_t = left_rotate1(ent_t,z);
                        x = z->p;
                    }


                    x->color = 'b';
                    x->p->color='r';
                    ent_t = right_rotate1(ent_t,x->p);
                }
            }
            else{
                y = x->p->left;
                if(y->color == 'r'){
                    x->color= 'b';
                    y->color = 'b';
                    x->p->color = 'r';
                    ent_t = rb_insert_fixup1(ent_t,x->p);
                }
                else {
                    if(z == x->left){
                        z = x;
                        ent_t = right_rotate1(ent_t,z);
                        x = z->p;
                    }


                    x->color = 'b';
                    x->p->color='r';
                    ent_t = left_rotate1(ent_t,x->p);


                }

            }
        }
    }

    return ent_t;
}

rb_Tree_relations *create_element1(rel relations,T1 *ent_t){
    rb_Tree_relations *punt;

    punt = malloc(sizeof(rb_Tree_relations));
    punt->p = ent_t->nil;
    punt->right = ent_t->nil;
    punt->left = ent_t->nil;
    punt->cont = NULL;
    punt->max_tree = NULL;
    punt->max_cont = 1;
    punt->entities = malloc((strlen(relations.type) + 1) *sizeof(char));
    strcpy(punt->entities,relations.type);
    return punt;


}

T1 *rb_insert1(T1 *ent_t,rel relations){
    rb_Tree_relations *z;
    z = create_element1(relations,ent_t);
    rb_Tree_relations *y=ent_t->nil;
    rb_Tree_relations *x=ent_t->root;

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
    else if(strcmp(z->entities,y->entities)<0){

        y->left = z;

    }
    else{
        y->right =z;
    }
    z->left = ent_t->nil;
    z->right = ent_t->nil;
    z->color = 'r';


    ent_t = rb_insert_fixup1(ent_t,z);

    return ent_t;
}

T1 *create_rb1(){

    T1 *t;
    t=malloc(sizeof(T1));
    t->nil=malloc(sizeof(rb_Tree_relations));
    t->root=malloc(sizeof(rb_Tree_relations));
    t->nil->left = t->nil;
    t->nil->right = t->nil;
    t->nil->p = t->nil;
    t->nil->color = 'b';
    t->nil->max_cont = 0;
    t->root = t->nil;
    return t;

}

rb_Tree_relations *tree_minimum1(rb_Tree_relations *x,rb_Tree_relations *nil){
    while(x->left != nil)
        x = x->left;
    return x;
}

rb_Tree_relations *tree_successor1(rb_Tree_relations *x,rb_Tree_relations *nil){

    rb_Tree_relations *y;

    if (x->right != nil)
        return tree_minimum1(x->right,nil);
    y = x->p;
    while( y != nil && x == y->right){

        x = y;
        y = y->p;
    }
    return y;
}

T1 *rb_delete_fixup1(T1 *ent_t,rb_Tree_relations *x){

    rb_Tree_relations *w;

    if(x->color == 'r' || x->p == ent_t->nil)
        x->color = 'b';
    else if(x == x->p->left){
        w = x->p->right;
        if(w->color == 'r'){
            w->color = 'b';
            x->p->color = 'r';
            ent_t = left_rotate1(ent_t,x->p);
            w = x->p->right;
        }
        if(w->left->color == 'b' && w->right->color == 'b'){
            w->color = 'r';
            ent_t = rb_delete_fixup1(ent_t,x->p);
        }
        else{

            if(w->right->color == 'b'){

                w->left->color = 'b';
                w->color = 'r';
                ent_t = right_rotate1(ent_t,w);
                w = x->p->right;
            }
            w->color = x->p->color;
            x->p->color = 'b';
            w->right->color = 'b';
            ent_t = left_rotate1(ent_t,x->p);

        }
    }
    else{
        w = x->p->left;

        if(w->color == 'r'){

            w->color = 'b';
            x->p->color = 'r';

            ent_t = right_rotate1(ent_t,x->p);

            w = x->p->left;

        }
        if(w->right->color == 'b' && w->left->color == 'b'){
            w->color = 'r';

            ent_t = rb_delete_fixup1(ent_t,x->p);

        }
        else{
            if(w->left->color == 'b'){

                w->right->color = 'b';
                w->color = 'r';
                ent_t = left_rotate1(ent_t,w);
                w = x->p->left;
            }
            w->color = x->p->color;
            x->p->color = 'b';
            w->left->color = 'b';
            ent_t = right_rotate1(ent_t,x->p);

        }

    }
    return ent_t;
}

T1 *delete_rb1(T1 *ent_t,rb_Tree_relations *z){

    int cont = 0 ;

    rb_Tree_relations *x,*y;

    if(z->left == ent_t->nil || z->right == ent_t->nil)
        y = z;
    else{
        y = tree_successor1(z,ent_t->nil);}

    if(y->left != ent_t->nil)
        x = y->left;
    else
        x = y->right;

    x->p = y->p;
    if(y->p == ent_t->nil){
        ent_t->root = x;
    }
    else if(y == y->p->left){
        y->p->left = x;
    }
    else{
        y->p->right = x;
    }

    if(y != z){
        if(strlen(z->entities) < strlen(y->entities)){
            z->entities = realloc(z->entities,(strlen(y->entities) + 1) *sizeof(char));

        }
        strcpy(z->entities,y->entities);
        z->cont = y->cont;
        z->max_cont = y->max_cont;
        z->max_tree = y->max_tree;
        cont =1;
    }
    if(y->color == 'b'){

        ent_t = rb_delete_fixup1(ent_t,x);
    }

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

void print_rb1(rb_Tree_relations *root,rb_Tree_relations *nil){

    if(root != nil){

        print_rb1(root->left,nil);
        printf("-> %s ",root->entities);
        print_rb1(root->right,nil);

    }
}

rb_Tree_relations *rb_search1(rb_Tree_relations *root,rb_Tree_relations *nil,char *value){

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





//defining functions of the rb-tree of the counter

T3 *left_rotate3(T3 *ent_t,rb_Tree_cont *x){
    rb_Tree_cont *y;

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

T3* right_rotate3(T3 *ent_t,rb_Tree_cont *x){
    rb_Tree_cont*y;

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
        x->p->right=y;
    }
    else{
        x->p->left = y;
    }
    y->right = x;
    x->p = y;

    return ent_t;
}

T3 *rb_insert_fixup3(T3 *ent_t , rb_Tree_cont *z){
    rb_Tree_cont *x,*y;

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
                    ent_t = rb_insert_fixup3(ent_t,x->p);
                }
                else{

                    if(z == x->right){
                        z = x;
                        ent_t = left_rotate3(ent_t,z);
                        x = z->p;
                    }


                    x->color = 'b';
                    x->p->color='r';
                    ent_t = right_rotate3(ent_t,x->p);
                }
            }
            else{
                y = x->p->left;
                if(y->color == 'r'){
                    x->color= 'b';
                    y->color = 'b';
                    x->p->color = 'r';
                    ent_t = rb_insert_fixup3(ent_t,x->p);
                }
                else {
                    if(z == x->left){
                        z = x;
                        ent_t = right_rotate3(ent_t,z);
                        x = z->p;
                    }


                    x->color = 'b';
                    x->p->color='r';
                    ent_t = left_rotate3(ent_t,x->p);


                }

            }
        }
    }

    return ent_t;
}

rb_Tree_cont *create_element3(rel relations,T3 *ent_t, int cont){
    rb_Tree_cont *punt;

    punt = malloc(sizeof(rb_Tree_cont));
    punt->p = ent_t->nil;
    punt->right = ent_t->nil;
    punt->left = ent_t->nil;
    punt->entities = malloc((strlen(relations.second) + 1) *sizeof(char));
    strcpy(punt->entities,relations.second);
    punt->contatore = cont;
    punt->received = NULL;
    return punt;


}

T3 *rb_insert3(T3 *ent_t,rel relations){
    rb_Tree_cont *z;
    z = create_element3(relations,ent_t,1);

    rb_Tree_cont *y=ent_t->nil;
    rb_Tree_cont *x=ent_t->root;

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
    else if(strcmp(z->entities,y->entities)<0){

        y->left = z;

    }
    else{
        y->right =z;
    }
    z->left = ent_t->nil;
    z->right = ent_t->nil;
    z->color = 'r';

    ent_t = rb_insert_fixup3(ent_t,z);
    return ent_t;
}

T3 *create_rb3(){

    T3 *t;
    t=malloc(sizeof(T3));

    t->nil=malloc(sizeof(rb_Tree_cont));
    t->nil->left = t->nil;
    t->nil->right = t->nil;
    t->nil->p = t->nil;
    t->nil->color = 'b';
    t->nil->contatore = 0;

    t->root = t->nil;
    return t;

}

rb_Tree_cont *tree_minimum3(rb_Tree_cont *x,rb_Tree_cont *nil){

    while(x->left != nil){

        x = x->left;

    }
    return x;
}

rb_Tree_cont *tree_successor3(rb_Tree_cont *x,rb_Tree_cont *nil){
    rb_Tree_cont *y;

    if (x->right != nil){

        return tree_minimum3(x->right,nil);

    }
    y = x->p;
    while( y != nil && x == y->right){

        x = y;
        y = y->p;
    }
    return y;
}

T3 *rb_delete_fixup3(T3 *ent_t,rb_Tree_cont *x){

    rb_Tree_cont *w;

    if(x->color == 'r' || x->p == ent_t->nil){
        x->color = 'b';
    }
    else if(x == x->p->left){
        w = x->p->right;
        if(w->color == 'r'){
            w->color = 'b';
            x->p->color = 'r';
            ent_t = left_rotate3(ent_t,x->p);
            w = x->p->right;
        }
        if(w->left->color == 'b' && w->right->color == 'b'){
            w->color = 'r';

            ent_t = rb_delete_fixup3(ent_t,x->p);
        }
        else{
            if(w->right->color == 'b'){
                w->left->color = 'b';
                w->color = 'r';
                ent_t = right_rotate3(ent_t,w);
                w = x->p->right;
            }
            w->color = x->p->color;
            x->p->color = 'b';
            w->right->color = 'b';

            ent_t = left_rotate3(ent_t,x->p);

        }
    }
    else{
        w = x->p->left;
        if(w->color == 'r'){
            w->color = 'b';
            x->p->color = 'r';
            ent_t = right_rotate3(ent_t,x->p);
            w = x->p->left;
        }
        if(w->right->color == 'b' && w->left->color == 'b'){
            w->color = 'r';

            ent_t = rb_delete_fixup3(ent_t,x->p);
        }
        else{
            if(w->left->color == 'b'){
                w->right->color = 'b';
                w->color = 'r';

                ent_t = left_rotate3(ent_t,w);


                w = x->p->left;
            }
            w->color = x->p->color;
            x->p->color = 'b';
            w->left->color = 'b';
            ent_t = right_rotate3(ent_t,x->p);

        }

    }
    return ent_t;
}

T3 *delete_rb3(T3 *ent_t,rb_Tree_cont *z){
    int cont = 0;

    rb_Tree_cont *x,*y;

    if(z->left == ent_t->nil || z->right == ent_t->nil){

        y = z;}
    else{
        y = tree_successor3(z,ent_t->nil);

    }
    if(y->left != ent_t->nil){
        x = y->left;

    }
    else{
        x = y->right;

    }

    x->p = y->p;


    if(y->p == ent_t->nil){
        ent_t->root = x;

    }
    else if(y == y->p->left){
        y->p->left = x;

    }
    else if(y == y->p->right){
        y->p->right = x;

    }
    if(y != z){
        if(strlen(z->entities) < strlen(y->entities)){
            z->entities = realloc(z->entities,(strlen(y->entities) + 1) *sizeof(char));

        }
        strcpy(z->entities,y->entities);
        z->contatore = y->contatore;
        z->received =y->received;
        cont =1;
    }

    if(y->color == 'b'){
        ent_t = rb_delete_fixup3(ent_t,x);

    }

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

void print_rb3(rb_Tree_cont *root,rb_Tree_cont *nil){

    if(root != nil){

        printf("$$$-> %d ",root->contatore);
        printf("-> %c ",root->color);
        printf("-> %s ||| ",root->entities);
        printf("parent---> %d ",root->p->contatore);
        printf("-> %s ||| ",root->p->entities);
        printf("left---> %d ",root->left->contatore);
        printf("-> %s ||| ",root->left->entities);
        printf("right---> %d ",root->right->contatore);
        printf("-> %s ||| ",root->right->entities);
        printf("\n");
        print_rb3(root->left,nil);
        print_rb3(root->right,nil);
    }
}

rb_Tree_cont *rb_search3(rb_Tree_cont *root,rb_Tree_cont *nil,char *value){

    while(root != nil){
        if(strcmp(value,root->entities) == 0){

            return root;
        }

        else if(strcmp(value,root->entities) < 0)
            root = root->left;
        else
            root = root->right;
    }

    return NULL;

}

void rb_search31(rb_Tree_cont *root,rb_Tree_cont *nil){

    if(root != nil){
        if(root->contatore == 0){
            search_pointer = root;
        }
        rb_search31(root->left,nil);
        rb_search31(root->right,nil);
    }
}

//end of functions



// End of RB Trees' structures and beginning of the algorithms----------------------------------------------------------------------------->



//function to read the input and divide it

rel read_rel(char * x){
    rel relations;

    char *token = strtok(x, " ");

    strcpy(relations.function,token);

    if(strcmp(relations.function,"addent") == 0){

        token = strtok(NULL, " ");
        strcpy(relations.first,token);
    }
    else if(strcmp(relations.function,"addrel") == 0){

        token = strtok(NULL, " ");
        strcpy(relations.first,token);


        token = strtok(NULL, " ");
        strcpy(relations.second,token);


        token = strtok(NULL, " ");
        strcpy(relations.type,token);
    }
    else if(strcmp(relations.function,"delrel") == 0){

        token = strtok(NULL, " ");
        strcpy(relations.first,token);


        token = strtok(NULL, " ");
        strcpy(relations.second,token);


        token = strtok(NULL, " ");
        strcpy(relations.type,token);
    }
    else if(strcmp(relations.function,"delent") == 0){

        token = strtok(NULL, " ");
        strcpy(relations.first,token);
    }

    return relations;
}

//function to add entities

T *addent(rel relations,T *ent_t){
    rb_Tree_entities *check;

    check = rb_search(ent_t->root,ent_t->nil,relations.first);

    if(check == NULL){

        ent_t = rb_insert(ent_t,relations);
    }
    return ent_t;
}

//function to delete all element of a tree

T *delete_all_rb(T *ent_t){

    while(ent_t->root != ent_t->nil){

        ent_t= delete_rb(ent_t,ent_t->root);
    }

    return ent_t;

}

//function to add a relation between two entitiess

puntatori *addrel(rel relations, puntatori *base){
    rb_Tree_relations *z;
    rb_Tree_cont *y;
    rb_Tree_entities *d;

    if(rb_search(base->t->root,base->t->nil,relations.first) != NULL && rb_search(base->t->root,base->t->nil,relations.second) != NULL){

        z =rb_search1(base->t1->root,base->t1->nil,relations.type);

        if(z != NULL ){
            y = rb_search3(z->cont->root,z->cont->nil,relations.second);
            if(y != NULL){

                d= rb_search(y->received->root,y->received->nil,relations.first);

                if(d == NULL){
                    y->received =rb_insert(y->received,relations);

                    y->contatore +=1;

                    if(y->contatore > z->max_cont){
                        z->max_cont  = y->contatore;
                        z->max_tree = delete_all_rb(z->max_tree);
                        z->max_tree->root = z->max_tree->nil;
                        strcpy(relations.first,relations.second);
                        z->max_tree = rb_insert(z->max_tree,relations);

                    }
                    else if(y->contatore == z->max_cont){

                        strcpy(relations.first,relations.second);
                        z->max_tree = rb_insert(z->max_tree,relations);
                    }
                }
            }
            else{

                z->cont = rb_insert3(z->cont,relations);
                y = rb_search3(z->cont->root,z->cont->nil,relations.second);
                y->received = create_rb();
                y->received = rb_insert(y->received,relations);

                if(y->contatore == z->max_cont){

                    strcpy(relations.first,relations.second);
                    z->max_tree = rb_insert(z->max_tree,relations);
                }
            }
        }
        else {
            base->t1 = rb_insert1(base->t1,relations);
            z =rb_search1(base->t1->root,base->t1->nil,relations.type);

            z->cont = create_rb3();
            z->cont = rb_insert3(z->cont,relations);
            y = rb_search3(z->cont->root,z->cont->nil,relations.second);
            y->received = create_rb();
            y->received = rb_insert(y->received,relations);

            z->max_tree =create_rb();
            strcpy(relations.first,relations.second);
            z->max_tree = rb_insert(z->max_tree,relations);
        }
    }

    return base;
}

//function to add all the entity with the max number of received relations to the rb-tree max.

T *insert_new_max(rb_Tree_cont *root,rb_Tree_cont *nil,T  *max,int maxcont){
    rel relations;
    if(root != nil){
        max= insert_new_max(root->left,nil,max,maxcont);

        if(root->contatore == maxcont ){
            strcpy(relations.first,root->entities);
            max = rb_insert(max,relations);
        }
        max = insert_new_max(root->right,nil,max,maxcont);
    }
    return max;
}

//function to delete a relations between entities

puntatori *delrel(rel relations, puntatori *base){
    rb_Tree_relations *z;
    rb_Tree_cont *y;
    rb_Tree_entities *d;

    if(rb_search(base->t->root,base->t->nil,relations.first) != NULL && rb_search(base->t->root,base->t->nil,relations.second) != NULL){
        z =rb_search1(base->t1->root,base->t1->nil,relations.type);
        if(z != NULL){
            y=rb_search3(z->cont->root,z->cont->nil,relations.second);
            if(y != NULL){
                d = rb_search(y->received->root,y->received->nil,relations.first);
                if(d != NULL){
                    y->received = delete_rb(y->received, d);
                    if(y->contatore == 1){
                        z->cont = delete_rb3(z->cont,y);
                        if(z->max_cont == 1){
                            d =rb_search(z->max_tree->root,z->max_tree->nil,relations.second);
                            z->max_tree = delete_rb(z->max_tree,d);

                            if(z->cont->root == z->cont->nil){

                                base->t1 = delete_rb1(base->t1,z);
                            }
                        }
                    }
                    else{
                        if(y->contatore == z->max_cont){
                            y->contatore -=1;
                            d =rb_search(z->max_tree->root,z->max_tree->nil,relations.second);
                            z->max_tree = delete_rb(z->max_tree,d);

                            if(z->max_tree->root == z->max_tree->nil){
                                z->max_cont -=1;
                                insert_new_max(z->cont->root,z->cont->nil,z->max_tree,z->max_cont);
                            }
                        }
                        else{
                            y->contatore -=1;
                        }
                    }
                }
            }
        }
    }

    return base;
}

//function to find the max number of relations received

void tree_max3(rb_Tree_cont *x,rb_Tree_cont *nil){
    if(x != nil){
        tree_max3(x->left,nil);
        if(x->contatore > max_number_relations_received)
            max_number_relations_received = x->contatore;
        tree_max3(x->right,nil);
    }
}

//comp1 to comp5 are function used in the delent function to delete an entity

T3 *comp5(T3 *t3){
    rb_Tree_cont *y;

    search_pointer =NULL;
    rb_search31(t3->root,t3->nil);
    y =search_pointer;

    while(y != NULL){
        t3 = delete_rb3(t3,y);
        search_pointer =NULL;
        rb_search31(t3->root,t3->nil);
        y =search_pointer;
    }
    return t3;
}

T1 *comp4(T1 *third,rb_Tree_relations *root1,int *cont){
    if(root1 != third->nil){
        if(root1->cont->root == root1->cont->nil){
            third = delete_rb1(third,root1);
            *cont+=1;
        }
        else{
            if(*cont == 0)
                third = comp4(third,root1->left,cont);
            if(*cont == 0)
                third = comp4(third,root1->right,cont);
        }
    }
    return third;
}

T3 *comp3(T3 *ent_t,rb_Tree_cont *root,rb_Tree_cont *nil,char *value){
    rb_Tree_entities *d;
    if(root != nil){
        ent_t = comp3(ent_t,root->left,nil,value);

        ent_t = comp3(ent_t,root->right,nil,value);

        d= rb_search(root->received->root,root->received->nil,value);
        if(d != NULL){
            verification =1;
            root->received =delete_rb(root->received,d);
            root->contatore -=1;
        }
    }
    return ent_t;
}

T3 *comp2(char *value,T3 *fourth){
    rb_Tree_cont *y;

    y = rb_search3(fourth->root,fourth->nil,value);
    if(y != NULL){
        verification =1;
        y->received = delete_all_rb(y->received);
        fourth = delete_rb3(fourth,y);
    }

    return fourth;
}

void comp(rb_Tree_relations *root1,rb_Tree_relations *nil, char *value){
    if(root1 != nil){
        verification = 0;

        root1->cont = comp2(value,root1->cont);

        root1->cont = comp3(root1->cont,root1->cont->root,root1->cont->nil,value);

        root1->cont = comp5(root1->cont);

        if(verification == 1){
            root1->max_tree = delete_all_rb(root1->max_tree);
            root1->max_tree->root = root1 ->max_tree->nil;
            max_number_relations_received = 0;
            tree_max3(root1->cont->root,root1->cont->nil);
            root1->max_cont = max_number_relations_received ;
            root1->max_tree = insert_new_max(root1->cont->root,root1->cont->nil,root1->max_tree,root1->max_cont);
        }
        comp(root1->left,nil,value);
        comp(root1->right,nil,value);
    }
}

//end of comp1/comp5


//function to delete an entity

puntatori *delent(rel relations,puntatori *base){
    rb_Tree_entities *check;
    int cont = 1;

    check = rb_search(base->t->root,base->t->nil,relations.first);
    if(check != NULL){
        base->t = delete_rb(base->t,check);
        comp(base->t1->root,base->t1->nil,relations.first);
        while(cont>0){
            cont = 0;
            base->t1 = comp4(base->t1,base->t1->root,&cont);
        }
    }

    return base;
}

//function to print the entity with the max number of received relations, for every relations, in alphabetical order

void print_report(rb_Tree_cont *root,rb_Tree_cont *nil,int max){
    if(root != nil){
        print_report(root->left,nil,max);
        if(root->contatore == max){
            printf(" ");
            fputs(root->entities,stdout);
        }
        print_report(root->right,nil,max);
    }
}

void rp1(T *t, char *value,int maximum){
    if(report_check != 0)
        fputs(" ",stdout);
    else
        report_check +=1;

    fputs(value,stdout);
    print_rb(t->root,t->nil);
    printf(" %d;",maximum);


}

void report(rb_Tree_relations *root,rb_Tree_relations *nil){
    if(root != nil){
        report(root->left,nil);

        rp1(root->max_tree,root->entities,root->max_cont);

        report(root->right,nil);
    }
}

//end of functions used for the report


//function used to choose the right command(addent,addrel,delrel,delent,report,end)

puntatori *chose_command(rel relations,puntatori *base){

    if(strcmp(relations.function,"addent") == 0){
        base->t = addent(relations,base->t);
    }
    else if(strcmp(relations.function,"addrel") == 0){

        base = addrel(relations,base);

    }
    else if(strcmp(relations.function,"delrel") == 0){

        base = delrel(relations,base);

    }
    else if(strcmp(relations.function,"delent") == 0){

        delent(relations,base);

    }
    else if(strcmp(relations.function,"report") == 0){

        if(base->t1->root == base->t1->nil){
            fputs("none",stdout);
        }
        else{
            report_check = 0;
            report(base->t1->root,base->t1->nil);
        }

        fputs("\n",stdout);
    }
    else if(strcmp(relations.function,"end") == 0){
        end=1;
    }

    return base;
}



int main()
{
    puntatori *base = malloc(sizeof(puntatori));
    rel relations;
    char x[100];
    int size;
    base->t = create_rb();
    base->t1 = create_rb1();

    while(end==0){

        fgets(x,100,stdin);
        size = strlen(x)-1;
        x[size] = '\0';

        relations = read_rel(x);

        base = chose_command(relations,base);

    }

    return 0;
}
