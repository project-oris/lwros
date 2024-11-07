
#include "base_config.h"
#include "zenoh-pico/protocol/core.h"
#include "zenoh-pico/utils/endianness.h"
#include "rtps/core.h"
#include "rtps/time.h"
#include "rtps/data_submsg.h"
#include "rtps/utils_net.h"
#include "rtps/utils_what.h"
#include "rtps/scout_msg.h"

// typedef struct {
//     _rtps_header_t _header;    
//     _rtps_time_t _info_ts;
//     _rtps_data_submsg_t _data;
// } _rtps_scouting_message_t;
const _rtps_protocol_version_t RTPS_PROTOCOL_VERSION_DEFAULT = {2,2};
const _rtps_entity_id_t RTPS_ENTITYID_UNKNOWN ={{0x00, 0x00, 0x00}, 0x00};
const _rtps_entity_id_t RTPS_ENTITYID_PARTICIPANT ={{0x00, 0x00, 0x01}, 0xc1};

const _rtps_entity_id_t RTPS_ENTITYID_SPDP_BUILTIN_PARTICIPANT_WRITER= {{0x00,0x01,0x00},0xc2};
const _rtps_vendor_id_t RTPS_SCOUT_VENDORID_UNKNOWN = {._id._vendorId = 0};
const _rtps_builtin_endpoint_set_t RTPS_SCOUT_BUILTIN_ENDPOINT_SET= 0x0000003f;

const _rtps_cdr_scheme_t RTPS_CDR_BE = {._scheme = 0x0000, ._options = 0};
const _rtps_cdr_scheme_t RTPS_CDR_LE = {._scheme = 0x0100, ._options = 0};
const _rtps_cdr_scheme_t RTPS_PL_CDR_BE = {._scheme = 0x0200, ._options = 0};
const _rtps_cdr_scheme_t RTPS_PL_CDR_LE = {._scheme = 0x0300, ._options = 0};

#define RTPS_PORT_PB 7400
#define RTPS_PORT_DG 250
#define RTPS_PORT_PG 2
#define RTPS_PORT_D0 0
#define RTPS_PORT_D1 10
#define RTPS_PORT_D2 1
#define RTPS_PORT_D3 11
//
// default config .



uint32_t _rtps_get_matartrafic_unicast_unicast_port(int domainId, int participantId)
{
    return (RTPS_PORT_PB + RTPS_PORT_DG * domainId + RTPS_PORT_D1 + RTPS_PORT_PG * participantId);
             // 7400         250                       10             2
}

uint32_t _rtps_get_default_unicast_unicast_port(int domainId, int participantId)
{
    return (RTPS_PORT_PB + RTPS_PORT_DG * domainId + RTPS_PORT_D3 + RTPS_PORT_PG * participantId);
             // 7400         250                       11             2
}




_rtps_locator_t _rtps_get_matartrafic_unicast_locator()
{
    _rtps_locator_t ret=
        {
            .kind=RTPS_LOCATOR_KIND_UDPv4, 
            .port = 0,
            .addr.raw = {0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0},
        };        

    long domainId = strtol(_rtps_config_get(RTPS_CONFIG_DOMAIN_ID_KEY), NULL, 10);
    long partId = strtol(_rtps_config_get(RTPS_CONFIG_PARTICIPANT_ID_KEY), NULL, 10);
    ret.port = _rtps_get_matartrafic_unicast_unicast_port(domainId,partId);
    //ret.addr.udp4.addr.value = htonl(strtol(_rtps_config_get(RTPS_CONFIG_UNICAST_IP4_ADDR_KEY),NULL, 16));
    uint32_t _addr=strtol(_rtps_config_get(RTPS_CONFIG_UNICAST_IP4_ADDR_KEY),NULL, 16);
    _z_be_store32(_addr, (uint8_t *)&ret.addr.udp4.addr.value);

#ifdef DEV_DEBUG_SCOUT_MSG
    ctrace("meta unicast addr is %d.%d.%d.%d:%d ", 
        ret.addr.udp4.addr.field[0], ret.addr.udp4.addr.field[1], 
        ret.addr.udp4.addr.field[2], ret.addr.udp4.addr.field[3],
        ret.port
        );
#endif        
    // ctrace("h_add_list");        

    return ret;
}

_rtps_locator_t _rtps_get_default_unicast_locator()
{
    _rtps_locator_t ret=
        {
            .kind=RTPS_LOCATOR_KIND_UDPv4, 
            .port = 0,
            .addr.raw = {0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0},
        };        
    ret.port = _rtps_get_default_unicast_unicast_port(0,1);

    long domainId = strtol(_rtps_config_get(RTPS_CONFIG_DOMAIN_ID_KEY), NULL, 10);
    long partId = strtol(_rtps_config_get(RTPS_CONFIG_PARTICIPANT_ID_KEY), NULL, 10);
    ret.port = _rtps_get_default_unicast_unicast_port(domainId,partId);
//     ret.addr.udp4.addr.value = htonl(strtol(_rtps_config_get(RTPS_CONFIG_UNICAST_IP4_ADDR_KEY),NULL, 16));   
    uint32_t _addr=strtol(_rtps_config_get(RTPS_CONFIG_UNICAST_IP4_ADDR_KEY),NULL, 16);
    _z_be_store32(_addr, (uint8_t *)&ret.addr.udp4.addr.value);

#ifdef DEV_DEBUG_SCOUT_MSG
    ctrace("user unicast addr is %d.%d.%d.%d:%d ", 
        ret.addr.udp4.addr.field[0], ret.addr.udp4.addr.field[1], 
        ret.addr.udp4.addr.field[2], ret.addr.udp4.addr.field[3],
        ret.port
        );
#endif        
    // ctrace("h_add_list");        

    return ret;

    return ret;
}



//_rtps_locator_t _rtps_get_scout_locator(_rtps_what_t what)
//{
    // get local ip and make port
//    int domainId = _rtps_get_domainId();
  //  int participantId = _rtps_get_participantId();  // meta traffic participantid is 1

//}

z_result_t _rtps_init_scout_msg_data(_rtps_scouting_message_t *msg)
{
    _rtps_header_init(&msg->_header);
    msg->_info_ts = _rtps_time_now();
    msg->_dataflags = RTPS_LITTLE_ENDIAN | RTPS_DATA_DATA_FLAG;    
    msg->_dataheader._extraFlags = 0; 
    msg->_dataheader._octetsToInlineQos =_SUBMSG_IDSET_SIZE;
    msg->_dataheader._readerId = RTPS_ENTITYID_UNKNOWN;
    msg->_dataheader._writerId = RTPS_ENTITYID_SPDP_BUILTIN_PARTICIPANT_WRITER;
    msg->_dataheader._writerSN._high = 0;
    msg->_dataheader._writerSN._low= 1;

    // add parameter to list.    

    _rtps_scout_paramItem_list_t *curs = NULL;
    z_result_t ret  = _Z_RES_OK;   
    if (ret == _Z_RES_OK) // RTPS_PARAM_PID_PROTOCOL_VERSION
    {
        _rtps_scout_paramItem_t *data = z_malloc(sizeof(_rtps_scout_paramItem_t));    
        data->_pid = RTPS_PARAM_PID_PROTOCOL_VERSION;
        data->u._version = RTPS_PROTOCOL_VERSION_DEFAULT;
        curs = _rtps_scout_paramItem_list_push(curs, (_rtps_scout_paramItem_t *)data);
    }

    if (ret == _Z_RES_OK) // RTPS_PARAM_PID_VENDOR_ID    
    {
        _rtps_scout_paramItem_t *data = z_malloc(sizeof(_rtps_scout_paramItem_t));    
        data->_pid = RTPS_PARAM_PID_VENDOR_ID;
        data->u._vendor_id = RTPS_SCOUT_VENDORID_UNKNOWN;
        curs = _rtps_scout_paramItem_list_push(curs, (_rtps_scout_paramItem_t *)data);
    }

    if (ret == _Z_RES_OK) // RTPS_PARAM_PID_METATRAFFIC_UNICAST_LOCATOR    
    {
        _rtps_scout_paramItem_t *data = z_malloc(sizeof(_rtps_scout_paramItem_t));    
        data->_pid = RTPS_PARAM_PID_METATRAFFIC_UNICAST_LOCATOR;
        data->u._locator = _rtps_get_matartrafic_unicast_locator(); //
        curs = _rtps_scout_paramItem_list_push(curs, (_rtps_scout_paramItem_t *)data);
    }


    if (ret == _Z_RES_OK) // RTPS_PARAM_PID_DEFAULT_UNICAST_LOCATOR    
    {
        _rtps_scout_paramItem_t *data = z_malloc(sizeof(_rtps_scout_paramItem_t));    
        data->_pid = RTPS_PARAM_PID_DEFAULT_UNICAST_LOCATOR;
        data->u._locator = _rtps_get_default_unicast_locator(); //
        curs = _rtps_scout_paramItem_list_push(curs, (_rtps_scout_paramItem_t *)data);
    }

    if (ret == _Z_RES_OK) // RTPS_PARAM_PID_PARTICIPANT_LEASE_DURATION    
    {
        _rtps_scout_paramItem_t *data = z_malloc(sizeof(_rtps_scout_paramItem_t));    
        data->_pid = RTPS_PARAM_PID_PARTICIPANT_LEASE_DURATION;
        data->u._duration._seconds= 30;
        data->u._duration._fraction= 0;
        curs = _rtps_scout_paramItem_list_push(curs, (_rtps_scout_paramItem_t *)data);
    }

    if (ret == _Z_RES_OK) // RTPS_PARAM_PID_PARTICIPANT_GUID    
    {
        _rtps_scout_paramItem_t *data = z_malloc(sizeof(_rtps_scout_paramItem_t));    
        data->_pid = RTPS_PARAM_PID_PARTICIPANT_GUID;
        data->u._guid._guidPrefix = _rtps_get_core_guidprefix();        
        data->u._guid._entityId =  RTPS_ENTITYID_PARTICIPANT;       
        curs = _rtps_scout_paramItem_list_push(curs, (_rtps_scout_paramItem_t *)data);
    }

    if (ret == _Z_RES_OK) // RTPS_PARAM_PID_BUILTIN_ENDPOINT_SET    
    {
        _rtps_scout_paramItem_t *data = z_malloc(sizeof(_rtps_scout_paramItem_t));    
        data->_pid = RTPS_PARAM_PID_BUILTIN_ENDPOINT_SET;
        data->u._endpoint_set = RTPS_SCOUT_BUILTIN_ENDPOINT_SET;
        curs = _rtps_scout_paramItem_list_push(curs, (_rtps_scout_paramItem_t *)data);
    }        

    if (curs != NULL)
    {
        msg->_params = curs;
    }

    return ret;
#if 0
    ctrace("curs is %x ", curs);

    _z_wbuf_t _pwbf;

    _rtps_scout_parameterlist_cdr_encode(&_pwbf, &curs,1); // le == 1 means little endian

    
    ctrace("\t\t##########written size %d ", _z_wbuf_len(&_pwbf));

    _z_wbuf_reset(&_pwbf);
    
    _rtps_scout_paramItem_list_free(&curs);    // JUST debug    
#endif    

    //exit(1);
//    msg->_params = curs;
    //exit(1);
}

size_t _rtps_scout_paramItem_size(const _rtps_scout_paramItem_t *pitem)
{
    ctrace("_rtps_scout_paramItem_size called");
}

void _rtps_scout_paramItem_clear(_rtps_scout_paramItem_t *pitem)
{
    ctrace("_rtps_scout_paramItem_clear %s called", _rtps_parameter_pid_what(pitem->_pid));
    if(pitem->_pid == RTPS_PARAM_PID_ENTITY_NAME) {
        ctrace("_entityName free");
        if (pitem->u._entityName != NULL) {
            z_free(pitem->u._entityName);
        }
    } 
    else if (pitem->_pid == RTPS_PARAM_PID_USER_DATA) {
        ctrace("Userdata free");
        if (pitem->u._userData != NULL) {
            z_free(pitem->u._userData);
        }        
    }   
}

void _rtps_scout_paramItem_copy(_rtps_scout_paramItem_t *dst, const _rtps_scout_paramItem_t *src)
{    
    ctrace("_rtps_scout_paramItem_copy called");
}

void _rtps_scout_paramItem_free(_rtps_scout_paramItem_t **_item)
{    
    _rtps_scout_paramItem_t *ptr = *_item;

    if (ptr != NULL) {
        //_rtps_scout_paramItem_clear(ptr);

        z_free(ptr);
        *_item = NULL;
    }

    ctrace("_rtps_scout_paramItem_free called");
}


// scout param item codec

void _rtps_write_pad(_z_wbuf_t *zbf, int len)
{
    uint8_t pad[4] = {0,0,0,0};
    if (len < 4 && len >0) {
        _z_wbuf_write_bytes(zbf, pad, 0, len);
    }
}

z_result_t _rtps_scout_paramItem_cdr_encode(_z_wbuf_t *zbf, _rtps_scout_paramItem_t *pitem, int _le) // le == 1 means little endian
{
    ctrace(" PID %s will be encoded", _rtps_parameter_pid_what(pitem->_pid));    

    z_result_t ret = _Z_RES_OK;

    switch(pitem->_pid) {
        case RTPS_PARAM_PID_PROTOCOL_VERSION : {   // CORE LOGIC
                //ctrace("### protocol version len is %d", sizeof(_rtps_protocol_version_t));
                size_t buflen = sizeof(_rtps_protocol_version_t) + sizeof(_rtps_protocol_version_t) % 4;
                //ctrace("### buf len is %d ... ", buflen);
                *zbf = _z_wbuf_make(buflen, false);
                _z_wbuf_write_bytes(zbf, (uint8_t *)&(pitem->u._version), 0, sizeof(_rtps_protocol_version_t));
                _rtps_write_pad(zbf, buflen - sizeof(_rtps_protocol_version_t));
            }
            break;
        case RTPS_PARAM_PID_VENDOR_ID: {
                size_t buflen = sizeof(_rtps_vendor_id_t) + sizeof(_rtps_vendor_id_t) % 4;
                *zbf = _z_wbuf_make(buflen, false);
                _z_wbuf_write_bytes(zbf, (uint8_t *)&(pitem->u._vendor_id), 0, sizeof(_rtps_vendor_id_t));
                _rtps_write_pad(zbf, buflen - sizeof(_rtps_vendor_id_t));
            }
            break;
        case RTPS_PARAM_PID_PARTICIPANT_GUID: {
                size_t buflen = sizeof(_rtps_guid_t) + sizeof(_rtps_guid_t) % 4;
                //ctrace(">>??? _rtps_guid_t len is origin%d .. %d ... ", sizeof(_rtps_guid_t), buflen);
                *zbf = _z_wbuf_make(buflen, false);
                _z_wbuf_write_bytes(zbf, (uint8_t *)&(pitem->u._guid), 0, sizeof(_rtps_guid_t));
                _rtps_write_pad(zbf, buflen - sizeof(_rtps_guid_t));
            }
            break;
        case RTPS_PARAM_PID_METATRAFFIC_MULTICAST_LOCATOR:
        case RTPS_PARAM_PID_METATRAFFIC_UNICAST_LOCATOR: {
                size_t buflen = sizeof(_rtps_locator_t) + sizeof(_rtps_locator_t) % 4;
                //ctrace(">>??? METATRAFFIC_UNICAST len is origin %d .. %d ... ", sizeof(_rtps_locator_t), buflen);
                *zbf = _z_wbuf_make(buflen, false);
                _z_wbuf_write_bytes(zbf, (uint8_t *)&(pitem->u._locator), 0, sizeof(_rtps_locator_t));
                _rtps_write_pad(zbf, buflen - sizeof(_rtps_locator_t));
            }
            break;
        case RTPS_PARAM_PID_DEFAULT_MULTICAST_LOCATOR:
        case RTPS_PARAM_PID_DEFAULT_UNICAST_LOCATOR: {
                size_t buflen = sizeof(_rtps_locator_t) + sizeof(_rtps_locator_t) % 4;
                //ctrace(">>??? DEFAULT_UNICAST len is origin %d .. %d ... ", sizeof(_rtps_locator_t), buflen);
                *zbf = _z_wbuf_make(buflen, false);
                _z_wbuf_write_bytes(zbf, (uint8_t *)&(pitem->u._locator), 0, sizeof(_rtps_locator_t));
                _rtps_write_pad(zbf, buflen - sizeof(_rtps_locator_t));

            }
            break;
        case RTPS_PARAM_PID_PARTICIPANT_LEASE_DURATION: {
                size_t buflen = sizeof(_rtps_duration_t) + sizeof(_rtps_duration_t) % 4;
                //ctrace(">>??? LEASE_DURATION len is origin %d .. %d ... ", sizeof(_rtps_duration_t), buflen);
                *zbf = _z_wbuf_make(buflen, false);
                _z_wbuf_write_bytes(zbf, (uint8_t *)&(pitem->u._duration), 0, sizeof(_rtps_duration_t));
                _rtps_write_pad(zbf, buflen - sizeof(_rtps_duration_t));

            }
            break;        
        case RTPS_PARAM_PID_BUILTIN_ENDPOINT_SET: {
                size_t buflen = sizeof(_rtps_builtin_endpoint_set_t) + sizeof(_rtps_builtin_endpoint_set_t) % 4;
                //ctrace(">>??? ENDPOINT_SET len is origin %d .. %d ... ", sizeof(_rtps_builtin_endpoint_set_t), buflen);
                *zbf = _z_wbuf_make(buflen, false);
                _z_wbuf_write_bytes(zbf, (uint8_t *)&(pitem->u._endpoint_set), 0, sizeof(_rtps_builtin_endpoint_set_t));
                _rtps_write_pad(zbf, buflen - sizeof(_rtps_builtin_endpoint_set_t));
            }
            break;
        default:
            ret = _Z_ERR_MESSAGE_SERIALIZATION_FAILED;
            ctrace("!!! PID %s not supported yet in scout message ",_rtps_parameter_pid_what(pitem->_pid));
            break;
    }

    return ret;    
}

z_result_t _rtps_scout_parameterlist_cdr_encode(_z_wbuf_t *_owbf, _rtps_scout_paramItem_list_t **_list, int _le) // le == 1 means little endian
{
    _rtps_scout_paramItem_list_t *curs = (*_list);
    size_t len = _rtps_scout_paramItem_list_len(curs);

    z_result_t ret = _Z_RES_OK;

    *_owbf = _z_wbuf_make(sizeof(_rtps_parameter_h_t), true);
    //*_wbf = _z_wbuf_make(120, true);

    int szz = 0;

    for (size_t i=0; i < len && ret ==_Z_RES_OK; i++)
    {
        _rtps_scout_paramItem_t *_pitem = _rtps_scout_paramItem_list_head(curs);
        _rtps_parameter_h_t _param_h = {_pitem->_pid, 0};        
        _z_wbuf_t _pwbf;        

        ret = _rtps_scout_paramItem_cdr_encode(&_pwbf, _pitem, _le);

        if (ret == _Z_RES_OK)
        {
            _param_h._length = (uint16_t) _z_wbuf_len(&_pwbf);

            // write param header
            _z_wbuf_write_bytes(_owbf, (uint8_t *)&_param_h, 0, sizeof(_rtps_parameter_h_t));            

            // attach paramItem wbuf(_pwbf) to out buf(_wbf)
            if (ret == _Z_RES_OK) {
                ret = _rtps_wbuf_add_wbuf(_owbf, &_pwbf);                
            }    // !!do not clear or reset _pwbf: its internal ios was appended out buf(_wbf)

            
#ifdef DEV_DEBUG_SCOUT_MSG          
            if (ret == _Z_RES_OK) {
                _z_zbuf_t _pzbf;

                _pzbf = _z_wbuf_to_zbuf(&_pwbf);
                _rtps_parameter_cdr_decode(&_pzbf, _pitem->_pid, _le);

                if (_z_wbuf_len(&_pwbf) != 0)
                {                    
                    _z_zbuf_clear(&_pzbf);
                }
            }            
#endif      
            szz = szz + sizeof(_rtps_parameter_h_t) + _param_h._length ;
        }

        //ctrace("PID is %d..%d..%d ", _pitem->_pid, _param_h._parameter_id, _param_h._length);
        curs = _rtps_scout_paramItem_list_pop(curs,NULL);
    }

    // pid sentinal encode
    if (ret == _Z_RES_OK)
    {
        _rtps_parameter_h_t _sentianl = { RTPS_PARAM_PID_SENTINEL, 0};
        _z_wbuf_write_bytes(_owbf, (uint8_t *)&(_sentianl), 0,sizeof(_rtps_parameter_h_t));
    }

    szz = szz + sizeof(_rtps_parameter_h_t);

#ifdef DEV_DEBUG_SCOUT_MSG
    ctrace("#####ooooooo written size in cdr_encode %d ", szz);
#endif    

    *_list = curs;    

    return ret;
}



z_result_t _rtps_scouting_message_encode(_z_wbuf_t *buf, _rtps_scouting_message_t *msg){
    z_result_t ret = _Z_RES_OK;

    _z_wbuf_t _i_wbf;

    _i_wbf = _z_wbuf_make(sizeof(_rtps_header_t), true);
    // write RTPS Header    
    ret = _z_wbuf_write_bytes(&_i_wbf,(uint8_t *)&msg->_header, 0, sizeof(_rtps_header_t));
    // write INFO_TS submessage
    if (ret == _Z_RES_OK) {
        _rtps_submsg_header_t _sub_header; 
        _sub_header._submsg_id = RTPS_INFO_TS;
        _sub_header._flags = RTPS_LITTLE_ENDIAN;
        _sub_header._submsg_length = sizeof(_rtps_time_t);

        ret = _z_wbuf_write_bytes(&_i_wbf,(uint8_t *)&_sub_header, 0, sizeof(_rtps_submsg_header_t)); 

        if (ret == _Z_RES_OK) {
            ret = _z_wbuf_write_bytes(&_i_wbf,(uint8_t *)&msg->_info_ts, 0, sizeof(_rtps_time_t)); 
        }
    }

    // write DATA submessage for scout message
    if (ret ==_Z_RES_OK ){        
        if (msg->_data_reuse != 1)
        {
            _rtps_submsg_header_t _sub_header; 
            _z_wbuf_t _datasub_wbf;

            _sub_header._submsg_id = RTPS_DATA;
            _sub_header._flags = msg->_dataflags;
            _sub_header._submsg_length = 0;
            ret = _rtps_scout_parameterlist_cdr_encode(&_datasub_wbf, &msg->_params, RTPS_LITTLE_ENDIAN);

            msg->_encoded_datasub = _z_wbuf_make(sizeof(_rtps_submsg_header_t), true);

            if (ret == _Z_RES_OK) {
                // write submessage header
                // we do not use inline qos in this implemation.
                _sub_header._submsg_length = 
                    sizeof(_rtps_data_submsg_head_t) + sizeof(_rtps_cdr_scheme_t) + _z_wbuf_len(&_datasub_wbf);
                ret = _z_wbuf_write_bytes(&msg->_encoded_datasub,(uint8_t *)&_sub_header, 0, sizeof(_rtps_submsg_header_t)); 
            }

            if (ret == _Z_RES_OK) {
                // write data messag header
                ret = _z_wbuf_write_bytes(&msg->_encoded_datasub,(uint8_t *)&msg->_dataheader, 0, sizeof(_rtps_data_submsg_head_t)); 
            }

            if (ret == _Z_RES_OK) {
                // write cdr encoded data as payload
                
                // write CDR scheme
                _z_wbuf_write_bytes(&msg->_encoded_datasub,(uint8_t *)&RTPS_PL_CDR_LE, 0, sizeof(_rtps_cdr_scheme_t)); 

                // write payload
                ret = _rtps_wbuf_add_wbuf(&msg->_encoded_datasub, &_datasub_wbf);
            }

            _rtps_scout_paramItem_list_free(&msg->_params);
            msg->_params = NULL;
            msg->_data_reuse = 1;
        }
        // write and compact reused datasub 

        // compact wbuf to one packet

        size_t len = _z_wbuf_len(&_i_wbf) + _z_wbuf_len(&(msg->_encoded_datasub));
        len = len + len % 4;
        *buf = _z_wbuf_make(len, true);
        printf("ENCODED SIZE WILL BE ,,, $%d\n", len);

        
        for (size_t i = _i_wbf._r_idx; i<= _i_wbf._w_idx;i++) {
            _z_iosli_t *ios = _z_wbuf_get_iosli(&_i_wbf, i);
            _z_wbuf_write_bytes(buf, ios->_buf, ios->_r_pos, _z_iosli_readable(ios));
        }

        for (size_t i = msg->_encoded_datasub._r_idx; i<= msg->_encoded_datasub._w_idx;i++) {
            _z_iosli_t *ios = _z_wbuf_get_iosli(&(msg->_encoded_datasub), i);
            _z_wbuf_write_bytes(buf, ios->_buf, ios->_r_pos, _z_iosli_readable(ios));
        }

        printf("WRITTEN size is %d !!!  \n",_z_wbuf_len(buf));

        printf(" packet size is %d !!!\n",_z_iosli_readable(_z_wbuf_get_iosli(buf, 0)));
        printf(" obf len  is %d...%d... !!!\n",_z_wbuf_len(buf),_z_wbuf_space_left(buf) );

        
    }
  

    return ret;
}



_rtps_submsg_list_t *_rtps_scouting_message_decode(_rtps_scouting_message_t *s_msg, _z_zbuf_t *zbf)     
{
    _rtps_submsg_list_t *ret = NULL;
    z_result_t err = _Z_RES_OK;

    int len;

    len = _z_zbuf_len(zbf);   

    if (len < sizeof(_rtps_header_t)) {
        ctrace("_Z_ERR_MESSAGE_UNEXPECTED");
        err = _Z_ERR_MESSAGE_UNEXPECTED;        
    }

    if (err == _Z_RES_OK) {
                  
        printf("readlen: %d \n", len);    

        // read rtps header in scouting(PDP) message
        _z_zbuf_read_bytes(zbf, (uint8_t *)&s_msg->_header, 0, sizeof(_rtps_header_t));

        // check rtps header is valid in scouting(PDP) message

        if (_rtps_header_invalid(&s_msg->_header)){
            printf("Invalid Header!!!!");
            err = _Z_ERR_MESSAGE_UNEXPECTED;        
        }
#ifndef DEV_DEBUG
        if (_rtps_guid_prefix_loopback(&s_msg->_header)) {
            printf("Loopback Header!!!!!!");
            err = _Z_ERR_MESSAGE_UNEXPECTED;        
        }
#endif        
    }
#ifdef DEV_DEBUG    
    if (err == _Z_RES_OK) {
        printf("%.*s .. %d %d .. %d %d .. \n", 
            4, s_msg->_header._protocol, 
            s_msg->_header._version[0], s_msg->_header._version[1],
            s_msg->_header._vendorId[0], s_msg->_header._vendorId[1]);
        for (int i=0; i< 12; i++ ) printf("%x ", s_msg->_header._guidPrefix[i]);
        printf("\n");
    }
#endif    

    if (err == _Z_RES_OK) { // HEADER is valid! // submessage
        while(_z_zbuf_can_read(zbf) && err == _Z_RES_OK) {
            _rtps_submsg_header_t _sub_header;            
            _z_zbuf_read_bytes(zbf, (uint8_t *)&_sub_header, 0, sizeof(_rtps_submsg_header_t));            
            printf("RECEIVE SUBMSG 0x%x %d\n", _sub_header._submsg_id, _sub_header._submsg_length);

            if (_sub_header._submsg_length > 0) {
                switch(_sub_header._submsg_id) {
                    case RTPS_INFO_TS: {
                            _z_zbuf_read_bytes(zbf, (uint8_t *)&s_msg->_info_ts, 0, sizeof(_rtps_time_t));
                            printf("  info ts is %d\n", _rtps_time_to_sec(&s_msg->_info_ts)); // (float)s_msg->_info_ts._seconds * ((float)s_msg->_info_ts._fraction)/(float)4294967296);
                        }
                        break;                    
                    case RTPS_DATA: {
                            printf("  submsg DATA decoding...\n");
                            _rtps_data_submsg_t *_submsg = NULL;
                            _submsg = _rtps_scout_submsg_data_decode(zbf, _sub_header._flags, _sub_header._submsg_length);                            
                        }
                        break;
                    default: {
                            printf("<<SUBMSG: %s \n", _rtps_submsg_kind_what(_sub_header._submsg_id));
                            size_t pos = _z_zbuf_get_rpos(zbf);
                            pos = pos + _sub_header._submsg_length;
                            if (pos > _z_zbuf_get_wpos(zbf)){
                                printf("Illegal operation %d > %d ", pos, _z_zbuf_get_wpos(zbf));
                                ret = _Z_ERR_MESSAGE_UNEXPECTED;
                                break;
                            }
                            _z_zbuf_set_rpos(zbf, pos);
                        }
                }
            }


            // size_t pos = _z_zbuf_get_rpos(zbf);
            // pos = pos + _sub_header._submsg_length;
            // if (pos > _z_zbuf_get_wpos(zbf))
            // {
            //     printf("Illegal operation %d > %d ", pos, _z_zbuf_get_wpos(zbf));
            //     break;
            // }
            // _z_zbuf_set_rpos(zbf, pos);
        }
    }

    return ret;

    //return _rtps_scouting_message_decode_na(s_msg, zbf);    
}


void _rtps_scouting_message_clear(_rtps_scouting_message_t *data)
{
    if (data->_params != NULL) {        
        _rtps_scout_paramItem_list_free(&data->_params);
        data->_params = NULL;
    }

    if (data->_data_reuse == 1)
    {        
        if(_z_wbuf_len(&data->_encoded_datasub)>0){     
            _z_wbuf_clear(&data->_encoded_datasub);
        }
    }
}