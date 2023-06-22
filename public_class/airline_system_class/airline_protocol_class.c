//
// Created by Administrator on 2023/6/22.
//
#include "airline_protocol_class.h"

void airline_api_ConfirmTicket(socket_info_t *client_sock_info) {

}

void airline_api_QueryFlightInfo(socket_info_t *client_sock_info, const linked_list_t *sys_flights_list) {
    struct airline_protocol_basic_result* server_hd_buffer =
            calloc(1,sizeof(struct airline_protocol_basic_result));

    server_hd_buffer->sz_count = linked_list_size(sys_flights_list);



}
