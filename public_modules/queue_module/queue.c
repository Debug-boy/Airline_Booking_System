//
// Created by 艾乐乐 on 2023/6/21.
//

#include "queue.h"

queue_t* queue_create() {
    queue_t* queue = (queue_t*)malloc(sizeof(queue_t));
    if (queue != NULL) {
        queue->list = linked_list_create();
    }
    return queue;
}

void queue_destroy(queue_t* queue) {
    if (queue != NULL) {
        linked_list_destroy(queue->list,0);
        free(queue);
    }
}

void queue_push(queue_t* queue, void* data) {
    if (queue != NULL) {
        linked_list_insert_last(queue->list, data);
    }
}

void queue_pop(queue_t* queue) {
    if (queue != NULL && !linked_list_is_empty(queue->list)) {
        linked_list_remove_first(queue->list,0);
    }
}

void* queue_front(const queue_t* queue) {
    if (queue != NULL && !linked_list_is_empty(queue->list)) {
        return linked_list_get_first(queue->list);
    }
    return NULL;
}

size_t queue_size(const queue_t* queue) {
    if (queue != NULL) {
        return linked_list_size(queue->list);
    }
    return 0;
}

bool_t queue_is_empty(const queue_t* queue) {
    if (queue != NULL) {
        return linked_list_is_empty(queue->list);
    }
    return 1;
}

void queue_init(queue_t *queue) {
    if(queue != NULL){
        linked_list_init(queue->list);
    }
}
