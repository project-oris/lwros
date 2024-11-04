#include "zenoh-pico/system/platform.h"
#include "rtps/time.h"

inline uint32_t _rtps_nano_to_frac(uint32_t nanos)
{
    return (uint32_t)((nanos * 4294967296ULL) / 1000000000ULL);
}

_rtps_time_t _rtps_time_now(void)
{
    _rtps_time_t _now;
    _z_time_since_epoch _z_now;

    z_result_t ret =_z_get_time_since_epoch(&_z_now);

    _now._seconds = _z_now.secs;
    _now._fraction = _rtps_nano_to_frac(_z_now.nanos);

    return _now;
}

uint32_t _rtps_time_to_sec(_rtps_time_t *ts)
{    
    uint64_t ret2;

    //ret2 = (uint64_t)ts->_seconds + (((uint64_t)ts->_fraction) >> 32);

    return (uint32_t)ts->_seconds ;
}

int32_t _rtps_duration_to_sec(_rtps_duration_t *ts)
{    
    int64_t ret2;

    // fracetion has no meaning.  
    //  faction is 32bit , so (frac / (2^32)) is 0 always

    //ret2 = (uint64_t)ts->_seconds + (((uint64_t)ts->_fraction) >> 32);

    return (int32_t)ts->_seconds ;
}