//
// Created by 艾乐乐 on 2023/6/21.
//

#ifndef AIRLINE_BOOKING_SYSTEM_FLIGHT_INFO_CLASS_H
#define AIRLINE_BOOKING_SYSTEM_FLIGHT_INFO_CLASS_H

#include "public_class_def.h"
#include "aircraft_class.h"

#define max_city_name_size 16

PUBLIC_CLASS flight_info_class{
    char fight_code[max_aircraft_code_size];//航班号
    char begin_city[max_city_name_size];
    char end_city[max_city_name_size];
    unsigned int ticket_price;
    long long begin_stamp;
    long long end_stamp;
    aircraft_class_t aircraft_info;//一个航班号对应一个 飞机信息
};

typedef struct flight_info_class flight_info_class_t;

PUBLIC_FUNCTION flight_info_class_t* flight_info_construct(const char* fight_code,
                                                           const char* begin_city,const char* end_city,
                                                           unsigned int ticket_price,
                                                           long long begin_stamp,long long end_stamp,
                                                           aircraft_class_t* aircraft);

PUBLIC_FUNCTION const char* flight_info_get_code(const flight_info_class_t* this_object);

PUBLIC_FUNCTION const char* flight_info_get_beginCity(const flight_info_class_t* this_object);

PUBLIC_FUNCTION const char* flight_info_get_endCity(const flight_info_class_t* this_object);

PUBLIC_FUNCTION unsigned int flight_info_get_ticketPrice(const flight_info_class_t* this_object);

PUBLIC_FUNCTION long long flight_info_get_beginStamp(const flight_info_class_t* this_object);

PUBLIC_FUNCTION long long flight_info_get_endStamp(const flight_info_class_t* this_object);

PUBLIC_FUNCTION aircraft_class_t flight_mgr_get_aircraftObj(const flight_info_class_t* this_object);

PUBLIC_FUNCTION void flight_mgr_get_set_aircraftObj(const flight_info_class_t *this_object, aircraft_class_t *aircraft_object);

PUBLIC_FUNCTION void flight_info_set_code(flight_info_class_t* this_object,const char* fight_code);

PUBLIC_FUNCTION void flight_info_set_beginCity(flight_info_class_t* this_object,const char* begin_city);

PUBLIC_FUNCTION void flight_info_set_endCity(flight_info_class_t* this_object,const char* end_city);

PUBLIC_FUNCTION void flight_info_set_aircraftObj(flight_info_class_t* this_object,aircraft_class_t* aircraft_object);

PUBLIC_FUNCTION void flight_info_set_ticketPrice(flight_info_class_t* this_object,unsigned int ticket_price);

PUBLIC_FUNCTION void flight_info_set_beginStamp(flight_info_class_t* this_object,long long begin_stamp);

PUBLIC_FUNCTION void flight_info_set_endStamp(flight_info_class_t* this_object,long long end_stamp);

#endif //AIRLINE_BOOKING_SYSTEM_FLIGHT_INFO_CLASS_H
