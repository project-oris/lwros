#include "rtps/cdr_codec.h"

#include "rtps/utils_what.h"

char *_rtps_submsg_kind_what( _rtps_submsg_kind_t kind)
{
    switch(kind) {
        case RTPS_PAD: return "RTPS_PAD";        
        case RTPS_ACKNACK: return "RTPS_ACKNACK";
        case RTPS_HEARTBEAT: return "RTPS_HEARTBEAT";
        case RTPS_GAP: return "RTPS_GAP";
        case RTPS_INFO_TS: return "RTPS_INFO_TS";
        case RTPS_INFO_SRC: return "RTPS_INFO_SRC";
        case RTPS_INFO_REPLY_IP4: return "RTPS_INFO_REPLY_IP4";
        case RTPS_INFO_DST: return "RTPS_INFO_DST";
        case RTPS_INFO_REPLY: return "RTPS_INFO_REPLY";
        case RTPS_NACK_FRAG: return "RTPS_NACK_FRAG";
        case RTPS_HEARTBEAT_FRAG: return "RTPS_HEARTBEAT_FRAG";
        case RTPS_DATA: return "RTPS_DATA";
        case RTPS_DATA_FRAG: return "RTPS_DATA_FRAG";
    }

    return "RTPS_UNKNOWN";
}

char *_rtps_parameter_pid_what(uint16_t pid)
{
    char *ret = "UNKNOWN";
    switch (pid) {
        case RTPS_PARAM_PID_PAD: ret = "RTPS_PARAM_PID_PAD"; break;
        case RTPS_PARAM_PID_SENTINEL: ret = "RTPS_PARAM_PID_SENTINEL"; break;
        case RTPS_PARAM_PID_PARTICIPANT_LEASE_DURATION: ret = "RTPS_PARAM_PID_PARTICIPANT_LEASE_DURATION"; break;
        case RTPS_PARAM_PID_TOPIC_NAME: ret = "RTPS_PARAM_PID_TOPIC_NAME"; break;
        case RTPS_PARAM_PID_TYPE_NAME: ret = "RTPS_PARAM_PID_TYPE_NAME"; break;        
        case RTPS_PARAM_PID_PROTOCOL_VERSION: ret = "RTPS_PARAM_PID_PROTOCOL_VERSION"; break;
        case RTPS_PARAM_PID_VENDOR_ID: ret = "RTPS_PARAM_PID_VENDOR_ID"; break;
        case RTPS_PARAM_PID_RELIABILITY: ret = "RTPS_PARAM_PID_RELIABILITY"; break;
        case RTPS_PARAM_PID_LIVELINESS: ret = "RTPS_PARAM_PID_LIVELINESS"; break;
        case RTPS_PARAM_PID_DURABILITY: ret = "RTPS_PARAM_PID_DURABILITY"; break;
        case RTPS_PARAM_PID_PRESENTATION: ret = "RTPS_PARAM_PID_PRESENTATION"; break;
        case RTPS_PARAM_PID_PARTITION: ret = "RTPS_PARAM_PID_PARTITION"; break;
        case RTPS_PARAM_PID_DEFAULT_UNICAST_LOCATOR: ret = "RTPS_PARAM_PID_DEFAULT_UNICAST_LOCATOR"; break;
        case RTPS_PARAM_PID_METATRAFFIC_UNICAST_LOCATOR: ret = "RTPS_PARAM_PID_METATRAFFIC_UNICAST_LOCATOR"; break;
        case RTPS_PARAM_PID_METATRAFFIC_MULTICAST_LOCATOR: ret = "RTPS_PARAM_PID_METATRAFFIC_MULTICAST_LOCATOR"; break;
        case RTPS_PARAM_PID_HISTORY: ret = "RTPS_PARAM_PID_HISTORY"; break;
        case RTPS_PARAM_PID_DEFAULT_MULTICAST_LOCATOR: ret = "RTPS_PARAM_PID_DEFAULT_MULTICAST_LOCATOR"; break;
        case RTPS_PARAM_PID_TRANSPORT_PRIORITY: ret = "RTPS_PARAM_PID_TRANSPORT_PRIORITY"; break;
        case RTPS_PARAM_PID_PARTICIPANT_GUID: ret = "RTPS_PARAM_PID_PARTICIPANT_GUID"; break;
        case RTPS_PARAM_PID_BUILTIN_ENDPOINT_SET: ret = "RTPS_PARAM_PID_BUILTIN_ENDPOINT_SET"; break;
        case RTPS_PARAM_PID_PROPERTY_LIST: ret = "RTPS_PARAM_PID_PROPERTY_LIST"; break;
        case RTPS_PARAM_PID_ENDPOINT_GUID: ret = "RTPS_PARAM_PID_ENDPOINT_GUID"; break;
        case RTPS_PARAM_PID_KEY_HASH: ret = "RTPS_PARAM_PID_KEY_HASH"; break;
        case RTPS_PARAM_PID_USER_DATA: ret = "RTPS_PARAM_PID_USER_DATA"; break;
        case RTPS_PARAM_PID_GROUP_DATA: ret = "RTPS_PARAM_PID_GROUP_DATA"; break;
        case RTPS_PARAM_PID_TOPIC_DATA: ret = "RTPS_PARAM_PID_TOPIC_DATA"; break;
        case RTPS_PARAM_PID_ENTITY_NAME: ret = "RTPS_PARAM_PID_ENTITY_NAME"; break;        

        default:
            printf("PID is %x \n", pid);
    }    

    return ret;
}

char *_rtps_vendor_id_what(_rtps_vendor_id_t vid)
{
  switch (vid._id._vendorId) // case is little endian but rtps use big endian
  {
    case 0x0101: return "RTI Connext";
    case 0x0201: return "PrismTech OpenSplice";
    case 0x0301: return "OCI OpenDDS";
    case 0x0401: return "MilSoft";
    case 0x0501: return "Gallium InterCOM";
    case 0x0601: return "TwinOaks CoreDX";
    case 0x0701: return "Lakota Technical Systems";
    case 0x0801: return "ICOUP Consulting";
    case 0x0901: return "ETRI";
    case 0x0a01: return "RTI Connext Micro";
    case 0x0b01: return "PrismTech Vortex Cafe";
    case 0x0c01: return "PrismTech Vortex Gateway";
    case 0x0d01: return "PrismTech Vortex Lite";
    case 0x0e01: return "Technicolor Qeo";
    case 0x0f01: return "eProsima";    // original is 010f
    case 0x2001: return "PrismTech Vortex Cloud";    
    default:     break;
  } 

  return "unknown";   
}

char *_rtps_entity_id_what(_rtps_entity_id_t *eid)
{
    char *ret = "UNKNOWN";

    switch(eid->_entityKind) {
        case RTPS_ENTITYKIND_USER_UNKNOWN: 
            ret = "ID_USER_UNKNOWN";
            break;
        case RTPS_ENTITYKIND_BUILTIN_UNKNOWN: 
            ret = "ID_BUILTIN_UNKNOWN";
            break;
        case RTPS_ENTITYKIND_BUILTIN_PARTIPANT: 
            ret = "ID_PARTICIPANT";
            break;
        case RTPS_ENTITYKIND_BUILTIN_WRITER_WITH_KEY: 
            {
                if (eid->_entityKey[1] == 0x01) 
                    ret = "ID_SPDP_BUILTIN_PARTICIPANT_WRITER";
                else if (eid->_entityKey[2] == 0x02)
                    ret = "ID_P2P_BUILTIN_PARTICIPANT_MESSAGE_WRITER";
                else if (eid->_entityKey[2] == 0x03)
                    ret = "ID_SEDP_BUILTIN_PUBLICATIONS_WRITER";
                else if (eid->_entityKey[2] == 0x04)
                    ret = "ID_SEDP_BUILTIN_SUBSCRIPTIONS_WRITER";            
            }
            break;        
        case RTPS_ENTITYKIND_BUILTIN_READER_WITH_KEY:
            {
                if (eid->_entityKey[1] == 0x01) 
                    ret = "ID_SPDP_BUILTIN_PARTICIPANT_READER";
                else if (eid->_entityKey[2] == 0x02)
                    ret = "ID_P2P_BUILTIN_PARTICIPANT_MESSAGE_READER";
                else if (eid->_entityKey[2] == 0x03)
                    ret = "ID_SEDP_BUILTIN_PUBLICATIONS_READER";
                else if (eid->_entityKey[2] == 0x04)
                    ret = "ID_SEDP_BUILTIN_SUBSCRIPTIONS_READER";             
            }
            break;
        case RTPS_ENTITYKIND_USER_WRITER_WITH_KEY: 
            ret = "ID_USER_WRITER_WITH_KEY";
            break;
        case RTPS_ENTITYKIND_USER_WRITER_NO_KEY:
            ret = "ID_USER_WRITER_NO_KEY"; 
            break;
        case RTPS_ENTITYKIND_USER_READER_NO_KEY: 
            ret = "ID_USER_READER_NO_KEY"; 
            break;
        case RTPS_ENTITYKIND_USER_READER_WITH_KEY: 
            ret = "ID_USER_READER_WITH_KEY"; 
            break;
    }

    return ret;
}

#define DISC_BUILTIN_ENDPOINT_PARTICIPANT_ANNOUNCER 0x00000001 << 0
#define DISC_BUILTIN_ENDPOINT_PARTICIPANT_DETECTOR 0x00000001 << 1
#define DISC_BUILTIN_ENDPOINT_PUBLICATION_ANNOUNCER 0x00000001 << 2
#define DISC_BUILTIN_ENDPOINT_PUBLICATION_DETECTOR 0x00000001 << 3
#define DISC_BUILTIN_ENDPOINT_SUBSCRIPTION_ANNOUNCER 0x00000001 << 4
#define DISC_BUILTIN_ENDPOINT_SUBSCRIPTION_DETECTOR 0x00000001 << 5
#define DISC_BUILTIN_ENDPOINT_PARTICIPANT_PROXY_ANNOUNCER 0x00000001 << 6
#define DISC_BUILTIN_ENDPOINT_PARTICIPANT_PROXY_DETECTOR 0x00000001 << 7
#define DISC_BUILTIN_ENDPOINT_PARTICIPANT_STATE_ANNOUNCER 0x00000001 << 8
#define DISC_BUILTIN_ENDPOINT_PARTICIPANT_STATE_DETECTOR 0x00000001 << 9
#define BUILTIN_ENDPOINT_PARTICIPANT_MESSAGE_DATA_WRITER 0x00000001 << 10
#define BUILTIN_ENDPOINT_PARTICIPANT_MESSAGE_DATA_READER 0x00000001 << 11

char *_rtps_builtin_endpoint_set_what(_rtps_builtin_endpoint_set_t value)
{
    printf("...\n")    ;
    if (value & DISC_BUILTIN_ENDPOINT_PARTICIPANT_ANNOUNCER) {
        printf("  PARTICIPANT_ANNOUNCER ");
    }
    if (value & DISC_BUILTIN_ENDPOINT_PARTICIPANT_DETECTOR) {
        printf("  PARTICIPANT_DETECTOR ");
    }
    if (value & DISC_BUILTIN_ENDPOINT_PUBLICATION_ANNOUNCER) {
        printf("  PUBLICATION_ANNOUNCER ");
    }
    if (value & DISC_BUILTIN_ENDPOINT_PUBLICATION_DETECTOR) {
        printf("  PUBLICATION_DETECTOR ");
    }
    if (value & DISC_BUILTIN_ENDPOINT_SUBSCRIPTION_ANNOUNCER) {
        printf("  SUBSCRIPTION_ANNOUNCER ");
    }
    if (value & DISC_BUILTIN_ENDPOINT_SUBSCRIPTION_DETECTOR) {
        printf("  SUBSCRIPTION_DETECTOR ");
    }
    if (value & DISC_BUILTIN_ENDPOINT_PARTICIPANT_PROXY_ANNOUNCER) {
        printf("  PARTICIPANT_PROXY_ANNOUNCER ");
    }
    if (value & DISC_BUILTIN_ENDPOINT_PARTICIPANT_PROXY_DETECTOR) {
        printf("  PARTICIPANT_PROXY_DETECTOR ");
    }
    if (value & DISC_BUILTIN_ENDPOINT_PARTICIPANT_STATE_ANNOUNCER) {
        printf("  PARTICIPANT_STATE_ANNOUNCER ");
    }
    if (value & DISC_BUILTIN_ENDPOINT_PARTICIPANT_STATE_DETECTOR) {
        printf("  PARTICIPANT_STATE_DETECTOR ");
    }

    if (value & BUILTIN_ENDPOINT_PARTICIPANT_MESSAGE_DATA_WRITER) {
        printf("  PARTICIPANT_MESSAGE_DATA_WRITER ");
    }
    if (value & BUILTIN_ENDPOINT_PARTICIPANT_MESSAGE_DATA_READER) {
        printf("  PARTICIPANT_MESSAGE_DATA_READER ");
    }

    printf("...\n")    ;

}



void dump_bytes(uint8_t *buf, int len)
{
    int i, j;
    printf("dump bytes---------start ----\n");
    for (i=0;i<len;) {
        for(j=0;j<16 && i < len; j++, i++) {
            printf("%.2x ",buf[i]);
            if (j%4==3) printf(" | ");
        }
        printf("\n");

    }
    printf("dump bytes---------ends=========\n");
}