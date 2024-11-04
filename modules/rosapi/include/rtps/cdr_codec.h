#ifndef LWROS_RTPS_CDR_CODEC_H
#define LWROS_RTPS_CDR_CODEC_H
#include "zenoh-pico/protocol/iobuf.h"
#include "rtps/types.h"

#define RTPS_PARAM_PID_PAD                           0x0000
#define RTPS_PARAM_PID_SENTINEL                      0x0001
#define RTPS_PARAM_PID_PARTICIPANT_LEASE_DURATION    0x0002

#define RTPS_PARAM_PID_TOPIC_NAME                    0x0005
#define RTPS_PARAM_PID_TYPE_NAME                     0x0007
#define RTPS_PARAM_PID_PROTOCOL_VERSION              0x0015
#define RTPS_PARAM_PID_VENDOR_ID                     0x0016
#define RTPS_PARAM_PID_RELIABILITY                   0x001a
#define RTPS_PARAM_PID_LIVELINESS                    0x001b
#define RTPS_PARAM_PID_DURABILITY                    0x001d
#define RTPS_PARAM_PID_PRESENTATION                  0x0021
#define RTPS_PARAM_PID_PARTITION                     0x0029
#define RTPS_PARAM_PID_DEFAULT_UNICAST_LOCATOR       0x0031
#define RTPS_PARAM_PID_METATRAFFIC_UNICAST_LOCATOR   0x0032
#define RTPS_PARAM_PID_METATRAFFIC_MULTICAST_LOCATOR 0x0033
#define RTPS_PARAM_PID_HISTORY                       0x0040
#define RTPS_PARAM_PID_DEFAULT_MULTICAST_LOCATOR     0x0048
#define RTPS_PARAM_PID_TRANSPORT_PRIORITY            0x0049
#define RTPS_PARAM_PID_PARTICIPANT_GUID              0x0050
#define RTPS_PARAM_PID_BUILTIN_ENDPOINT_SET          0x0058
#define RTPS_PARAM_PID_PROPERTY_LIST                 0x0059
#define RTPS_PARAM_PID_ENDPOINT_GUID                 0x005a
#define RTPS_PARAM_PID_KEY_HASH                      0x0070

#define RTPS_PARAM_PID_USER_DATA                     0x002c
#define RTPS_PARAM_PID_GROUP_DATA                    0x002d
#define RTPS_PARAM_PID_TOPIC_DATA                    0x002e
#define RTPS_PARAM_PID_DURABILITY_SERVICE            0x001e
#define RTPS_PARAM_PID_ENTITY_NAME                   0x0062

typedef struct {
    uint16_t _scheme;
    uint16_t _options;
} __attribute__((packed)) _rtps_cdr_scheme_t; 

void *_rtps_parameter_cdr_decode(_z_zbuf_t *zbf, uint16_t paramId, int _le);
void *_rtps_parameterlist_cdr_decode(_z_zbuf_t *zbf, int endianess); 



#endif // LWROS_RTPS_DATASUBMSG_H
