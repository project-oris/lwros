#ifndef LWROS_RTPS_DATASUBMSG_H
#define LWROS_RTPS_DATASUBMSG_H
#include "zenoh-pico/protocol/iobuf.h"
#include "rtps/types.h"

typedef struct {   
    uint16_t _extraFlags;  // 32bit : = 0
    uint16_t _octetsToInlineQos;
    _rtps_entity_id_t _readerId;
    _rtps_entity_id_t _writerId;
    _rtps_sequence_t _writerSN;
} __attribute__((packed)) _rtps_data_submsg_head_t;  //time = seconds + (fraction / 2^(32))

typedef struct {
    bool _dataFlag;
    bool _qosFlag;
    bool _keyFlag;
    bool _bigEndian; // True is big
    _rtps_data_submsg_head_t _head;
    //_rtps_parameter_list_t *_inlineQos;
    uint8_t *inlineQos;
    //_rtps_serialized_payload_t *_payload;
    uint8_t *_payload;
} _rtps_data_submsg_t;

_rtps_data_submsg_t *_rtps_scout_submsg_data_decode(_z_zbuf_t *zbf, uint8_t flags, uint16_t length);

#define _SUBMSG_IDSET_SIZE (sizeof(_rtps_entity_id_t) *2 + sizeof(_rtps_sequence_t))

#endif // LWROS_RTPS_DATASUBMSG_H
