//
// Created by Administrator on 2023/6/20.
//


#include "aircraft_class.h"

aircraft_class_t*
aircraft_class_construct(const char *plane_code, unsigned short current_capacity,unsigned short total_capacity) {
    aircraft_class_t *instance_object = (aircraft_class_t*)calloc(1,sizeof(aircraft_class_t));
    strcpy(instance_object->plane_code,plane_code);
    instance_object->current_capacity = current_capacity;
    instance_object->total_capacity = total_capacity;
    linked_list_init(&instance_object->passengers_info);
    return instance_object;
}

PUBLIC_FUNCTION void aircraft_class_destruct(aircraft_class_t* this_object){
    free(this_object);
}

void aircraft_set_planeCode(aircraft_class_t *this_object, const char *plane_code) {
    strcpy(this_object->plane_code,plane_code);
}

void aircraft_set_currentCapacity(aircraft_class_t *this_object, unsigned short current_capacity) {
    this_object->current_capacity = current_capacity;
}

void aircraft_set_totalCapacity(aircraft_class_t *this_object, unsigned short total_capacity) {
    this_object->total_capacity = total_capacity;
}

void aircraft_add_passengers(aircraft_class_t *this_object,client_info_class_t *client_info) {
    if(client_info == NULL){
        return;
    }

    if(this_object->current_capacity == this_object->total_capacity){
        return;
    }

    aircraft_set_currentCapacity(this_object,this_object->current_capacity + 1);

    client_info->ticketed = true;

    linked_list_insert_last(&this_object->passengers_info,client_info);
}

const char *aircraft_get_planeCode(const aircraft_class_t *this_object) {
    return this_object->plane_code;
}

unsigned short aircraft_get_currentCapacity(const aircraft_class_t *this_object) {
    return this_object->current_capacity;
}

unsigned short aircraft_get_residualCapacity(const aircraft_class_t *this_object) {
    if(this_object->total_capacity < this_object->current_capacity){
        return 0;
    }
    return this_object->total_capacity - this_object->current_capacity;
}

linked_list_t aircraft_get_passengersInfo(const aircraft_class_t* this_object) {
    return this_object->passengers_info;
}

PRIVATE_FUNCTION int aircraft_compare_client_name_filed(void* _this_object,void* _compare_name){
    client_info_class_t *this_object = (client_info_class_t*)_this_object;
    const char* compare_name = (const char*)(_compare_name);
    return strcmp(this_object->name,compare_name) == 0;
}

void aircraft_delete_passengers_from_name(aircraft_class_t *this_object, const char *name) {
    linked_list_remove_if(&this_object->passengers_info,aircraft_compare_client_name_filed,(void*)name,true);
}

void aircraft_delete_passengers_from_id(aircraft_class_t *this_object, const char *id) {
    linked_list_remove_if(&this_object->passengers_info,aircraft_compare_client_name_filed,(void*)id,true);
}

void aircraft_delete_passengers_from_seat(aircraft_class_t *this_object, const char *seat) {
    linked_list_remove_if(&this_object->passengers_info,aircraft_compare_client_name_filed,(void*)seat,true);
}

void aircraft_release_passengers(aircraft_class_t *this_object) {
    linked_list_destroy(&this_object->passengers_info,true);
}

client_info_class_t *aircraft_get_clientInfo_from_name(aircraft_class_t *this_object, const char *name) {
    linked_list_get_if(&this_object->passengers_info,aircraft_compare_client_name_filed,(void*)name);
}




