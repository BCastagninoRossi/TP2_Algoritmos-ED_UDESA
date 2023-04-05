#include "tp2.h"
#include <stdlib.h>
#include <stdbool.h>

struct node;
typedef struct node node_t;

struct node {
    void* value;
    node_t* next;
    node_t* prev;
};

struct list {
    node_t* head;
    node_t* tail;
    size_t size;
};

struct list_iter {
    list_t* list;
    node_t* curr;
};

list_t *list_new(){
    list_t* new_list = malloc(sizeof(list_t));
    if(new_list){
        new_list->head = NULL;
        new_list->tail = NULL;
        new_list->size = 0;
    }
    return new_list;
}

size_t list_length(const list_t *list){
    if(list){
        size_t len = list->size;
        return len;
    }
    return 0;
}

bool list_is_empty(const list_t *list){
    if(!list){
        return false;
    }
    if(list->size==0){
        return true;
    }
    return false;
}

bool list_insert_head(list_t *list, void *value){
    if(!list){
        return false;
    }
    node_t* new_head = malloc(sizeof(node_t));
    if (!new_head){
        return false;
    }
    list->head = new_head;
    list->head->value = value;

    return true;
}

bool list_insert_tail(list_t *list, void *value){
    if (!list){
        return false;
    }
    node_t* new_tail = malloc(sizeof(node_t));
    if(!new_tail){
        return false;
    }
    list->tail = new_tail;
    list->tail->value = value;
    list->tail->next = NULL; // ESTO ESTÁ MAL, CLARAMENTE EL PREV DEL TAIL TIENE QUE SER EL ANTEÚLTIMO ELEMENTO DE LA LISTA
    list->tail->prev = NULL;
    return true;;
}

void *list_peek_head(const list_t *list){
    return NULL;
}

void *list_peek_tail(const list_t *list){
    return NULL;
}

void *list_pop_head(list_t *list){
    return NULL;
}

void *list_pop_tail(list_t *list){
    return NULL;
}

void list_destroy(list_t *list, void destroy_value(void *)){
    return;
}

list_iter_t *list_iter_create_head(list_t *list){
    return NULL;
}

list_iter_t *list_iter_create_tail(list_t *list){
    return NULL;
}

bool list_iter_forward(list_iter_t *iter){
    return false;
}

bool list_iter_backward(list_iter_t *iter){
    return false;
}

void *list_iter_peek_current(const list_iter_t *iter){
    return NULL;
}

bool list_iter_at_last(const list_iter_t *iter){
    return false;
}

bool list_iter_at_first(const list_iter_t *iter){
    return false;
}

void list_iter_destroy(list_iter_t *iter){
    return;
}

bool list_iter_insert_after(list_iter_t *iter, void *value){
    return false;
}

bool list_iter_insert_before(list_iter_t *iter, void *value){
    return false;
}

void *list_iter_delete(list_iter_t *iter){
    return NULL;
}