#ifndef LWROS_RTPS_TIME_H
#define LWROS_RTPS_TIME_H
#include "rtps/types.h"

_rtps_time_t _rtps_time_now(void);
uint32_t _rtps_time_to_sec(_rtps_time_t *ts);
int32_t _rtps_duration_to_sec(_rtps_duration_t *ts);


#endif // LWROS_RTPS_TIME_H