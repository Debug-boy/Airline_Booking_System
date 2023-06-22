//
// Created by Administrator on 2023/6/20.
//

#ifndef AIRLINEBOOKINGSYSTEM_PUBLIC_CLASS_DEF_H
#define AIRLINEBOOKINGSYSTEM_PUBLIC_CLASS_DEF_H

#define PUBLIC_CLASS struct

#define PUBLIC_FUNCTION

#ifndef THIS
#define THIS
#endif

#ifndef OBJECT
#define OBJECT
#endif

#define PRIVATE_FUNCTION static

#ifndef mem_zero
#define mem_zero(not_const_target,size) memset(not_const_target,0,size)
#endif

#endif //AIRLINEBOOKINGSYSTEM_PUBLIC_CLASS_DEF_H
