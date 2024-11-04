#include "zenoh-pico/protocol/core.h"
#include "zenoh-pico/utils/endianness.h"
#include "rtps/data_submsg.h"

/*

typedef struct {   
    uint16_t _extraFlags;  // 32bit : = 0
    uint16_t _octetsToInlineQos;    
    _rtps_entity_id_t _readerId;
    _rtps_entity_id_t _writerId;
    _rtps_sequence_t _writerSN;
} __attribute__((packed)) _rtps_data_submsg_head_t;  //time = seconds + (fraction / 2^(32))

typedef struct {
    bool _dataFlag;
    bool _inlineQosFlag;
    bool _keyFlag;
    _rtps_data_submsg_head_t _head;
    //_rtps_parameter_list_t *_inlineQos;
    uint8_t *inlineQos;
    //_rtps_serialized_payload_t *_payload;
    uint8_t *_payload;
} _rtps_data_submsg_t;

*/

void check_rtps_data_submsg(_rtps_data_submsg_t *data) {
    ctrace("data %d, inline %d, key %d",data->_dataFlag, data->_qosFlag, data->_keyFlag);
    ctrace("_readerId is %x %x %x[%x] ", data->_head._readerId._entityKey[0],
            data->_head._readerId._entityKey[1],data->_head._readerId._entityKey[2],
            data->_head._readerId._entityKind);        
    ctrace("_writerId is %x %x %x[%x] ", data->_head._writerId._entityKey[0],
            data->_head._writerId._entityKey[1],data->_head._writerId._entityKey[2],
            data->_head._writerId._entityKind);
    ctrace("_writerSN is %d %d",  data->_head._writerSN._high, data->_head._writerSN._low);
}

_rtps_data_submsg_t *_rtps_scout_submsg_data_decode(_z_zbuf_t *zbf, uint8_t flags, uint16_t length)
{    
    z_result_t err = _Z_RES_OK;
    _rtps_data_submsg_t *submsg_data= (_rtps_data_submsg_t *)z_malloc(sizeof(_rtps_data_submsg_t));

    submsg_data->_qosFlag = ((flags & 0x02) == 0x02);
    submsg_data->_dataFlag = ((flags & 0x04) == 0x04);    
    submsg_data->_keyFlag = ((flags & 0x08) == 0x08); 
    submsg_data->_bigEndian = ((flags & 0x01) == 0); 

    ctrace("submsg %d ... %d ",_z_zbuf_len(zbf), length );    
    ctrace(" flag %x ", flags);
    ctrace(" qos flag %d ", submsg_data->_qosFlag);
    ctrace(" data flag %d ", submsg_data->_dataFlag);
    ctrace(" _keyFlag flag %d ", submsg_data->_keyFlag);
    ctrace(" _bigEndian flag %d ", submsg_data->_bigEndian);
    

    if (err == _Z_RES_OK && length >=sizeof(_rtps_data_submsg_head_t)) {
        size_t _payloadLen = 0;

        _z_zbuf_read_bytes(zbf, (uint8_t *)&submsg_data->_head, 0, sizeof(_rtps_data_submsg_head_t));

        if (submsg_data->_qosFlag) {
            // read qos
            ctrace("QOS exist!!1");

        } else {            
            // skip to payload
            ctrace("qos len is %d %d",submsg_data->_head._octetsToInlineQos ,_SUBMSG_IDSET_SIZE);
            size_t pos = _z_zbuf_get_rpos(zbf);            
            _payloadLen =  length - (submsg_data->_head._octetsToInlineQos + 4);
            pos = pos + submsg_data->_head._octetsToInlineQos - _SUBMSG_IDSET_SIZE;            
            _z_zbuf_set_rpos(zbf, pos);
        }

        ctrace("reader ID %x %x %x %x ",
            submsg_data->_head._readerId._entityKey[0], 
            submsg_data->_head._readerId._entityKey[1], 
            submsg_data->_head._readerId._entityKey[2], 
            submsg_data->_head._readerId._entityKind
        );
        ctrace("writer ID %x %x %x %x ",
            submsg_data->_head._writerId._entityKey[0], 
            submsg_data->_head._writerId._entityKey[1], 
            submsg_data->_head._writerId._entityKey[2], 
            submsg_data->_head._writerId._entityKind
        );

        // dump payload
#if 0 // for debug        
        char _dump[536];
        _z_zbuf_read_bytes(zbf, (uint8_t *)_dump, 0, _payloadLen);

        dump_bytes(_dump, _payloadLen);
#endif        

        // check SPDP
        _rtps_entity_id_kind_t _readerKind = _rtps_entity_id_kind(&submsg_data->_head._readerId);
        _rtps_entity_id_kind_t _writerKind = _rtps_entity_id_kind(&submsg_data->_head._writerId);        

        if (_readerKind == ENTITYID_SPDP_BUILTIN_PARTICIPANT_READER || 
            _writerKind == ENTITYID_SPDP_BUILTIN_PARTICIPANT_WRITER) {             
            ctrace("SCOUT Message received!!");

            ctrace("payd len is %d .. %d ",_payloadLen , _z_zbuf_len(zbf));            

            _z_zbuf_t _zbf_payload = _z_zbuf_view(zbf, _payloadLen);           

            // skip payload (we will use zbuf view)
            size_t pos = _z_zbuf_get_rpos(zbf) + _payloadLen;
            _z_zbuf_set_rpos(zbf, pos); 

            if (_z_zbuf_len(&_zbf_payload) != _payloadLen) {             
                err = _Z_ERR_MESSAGE_UNEXPECTED;
                ctrace("_Z_ERR_MESSAGE_UNEXPECTED");
            }

            if (err == _Z_RES_OK) {
                ctrace(" SCOUT SN %x %x", submsg_data->_head._writerSN._high,submsg_data->_head._writerSN._low);
                // read builtin PDP message
                ctrace("paydload len is %d",_payloadLen );

                // scheme
                uint8_t _cdr_scheme_opts[4]; 
                _z_zbuf_read_bytes(&_zbf_payload, _cdr_scheme_opts, 0, 4);
                //_scheme = _z_host_le_load16((uint8_t *)&_scheme);
                ctrace("SCHEME %x %x ", _cdr_scheme_opts[0], _cdr_scheme_opts[1]);

                switch(_cdr_scheme_opts[1]) {
                    case 0x00: // CDR_BE
                        break;
                    case 0x01: // CDR_LE
                        break;
                    case 0x02: // PL_CDR_BE
                        _rtps_parameterlist_cdr_decode(&_zbf_payload, 0); // 1 means little endian
                        break;
                    case 0x03: // PL_CDR_LE // ParameterList CDR LittleEndian
                        _rtps_parameterlist_cdr_decode(&_zbf_payload, 1); // 1 means little endian
                        break;
                }
            }
            
        } else {
            ctrace("!!!! NO SCOUT message kind %d %d ",_readerKind, _writerKind);
        
        // read data

        
            ctrace("Data payload size is %d", length - submsg_data->_head._octetsToInlineQos);
            {
                size_t pos = _z_zbuf_get_rpos(zbf) + length - sizeof(_rtps_data_submsg_head_t) - submsg_data->_head._octetsToInlineQos;
                _z_zbuf_set_rpos(zbf, pos); // it make cursor to data 
            }
            check_rtps_data_submsg(submsg_data);

            
        }                
        
    }

    z_free(submsg_data);
//    exit(1);

    return NULL;
}

