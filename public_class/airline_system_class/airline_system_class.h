//
// Created by 艾乐乐 on 2023/6/20.
//

#ifndef AIRLINE_BOOKING_SYSTEM_AIR_SYSTEM_H
#define AIRLINE_BOOKING_SYSTEM_AIR_SYSTEM_H

#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include "socket.h"
#include "thread_pool.h"
#include "public_class_def.h"
#include "flight_mgr_class.h"

enum airline_sys_exception_code{
    success = 0,
    sock_err_create ,
    sock_err_bind ,
    sock_err_listen ,
};

PUBLIC_CLASS airline_system_class{

    //LPWSADATA sock_init_handle;
    //socket_info_t sock_info;
    //thread_pool_t th_pool;

    int running;
    flight_mgr_class_t flight_manager;
    client_info_class_t *local_user;
    flight_mgr_class_t *local_user_flight_mgr;
};

typedef struct airline_system_class airline_system_class_t;
typedef struct airline_system_class_t asc_t;

//PUBLIC_FUNCTION enum airline_sys_exception_code airline_system_init(airline_system_class_t *this_object);
//PUBLIC_FUNCTION void airline_system_start(airline_system_class_t* this_object);


PUBLIC_FUNCTION airline_system_class_t* airline_system_construct();

PUBLIC_FUNCTION void airline_system_start(airline_system_class_t* this_object);

PUBLIC_FUNCTION void airline_system_destruct(airline_system_class_t* this_object);

#endif
