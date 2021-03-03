#include "linked_list.h"
#include <stdlib.h>
#include <stdio.h>
#include <time.h>

void list_add_node_t(node_t **list, node_t *node_t){
    node_t->next = *list;
    *list = node_t;
}

void list_concat(node_t **left, node_t *right){
    while (*left)
    {
        left = &((*left)->next);    
    }
    *left = right;
}

void quicksort(node_t **list)
{
    if(!*list)
        return;
    
    node_t *pivot = *list;
    int value = pivot->value;
    node_t *p = pivot->next;
    pivot->next = NULL;

    node_t *left = NULL, *right = NULL;
    while (p){
        node_t *n = p;
        p = p->next;
        list_add_node_t(n->value > value ? &right : &left, n);
    }

    quicksort(&left);
    quicksort(&right);

    node_t *result = NULL;
    list_concat(&result, left);
    list_concat(&result, pivot); 
    list_concat(&result, right);
    *list = result;
}

bool list_is_ordered(node_t *list) {
    bool first = true;
    int value;
    while (list) {
        if (first) {
            value = list->value;
            first = false;
        } else {
            if (list->value < value)
                return false;
            value = list->value;
        }
        list = list->next;
    }
    return true;
}

node_t *list_make_node_t(node_t *list, int data){
    node_t *temp = malloc(sizeof(node_t));
    if(!temp){
        return list;
    }
    temp->value = data;
    temp->next = list;
    return temp;
}

void list_free(node_t **list){
    node_t *temp;
    while (*list)
    {
        temp = *list;
        *list = (*list)->next;
        free(temp);
    }
}

void list_display(node_t *list) {
    printf("%s IN ORDER : ", list_is_ordered(list) ? "   " : "NOT");
    while (list) {
        printf("%d ", list->value);
        list = list->next;
    }
    printf("\n");
}

int main(int argc, char **argv) {
    size_t count = 20;
    srand(time(NULL));
    node_t *list = NULL;
    while (count--)
        list = list_make_node_t(list, random() % 1024);

    list_display(list);
    quicksort(&list);
    list_display(list);

    if (!list_is_ordered(list))
        return EXIT_FAILURE;

    list_free(&list);
    return EXIT_SUCCESS;
}  
