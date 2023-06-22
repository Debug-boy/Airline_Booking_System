//
// Created by 艾乐乐 on 2023/6/20.
//

#include "airline_system_class.h"

/*
PRIVATE_FUNCTION void* airline_system_handle_client_impl(void* sock_info_arg){

    socket_info_t *client_sock_info = (socket_info_t*)(sock_info_arg);

    struct airline_protocol_basic_request * client_req_protocol_buffer =
            calloc(1,sizeof(struct airline_protocol_basic_request));

    struct airline_protocol_basic_result * client_res_protocol_buffer =
            calloc(1,sizeof(struct airline_protocol_basic_result));


    for(;;){

        socket_io_recv(client_sock_info->socket,
                       client_req_protocol_buffer,
                       sizeof(struct airline_protocol_basic_request),
                               NULL);

        switch(client_req_protocol_buffer->protocol_request_code){

            case AirlineProtocol_ApiCode_ConfirmTicket:
                break;

            case AirlineProtocol_ApiCode_CancelTicket:
                break;

            case AirlineProtocol_ApiCode_QueryFlightInfo:
                break;

            case AirlineProtocol_ApiCode_QueryFlightInfoByCode:
                break;

            case AirlineProtocol_ApiCode_QueryFlightInfoByCity:
                break;

            case AirlineProtocol_ApiCode_QueryFlightInfoByCid:
                break;

            default:
                break;
        }

    }

    socket_close2(client_sock_info);
    free(client_sock_info);
    return NULL;
}

PRIVATE_FUNCTION void airline_system_handle_client_entry(airline_system_class_t* this_object){
    for(;;){
        socket_info client = socket_accept(this_object->sock_info.socket);
        printf("client socket connect [address : %s] [port : %d]\n", inet_ntoa(client.sock_addr.sin_addr),client.sock_addr.sin_port);
        socket_info_t *client_sock_info = calloc(1,sizeof(socket_info_t));
        memcpy((void*)client_sock_info,(void*)(&client),sizeof(socket_info_t));
        thread_pool_push(&this_object->th_pool,airline_system_handle_client_impl,(void*)(client_sock_info));
    }
}

enum airline_sys_exception_code airline_system_init(airline_system_class_t *this_object) {

    this_object->sock_init_handle = socket_init();

    if(this_object->sock_init_handle == NULL){
        return false;
    }

    this_object->sock_info = socket_create(2764,"127.0.0.1");

    if(socket_is_failed(this_object->sock_info.socket)){
        perror("socket create is failed!\n");
        return sock_err_create;
    }

    socket_code sock_res_code = 0;

    sock_res_code = socket_bind(this_object->sock_info.socket,this_object->sock_info.sock_addr);
    if(socket_is_failed(sock_res_code)){
        perror("socket bind is failed!\n");
        return sock_err_bind;
    }

    sock_res_code = socket_listen(this_object->sock_info.socket,10);
    if(socket_is_failed(sock_res_code)){
        perror("socket listen is failed!\n");
        return sock_err_listen;
    }

    thread_pool_init(&this_object->th_pool,4);
}

void airline_system_start(airline_system_class_t *this_object) {
    airline_system_handle_client_entry(this_object);
}
 */

char* timestamp_to_text(time_t timestamp, char* buffer, size_t buffer_size) {
    struct tm *timeinfo;

    //mem_zero(buffer,buffer_size);

    // 将时间戳转换为本地时间
    timeinfo = localtime(&timestamp);

    // 格式化时间文本
    strftime(buffer, buffer_size, "%Y年%m月%d日%H时%M分", timeinfo);
    //puts(buffer);
    return buffer;
}

time_t text_to_timestamp(const char* text) {
    struct tm timeinfo = {0};

    // 解析时间文本
    sscanf(text, "%d年%d月%d日%d时%d分", &timeinfo.tm_year, &timeinfo.tm_mon, &timeinfo.tm_mday,
           &timeinfo.tm_hour, &timeinfo.tm_min, &timeinfo.tm_sec);
    // 转换为年份（需要减去1900）
    timeinfo.tm_year -= 1900;
    // 转换为月份（需要减去1）
    timeinfo.tm_mon -= 1;

    // 将时间转换为时间戳
    time_t timestamp = mktime(&timeinfo);

    return timestamp;
}

PRIVATE_FUNCTION void airline_system_show_branch(){
    const char* branch_show_str[] = {"    _    ___ ____      ______   ______ _____ _____ __  __ ",
                                      "   / \\  |_ _|  _ \\    / ___\\ \\ / / ___|_   _| ____|  \\/  |",
                                      "  / _ \\  | || |_) |___\\___ \\\\ V /\\___ \\ | | |  _| | |\\/| |",
                                      " / ___ \\ | ||  _ <_____|__) || |  ___) || | | |___| |  | |",
                                      "/_/   \\_\\___|_| \\_\\   |____/ |_| |____/ |_| |_____|_|  |_|",
                                      "                                                          "};

    for(int i = 0 ; i < 6 ; ++i){
        puts(branch_show_str[i]);
        Sleep(150);
    }
}

PRIVATE_FUNCTION void airline_system_show_menu(){
    printf("┌───────────────────────────────────────┐\n");
    printf("│          Airline Booking System       │\n");
    printf("├───────────────────────────────────────┤\n");
    printf("│    1. 订票业务                        │\n");
    printf("│    2. 退票业务                        │\n");
    printf("│    3. 查询航班                        │\n");
    printf("│    4. 查询预订                        │\n");
    printf("├───────────────────────────────────────┤\n");
    printf("│    0. 退出                            │\n");
    printf("└───────────────────────────────────────┘\n");
    printf("请选择功能：");
}

PRIVATE_FUNCTION int airline_system_choose_menu(){
    int choose_menu_code;
    scanf("%d",&choose_menu_code);
    return choose_menu_code;
}

PRIVATE_FUNCTION bool_t airline_system_has_reg_user(airline_system_class_t* this_object){
    return this_object->local_user != NULL;
}

PRIVATE_FUNCTION void airline_system_reg_user(airline_system_class_t *this_object,const char* user_name,const char* user_id){
    if(this_object->local_user != NULL){
        return;
    }

    this_object->local_user = (client_info_class_t*) calloc(1,sizeof(client_info_class_t));
    client_info_class_set_name(this_object->local_user,user_name);
    client_info_class_set_id(this_object->local_user,user_id);
}


PRIVATE_FUNCTION void airline_system_show_flight(flight_info_class_t* flight){
    char stamp_buffer[2][64] = {0};

    printf("+--------------------------------------------------------------------------------------------------------------------------------------------------+\n");
    printf("|                                                       航班表(1)                                                                                  |\n");
    printf("+--------------+---------+-----------------+-----------------+------------------------+------------------------+-----------------+-----------------+\n");
    printf("| 航班号       | 飞机号  | 飞机起点城市    | 飞机落点城市    | 起飞时间               | 落地时间               | 当前载客数      | 最大载客数      |\n");


    printf("+--------------+---------+-----------------+-----------------+------------------------+------------------------+-----------------+-----------------+\n");
    printf("| %s\t %s\t\t %s\t\t %s\t      %s\t%s\t\t %d \t\t %d\t   |\n",
           flight->fight_code, flight->aircraft_info.plane_code,
           flight->begin_city,flight->end_city,
           timestamp_to_text(flight->begin_stamp,&stamp_buffer[0][0],64), timestamp_to_text(flight->end_stamp,&stamp_buffer[1][0],64),
           flight->aircraft_info.current_capacity, flight->aircraft_info.total_capacity);

    printf("+--------------+---------+-----------------+-----------------+------------------------+------------------------+-----------------+-----------------+\n");
}

PRIVATE_FUNCTION void airline_system_other_show_flights(flight_mgr_class_t* flight_manager){
    flight_info_class_t* flight = NULL;

    char stamp_buffer[2][64] = {0};

    printf("+--------------------------------------------------------------------------------------------------------------------------------------------------+\n");
    printf("|                                                       航班表(%zu)                                                                                  |\n",
           flight_manager->flight_info_table.size);
    printf("+--------------+---------+-----------------+-----------------+------------------------+------------------------+-----------------+-----------------+\n");
    printf("| 航班号       | 飞机号  | 飞机起点城市    | 飞机落点城市    | 起飞时间               | 落地时间               | 当前载客数      | 最大载客数      |\n");

    flight_mgr_for_each(flight_manager,flight){
        printf("+--------------+---------+-----------------+-----------------+------------------------+------------------------+-----------------+-----------------+\n");
        printf("| %s\t %s\t\t %s\t\t %s\t      %s\t%s\t\t %d \t\t %d\t   |\n",
               flight->fight_code, flight->aircraft_info.plane_code,
               flight->begin_city,flight->end_city,
               timestamp_to_text(flight->begin_stamp,&stamp_buffer[0][0],64), timestamp_to_text(flight->end_stamp,&stamp_buffer[1][0],64),
               flight->aircraft_info.current_capacity, flight->aircraft_info.total_capacity);
    }
    printf("+--------------+---------+-----------------+-----------------+------------------------+------------------------+-----------------+-----------------+\n");
}


//显示航班信息表
PRIVATE_FUNCTION void airline_system_show_flights(airline_system_class_t *this_object){
    airline_system_other_show_flights(&this_object->flight_manager);
}



//制造航班信息表
PRIVATE_FUNCTION void airline_system_vir_make_flight(airline_system_class_t *this_object){

    aircraft_class_t * aircraft_B738 = aircraft_class_construct("B738",0,5);
    aircraft_add_passengers(aircraft_B738, client_info_class_construct("Apple","421001","1A"));
    aircraft_add_passengers(aircraft_B738, client_info_class_construct("Banana","421002","1B"));
    aircraft_add_passengers(aircraft_B738, client_info_class_construct("Orange","421003","1C"));
    aircraft_add_passengers(aircraft_B738, client_info_class_construct("Grape","421004","1D"));
    flight_info_class_t *flight_CA1234 = flight_info_construct("CA1234","北京","上海",2888,1626745200,1626752400,aircraft_B738);


    aircraft_class_t * aircraft_A320 = aircraft_class_construct("A320",0,5);
    aircraft_add_passengers(aircraft_A320, client_info_class_construct("Strawberry","421005","1A"));
    aircraft_add_passengers(aircraft_A320, client_info_class_construct("Peach","421006","1B"));
    aircraft_add_passengers(aircraft_A320, client_info_class_construct("Watermelon","421007","1C"));
    flight_info_class_t *flight_CZ5678 = flight_info_construct("CZ5678","广州","深圳",1888,1626766800,1626774000,aircraft_A320);


    aircraft_class_t * aircraft_B777 = aircraft_class_construct("B777",0,5);
    aircraft_add_passengers(aircraft_B777, client_info_class_construct("Pear","421008","1A"));
    aircraft_add_passengers(aircraft_B777, client_info_class_construct("Lemon","421009","1B"));
    aircraft_add_passengers(aircraft_B777, client_info_class_construct("Cherry","421010","1C"));
    flight_info_class_t *flight_MU9012 = flight_info_construct("MU9012","上海","香港",3666,1626792000,1626799200,aircraft_B777);

    aircraft_class_t * aircraft_B737 = aircraft_class_construct("B737",0,5);
    aircraft_add_passengers(aircraft_B737, client_info_class_construct("Pineapple","421011","1A"));
    aircraft_add_passengers(aircraft_B737, client_info_class_construct("Blueberry","421012","1B"));
    flight_info_class_t *flight_CA5678 = flight_info_construct("CA5678","上海","广州",3222,1655737200,1655744400,aircraft_B737);


    flight_mgr_add(&this_object->flight_manager,flight_CA1234);
    flight_mgr_add(&this_object->flight_manager,flight_CZ5678);
    flight_mgr_add(&this_object->flight_manager,flight_MU9012);
    flight_mgr_add(&this_object->flight_manager,flight_CA5678);
}

airline_system_class_t *airline_system_construct() {
    airline_system_show_branch();
    airline_system_class_t *system_instance = calloc(1,sizeof(airline_system_class_t));
    return system_instance;
}

PRIVATE_FUNCTION char airline_system_get_user_input_confirm(){
    fflush(stdin);
    int user_input_code = getchar();
    return user_input_code == 'y' || user_input_code == 'Y';
}

void airline_system_start(airline_system_class_t *this_object) {

    airline_system_vir_make_flight(this_object);

    this_object->running = true;

    while(this_object->running){

        airline_system_show_menu();

        switch (airline_system_choose_menu()) {

            case 0:
                printf("[系统] 确定要退出吗?[y/n]\n");
                if(airline_system_get_user_input_confirm()){
                    printf("[系统] 栓Q,欢迎下次使用!\n");
                    this_object->running = false;
                }
                break;

            case 1: {
                system("cls");
                airline_system_show_flights(this_object);


                fflush(stdin);
                char user_input_endCity[max_city_name_size] = {0};
                printf("[系统] 请输入抵达的城市名称:");
                scanf("%s", user_input_endCity);

                flight_mgr_class_t *flight_grep_from_endCity = flight_mgr_cond_endCity(&this_object->flight_manager,
                                                                                       user_input_endCity);


                airline_system_other_show_flights(flight_grep_from_endCity);

                //过滤后没有任何航班信息
                if (flight_mgr_size(flight_grep_from_endCity) == 0) {
                    printf("[系统] 经过筛选后没有任何航班信息,请重新进入页面!\n");
                    goto _to_restart_ticket;
                }


                fflush(stdin);
                char user_input_beginStamp[64] = {0};
                printf("[系统] 输入最早的出发时间 格式为(xxxx年xx月xx日xx时xx分):");
                scanf("%s", user_input_beginStamp);
                time_t cond_stamp = text_to_timestamp(user_input_beginStamp);

                flight_mgr_class_t *flight_grep_from_Stamp = flight_mgr_cond_Stamp(flight_grep_from_endCity,
                                                                                   cond_stamp);

                airline_system_other_show_flights(flight_grep_from_Stamp);


                fflush(stdin);
                printf("[系统] 请输入航班号进行下一步手续:");
                char temp_flight_code[max_aircraft_code_size];
                fgets(temp_flight_code, max_aircraft_code_size, stdin);
                temp_flight_code[strlen(temp_flight_code) - 1] = '\0';
                flight_info_class_t *query_flight_result = flight_mgr_cond_code(&this_object->flight_manager,
                                                                                temp_flight_code);


                if (query_flight_result != NULL) {
                    printf("[系统] 本次航班费用为:%d\n,请输入(y/n)进行购票:", query_flight_result->ticket_price);

                    if (airline_system_get_user_input_confirm()) {

                        if (!airline_system_has_reg_user(this_object)) {
                            printf("[系统] 当前是游客身份,请注册账号!\n");

                            fflush(stdin);
                            printf("[系统] 请输入用户名:");
                            char user_input_name[max_client_name_size];
                            fgets(user_input_name, max_client_name_size, stdin);
                            user_input_name[strlen(user_input_name) - 1] = '\0';

                            fflush(stdin);
                            printf("[系统] 请输入用户ID:");
                            char user_input_id[max_client_name_size];
                            fgets(user_input_id, max_client_name_size, stdin);
                            user_input_id[strlen(user_input_id) - 1] = '\0';

                            airline_system_reg_user(this_object, user_input_name, user_input_id);

                        }

                        const client_info_class_t *iter_client_info = (client_info_class_t *) linked_list_get_last(
                                &query_flight_result->aircraft_info.passengers_info);
                        char reset_user_sear[max_client_seat_size] = {0};

                        reset_user_sear[0] = '1';
                        reset_user_sear[1] = 'A';

                        if (iter_client_info != NULL) {
                            if (iter_client_info->seat[1] >= 'A' && iter_client_info->seat[1] < 'D') {
                                reset_user_sear[0] = iter_client_info->seat[0];
                                reset_user_sear[1] = iter_client_info->seat[1] + 1;
                            } else {
                                reset_user_sear[0] = iter_client_info->seat[0] + 1;
                            }
                        }

                        client_info_class_set_seat(this_object->local_user, reset_user_sear);

                        this_object->local_user->ticketed = true;

                        aircraft_add_passengers(&query_flight_result->aircraft_info, this_object->local_user);

                        printf("[系统] 好的,尊敬的:%s,系统已经为您成功购买 航班为:%s 飞机为:%s,您的座位号是:%s\n",
                               this_object->local_user->name,
                               temp_flight_code,
                               query_flight_result->aircraft_info.plane_code,
                               this_object->local_user->seat);

                    } else {
                        printf("[系统] 好的已经取消本次订单!\n");
                    }
                } else {
                    printf("[系统] 未检索到您输入的航班代码:%s 请您重新进入页面后尝试!\n", temp_flight_code);
                }

                _to_restart_ticket:
                system("pause");
                system("cls");
                break;
            }
            case 2:
                break;
            case 3: {
                airline_system_show_flights(this_object);

                fflush(stdin);
                char user_input_flight_code[max_aircraft_code_size] = {0};

                int select_mod = 0;
                printf("[系统] 你希望通过什么来查询相关航班信息!\n");
                printf("[系统] (1).通过航班号\n");
                printf("[系统] (2).通过抵达城市名称\n");
                printf("[系统] 请输入条件号:");
                scanf("%d", &select_mod);

                if (select_mod == 1) {

                    fflush(stdin);
                    printf("[系统] 请输入航班号:");
                    char temp_flight_code[max_aircraft_code_size];
                    fgets(temp_flight_code, max_aircraft_code_size, stdin);
                    temp_flight_code[strlen(temp_flight_code) - 1] = '\0';
                    flight_info_class_t *query_flight_result = flight_mgr_cond_code(&this_object->flight_manager,
                                                                                    temp_flight_code);

                    airline_system_show_flight(query_flight_result);

                }else if(select_mod == 2){

                    fflush(stdin);
                    char user_input_endCity[max_city_name_size] = {0};
                    printf("[系统] 请输入抵达的城市名称:");
                    scanf("%s", user_input_endCity);

                    flight_mgr_class_t *flight_grep_from_endCity = flight_mgr_cond_endCity(&this_object->flight_manager,
                                                                                           user_input_endCity);

                    airline_system_other_show_flights(flight_grep_from_endCity);


                    if (flight_mgr_size(flight_grep_from_endCity) == 0) {
                        printf("[系统] 经过查询筛选后没有任何航班信息,请重新进入页面!\n");
                    }

                }

                system("pause");
                system("cls");
                break;
            }

            //通过用户ID来获取 用户订购的航班
            case 4:
            {
                if(this_object->local_user != NULL){

                    if(this_object->local_user_flight_mgr == NULL){
                        printf("[系统] 当前用户还为选购任何航班!\n");
                    }else{


                    }

                }else{
                    printf("[系统] 当前用户还为选购任何航班!\n");
                }

                system("pause");
                system("cls");
                break;
            }
            default:
                printf("[系统] 错误,请输入正常的菜单选项! [按下任意键后刷写]\n!");
                getchar();
                break;
        }

    }

}

void airline_system_destruct(airline_system_class_t *this_object) {
    free(this_object);
}
