//
// Created by 艾乐乐 on 2023/6/22.
//

#ifndef AIRLINE_BOOKING_SYSTEM_FLIGHT_MGR_CLASS_H
#define AIRLINE_BOOKING_SYSTEM_FLIGHT_MGR_CLASS_H

#include "public_class_def.h"
#include "flight_info_class.h"

PUBLIC_CLASS flight_mgr_class{
    linked_list_t flight_info_table;
};

typedef struct flight_mgr_class flight_mgr_class_t;

PUBLIC_FUNCTION void flight_mgr_add(flight_mgr_class_t *this_object,flight_info_class_t* flight_info);

PUBLIC_FUNCTION flight_info_class_t* flight_mgr_cond_code(flight_mgr_class_t* this_object,const char* flight_code);

PUBLIC_FUNCTION unsigned int flight_mgr_size(flight_mgr_class_t* this_object);

PUBLIC_FUNCTION flight_mgr_class_t* flight_mgr_cond_endCity(flight_mgr_class_t* this_object,const char* fight_endCity);

PUBLIC_FUNCTION flight_mgr_class_t* flight_mgr_cond_Stamp(flight_mgr_class_t *this_object,unsigned long long begin_stamp);

//迭代遍航班信息
#ifndef flight_mgr_for_each

#define flight_mgr_for_each(this_object,flight_info_object) \
    for(                                                             \
        list_node_t *iter = (this_object)->flight_info_table.head;          \
        (iter != NULL) && ((flight_info_object) = (flight_info_class_t*)(iter->data)) ; \
        ( (iter = iter->next) ) \
    )                                                                \

#endif



#endif