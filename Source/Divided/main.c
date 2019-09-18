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

#include "entity_rb.h"
#include "relations_rb.h"
#include "counter_rb.h"



//defining all the rb-tree structures and the relations structure

typedef struct puntatori {

    struct T *t;
    struct T1 *t1;


}puntatori;

//end of structures


//defining global variables

int report_check = 0;
int end=0;
int verification =0;
rb_Tree_cont *search_pointer = NULL;
int max_number_relations_received = 0;

//end of global variables



//Beginning of functions-------------------------------------------------------------------------->


//function to visit all the nodes of the count_rb structure

void rb_search31(rb_Tree_cont *root,rb_Tree_cont *nil){

    if(root != nil){
        if(root->contatore == 0){
            search_pointer = root;
        }
        rb_search31(root->left,nil);
        rb_search31(root->right,nil);
    }
}

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
