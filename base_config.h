
#ifndef LWROS_BASE_CONFIG_H
#define LWROS_BASE_CONFIG_H
#define DEV_DEBUG
#define DEV_DEBUG_SCOUT_MSG
#define CODE_TRACE_ON

#ifdef CODE_TRACE_ON
#include <stdio.h>
//##define ctrace(mesg)  { printf("##CT: %s/%s:%d\n\t--> [%s]  \n", __FILE__, __FUNCTION__, __LINE__, mesg);}
//#define ctracef(format, args...)  { printf("CT: %s/%s:%d\n\t-->[" format "] \n",__FILE__,__FUNCTION__, __LINE__, args);}
#define ctrace(format, ...)  { printf("CT: %s/%s:%d\n\t-->[" format "] \n",__FILE__,__FUNCTION__, __LINE__, ##__VA_ARGS__);}
#else
#define ctrace(mesg)
#endif

#endif // LWROS_BASE_CONFIG_H