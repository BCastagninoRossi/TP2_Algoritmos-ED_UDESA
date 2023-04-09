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
    node_t* temp = NULL;

    if(!list_is_empty(list)){
        temp = list->head;
    }

    list->head = new_head;
    list->head->value = value;
    list->head->next = temp;
    list->head->prev = NULL;
    list->size ++;

    if(list->size == 1){
        list->tail = list->head;
    }else{
        list->head->next->prev = list->head;
    }
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
    node_t* temp = NULL;

    if(!list_is_empty(list)){
        temp = list->tail;
    }

    list->tail = new_tail;
    list->tail->value = value;
    list->tail->next = NULL;
    list->tail->prev = temp;
    list->size ++;
    if(list->size == 1){
        list->head = list->tail;
    } else {
        list->tail->prev->next = list->tail;
    }
    return true;
}


void *list_peek_head(const list_t *list){
    if(!list || list_is_empty(list)){
        return NULL;
    }
    return list->head->value;
}

void *list_peek_tail(const list_t *list){
    if(!list || list_is_empty(list)){
        return NULL;
    }
    return list->tail->value;
}

void *list_pop_head(list_t *list){
    if(!list || list->size == 0){
        return NULL;
    }
    void* data = list->head->value;
    node_t* tmp = list->head;
    if(list->size == 1){
        list->head = NULL;
        list->tail = NULL;
    }else{
        list->head = list->head->next;
        list->head->prev = NULL;
    }
    list->size--;
    free(tmp);
    tmp = NULL;
    return data;
}

void *list_pop_tail(list_t *list){
    if(!list || list->size == 0){
        return NULL;
    }
    void* data = list->tail->value;
    node_t* tmp = list->tail;
    if(list->size == 1){
        list->head = NULL;
        list->tail = NULL;
    }else{
        list->tail = list->tail->prev;
        list->tail->next = NULL;
    }
    list->size--;
    free(tmp);
    tmp = NULL;
    return data;
}

void list_destroy(list_t *list, void destroy_value(void *)) {
    if (!list) {
        return;
    }

    if (list_is_empty(list)) {
        free(list);
        return;
    }

    list_iter_t* iterator = list_iter_create_head(list);
    while(iterator) {
        node_t *temp = iterator->curr;
        bool status = list_iter_forward(iterator);
        if(destroy_value){
            destroy_value(temp->value);
        }
        if (!status) {
            break;
        }
    }
    free(iterator);
    list->head = NULL;
    list->tail = NULL;
    list->size = 0;
    free(list);
}



list_iter_t *list_iter_create_head(list_t *list){
    if(!list || list_is_empty(list)){
        return NULL;
    }
    list_iter_t* new_iter = malloc(sizeof(list_iter_t));
    if (!new_iter){
        return NULL;
    }
    new_iter->list = list;
    new_iter->curr = list->head;
    return new_iter;
}

list_iter_t *list_iter_create_tail(list_t *list){
    if(!list|| list_is_empty(list)){
        return NULL;
    }
    list_iter_t* new_iter = malloc(sizeof(list_iter_t));
    if (!new_iter){
        return NULL;
    }
    new_iter->list = list;
    new_iter->curr = list->tail;
    return new_iter;
}

bool list_iter_forward(list_iter_t *iter){
    if(!iter || (iter->curr->next) == NULL){
        return false;
    }
    iter->curr = iter->curr->next;
    return true;
}

bool list_iter_backward(list_iter_t *iter){
    if(!iter || (iter->curr->prev) == NULL){
        return false;
    }
    iter->curr = iter->curr->prev;
    return true;
}

void *list_iter_peek_current(const list_iter_t *iter){
    if(!iter||!(iter->list)||!(iter->curr)){
    return NULL;
    }
    return iter->curr->value;
}

bool list_iter_at_last(const list_iter_t *iter){
    if(!iter||!(iter->list)||!(iter->curr)){
    return false;
    }
    if(iter->curr == iter->list->tail){
        return true;
    }
    return false;
}

bool list_iter_at_first(const list_iter_t *iter){
    if(!iter||!(iter->list)||!(iter->curr)){
    return false;
    }
    if(iter->curr == iter->list->head){
        return true;
    }
    return false;
}

void list_iter_destroy(list_iter_t *iter){
    if(iter){
        iter->curr = NULL;
        iter->list = NULL;
        free(iter);
    }
    return;
}

bool list_iter_insert_after(list_iter_t *iter, void *value){
    if(!iter||!(iter->curr)||!(iter->list)){
    return false;
    }
    node_t* new_node = malloc(sizeof(node_t));
    if (!new_node){
        return false;
    }
    new_node->value = value;
    new_node->next = iter->curr->next;
    new_node->prev = iter->curr;
    if(iter->curr->next){
        iter->curr->next->prev = new_node;
        }
    iter->curr->next = new_node;
    iter->list->size++;
    return true;
}

bool list_iter_insert_before(list_iter_t *iter, void *value){
    if(!iter||!(iter->curr)||!(iter->list)){
    return false;
    }
    node_t* new_node = malloc(sizeof(node_t));
    if (!new_node){
        return false;
    }
    return false;
    new_node->value = value;
    new_node->next = iter->curr;
    new_node->prev = iter->curr->prev;
    if(iter->curr->prev){
        iter->curr->prev->next = new_node;
    }
    iter->curr->prev = new_node;
    iter->list->size ++;
    return true;
}

void *list_iter_delete(list_iter_t *iter){
    if(!iter||!(iter->curr)||!(iter->list)||list_is_empty(iter->list)){
    return NULL;
    }
    void* value = iter->curr->value;
    iter->curr->prev->next = iter->curr->next;
    iter->curr->next->prev = iter->curr->prev;
    if(iter->curr->next){
        iter->curr = iter->curr->next;
    }else{iter->curr = iter->curr->prev;}
    iter->list->size --;
    return value;
}
