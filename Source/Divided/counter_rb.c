#include "counter_rb.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>


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


//end of functions

