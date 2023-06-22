#include <stdio.h>

#include "socket.h"



int main(int argc,char *argv[]){

    printf("Hello, World!\n");

    LPWSADATA sock_init_handle = socket_init();

    printf("win socket init is %p\n",sock_init_handle);

    if(socket_is_failed(sock_init_handle)){
        perror("win socket init error!\n");
        goto __to_release;
    }

    socket_code sock_res_code = 0;

    socket_info airline_sock_info = socket_create(2764,"127.0.0.1");

    printf("socket create fd is : 0x%llX\n",airline_sock_info.socket);

    if(socket_is_failed(airline_sock_info.socket)){
        perror("socket create is failed!\n");
        goto __to_release;
    }

    sock_res_code = socket_connect(airline_sock_info.socket, (struct sockaddr *) &airline_sock_info.sock_addr);

    printf("socket connect res : %d\n",sock_res_code);

    if(socket_is_failed(sock_res_code)){
        perror("socket connect is failed!\n");
        goto __to_release;
    }

    const char *hello = "Hello server!";
    printf("socket sendto airline_sys\n");
    int total_bytes = socket_io_send(airline_sock_info.socket,hello, strlen(hello),NULL);
    printf("socket sendto bytes:%d\n",total_bytes);

    __to_release:
    printf("socket close server\n");
    socket_close(airline_sock_info.socket);
    printf("socket release winsock\n");
    socket_release(sock_init_handle);
    return 0;
}