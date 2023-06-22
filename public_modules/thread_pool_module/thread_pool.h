//
// Created by 艾乐乐 on 2023/6/22.
//

#ifndef AIRLINE_BOOKING_SYSTEM_THREAD_POOL_H
#define AIRLINE_BOOKING_SYSTEM_THREAD_POOL_H

#include <pthread.h>
#include "queue.h"

#ifndef true
#define true 1
#endif

#ifndef false
#define false 0
#endif

typedef void* (*task_fun_t)(void*);

typedef struct task{
    task_fun_t f;  // 任务函数指针
    void* arg;  // 任务参数
} task_t;

typedef struct {
    int num_threads;  // 线程数量
    int shutdown;  // 线程池关闭标志
    pthread_t* threads;  // 线程数组
    pthread_mutex_t mutex;  // 互斥锁
    pthread_cond_t cond;  // 条件变量
    queue_t* tasks;  // 任务队列
} thread_pool_t;

// 初始化线程池
void thread_pool_init(thread_pool_t* pool, int num_threads);

// 销毁线程池
void thread_pool_destroy(thread_pool_t* pool);

// 向线程池提交任务
void thread_pool_push(thread_pool_t* pool, void* (*task)(void*), void* arg);


#endif //AIRLINE_BOOKING_SYSTEM_THREAD_POOL_H
