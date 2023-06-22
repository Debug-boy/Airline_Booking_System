//
// Created by 艾乐乐 on 2023/6/22.
//

#include "thread_pool.h"


// 线程池工作线程函数
void* thread_pool_worker(void* arg) {
    thread_pool_t* pool = (thread_pool_t*)arg;

    while (true) {
        // 加锁
        pthread_mutex_lock(&(pool->mutex));

        // 如果任务队列为空且线程池未被销毁，则等待任务到来
        while (queue_is_empty(pool->tasks) && !(pool->shutdown)) {
            pthread_cond_wait(&(pool->cond), &(pool->mutex));
        }

        // 如果线程池已经被销毁，则退出循环
        if (pool->shutdown) {
            pthread_mutex_unlock(&(pool->mutex));
            pthread_exit(NULL);
        }

        // 获取任务和参数
        task_t* task = (task_t*)queue_front(pool->tasks);
        task_fun_t task_f = task->f;
        void* task_arg = task->arg;

        // 执行任务
        task_f(task_arg);

        // 任务完成，释放内存
        free(task);

        // 出队
        queue_pop(pool->tasks);

        // 解锁
        pthread_mutex_unlock(&(pool->mutex));
    }

    pthread_exit(NULL);
}

// 初始化线程池
void thread_pool_init(thread_pool_t* pool, int num_threads) {
    // 初始化线程池属性
    pool->num_threads = num_threads;
    pool->shutdown = 0;

    // 初始化互斥锁和条件变量
    pthread_mutex_init(&(pool->mutex), NULL);
    pthread_cond_init(&(pool->cond), NULL);

    // 创建线程数组
    pool->threads = (pthread_t*)malloc(num_threads * sizeof(pthread_t));

    // 初始化任务队列
    pool->tasks = (queue_t*)malloc(sizeof(queue_t));
    queue_init(pool->tasks);

    // 创建工作线程
    for (int i = 0; i < num_threads; ++i) {
        pthread_create(&(pool->threads[i]), NULL, thread_pool_worker, (void*)pool);
    }
}

// 销毁线程池
void thread_pool_destroy(thread_pool_t* pool) {
    // 设置线程池关闭标志
    pool->shutdown = 1;

    // 唤醒所有等待的线程
    pthread_cond_broadcast(&(pool->cond));

    // 等待工作线程退出
    for (int i = 0; i < pool->num_threads; ++i) {
        pthread_join(pool->threads[i], NULL);
    }

    // 释放线程数组和任务队列
    free(pool->threads);
    queue_destroy(pool->tasks);

    // 销毁互斥锁和条件变量
    pthread_mutex_destroy(&(pool->mutex));
    pthread_cond_destroy(&(pool->cond));
}

// 向线程池提交任务
void thread_pool_push(thread_pool_t* pool, void* (*task)(void*), void* arg) {
    // 创建任务结构体
    task_t* new_task = (task_t*)malloc(sizeof(task_t));
    new_task->f = task;
    new_task->arg = arg;

    // 将任务入队
    queue_push(pool->tasks, new_task);

    // 唤醒一个等待的线程
    pthread_cond_signal(&(pool->cond));
}
