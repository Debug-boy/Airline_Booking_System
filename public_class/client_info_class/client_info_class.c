//
// Created by 艾乐乐 on 2023/6/20.
//

#include "client_info_class.h"

PUBLIC_FUNCTION
client_info_class_t* client_info_class_construct(const char *name, const char *id, const char *seat) {
    client_info_class_t* instance_object = calloc(1,sizeof(client_info_class_t));
    strcpy(instance_object->name, name);
    strcpy(instance_object->id, id);
    strcpy(instance_object->seat, seat);
    return instance_object;
}

PUBLIC_FUNCTION
void client_info_class_destruct(client_info_class_t* this_object){
    free(this_object);
}

PUBLIC_FUNCTION
void client_info_class_set_name(struct client_info_class* this_object,const char *new_name) {
    strcpy(this_object->name,new_name);
}

PUBLIC_FUNCTION
void client_info_class_set_id(struct client_info_class *this_object, const char *new_id) {
    strcpy(this_object->id,new_id);
}

PUBLIC_FUNCTION
void client_info_class_set_seat(struct client_info_class *this_object, const char *new_seat) {
    strcpy(this_object->seat,new_seat);
}

PUBLIC_FUNCTION
void client_info_class_set_ticketed(client_info_class_t *this_object, bool_t new_ticketed) {
    this_object->ticketed = new_ticketed;
}


PUBLIC_FUNCTION
const char *client_info_class_get_name(client_info_class_t* this_object) {
    return this_object->name;
}

PUBLIC_FUNCTION
const char *client_info_class_get_id(client_info_class_t *this_object) {
    return this_object->name;
}

PUBLIC_FUNCTION
bool_t client_info_class_get_ticketed(client_info_class_t *this_object) {
    return this_object->ticketed;
}

PUBLIC_FUNCTION
int client_info_class_equal(client_info_class_t *this_object, client_info_class_t *other_object) {
    return 1;
}