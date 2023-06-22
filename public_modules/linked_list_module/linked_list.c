//
// Created by 艾乐乐 on 2023/6/21.
//


#include "linked_list.h"

// 创建双向链表
linked_list_t* linked_list_create() {
    linked_list_t* list = (linked_list_t*)malloc(sizeof(linked_list_t));
    if (list != NULL) {
        list->head = NULL;
        list->tail = NULL;
        list->size = 0;
    }
    return list;
}

void linked_list_init(linked_list_t *list) {
    if(list != NULL){
        list->head = NULL;
        list->tail = NULL;
        list->size = 0;
    }
}

// 销毁双向链表
void linked_list_destroy(linked_list_t* list,bool_t is_release_data) {
    if (list != NULL) {
        list_node_t* current = list->head;
        while (current != NULL) {
            list_node_t* next = current->next;

            if(is_release_data){
                free(current->data);
            }

            free(current);
            current = next;
        }
        free(list);
    }
}

// 获取链表大小
size_t linked_list_size(const linked_list_t* list) {
    return (list != NULL) ? list->size : 0;
}

// 检查链表是否为空
int linked_list_is_empty(const linked_list_t* list) {
    return (list != NULL) ? (list->size == 0) : 1;
}

// 在链表头部插入元素
void linked_list_insert_first(linked_list_t* list, void* data) {
    if (list != NULL) {
        list_node_t* new_node = (list_node_t*)malloc(sizeof(list_node_t));
        if (new_node != NULL) {
            new_node->data = data;
            new_node->prev = NULL;
            new_node->next = list->head;

            if (list->head != NULL) {
                list->head->prev = new_node;
            } else {
                list->tail = new_node;
            }

            list->head = new_node;
            list->size++;
        }
    }
}

// 在链表尾部插入元素
void linked_list_insert_last(linked_list_t* list, void* data) {
    if (list != NULL) {
        list_node_t* new_node = (list_node_t*)malloc(sizeof(list_node_t));
        if (new_node != NULL) {
            new_node->data = data;
            new_node->prev = list->tail;
            new_node->next = NULL;

            if (list->tail != NULL) {
                list->tail->next = new_node;
            } else {
                list->head = new_node;
            }

            list->tail = new_node;
            list->size++;
        }
    }
}

// 在指定位置插入元素
void linked_list_insert_at(linked_list_t* list, size_t index, void* data) {
    if (list != NULL && index <= list->size) {
        if (index == 0) {
            linked_list_insert_first(list, data);
        } else if (index == list->size) {
            linked_list_insert_last(list, data);
        } else {
            list_node_t* current = list->head;
            size_t i = 0;

            while (current != NULL && i < index) {
                current = current->next;
                i++;
            }

            if (current != NULL) {
                list_node_t* new_node = (list_node_t*)malloc(sizeof(list_node_t));
                if (new_node != NULL) {
                    new_node->data = data;
                    new_node->prev = current->prev;
                    new_node->next = current;

                    current->prev->next = new_node;
                    current->prev = new_node;
                    list->size++;
                }
            }
        }
    }
}

// 删除链表头部元素
void linked_list_remove_first(linked_list_t* list,bool_t is_release_data) {
    if (list != NULL && list->head != NULL) {
        list_node_t* node_to_remove = list->head;
        list->head = list->head->next;

        if (list->head != NULL) {
            list->head->prev = NULL;
        } else {
            list->tail = NULL;
        }

        if(is_release_data){
            free(node_to_remove->data);
        }
        free(node_to_remove);
        list->size--;
    }
}

// 删除链表尾部元素
void linked_list_remove_last(linked_list_t* list,bool_t is_release_data) {
    if (list != NULL && list->tail != NULL) {
        list_node_t* node_to_remove = list->tail;
        list->tail = list->tail->prev;

        if (list->tail != NULL) {
            list->tail->next = NULL;
        } else {
            list->head = NULL;
        }
        if(is_release_data){
            free(node_to_remove->data);
        }
        free(node_to_remove);
        list->size--;
    }
}

// 删除指定位置的元素
void linked_list_remove_at(linked_list_t* list, size_t index,bool_t is_release_data) {
    if (list != NULL && index < list->size) {
        if (index == 0) {
            linked_list_remove_first(list,is_release_data);
        } else if (index == list->size - 1) {
            linked_list_remove_last(list,is_release_data);
        } else {
            list_node_t* current = list->head;
            size_t i = 0;

            while (current != NULL && i < index) {
                current = current->next;
                i++;
            }

            if (current != NULL) {
                current->prev->next = current->next;
                current->next->prev = current->prev;

                if(is_release_data){
                    free(current->data);
                }

                free(current);
                list->size--;
            }
        }
    }
}

// 获取链表头部元素
void* linked_list_get_first(const linked_list_t* list) {
    return (list != NULL && list->head != NULL) ? list->head->data : NULL;
}

// 获取链表下一个元素
list_node_element linked_list_get_next(const linked_list_t *list,const list_node_t *node) {\
    if(list == NULL || list->head == NULL || node == NULL){
        return NULL;
    }
    return node->next;
}

// 获取链表尾部元素
void* linked_list_get_last(const linked_list_t* list) {
    return (list != NULL && list->tail != NULL) ? list->tail->data : NULL;
}

// 获取指定位置的元素
void* linked_list_get_at(const linked_list_t* list, size_t index) {
    if (list != NULL && index < list->size) {
        if (index == 0) {
            return linked_list_get_first(list);
        } else if (index == list->size - 1) {
            return linked_list_get_last(list);
        } else {
            list_node_t* current = list->head;
            size_t i = 0;

            while (current != NULL && i < index) {
                current = current->next;
                i++;
            }

            if (current != NULL) {
                return current->data;
            }
        }
    }

    return NULL;
}

size_t linked_list_remove_if(linked_list_t* list,
                             int (*cond_callback)(void* data_object,void* cond_data),
                             void* cond_data_filed,bool_t is_release_data) {
    if (list == NULL || cond_callback == NULL) {
        return 0;
    }

    if(list->size <= 0){
        return 0;
    }

    size_t count = 0;
    list_node_t* current = list->head;
    list_node_t* prev = NULL;

    while (current != NULL) {
        if (cond_callback(current->data,cond_data_filed)) {
            list_node_t* next = current->next;

            if (prev == NULL) {
                // 移除头节点
                list->head = next;
            } else {
                // 移除中间或尾节点
                prev->next = next;
            }

            if (next == NULL) {
                // 更新尾节点
                list->tail = prev;
            }

            if(is_release_data){
                free(current->data);
            }

            free(current);
            count++;
            current = next;
        } else {
            prev = current;
            current = current->next;
        }
    }

    return count;
}

list_node_element linked_list_get_if(const linked_list_t* list,
                                     int (*cond_callback)(list_node_element data,void* cond_data),
                                     void* cond_data_filed) {
    if(list == NULL || linked_list_get_first(list) == NULL){
        return NULL;
    }

    if(cond_callback == NULL){
        return NULL;
    }

    list_node_t* iter_node = NULL;

    linked_list_for_each(list,iter_node){
        if(cond_callback(iter_node->data,cond_data_filed)){
            return iter_node->data;
        }
    }
    return NULL;
}
