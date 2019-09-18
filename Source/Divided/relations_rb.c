#include "relations_rb.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>


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

