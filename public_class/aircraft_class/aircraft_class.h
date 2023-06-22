//
// Created by 艾乐乐 on 2023/6/20.
//

#ifndef AIRLINE_BOOKING_SYSTEM_AIRCRAFT_CLASS_H
#define AIRLINE_BOOKING_SYSTEM_AIRCRAFT_CLASS_H

#include <string.h>
#include "public_class_def.h"
#include "client_info_class.h"

#include "linked_list.h"

#define max_aircraft_code_size 16

#ifndef true
#define true 1
#endif

#ifndef false
#define false 0
#endif

/*
航空公司: 中国国际航空公司 (Airline Code: CA)
航班号: CA1234
飞机型号: 波音737-800 (Aircraft Code: B738)
最大载员人数: 189人

航空公司: 中国南方航空公司 (Airline Code: CZ)
航班号: CZ5678
飞机型号: 空中客车A320 (Aircraft Code: A320)
最大载员人数: 180人

航空公司: 中国东方航空公司 (Airline Code: MU)
航班号: MU9012
飞机型号: 波音777-300ER (Aircraft Code: B777-300ER)
最大载员人数: 365人
 */

//飞机类
PUBLIC_CLASS aircraft_class{
    char plane_code[max_aircraft_code_size];//飞机号

    unsigned short current_capacity;//当前载员
    unsigned short total_capacity;//总共可载员

    linked_list_t passengers_info;//当前航班的乘客信息 client_info_class.h
};

typedef struct aircraft_class aircraft_class_t;

PUBLIC_FUNCTION aircraft_class_t*
aircraft_class_construct(const char* plane_code,unsigned short current_capacity,unsigned short total_capacity);

PUBLIC_FUNCTION void aircraft_class_destruct(aircraft_class_t* this_object);

PUBLIC_FUNCTION void aircraft_set_planeCode(aircraft_class_t* this_object,const char* plane_code);

PUBLIC_FUNCTION void aircraft_set_currentCapacity(aircraft_class_t* this_object,unsigned short current_capacity);

PUBLIC_FUNCTION void aircraft_set_totalCapacity(aircraft_class_t* this_object,unsigned short total_capacity);

PUBLIC_FUNCTION void aircraft_set_passengersInfo(aircraft_class_t* this_object);

PUBLIC_FUNCTION void aircraft_add_passengers(aircraft_class_t *this_object,client_info_class_t *client_info);

//通过用户名查找称来删除该用户信息
PUBLIC_FUNCTION void aircraft_delete_passengers_from_name(aircraft_class_t* this_object,const char* name);

PUBLIC_FUNCTION void aircraft_delete_passengers_from_id(aircraft_class_t* this_object,const char* id);

PUBLIC_FUNCTION void aircraft_delete_passengers_from_seat(aircraft_class_t* this_object,const char* seat);

PUBLIC_FUNCTION void aircraft_release_passengers(aircraft_class_t* this_object);

//获取航班号
PUBLIC_FUNCTION const char* aircraft_get_fightCode(const aircraft_class_t* this_object);

//获取飞机代码
PUBLIC_FUNCTION const char* aircraft_get_planeCode(const aircraft_class_t* this_object);

//获取当前已使用座位
PUBLIC_FUNCTION unsigned short aircraft_get_currentCapacity(const aircraft_class_t* this_object);

//获取剩余座位容量
PUBLIC_FUNCTION unsigned short aircraft_get_residualCapacity(const aircraft_class_t* this_object);

//获取当前飞机的所有乘客信息
PUBLIC_FUNCTION linked_list_t aircraft_get_passengersInfo(const aircraft_class_t* this_object);

//通过字段返回乘客信息
PUBLIC_FUNCTION client_info_class_t* aircraft_get_clientInfo_from_name(aircraft_class_t* this_object,const char* name);

//迭代遍历乘客信息
#ifndef aircraft_for_each_passengers

#define aircraft_for_each_passengers(this_object,client_info_object) \
    for(                                                             \
        list_node_t *iter = (this_object)->passengers_info.head;          \
        (iter != NULL) && ((client_info_object) = (client_info_class_t*)(iter->data)) ; \
        ( (iter = iter->next) ) \
    )                                                                \

#endif

#endif //AIRLINE_BOOKING_SYSTEM_AIRCRAFT_CLASS_H
