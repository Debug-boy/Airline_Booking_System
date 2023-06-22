#include <stdio.h>

#include "queue.h"
#include "socket.h"
#include "airline_system_class.h"

int main(int argc,char *argv[]) {
    airline_system_class_t *airline_system = airline_system_construct();
    airline_system_start(airline_system);
    airline_system_destruct(airline_system);
    system("pause");
    return 0;
}
