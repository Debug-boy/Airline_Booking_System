cmake_minimum_required(VERSION 3.23)
project(Airline_Booking_System C)

set(CMAKE_C_STANDARD 23)

include_directories(public_class)

include_directories(public_class/aircraft_class)
aux_source_directory(public_class/aircraft_class AUX_SOURCE_CLASS_AIRCRAFT)

include_directories(public_class/airline_system_class)
aux_source_directory(public_class/airline_system_class AUX_SOURCE_CLASS_AIR_SYS)

include_directories(public_class/client_info_class)
aux_source_directory(public_class/client_info_class AUX_SOURCE_CLASS_CLIENT_INFO)

include_directories(public_class/flight_info_class)
aux_source_directory(public_class/flight_info_class AUX_SOURCE_CLASS_FLIGHT_INFO)


include_directories(public_modules/socket_module)
aux_source_directory(public_modules/socket_module AUX_SOURCE_MODULE_SOCKET)

include_directories(public_modules/file_util_module)
aux_source_directory(public_modules/socket_module AUX_SOURCE_MODULE_FILE_UTIL)

include_directories(public_modules/linked_list_module)
aux_source_directory(public_modules/linked_list_module AUX_SOURCE_MODULE_LINKED_LIST)

include_directories(public_modules/queue_module)
aux_source_directory(public_modules/queue_module AUX_SOURCE_MODULE_QUEUE)

include_directories(public_modules/stack_module)
aux_source_directory(public_modules/stack_module AUX_SOURCE_MODULE_STACK)

include_directories(public_modules/thread_pool_module)
aux_source_directory(public_modules/thread_pool_module AUX_SOURCE_MODULE_THREAD_POOL)


add_executable(airline_server
        airline_server/airline_server.c
        ${AUX_SOURCE_MODULE_SOCKET}
        ${AUX_SOURCE_MODULE_FILE_UTIL}
        ${AUX_SOURCE_CLASS_CLIENT_INFO}
        ${AUX_SOURCE_CLASS_FLIGHT_INFO}
        ${AUX_SOURCE_CLASS_AIRCRAFT}
        ${AUX_SOURCE_CLASS_AIR_SYS}
        ${AUX_SOURCE_MODULE_LINKED_LIST}
        ${AUX_SOURCE_MODULE_QUEUE}
        ${AUX_SOURCE_MODULE_THREAD_POOL}
        )

add_executable(airline_client
        airline_client/airline_client.c
        ${AUX_SOURCE_MODULE_SOCKET}
        ${AUX_SOURCE_MODULE_FILE_UTIL}
        ${AUX_SOURCE_CLASS_CLIENT_INFO}
        ${AUX_SOURCE_CLASS_FLIGHT_INFO}
        ${AUX_SOURCE_CLASS_AIRCRAFT}
        ${AUX_SOURCE_CLASS_AIR_SYS}
        ${AUX_SOURCE_MODULE_LINKED_LIST}
        ${AUX_SOURCE_MODULE_QUEUE}
        ${AUX_SOURCE_MODULE_THREAD_POOL}
        )


target_link_libraries(airline_server ws2_32)
target_link_libraries(airline_client ws2_32)