//
// Created by 艾乐乐 on 2023/6/21.
//

#ifndef AIRLINE_BOOKING_SYSTEM_LINKED_LIST_H
#define AIRLINE_BOOKING_SYSTEM_LINKED_LIST_H

#include <stdlib.h>

#ifndef bool_t
#define bool_t unsigned char
#endif

typedef void* list_node_element;

// 双向链表节点结构体
typedef struct list_node {
    list_node_element data;       // 存储的数据指针
    struct list_node* prev;       // 前一个节点指针
    struct list_node* next;       // 后一个节点指针
} list_node_t;

// 双向链表结构体
typedef struct {
    list_node_t* head;            // 头节点指针
    list_node_t* tail;            // 尾节点指针
    size_t size;                  // 链表大小
} linked_list_t;

// 创建双向链表
linked_list_t* linked_list_create();

void linked_list_init(linked_list_t* list);

// 销毁双向链表
void linked_list_destroy(linked_list_t* list,bool_t is_release_data);

// 获取链表大小
size_t linked_list_size(const linked_list_t* list);

// 检查链表是否为空
int linked_list_is_empty(const linked_list_t* list);

// 在链表头部插入元素
void linked_list_insert_first(linked_list_t* list, void* data);

// 在链表尾部插入元素
void linked_list_insert_last(linked_list_t* list, void* data);

// 在指定位置插入元素
void linked_list_insert_at(linked_list_t* list, size_t index, void* data);

// 删除链表头部元素
void linked_list_remove_first(linked_list_t* list,bool_t is_release_data);

// 删除链表尾部元素
void linked_list_remove_last(linked_list_t* list,bool_t is_release_data);

// 删除指定位置的元素
void linked_list_remove_at(linked_list_t* list, size_t index,bool_t is_release_data);

//条件移除节点
size_t linked_list_remove_if(linked_list_t* list, int (*cond_callback)(void* data,void *cond),void* cond_data_filed,bool_t is_release_data);

// 获取链表头部元素
list_node_element linked_list_get_first(const linked_list_t* list);

// 获取链表下一个元素
list_node_element linked_list_get_next(const linked_list_t *list,const list_node_t *node);

// 获取链表尾部元素
list_node_element linked_list_get_last(const linked_list_t* list);

// 获取指定位置的元素
list_node_element linked_list_get_at(const linked_list_t* list, size_t index);

//条件获取元素
list_node_element linked_list_get_if(const linked_list_t* list,int (*cond_callback)(list_node_element data,void* cond_data),void* cond_data_filed);

//判断节点是否安全不为空
#define linked_list_get_node_safe(node) ((node) != NULL)

//宏迭代获取每个节点元素
#define linked_list_for_each(list, node) \
    for ((node) = ((list)->head); \
               linked_list_get_node_safe(node) ; \
               (node) = (node)->next)

#define linked_list_rev_each(list, node) \
    for ((node) = ((list)->tail); \
               linked_list_get_node_safe(node) ; \
               (node) = (node)->prev)
#endif