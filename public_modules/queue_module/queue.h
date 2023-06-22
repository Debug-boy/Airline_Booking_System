//
// Created by 艾乐乐 on 2023/6/21.
//

#ifndef AIRLINE_BOOKING_SYSTEM_QUEUE_H
#define AIRLINE_BOOKING_SYSTEM_QUEUE_H

#include "linked_list.h"

#ifndef bool_t
#define bool_t unsigned char
#endif

struct queue{
    linked_list_t* list;
};

typedef struct queue queue_t;

queue_t* queue_create();

void queue_init(queue_t* queue);

void queue_destroy(queue_t* queue);

void queue_push(queue_t* queue,void* data);

void queue_pop(queue_t* queue);

void* queue_front(const queue_t* queue);

size_t queue_size(const queue_t* queue);

bool_t queue_is_empty(const queue_t* queue);

#endif //AIRLINE_BOOKING_SYSTEM_QUEUE_H