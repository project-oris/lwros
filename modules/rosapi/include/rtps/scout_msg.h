#ifndef LWROS_RTPS_SCOUT_MSG_H
#define LWROS_RTPS_SCOUT_MSG_H
#include "zenoh-pico/protocol/iobuf.h"
#include "zenoh-pico/collections/list.h"
#include "rtps/types.h"
#include "rtps/data_submsg.h"



typedef struct {
    uint16_t _pid;
    union {
        _rtps_protocol_version_t _version;
        _rtps_vendor_id_t _vendor_id;
        _rtps_guid_t _guid;
        _rtps_locator_t _locator;
        _rtps_duration_t _duration;
        _rtps_builtin_endpoint_set_t _endpoint_set;
        _rtps_entityname_t *_entityName;
        _rtps_string_t *_userData;
    } u;
}_rtps_scout_paramItem_t;
size_t _rtps_scout_paramItem_size(const _rtps_scout_paramItem_t *ios);
void _rtps_scout_paramItem_clear(_rtps_scout_paramItem_t *ios);
void _rtps_scout_paramItem_copy(_rtps_scout_paramItem_t *dst, const _rtps_scout_paramItem_t *src);
_Z_ELEM_DEFINE(_rtps_scout_paramItem, _rtps_scout_paramItem_t, _rtps_scout_paramItem_size, _rtps_scout_paramItem_clear, _rtps_scout_paramItem_copy)
_Z_LIST_DEFINE(_rtps_scout_paramItem, _rtps_scout_paramItem_t)

typedef struct {
    _rtps_header_t _header;    
    _rtps_time_t _info_ts;
    uint8_t _dataflags;
    _rtps_data_submsg_head_t _dataheader;
    _rtps_scout_paramItem_list_t *_params;
    uint8_t _data_reuse; // when 1, data reused
    _z_wbuf_t _encoded_datasub;
} _rtps_scouting_message_t;

z_result_t _rtps_init_scout_msg_data(_rtps_scouting_message_t *msg);
z_result_t _rtps_scouting_message_encode(_z_wbuf_t *buf, _rtps_scouting_message_t *msg);
z_result_t _rtps_scout_parameterlist_cdr_encode(_z_wbuf_t *zbf, _rtps_scout_paramItem_list_t **_list, int _le); // le == 1 means little endian
_rtps_submsg_list_t *_rtps_scouting_message_decode(_rtps_scouting_message_t *s_msg, _z_zbuf_t *zbf);
void _rtps_scouting_message_clear(_rtps_scouting_message_t *data);



#endif // LWROS_RTPS_DATASUBMSG_H
