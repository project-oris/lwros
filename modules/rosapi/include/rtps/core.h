#ifndef LWROS_RTPS_CORE_H
#define LWROS_RTPS_CORE_H
#include "zenoh-pico/protocol/iobuf.h"
#include "rtps/types.h"
#include "rtps/data_submsg.h"


#define RTPS_CONFIG_UNICAST_IP4_ADDR_KEY 0x50  // XX XX XX XX
#define RTPS_CONFIG_DOMAIN_ID_KEY 0x51
#define RTPS_CONFIG_PARTICIPANT_ID_KEY 0x52
#define RTPS_CONFIG_BASE_GUID_PREFIX 0x53

typedef struct {
    _rtps_submsg_header_t _header;
    uint8_t _body[];
} _rtps_submsg_t;

typedef uint8_t *_rtps_scout_context_h;

/*

*/

size_t _rtps_submsg_size(const _rtps_submsg_t *ios);
void _rtps_submsg_clear(_rtps_submsg_t *ios);
void _rtps_submsg_free(_rtps_submsg_t **ios);
void _rtps_submsg_copy(_rtps_submsg_t *dst, const _rtps_submsg_t *src);
_rtps_submsg_t *_rtps_submsg_t_clone(const _rtps_submsg_t *src);


_Z_ELEM_DEFINE(_rtps_submsg, _rtps_submsg_t, _rtps_submsg_size, _rtps_submsg_clear, _rtps_submsg_copy)
_Z_LIST_DEFINE(_rtps_submsg, _rtps_submsg_t)  // _rtps_submsg_list_t


void _rtps_init();
char *_rtps_config_get(uint8_t key);
void _rtps_header_init(_rtps_header_t *head);
_rtps_header_t _rtps_header_empty();
bool _rtps_guid_prefix_loopback(_rtps_header_t * const a);
bool _rtps_guid_prefix_identical(_rtps_header_t * const a, _rtps_header_t * const b);
bool _rtps_header_invalid(_rtps_header_t *header);
_rtps_guidprefix_t _rtps_get_core_guidprefix();

#endif // LWROS_RTPS_DATASUBMSG_H
