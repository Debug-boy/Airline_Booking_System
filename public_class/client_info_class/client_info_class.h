//
// Created by 艾乐乐 on 2023/6/20.
//

#ifndef AIRLINE_BOOKING_SYSTEM_CLIENT_INFO_CLASS_H
#define AIRLINE_BOOKING_SYSTEM_CLIENT_INFO_CLASS_H

#include "public_class_def.h"
#include <stdlib.h>
#include <string.h>

#ifndef bool_t
#define bool_t unsigned char
#endif

#define max_client_name_size 32
#define max_client_id_size 32
#define max_client_seat_size 16

//航空系统客户信息类
PUBLIC_CLASS client_info_class{

    char name[max_client_name_size];//客户名称

    char id[max_client_id_size];//客户身份编码

    bool_t ticketed;//有订票 1就是有 0就是无

    char seat[max_client_seat_size];//客户座位号
};

typedef struct client_info_class client_info_class_t;

PUBLIC_FUNCTION client_info_class_t* client_info_class_construct(const char* name,const char *id,const char* seat);

PUBLIC_FUNCTION void client_info_class_destruct(client_info_class_t* this_object);

PUBLIC_FUNCTION void client_info_class_set_name(client_info_class_t* this_object,const char* new_name);

PUBLIC_FUNCTION void client_info_class_set_id(client_info_class_t* this_object,const char* new_id);

PUBLIC_FUNCTION void client_info_class_set_seat(client_info_class_t* this_object,const char* new_seat);

PUBLIC_FUNCTION void client_info_class_set_ticketed(client_info_class_t *this_object,bool_t new_ticketed);

PUBLIC_FUNCTION const char* client_info_class_get_name(client_info_class_t* this_object);

PUBLIC_FUNCTION const char* client_info_class_get_id(client_info_class_t* this_object);

PUBLIC_FUNCTION bool_t client_info_class_get_ticketed(client_info_class_t* this_object);

PUBLIC_FUNCTION int client_info_class_equal(client_info_class_t* this_object,client_info_class_t* other_object);

#endif