#include "zenoh-pico/system/platform.h"
#include "rtps/types.h"

_rtps_entity_id_kind_t _rtps_entity_id_kind( _rtps_entity_id_t *_id)
{
    _rtps_entity_id_kind_t ret = ENTITYID_ERR;   

    switch(_id->_entityKind) {
        case RTPS_ENTITYKIND_USER_UNKNOWN: 
            ret = ENTITYID_USER_UNKNOWN;
            break;
        case RTPS_ENTITYKIND_BUILTIN_UNKNOWN: 
            ret = ENTITYID_BUILTIN_UNKNOWN;
            break;
        case RTPS_ENTITYKIND_BUILTIN_PARTIPANT: ret = ENTITYID_PARTICIPANT;
            break;
        case RTPS_ENTITYKIND_BUILTIN_WRITER_WITH_KEY: 
            if (_id->_entityKey[1] == 0x01) 
                ret = ENTITYID_SPDP_BUILTIN_PARTICIPANT_WRITER;
            else if (_id->_entityKey[2] == 0x02)
                ret = ENTITYID_P2P_BUILTIN_PARTICIPANT_MESSAGE_WRITER;
            else if (_id->_entityKey[2] == 0x03)
                ret = ENTITYID_SEDP_BUILTIN_PUBLICATIONS_WRITER;
            else if (_id->_entityKey[2] == 0x04)
                ret = ENTITYID_SEDP_BUILTIN_SUBSCRIPTIONS_WRITER;            
            break;        
        case RTPS_ENTITYKIND_BUILTIN_READER_WITH_KEY:
            if (_id->_entityKey[1] == 0x01) 
                ret = ENTITYID_SPDP_BUILTIN_PARTICIPANT_READER;
            else if (_id->_entityKey[2] == 0x02)
                ret = ENTITYID_P2P_BUILTIN_PARTICIPANT_MESSAGE_READER;
            else if (_id->_entityKey[2] == 0x03)
                ret = ENTITYID_SEDP_BUILTIN_PUBLICATIONS_READER;
            else if (_id->_entityKey[2] == 0x04)
                ret = ENTITYID_SEDP_BUILTIN_SUBSCRIPTIONS_READER;             
            break;
        case RTPS_ENTITYKIND_USER_WRITER_WITH_KEY: 
            ret = ENTITYID_USER_WRITER_WITH_KEY;
            break;
        case RTPS_ENTITYKIND_USER_WRITER_NO_KEY:
            ret = ENTITYID_USER_WRITER_NO_KEY; 
            break;
        case RTPS_ENTITYKIND_USER_READER_NO_KEY: 
            ret = ENTITYID_USER_READER_NO_KEY; 
            break;
        case RTPS_ENTITYKIND_USER_READER_WITH_KEY: 
            ret = ENTITYID_USER_READER_WITH_KEY; 
            break;
    }

    return ret;

}