//
// Created by 艾乐乐 on 2023/6/19.
// 该头文件是 socket 通讯模块的接口文件,请参考函数的注释和细节
//

#ifndef AIRLINEBOOKINGSYSTEM_SOCKET_H
#define AIRLINEBOOKINGSYSTEM_SOCKET_H

#include <winsock2.h>

#ifndef mem_zero
#define mem_zero(not_const_target,size) memset(not_const_target,0,size)
#endif

#ifndef socket_is_failed
#define socket_is_failed(s_value) ((s_value == SOCKET_ERROR))
#endif

#ifndef socket_is_success
#define socket_is_success(s_value) (!socket_is_failed(s_value))
#endif

typedef int socket_code;

typedef SOCKET socket_t;

typedef struct SOCKET_INFO{
    socket_t socket;
    struct sockaddr_in sock_addr;
}socket_info;

typedef socket_info socket_info_t;

typedef void (*progress_callback)(int current, int total);

/*
 * 在任意的地方使用socket之前,必须要使用初始化 impl_socket_init 库接口函数,不然后面的操作会失败
 * 函数会返回一个初始化 socket 库的结果句柄 实际上是一个指针 可以用于 if( impl_socket_init() !=NULL) 判断是否成功初始化
 * 当不再进行任何的 socket 操作 一定要使用 impl_socket_release 将句柄释放 否则会造成内存泄漏,使得计算机资源浪费
*/
LPWSADATA socket_init();


/*
 * 当前程序不再使用任意的socket之后进行关闭wsa套接字接口句柄,具体看impl_socket_init函数介绍
 */
void socket_release(LPWSADATA real_ptr);


/* impl_socket_create
 * 参数:
 *   - sock_port: 无符号短整型，套接字绑定的端口号。
 *   - sock_address: 字符串指针，套接字绑定的地址，使用字符串表示（例如："127.0.0.1"）。
 *
 * 返回值:
 *   - 返回一个 socket_info 结构体，包含创建的套接字和套接字地址信息。
 *   - 如果创建套接字失败，返回的 socket_info 结构体中的套接字为无效值，需要进行错误处理。
 */
socket_info socket_create(unsigned short sock_port,const char* sock_address);


/*impl_socket_bind
* 参数：
*   - sock_port: 套接字绑定的端口号
*   - sock_address: 套接字绑定的地址，使用字符串表示（例如："127.0.0.1"）
*
* 返回值：
*   - 返回一个 socket_info 结构体，包含创建的套接字和套接字地址信息。
*   - 如果创建套接字失败，返回的 socket_info 结构体中的套接字为无效值，需进行错误处理。
*/
socket_code socket_bind(socket_t socket,struct sockaddr_in sock_address);


/*
 * 该函数 impl_socket_listen 是用于监听套接字的函数。
 * 该函数将指定的套接字设置为监听模式，以便接受传入的连接请求。
 *
 * 参数:
 *   - socket: 套接字描述符，要进行监听的套接字。
 *   - max_client: 整型，指定最大连接客户端数量。
 *
 * 返回值:
 *   - 返回一个 socket_code，表示函数执行结果。
 *   - 如果监听成功，返回值为0；如果监听失败，返回值为SOCKET_ERROR。
 */
socket_code socket_listen(socket_t socket, int max_client);


socket_code socket_connect(socket_t socket,struct sockaddr* sock_addr);


/*
 * 该函数 impl_socket_accept 用于接受传入的连接请求。
 * 本航空选票服务系统采用基于TCP/IP的可靠的socket数据流通信。
 * 调用该函数会阻塞当前线程，直到有客户端连接请求到达。
 * 当函数成功返回后，将返回一个新的与客户端会话的套接字描述符，以及客户端的地址信息。
 *
 * 参数:
 *   - socket: 套接字描述符，用于监听连接请求的套接字。
 *
 * 返回值:
 *   - 返回一个 socket_info 结构体，包含与客户端会话的套接字描述符和客户端的地址信息。
 *   - 如果接受连接请求失败，返回的 socket_info 结构体中的套接字为无效值，需要进行错误处理。
 */
socket_info socket_accept(socket_t socket);


/*
 * 该函数 impl_socket_close 用于关闭套接字连接。
 * 本航空选票服务系统采用基于TCP/IP的可靠的socket数据流通信。
 * 调用该函数可以主动关闭某个连接的套接字对象，无论是客户端还是服务端的套接字。
 *
 * 参数:
 *   - socket: 套接字描述符，要关闭的套接字对象。
 *
 * 返回值:
 *   - 返回一个 socket_code，表示函数执行结果。
 *   - 如果关闭成功，返回值为0；如果关闭失败，返回值为SOCKET_ERROR。
 */
socket_code socket_close(socket_t socket);



/*
 * 该函数 impl_socket_close2 用于关闭套接字连接。
 * 本航空选票服务系统采用基于TCP/IP的可靠的socket数据流通信。
 * 调用该函数可以主动关闭某个连接的套接字对象，无论是客户端还是服务端的套接字。
 *
 * 参数:
 *   - s_i: 指向 socket_info 结构体的指针，包含要关闭的套接字对象和相关信息。
 *
 * 返回值:
 *   - 返回一个 socket_code，表示函数执行结果。
 *   - 如果关闭成功，返回值为0；如果关闭失败，返回值为SOCKET_ERROR。
 */
socket_code socket_close2(socket_info *s_i);



/*
 * 该函数 impl_socket_io_send 是封装的socket的io类型函数，
 * 用于发送数据。本航空选票服务系统采用基于TCP/IP的可靠的socket数据流通信。
 * 由于TCP协议栈的定义，数据是流动的而不是固定的，因此可能出现数据粘连现象。
 * 为了解决这个问题，我们自定义了一个固定接收数据流的算法来保证稳定的数据接收。
 *
 * 参数：
 *   - socket: 要发送数据的套接字描述符
 *   - data: 要发送的数据的指针
 *   - size: 要发送的数据的大小（字节数）
 *   - progress_callback: 函数指针类型,通知为2个参数 分别是 当前任务字节数 和 总任务字节数
 *
 * 返回值：
 *   - 返回实际发送的字节数，如果发送失败，则返回-1。
 */
int socket_io_send(socket_t socket,const void* data, int size,progress_callback callback);


/*
 * 该函数 impl_socket_io_send2 是封装的socket的io类型函数,函数原理同impl_socket_io_send
 */
int socket_io_send2(socket_info *sock_info,const void* data, int size,progress_callback callback);


/*
 * 该函数 impl_socket_io_recv 是封装的套接字输入/接收函数。
 * 本航空选票服务系统采用基于TCP/IP的可靠的socket数据流通信。
 * 由于TCP协议的特性，数据可能会被分割成多个数据包进行传输，因此需要自定义接收算法以稳定地接收数据。
 *
 * 参数:
 *   - socket: 套接字描述符，要进行接收操作的套接字。
 *   - buffer: 指向接收缓冲区的指针，用于存储接收到的数据。
 *   - buffer_size: 整型，接收缓冲区的大小，即可存储的最大数据长度。
 *   - progress_callback: 函数指针类型,通知为2个参数 分别是 当前任务字节数 和 总任务字节数
 *
 * 返回值:
 *   - 返回一个 socket_code，表示函数执行结果。
 *   - 如果接收成功，返回值为真实的接收字节数；如果接收失败，返回值为SOCKET_ERROR。
 */
int socket_io_recv(socket_t socket, void* buffer, int buffer_size,progress_callback callback);


/*
 * 该函数 impl_socket_io_recv2 是封装的socket的io类型函数,函数原理同 impl_socket_io_recv
 */
int socket_io_recv2(socket_info *sock_info,void* data, int size,progress_callback callback);


#endif //AIRLINEBOOKINGSYSTEM_SOCKET_H