//
// Created by 艾乐乐 on 2023/6/21.
//

#include "flight_info_class.h"

const char *flight_info_get_code(const flight_info_class_t* this_object){
    return this_object->fight_code;
}

const char *flight_info_get_beginCity(const flight_info_class_t *this_object) {
    return this_object->begin_city;
}

const char *flight_info_get_endCity(const flight_info_class_t *this_object) {
    return this_object->end_city;
}

unsigned int flight_info_get_ticketPrice(const flight_info_class_t *this_object) {
    return this_object->ticket_price;
}

long long flight_info_get_beginStamp(const flight_info_class_t *this_object) {
    return this_object->begin_stamp;
}

long long flight_info_get_endStamp(const flight_info_class_t *this_object) {
    return this_object->end_stamp;
}

aircraft_class_t flight_info_get_aircraftObj(const flight_info_class_t *this_object) {
    aircraft_class_t buffer;
    mem_zero((void*)(&buffer),sizeof(aircraft_class_t));
    memcpy((void*)(&buffer),(void*)(&this_object->aircraft_info),sizeof(aircraft_class_t));
    return buffer;
}

void flight_info_get_set_aircraftObj(const flight_info_class_t *this_object, aircraft_class_t *aircraft_object) {
    if(aircraft_object == NULL){
        return;
    }
    memcpy(aircraft_object,(void*)(&this_object->aircraft_info),sizeof(aircraft_class_t));
}


void flight_info_set_code(flight_info_class_t* this_object,const char* fight_code){
    mem_zero(this_object->fight_code,max_aircraft_code_size);
    strcpy(this_object->fight_code,fight_code);
}

void flight_info_set_beginCity(flight_info_class_t *this_object, const char *begin_city) {
    mem_zero(this_object->begin_city,max_city_name_size);
    strcpy(this_object->begin_city,begin_city);
}

void flight_info_set_endCity(flight_info_class_t *this_object, const char *end_city) {
    mem_zero(this_object->end_city,max_city_name_size);
    strcpy(this_object->end_city,end_city);
}

void flight_info_set_aircraftObj(flight_info_class_t *this_object, aircraft_class_t *aircraft_object) {
    if(aircraft_object == NULL){
        return;
    }
    memcpy(&this_object->aircraft_info,aircraft_object,sizeof(aircraft_class_t));
}

void flight_info_set_ticketPrice(flight_info_class_t *this_object, unsigned int ticket_price) {
    this_object->ticket_price = ticket_price;
}

void flight_info_set_beginStamp(flight_info_class_t *this_object, long long int begin_stamp) {
    this_object->begin_stamp = begin_stamp;
}

void flight_info_set_endStamp(flight_info_class_t *this_object, long long int end_stamp) {
    this_object->end_stamp = end_stamp;
}

flight_info_class_t *
flight_info_construct(const char *fight_code, const char *begin_city, const char *end_city, unsigned int ticket_price,
                      long long int begin_stamp, long long int end_stamp, aircraft_class_t *aircraft) {

    flight_info_class_t *flight_instance = calloc(1,sizeof(flight_info_class_t));

    flight_info_set_code(flight_instance,fight_code);
    flight_info_set_beginCity(flight_instance,begin_city);
    flight_info_set_endCity(flight_instance,end_city);
    flight_info_set_ticketPrice(flight_instance,ticket_price);
    flight_info_set_beginStamp(flight_instance,begin_stamp);
    flight_info_set_endStamp(flight_instance,end_stamp);
    flight_info_set_aircraftObj(flight_instance,aircraft);

    return flight_instance;
}













