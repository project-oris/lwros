#ifndef LWROS_RTPS_UTILS_NET_H
#define LWROS_RTPS_UTILS_NET_H

#include "zenoh-pico/protocol/core.h"
#include "rtps/cdr_codec.h"
#include "rtps/types.h"

z_result_t _get_local_ip4_address(uint8_t *buf);
z_result_t _rtps_wbuf_add_wbuf(_z_wbuf_t *_dst, _z_wbuf_t *src);
#endif // LWROS_RTPS_UTILS_WHAT_H