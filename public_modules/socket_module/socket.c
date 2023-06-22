#include "socket.h"

static LPWSADATA impl_socket_init() {
    LPWSADATA win_socket_data = (LPWSADATA) malloc(sizeof(WSADATA));
    mem_zero(win_socket_data,sizeof(WSADATA));
    if(WSAStartup(MAKEWORD(2,2),win_socket_data) != 0){
        return NULL;
    }
    return win_socket_data;
}

static void impl_socket_release(LPWSADATA real_ptr) {
    if(real_ptr != NULL){
        free(real_ptr);
        WSACleanup();
    }
}


static socket_info impl_socket_create(unsigned short sock_port,const char* sock_address) {

    socket_info sock_res_info;

    socket_t socket_fd = socket(AF_INET,SOCK_STREAM,IPPROTO_IP);

    struct sockaddr_in socket_addr;
    socket_addr.sin_family = AF_INET;
    socket_addr.sin_port = htons(sock_port);
    socket_addr.sin_addr.S_un.S_addr = inet_addr(sock_address);

    sock_res_info.socket = socket_fd;
    sock_res_info.sock_addr = socket_addr;

    return sock_res_info;
}

static socket_code impl_socket_bind(SOCKET socket,struct sockaddr_in sock_address) {
    return bind(socket,
         (struct sockaddr*)(&sock_address),
            sizeof(struct sockaddr_in));

}


static socket_code impl_socket_listen(socket_t socket,int max_client) {
    return listen(socket,max_client);
}


static socket_code impl_socket_connect(socket_t socket,struct sockaddr* sock_addr){
    return connect(socket,sock_addr,sizeof(struct sockaddr_in));
}

static socket_info impl_socket_accept(socket_t socket) {

    struct sockaddr_in sock_client_ad;
    int sock_client_ad_size = sizeof(struct sockaddr_in);

    socket_t socket_client_fd = accept(socket, (struct sockaddr *)&sock_client_ad, &sock_client_ad_size);

    socket_info sock_res_info;
    mem_zero((void*)&sock_res_info,sizeof(socket_info));

    if(socket_is_failed(socket_client_fd)){
        return sock_res_info;
    }

    sock_res_info.socket = socket_client_fd;
    sock_res_info.sock_addr = sock_client_ad;

    return sock_res_info;
}

static socket_code impl_socket_close(socket_t socket) {
    if(socket_is_success(socket)){
        return closesocket(socket);
    }
    return SOCKET_ERROR;
}

static socket_code impl_socket_close2(socket_info *s_i){
    if(socket_is_success(s_i->socket)){
        return closesocket(s_i->socket);
    }
    return SOCKET_ERROR;
}

static int impl_socket_io_send(socket_t socket, const void* buffer, int buffer_size,progress_callback callback) {
    int total_bytes_sent = 0;  // 记录已发送的总字节数
    int bytes_sent = 0;       // 每次发送的字节数
    const char* send_buffer = (const char*)buffer;  // 将 void* 类型转换为 const char* 类型

    while (total_bytes_sent < buffer_size) {
        // 发送数据到套接字
        bytes_sent = send(socket, send_buffer + total_bytes_sent, buffer_size - total_bytes_sent, 0);

        if (bytes_sent == SOCKET_ERROR) {
            // 发送失败，返回错误代码
            return SOCKET_ERROR;
        }

        total_bytes_sent += bytes_sent;

        // 调用回调通知函数，传递已发送的总字节数和当前发送的字节数
        if (callback != NULL) {
            callback(total_bytes_sent, bytes_sent);
        }

        // 数据已经完全发送，退出循环
        if (total_bytes_sent == buffer_size) {
            break;
        }
    }

    return total_bytes_sent;  // 返回发送的字节数
}

static int impl_socket_io_send2(socket_info *sock_info, const void *data, int size,progress_callback callback) {
    return impl_socket_io_send(sock_info->socket,data,size,callback);
}


static socket_code impl_socket_io_recv(socket_t socket, void* buffer, int buffer_size,progress_callback callback) {
    int total_bytes_received = 0;  // 记录已接收的总字节数
    int bytes_received = 0;       // 每次接收的字节数
    char* recv_buffer = (char*)buffer;  // 将 void* 类型转换为 char* 类型 来方便进行指针计算

    while (total_bytes_received < buffer_size) {
        // 从套接字接收数据，存储到缓冲区中
        bytes_received = recv(socket, recv_buffer + total_bytes_received, buffer_size - total_bytes_received, 0);

        if (bytes_received == SOCKET_ERROR) {
            // 接收失败，返回错误代码
            return SOCKET_ERROR;
        } else if (bytes_received == 0) {
            // 对端已关闭连接，返回接收结束
            break;
        }

        total_bytes_received += bytes_received;

        // 调用回调通知函数，传递已发送的总字节数和当前发送的字节数
        if (callback != NULL) {
            callback(total_bytes_received, bytes_received);
        }

        // 数据已经完全接收，退出循环
        if (total_bytes_received == buffer_size) {
            break;
        }
    }

    return total_bytes_received;  // 返回成功状态
}

static int impl_socket_io_recv2(socket_info *sock_info,void *data, int size, progress_callback callback) {
    return impl_socket_io_recv(sock_info->socket,data,size,callback);
}

LPWSADATA socket_init() {
    return impl_socket_init();
}

void socket_release(LPWSADATA real_ptr) {
    impl_socket_release(real_ptr);
}

socket_info socket_create(unsigned short sock_port, const char *sock_address) {
    return impl_socket_create(sock_port,sock_address);
}

socket_code socket_bind(socket_t socket, struct sockaddr_in sock_address) {
    return impl_socket_bind(socket,sock_address);
}

socket_code socket_listen(socket_t socket, int max_client) {
    return impl_socket_listen(socket,max_client);
}

socket_code socket_connect(socket_t socket, struct sockaddr *sock_addr) {
    return impl_socket_connect(socket,sock_addr);
}

socket_info socket_accept(socket_t socket) {
    return impl_socket_accept(socket);
}

socket_code socket_close(socket_t socket) {
    return impl_socket_close(socket);
}

socket_code socket_close2(socket_info *s_i) {
    return impl_socket_close2(s_i);
}

int socket_io_send(socket_t socket, const void *data, int size, progress_callback callback) {
    return impl_socket_io_send(socket,data,size,callback);
}

int socket_io_send2(socket_info *sock_info, const void *data, int size, progress_callback callback) {
    return impl_socket_io_send2(sock_info,data,size,callback);
}

int socket_io_recv(socket_t socket, void *buffer, int buffer_size, progress_callback callback) {
    return impl_socket_io_recv(socket,buffer,buffer_size,callback);
}

int socket_io_recv2(socket_info *sock_info, void *data, int size, progress_callback callback) {
    return impl_socket_io_send2(sock_info,data,size,callback);
}
















