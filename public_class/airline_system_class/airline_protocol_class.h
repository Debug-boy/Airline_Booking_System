//
// Created by 艾乐乐 on 2023/6/22.
//

#ifndef AIRLINE_BOOKING_SYSTEM_AIRLINE_PROTOCOL_CLASS_H
#define AIRLINE_BOOKING_SYSTEM_AIRLINE_PROTOCOL_CLASS_H

#include "public_class_def.h"
#include "socket.h"
#include "linked_list.h"
#include "flight_info_class.h"

#define max_protocol_buf_sz 1024

enum airline_protocol_st_code{
    AirlineProtocol_StCode_Failed,
    AirlineProtocol_StCode_Success,
};

enum airline_protocol_api_code{
    AirlineProtocol_ApiCode_ConfirmTicket,
    AirlineProtocol_ApiCode_CancelTicket,
    AirlineProtocol_ApiCode_QueryFlightInfo,
    AirlineProtocol_ApiCode_QueryFlightInfoByCode,
    AirlineProtocol_ApiCode_QueryFlightInfoByCity,
    AirlineProtocol_ApiCode_QueryFlightInfoByCid,
};

//标准请求
PUBLIC_CLASS airline_protocol_basic_request{
    enum airline_protocol_api_code protocol_request_code;//请求的API代码
    char protocol_request_buffer[max_protocol_buf_sz];//请求的参数
};

//标准返回
PUBLIC_CLASS airline_protocol_basic_result{
    enum airline_protocol_st_code protocol_result_code;//服务端处理API返回的代码
    unsigned int sz_count;
    char protocol_result_buffer[max_protocol_buf_sz];//返回的缓冲区
};

//其它类请求
#ifndef airline_protocol_query_flight_request
#define airline_protocol_query_flight_request struct airline_protocol_basic_request;
#endif

PUBLIC_CLASS airline_protocol_query_flight_result{
    enum airline_protocol_st_code code;//服务端处理API返回的状态代码
    char msg[32];
    flight_info_class_t flight_table[10];
};

PUBLIC_FUNCTION void airline_api_QueryFlightInfo(socket_info_t* client_sock_info,const linked_list_t* sys_flights_list);

PUBLIC_FUNCTION void airline_api_ConfirmTicket(socket_info_t* client_sock_info);

#endif //AIRLINE_BOOKING_SYSTEM_AIRLINE_PROTOCOL_CLASS_H
