#include "zenoh-pico/protocol/core.h"
#include "zenoh-pico/utils/endianness.h"
#include "rtps/types.h"
#include "rtps/cdr_codec.h"
#include "rtps/data_submsg.h"

// for dev
#include "rtps/utils_what.h"

#if defined(__BYTE_ORDER__) && __BYTE_ORDER__ == __ORDER_BIG_ENDIAN__
#error host big endian not supported
#endif


void *_rtps_parameter_cdr_decode(_z_zbuf_t *zbf, uint16_t paramId, int _le)
{
    ctrace(" PID is %x %s len is %d", paramId, _rtps_parameter_pid_what(paramId), _z_zbuf_len(zbf));

    switch (paramId) {        
        case RTPS_PARAM_PID_PROTOCOL_VERSION : {   // CORE LOGIC
                _rtps_protocol_version_t _version;  // skip remaind
                _z_zbuf_read_bytes(zbf, &_version, 0, sizeof(_rtps_protocol_version_t));
                ctrace(" version=%x %x ", _version._major, _version._minor);
            }
            break;
        case RTPS_PARAM_PID_VENDOR_ID: {    // CORE LOGIC
                _rtps_vendor_id_t _vendor_id; // id is written Big Endian.. 
                _z_zbuf_read_bytes(zbf, &_vendor_id, 0, sizeof(_rtps_vendor_id_t));
                ctrace(" vendorid=%x %s ", _vendor_id._id._vendorId, _rtps_vendor_id_what(_vendor_id));
            }            
            break;
        case RTPS_PARAM_PID_PARTICIPANT_GUID :{  // CORE LOGIC
                _rtps_guid_t _guid;
                _z_zbuf_read_bytes(zbf, &_guid, 0, sizeof(_rtps_guid_t));

                for (int i=0;i<12;i++) printf(" %d ", _guid._guidPrefix._ids[i]);
                ctrace("\n guid entityid key=(%x %x %x),kind =[%x]  ", 
                    _guid._entityId._entityKey[0],_guid._entityId._entityKey[1],_guid._entityId._entityKey[2],
                    _guid._entityId._entityKind);
                ctrace(" guid entity=%s ", _rtps_entity_id_what(&_guid._entityId));

            }
            break;
        case RTPS_PARAM_PID_METATRAFFIC_UNICAST_LOCATOR :    //  NOT CORE LOGIC
        case RTPS_PARAM_PID_METATRAFFIC_MULTICAST_LOCATOR :     //  NOT CORE LOGIC  
            {
                _rtps_locator_t _locator;
                _z_zbuf_read_bytes(zbf, &_locator, 0, sizeof(_rtps_locator_t));
                if (_locator.kind) { //} == 1) { // udp4
                    ctrace(" %d addr %d.%d.%d.%d:%d ", _locator.kind,
                        _locator.addr.udp4.addr.field[0], _locator.addr.udp4.addr.field[1],
                        _locator.addr.udp4.addr.field[2], _locator.addr.udp4.addr.field[3],
                        _locator.port
                        );               
                } else {
                    ctrace("addr kind %d .. unknown", _locator.kind);
                }
            }                
            break;                            
        case RTPS_PARAM_PID_DEFAULT_UNICAST_LOCATOR :      //  CORE LOGIC       
        case RTPS_PARAM_PID_DEFAULT_MULTICAST_LOCATOR :    //  NOT CORE LOGIC
            {
                _rtps_locator_t _locator;
                _z_zbuf_read_bytes(zbf, &_locator, 0, sizeof(_rtps_locator_t));
                if (_locator.kind) { //} == 1) { // udp4
                    ctrace(" %d addr %d.%d.%d.%d:%d ", _locator.kind,
                        _locator.addr.udp4.addr.field[0], _locator.addr.udp4.addr.field[1],
                        _locator.addr.udp4.addr.field[2], _locator.addr.udp4.addr.field[3],
                        _locator.port
                        );               
                } else {
                    ctrace("addr kind %d .. unknown", _locator.kind);
                }
            }          
            break;        
        case RTPS_PARAM_PID_PARTICIPANT_LEASE_DURATION :  //  CORE LOGIC for check scout
            {
                _rtps_duration_t _lease_duration;
                _z_zbuf_read_bytes(zbf, &_lease_duration, 0, sizeof(_rtps_duration_t));
                ctrace(" duration = %ld %lu = %lds", 
                    _lease_duration._seconds, 
                    _lease_duration._fraction, 
                    _rtps_duration_to_sec(&_lease_duration)
                );
            }
            break;        
        case RTPS_PARAM_PID_BUILTIN_ENDPOINT_SET :  // NOT CORE LOGIC just 0x0f is ok
            {
                _rtps_builtin_endpoint_set_t _value;
                _z_zbuf_read_bytes(zbf, &_value, 0, sizeof(_rtps_builtin_endpoint_set_t));
                ctrace(" builtin_endpoint_set %08x", _value);
                _rtps_builtin_endpoint_set_what(_value);
                _rtps_builtin_endpoint_set_what(0x0000003f);
            }
            break;        
        case RTPS_PARAM_PID_ENTITY_NAME :      // NOT CORE LOGIC
            {
                _rtps_entityname_t *entityName = (_rtps_entityname_t *)z_malloc(_z_zbuf_len(zbf));
                _z_zbuf_read_bytes(zbf, entityName, 0, _z_zbuf_len(zbf));
                ctrace(" entity len is %d name=[%s] ",entityName->_length, entityName->_value);                
                // for debug
                z_free(entityName);
            }
            break;        
        case RTPS_PARAM_PID_USER_DATA :           // CAN BE CORE LOGIC
            {  // UserDataQosPolicy // it is not supported, currently.
                _rtps_string_t *userData = (_rtps_string_t *)z_malloc(_z_zbuf_len(zbf));
                _z_zbuf_read_bytes(zbf, userData, 0, _z_zbuf_len(zbf));
                ctrace(" user data %d name=[%s] ",userData->_length, userData->_value);                
                // for debug
                z_free(userData);                
            }
            break;        
        case RTPS_PARAM_PID_PROPERTY_LIST :       // NOT CORE LOGIC  
            { // sequence<Property_t>
               //read sequnce length
               uint32_t seqLen = 0;
                _z_zbuf_read_bytes(zbf, &seqLen, 0, sizeof(uint32_t));
                ctrace(" %d property included ", seqLen);
                for (int i=0;i<seqLen;i++) // name . vlaue.
                {
                    uint8_t name[100], value[100];
                    uint32_t nl = 0, vl;
                    _z_zbuf_read_bytes(zbf, &nl, 0, sizeof(uint32_t));
                    //ctrace("nl is %d\n", nl);
                    if(nl % 4) nl = nl + (4 - (nl %4)); // paded
                    //ctrace("after nl is %d\n", nl);                    
                    _z_zbuf_read_bytes(zbf, name, 0, nl);                    
                    _z_zbuf_read_bytes(zbf, &vl, 0, sizeof(uint32_t));
                    //ctrace("vl is %d\n", vl);
                    if(vl % 4) vl = vl + (4 - (vl%4)); // paded
                    //ctrace("after vl is %d\n", vl);                    
                    _z_zbuf_read_bytes(zbf, value, 0, vl);
                    ctrace(" property n=[%s], v=[%s] ", name, value);
                }
            }

            break;        
        default:
            ctrace(" PID %s is not supported", _rtps_parameter_pid_what(paramId));
            break;
    }

}

// void ctrace_rtps_paramItem(_rtps_paramItem_t *item)
// {
    

// }



void *_rtps_parameterlist_cdr_decode(_z_zbuf_t *zbf, int _le) // le == 1 means little endian
{
    ctrace("enter");
    char *ret = NULL;

    z_result_t err = _Z_RES_OK;   

    if (_le) {  // little endian
        // _z_le_load16()        
        int itemnum = 0;
        while (_z_zbuf_can_read(zbf)){
            _rtps_parameter_t _param;            
            _z_zbuf_read_bytes(zbf, (uint8_t *)&_param._head, 0, sizeof(_rtps_parameter_h_t));            
            if (_param._head._parameter_id != RTPS_PARAM_PID_SENTINEL) 
            {
                //ctrace("Parameter ID %x:%s %d ....\n ",_param._head._parameter_id, _rtps_parameter_pid_what(_param._head._parameter_id),_param._head._length );
                
                ctrace("Parameter ID %x %d .... ",_param._head._parameter_id,_param._head._length );
                _z_zbuf_t _zbf_parameter = _z_zbuf_view(zbf, _param._head._length);                
                //_rtps_paramItem_t *_paramItem;
                void *_paramItem;
                _paramItem = _rtps_parameter_cdr_decode(&_zbf_parameter, _param._head._parameter_id , _le);
                //ctrace_rtps_paramItem(_paramItem);
                _z_zbuf_set_rpos(zbf, _z_zbuf_get_rpos(zbf) + _param._head._length);
                

                //char buf[100];
                //memset(buf,0,100);
                //_z_zbuf_read_bytes(zbf, buf, 0, _param._head._length);
            }
            //ctrace("Item %d\n", itemnum++);
        }
    } else {
        ctrace("NO implemented");
        exit(1);
        //_z_be_load16()
    }

    return ret;
}