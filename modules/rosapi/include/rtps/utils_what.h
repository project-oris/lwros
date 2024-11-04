#ifndef LWROS_RTPS_UTILS_WHAT_H
#define LWROS_RTPS_UTILS_WHAT_H

#include "zenoh-pico/protocol/core.h"
#include "rtps/cdr_codec.h"
#include "rtps/types.h"

char *_rtps_submsg_kind_what( _rtps_submsg_kind_t kind);
char *_rtps_parameter_pid_what(uint16_t pid);
char *_rtps_vendor_id_what(_rtps_vendor_id_t vid);
char *_rtps_entity_id_what(_rtps_entity_id_t *eid);
void dump_bytes(uint8_t *buf, int len);
char *_rtps_builtin_endpoint_set_what(_rtps_builtin_endpoint_set_t value);
#endif // LWROS_RTPS_UTILS_WHAT_H