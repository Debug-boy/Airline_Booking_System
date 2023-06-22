//
// Created by Administrator on 2023/6/22.
//

#include "flight_mgr_class.h"


void flight_mgr_add(flight_mgr_class_t *this_object, flight_info_class_t *flight_info) {
    linked_list_insert_last(&this_object->flight_info_table,flight_info);
}

flight_info_class_t *flight_mgr_cond_code(flight_mgr_class_t *this_object, const char *flight_code) {
    flight_info_class_t *flight_info = NULL;
    flight_mgr_for_each(this_object,flight_info){
        if(strcmp(flight_info->fight_code,flight_code) == 0){
            return flight_info;
        }
    }
    return NULL;
}

flight_mgr_class_t* flight_mgr_cond_endCity(flight_mgr_class_t* this_object,const char* fight_endCity){

    flight_mgr_class_t *f_mgr = calloc(1,sizeof(flight_mgr_class_t));

    flight_info_class_t *flight_info = NULL;
    flight_mgr_for_each(this_object,flight_info){
        if(strcmp(flight_info->end_city,fight_endCity) == 0){
            flight_mgr_add(f_mgr,flight_info);
        }
    }

    return f_mgr;
}

flight_mgr_class_t* flight_mgr_cond_Stamp(flight_mgr_class_t *this_object,unsigned long long begin_stamp){
    flight_mgr_class_t *f_mgr = calloc(1,sizeof(flight_mgr_class_t));

    flight_info_class_t *flight_info = NULL;
    flight_mgr_for_each(this_object,flight_info){
        if(flight_info->begin_stamp > begin_stamp){
            flight_mgr_add(f_mgr,flight_info);
        }
    }
    return f_mgr;
}

unsigned int flight_mgr_size(flight_mgr_class_t* this_object) {
    return linked_list_size(&this_object->flight_info_table);
}
