#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/socket.h>
#include <netdb.h>
#include <arpa/inet.h>
#include <sys/random.h>
#include "zenoh-pico/utils/config.h"
#include "zenoh-pico/collections/string.h"
#include "rtps/utils_what.h"
#include "rtps/utils_net.h"
#include "rtps/core.h"


_z_config_t _rtps_default_config;
_rtps_guidprefix_t _base_guid_prefix = {._ids = {0,0,0,0,0,0,0,0,0,0,0,0}};

#define LWROS_RTPS_VENDORID 0x2f2f

typedef struct {

} _rtps_scout_context;

_rtps_scout_context _core_scout_ctx;


_rtps_guidprefix_t _rtps_get_core_guidprefix()
{
    return _base_guid_prefix;
}

_z_string_t _rtps_bytes_to_string(uint8_t *data, size_t len)
{
    size_t s_len  = len * (size_t)2 + 1;
    _z_string_t ret = _z_string_preallocate(s_len * sizeof(uint8_t));
    char *s_val = ret._slice.start;
    const char c[] = "0123456789ABCDEF";
    for (size_t i = 0; i < len; i++) {
        s_val[i * (size_t)2] = c[(data[i] & (uint8_t)0xF0) >> (uint8_t)4];
        s_val[(i * (size_t)2) + 1] = c[data[i] & (uint8_t)0x0F];
    }    
    s_val[s_len] = 0;

    return ret;
}

void _rtps_init() 
{
    ctrace("###_rtps_init###");
    _z_config_init(&_rtps_default_config);

    // set guid prefix
    _base_guid_prefix._ids[0] = LWROS_RTPS_VENDORID >> 8;
    _base_guid_prefix._ids[1] = LWROS_RTPS_VENDORID & 0x0f;
    z_random_fill(&_base_guid_prefix._ids[2], 10);
    _z_string_t _guid_str = _rtps_bytes_to_string(_base_guid_prefix._ids, sizeof(_base_guid_prefix));
    _zp_config_insert(&_rtps_default_config, RTPS_CONFIG_BASE_GUID_PREFIX, _z_string_data(&_guid_str));
    _z_string_clear(&_guid_str);
    // set doman id
    _zp_config_insert(&_rtps_default_config, RTPS_CONFIG_DOMAIN_ID_KEY, "0");
    // set participant id key
    _zp_config_insert(&_rtps_default_config, RTPS_CONFIG_PARTICIPANT_ID_KEY, "1");    

    uint8_t _addr[4];
    uint8_t _buf[30];    
    _get_local_ip4_address(_addr);    
    snprintf(_buf, 30,"%02x%02x%02x%02x",_addr[0],_addr[1],_addr[2],_addr[3] );
    _zp_config_insert(&_rtps_default_config, RTPS_CONFIG_UNICAST_IP4_ADDR_KEY, _buf);
    
    // _rtps_locator_t adr;
    // adr.addr.udp4.addr.value = htonl(strtol(_z_config_get(&_rtps_default_config,RTPS_CONFIG_UNICAST_IP4_ADDR_KEY),NULL, 16));
    // printf(" DOM is %d \n",strtol(_z_config_get(&_rtps_default_config,RTPS_CONFIG_DOMAIN_ID_KEY),NULL, 10));
    // printf(" PART is %d \n",strtol(_z_config_get(&_rtps_default_config,RTPS_CONFIG_PARTICIPANT_ID_KEY),NULL, 10));    
    // printf(" ADDR3 is %d.%d.%d.%d \n",
    //     adr.addr.udp4.addr.field[0],adr.addr.udp4.addr.field[1],
    //     adr.addr.udp4.addr.field[2],adr.addr.udp4.addr.field[3]
    //      );       
    
    // exit(1);

}

char *_rtps_config_get(uint8_t key)
{
    return _z_config_get(&_rtps_default_config, key);
}    


void _rtps_header_init(_rtps_header_t *head)
{
    // make unique guid 
    // if config has UUID for guid, set guid wtih UUID
    *head = _rtps_header_empty();

    for (int i; i< 12; i++)
        head->_guidPrefix[i] = _base_guid_prefix._ids[i];
    
}


bool _rtps_guid_prefix_loopback(_rtps_header_t * const a) {
    bool ret = false;

    for (int i=0; !ret && i< 12; i++)
        ret |= a->_guidPrefix[i] != _base_guid_prefix._ids[i];

    return !ret;
}

bool _rtps_guid_prefix_identical(_rtps_header_t * const a, _rtps_header_t * const b) {
    bool ret = false;

    for (int i=0; !ret && i< 12; i++)
        ret |= a->_guidPrefix[i] != b->_guidPrefix[i];

    return !ret;
}

_rtps_header_t _rtps_header_empty() 
{
    return (_rtps_header_t){
        ._protocol = RTPS_PROTOCOL_ID,
        ._version = {2,2},
        ._vendorId = RTPS_VENDORID_UNKNOWN,
        ._guidPrefix = RTPS_GUIDPREFIX_UNKNOWN
    };
}

bool _rtps_header_invalid(_rtps_header_t *header)
{
    bool ret = false;    
    _rtps_header_t _head = _rtps_header_empty();
    
    for (int i=0; !ret && i < 4; i++) {        
        ret |= header->_protocol[i] != _head._protocol[i];
    }
    if (ret) {
        ret |= (header->_version[0] < 0 | header->_version[0] > 2 |
            header->_version[1] < 0 | header->_version[1] > 3);
    }

    return ret;    
}


size_t _rtps_submsg_size(const _rtps_submsg_t *ios) {

}
void _rtps_submsg_clear(_rtps_submsg_t *ios) {

}
void _rtps_submsg_free(_rtps_submsg_t **ios) {

}
void _rtps_submsg_copy(_rtps_submsg_t *dst, const _rtps_submsg_t *src) {

}
_rtps_submsg_t *_rtps_submsg_t_clone(const _rtps_submsg_t *src) {

}