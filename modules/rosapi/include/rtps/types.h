#ifndef LWROS_RTPS_TYPES_H
#define LWROS_RTPS_TYPES_H

typedef struct {
    uint8_t _protocol[4];    // RTPS
    uint8_t _version[2];  // 0: major, 1: minor
    uint8_t _vendorId[2];
    uint8_t _guidPrefix[12];
} __attribute__((packed)) _rtps_header_t;

typedef struct {
    uint8_t _submsg_id;    
    uint8_t _flags; 
    uint16_t _submsg_length;
} __attribute__((packed)) _rtps_submsg_header_t;


typedef struct {
    uint8_t _major;
    uint8_t _minor;
} __attribute__((packed)) _rtps_protocol_version_t;

typedef struct {
    union {
        uint16_t _vendorId;
        uint8_t _ids[2];
    } _id;
} __attribute__((packed)) _rtps_vendor_id_t;

typedef struct {
    uint8_t _entityKey[3];
    uint8_t _entityKind;
} __attribute__((packed)) _rtps_entity_id_t;

typedef struct {
    uint8_t _ids[12];
} __attribute__((packed)) _rtps_guidprefix_t;

typedef struct {
    _rtps_guidprefix_t _guidPrefix;
    _rtps_entity_id_t _entityId;    
} __attribute__((packed)) _rtps_guid_t;


typedef struct {
    int32_t kind;
    uint32_t port;
    union
    {
        uint8_t raw[16];
        struct
        {
            uint8_t zeros[12];
            union {
                uint32_t value;
                uint8_t field[4];
            } addr;            
        } udp4;
    } addr; 
} __attribute__((packed)) _rtps_locator_t;

typedef struct {   
    uint16_t            _parameter_id;
    uint16_t            _length;
} __attribute__((packed)) _rtps_parameter_h_t; 

typedef struct {   
    _rtps_parameter_h_t _head;
    uint8_t             *_value;
} __attribute__((packed)) _rtps_parameter_t; 

typedef struct {
    uint16_t _pid;    
}_rtps_paramItem_t;

typedef struct {   
    int32_t _high;  // 32bit
    uint32_t _low;    
} __attribute__((packed)) _rtps_sequence_t;  // seq_num = high * 2^32 + low

typedef struct {   
    uint32_t _seconds;  // 32bit
    uint32_t _fraction;    
} __attribute__((packed)) _rtps_time_t; 

typedef struct {   
    int32_t _seconds;  // 32bit
    uint32_t _fraction;    
} __attribute__((packed)) _rtps_duration_t; 

typedef uint32_t _rtps_builtin_endpoint_set_t;

typedef struct {
    uint32_t _length;
    uint8_t _value[];
} __attribute__((packed)) _rtps_entityname_t; 

typedef struct {
    uint32_t _length;
    uint8_t _value[];
} __attribute__((packed)) _rtps_string_t; 



typedef enum {
    RTPS_PAD = 0x01, /* Pad */
    RTPS_ACKNACK = 0x06, /* AckNack */
    RTPS_HEARTBEAT = 0x07, /* Heartbeat */
    RTPS_GAP = 0x08, /* Gap */
    RTPS_INFO_TS = 0x09, /* InfoTimestamp */
    RTPS_INFO_SRC = 0x0c, /* InfoSource */
    RTPS_INFO_REPLY_IP4 = 0x0d, /* InfoReplyIp4 */
    RTPS_INFO_DST = 0x0e, /* InfoDestination */
    RTPS_INFO_REPLY = 0x0f, /* InfoReply */
    RTPS_NACK_FRAG = 0x12, /* NackFrag */
    RTPS_HEARTBEAT_FRAG = 0x13, /* HeartbeatFrag */
    RTPS_DATA = 0x15, /* Data */
    RTPS_DATA_FRAG = 0x16, /* DataFrag */   
} _rtps_submsg_kind_t;

typedef enum {
    RTPS_BIG_ENDIAN = 0x00,
    RTPS_LITTLE_ENDIAN = 0x01,
    RTPS_TS_INVALIDATE = 0x02,
    RTPS_DATA_INLINE_QOS = 0x02,
    RTPS_DATA_DATA_FLAG = 0x04,
    RTPS_DATA_KEY_FLAG = 0x08,
} _rtps_submsg_flag_t;

typedef enum {    
    ENTITYID_ERR = -1, 
    ENTITYID_USER_UNKNOWN = 0,
    ENTITYID_BUILTIN_UNKNOWN,
    ENTITYID_PARTICIPANT,
    ENTITYID_SEDP_BUILTIN_TOPIC_WRITER ,
    ENTITYID_SEDP_BUILTIN_TOPIC_READER,
    
    ENTITYID_SEDP_BUILTIN_PUBLICATIONS_WRITER,
    ENTITYID_SEDP_BUILTIN_PUBLICATIONS_READER,
    
    ENTITYID_SEDP_BUILTIN_SUBSCRIPTIONS_WRITER,
    ENTITYID_SEDP_BUILTIN_SUBSCRIPTIONS_READER,

    ENTITYID_SPDP_BUILTIN_PARTICIPANT_WRITER,
    ENTITYID_SPDP_BUILTIN_PARTICIPANT_READER,

    ENTITYID_P2P_BUILTIN_PARTICIPANT_MESSAGE_WRITER,
    ENTITYID_P2P_BUILTIN_PARTICIPANT_MESSAGE_READER,

    ENTITYID_USER_WRITER_WITH_KEY,
    ENTITYID_USER_WRITER_NO_KEY,

    ENTITYID_USER_READER_NO_KEY,
    ENTITYID_USER_READER_WITH_KEY,
} _rtps_entity_id_kind_t;

#define RTPS_PROTOCOL_ID {'R','T','P','S'}
//#define RTPS_PROTOCOL_VERSION_DEFAULT {2,2}
#define RTPS_VENDORID_UNKNOWN {0,0}

#define RTPS_GUIDPREFIX_UNKNOWN {0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00}


#define PARTICIPANT_MESSAGE_DATA_KIND_UNKNOWN {0x00, 0x00, 0x00, 0x00}
#define PARTICIPANT_MESSAGE_DATA_KIND_AUTOMATIC_LIVELINESS_UPDATE {0x00, 0x00, 0x00, 0x01}
#define PARTICIPANT_MESSAGE_DATA_KIND_MANUAL_LIVELINESS_UPDATE {0x00, 0x00, 0x00, 0x02}

#define RTPS_TIME_ZERO {0, 0}
#define RTPS_TIME_INVALID {-1, 0xffffffff}
#define RTPS_TIME_INFINITE {0x7fffffff, 0xffffffff}

//const _rtps_entity_id_t RTPS_ENTITYID_UNKNOWN ={{0x00, 0x00, 0x00}, 0x00};
//#define RTPS_ENTITYID_PARTICIPANT {{0x00, 0x00, 0x01}, 0xc1}

#define RTPS_ENTITYID_SEDP_BUILTIN_TOPIC_WRITER  {{0x00,0x00,0x02},0xc2}
#define RTPS_ENTITYID_SEDP_BUILTIN_TOPIC_READER  {{0x00,0x00,0x02},0xc7}

#define RTPS_ENTITYID_SEDP_BUILTIN_PUBLICATIONS_WRITER  {{0x00,0x00,0x03},0xc2}
#define RTPS_ENTITYID_SEDP_BUILTIN_PUBLICATIONS_READER  {{0x00,0x00,0x03},0xc7}

#define RTPS_ENTITYID_SEDP_BUILTIN_SUBSCRIPTIONS_WRITER  {{0x00,0x00,0x04},0xc2}
#define RTPS_ENTITYID_SEDP_BUILTIN_SUBSCRIPTIONS_READER  {{0x00,0x00,0x04},0xc7}

//#define RTPS_ENTITYID_SPDP_BUILTIN_PARTICIPANT_WRITER  {{0x00,0x01,0x00},0xc2}
#define RTPS_ENTITYID_SPDP_BUILTIN_PARTICIPANT_READER  {{0x00,0x01,0x00},0xc7}

#define RTPS_ENTITYID_P2P_BUILTIN_PARTICIPANT_MESSAGE_WRITER  {{0x00,0x02,0x00},0xc2}
#define RTPS_ENTITYID_P2P_BUILTIN_PARTICIPANT_MESSAGE_READER  {{0x00,0x02,0x00},0xc7}

#define RTPS_ENTITYKIND_BUILTIN_UNKNOWN             0xc0
#define RTPS_ENTITYKIND_BUILTIN_PARTIPANT           0xc1
#define RTPS_ENTITYKIND_BUILTIN_WRITER_WITH_KEY     0xc2
#define RTPS_ENTITYKIND_BUILTIN_WRITER_NO_KEY       0xc3
#define RTPS_ENTITYKIND_BUILTIN_READER_NO_KEY       0xc4
#define RTPS_ENTITYKIND_BUILTIN_READER_WITH_KEY     0xc7

#define RTPS_ENTITYKIND_USER_UNKNOWN                0x00
#define RTPS_ENTITYKIND_USER_WRITER_WITH_KEY        0x02
#define RTPS_ENTITYKIND_USER_WRITER_NO_KEY          0x03
#define RTPS_ENTITYKIND_USER_READER_NO_KEY          0x04
#define RTPS_ENTITYKIND_USER_READER_WITH_KEY        0x07

#define RTPS_SEQUENCENUMBER_UNKNOWN { -1, 0}

// LOCATOR
#define RTPS_LOCATOR_KIND_INVALID   -1
#define RTPS_LOCATOR_ADDRESS_INVALID {0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0}
#define RTPS_LOCATOR_PORT_INVALID   0
#define RTPS_LOCATOR_KIND_RESERVED  0
#define RTPS_LOCATOR_KIND_UDPv4     1
#define RTPS_LOCATOR_KIND_UDPv6     2
#define RTPS_LOCATOR_INVALID { RTPS_LOCATOR_KIND_INVALID, RTPS_LOCATOR_PORT_INVALID, RTPS_LOCATOR_ADDRESS_INVALID}

_rtps_entity_id_kind_t _rtps_entity_id_kind( _rtps_entity_id_t *_id);





#endif // LWROS_RTPS_TYPES_H