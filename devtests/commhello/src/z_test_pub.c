#include <stdio.h>
#include "zenoh-pico/api/constants.h"
#include "zenoh-pico/utils/config.h"
#include "zenoh-pico/link/manager.h"
#include "zenoh-pico/protocol/core.h"
#include "rosapi/include/rtps/core.h"
#include "rosapi/include/rtps/time.h"
#include "rosapi/include/rtps/types.h"
#include "rosapi/include/rtps/data_submsg.h"
#include "rosapi/include/rtps/scout_msg.h"
#include "rosapi/include/rtps/scout.h"
#include "base_config.h"
//#include "rosapi/include/rtps/utils.h"

//#define DEV_CHECK_STAGE1


//#define MULTICAST_LOCATOR_DEFAULT "udp/224.0.0.224:7446"

//SPDP_MCAST_PORT = PB + DG * domainId + d0
// SPDP_UNICAST_PORT = PB + DG * domainId + d1 + PG * participantId
// user trafic = PB + DG * domainId + d2
// user unicast = PB + DG * domainId + d3 + PG * participantId
// PB = 7400
// DG = 250
// PG = 2
// d0 = 0, d1 = 10, d2 = 1, d2 = 11

#define RTPSMESSGE_DEFAULT_SIZE 10500
#define RTPSMESSAGE_COMMON_RTPS_PAYLOAD_SIZE 536
#define RTPSMESSAGE_COMMON_DATA_PAYLOAD_SIZE 10000
#define RTPSMESSAGE_HEADER_SIZE 20
#define RTPSMESSAGE_SUBMESSAGEHEADER_SIZE 4
#define RTPSMESSAGE_DATA_EXTRA_INLINEQOS_SIZE 4
#define RTPSMESSAGE_INFOTS_SIZE 12
#define RTPSMESSAGE_DATA_MIN_LENGTH 24

#define LWROS_SCOUT_MSG_DEFAULT_SIZE RTPSMESSGE_DEFAULT_SIZE

//#define SPDP_MCAST_DEFAULT_0 "udpm/239.255.0.1:7400#iface=eth0" // udp multicast
#define SPDP_MCAST_DEFAULT_0 "udpm/239.255.0.1:7400#iface=eth0" // udp multicast



typedef enum rtps_whatami_t {
    RTPS_ROUTER = 0x01,
    RTPS_PEER = 0x02,
    RTPS_CLIENT = 0x04,
} rtps_whatami_t;

typedef struct {    
    _rtps_what_t _what;
    uint8_t _version;
} _rtps_msg_scout_t;

typedef struct {    
    _z_locator_array_t _locators;
    rtps_whatami_t _whatami;
    uint8_t _version;
} _rtps_msg_hello_t;

typedef union {
    _rtps_msg_scout_t _scout;
    _rtps_msg_hello_t _hello;
} _rtps_scouting_body_t;


// entityKind : 00-> user defined, 11 -> built-in, 01 -> vendor specific



// for topic kind
struct {
    int32_t value;
} __attribute__((packed)) _rtps_topicKind_t;

#define RTPS_TOPICKIND_NO_KEY 1
#define RTPS_TOPICKIND_WITH_KEY 2

//  rtps mesg struct
typedef struct 
{
    //_rtps_msg_header_t header;
    void *submsgs; //uint8_t submsgs[];
}_rtps_msg_t;

///////////////////////////////
/////////// const area
//////////////////////////////


////////////////////////////

typedef struct {

} _rtps_context_t;

//SPDP_MCAST_PORT = PB + DG * domainId + d0
// SPDP_UNICAST_PORT = PB + DG * domainId + d1 + PG * participantId
// user trafic = PB + DG * domainId + d2
// user unicast = PB + DG * domainId + d3 + PG * participantId
// PB = 7400
// DG = 250
// PG = 2
// d0 = 0, d1 = 10, d2 = 1, d3 = 11





_rtps_scouting_message_t _rtps_msg_make_hello(rtps_whatami_t whatami, _rtps_header_t zid, _z_locator_array_t locators) 
{
    /*
    _rtps_scouting_message_t msg;
    msg._header = _Z_MID_HELLO;

    msg._body._hello._version = Z_PROTO_VERSION;
    msg._body._hello._whatami = whatami;
    msg._body._hello._zid = zid;
    msg._body._hello._locators = locators;

    if (_z_locator_array_is_empty(&locators) == false) {
        _Z_SET_FLAG(msg._header, _Z_FLAG_T_HELLO_L);
    }

    return msg;
    */
}

z_result_t _rtps_scout_encode(_z_wbuf_t *wbf, uint8_t header, const _rtps_msg_scout_t *msg) { 
    /*
    z_result_t ret = _Z_RES_OK;
    (void)(header);
    _Z_DEBUG("Encoding _Z_MID_SCOUT");

    _Z_RETURN_IF_ERR(_z_uint8_encode(wbf, msg->_version))

    uint8_t cbyte = 0;
    cbyte |= (msg->_what & 0x07);
    uint8_t zid_len = _z_id_len(msg->_zid);
    if (zid_len > 0) {
        _Z_SET_FLAG(cbyte, _Z_FLAG_T_SCOUT_I);
        cbyte |= (uint8_t)(((zid_len - 1) & 0x0F) << 4);
    }
    _Z_RETURN_IF_ERR(_z_uint8_encode(wbf, cbyte))

    ret |= _z_wbuf_write_bytes(wbf, msg->_zid.id, 0, zid_len);

    return ret;
    */
}

z_result_t _rtps_scout_decode(_rtps_msg_scout_t *msg, _z_zbuf_t *zbf, uint8_t header) {
    /*
    z_result_t ret = _Z_RES_OK;
    (void)(header);
    _Z_DEBUG("Decoding _Z_MID_SCOUT");
    *msg = (_z_s_msg_scout_t){0};

    ret |= _z_uint8_decode(&msg->_version, zbf);

    uint8_t cbyte = 0;
    ret |= _z_uint8_decode(&cbyte, zbf);
    msg->_what = cbyte & 0x07;
    msg->_zid = _z_id_empty();
    if ((ret == _Z_RES_OK) && (_Z_HAS_FLAG(cbyte, _Z_FLAG_T_SCOUT_I) == true)) {
        uint8_t zidlen = ((cbyte & 0xF0) >> 4) + (uint8_t)1;
        _z_zbuf_read_bytes(zbf, msg->_zid.id, 0, zidlen);
    }

    return ret;
    */
}


// codec


z_result_t _rtps_scouting_message_decode_na(_rtps_scouting_message_t *msg, _z_zbuf_t *zbf) {
    /*
    z_result_t ret = _Z_RES_OK;
    *msg = (_z_scouting_message_t){0};

    bool is_last = false;

    do {
        ret |= _z_uint8_decode(&msg->_header, zbf);  // Decode the header
        if (ret == _Z_RES_OK) {
            uint8_t mid = _Z_MID(msg->_header);
            switch (mid) {
                case _Z_MID_SCOUT: {
                    ret |= _z_scout_decode(&msg->_body._scout, zbf, msg->_header);
                    is_last = true;
                } break;

                case _Z_MID_HELLO: {
                    ret |= _z_hello_decode(&msg->_body._hello, zbf, msg->_header);
                    is_last = true;
                } break;

                default: {
                    _Z_DEBUG("WARNING: Trying to decode scouting message with unknown ID(0x%x)", mid);
                    ret |= _Z_ERR_MESSAGE_TRANSPORT_UNKNOWN;
                    is_last = true;
                } break;
            }
        } else {
            msg->_header = 0xFF;
        }
    } while ((ret == _Z_RES_OK) && (is_last == false));

    if ((ret == _Z_RES_OK) && (msg->_header & _Z_MSG_EXT_FLAG_Z) != 0) {
        ret |= _z_msg_ext_skip_non_mandatories(zbf, 0x06);
    }

    return ret;    */
}

// parse PDP message




//typedef char _z_hello_list_t ;

// typedef struct {
//     _z_id_t _zid;
//     _z_string_svec_t _locators;
//     z_whatami_t _whatami;
//     uint8_t _version;
// }_rtps_peer_t;

// _Z_LIST_DEFINE(_rtps_peer, _rtps_peer_t)
// _Z_ARRAY_DEFINE

_z_hello_list_t *rtps_scout_loop(const _z_wbuf_t *wbf, _z_string_t *locator, unsigned long period, bool exit_on_first) {
//    ctrace("mesg");
    // Define an empty array
    _z_hello_list_t *ret = NULL;
    z_result_t err = _Z_RES_OK;  


    _z_link_t zl;
    err = _rtps_scout_link_init(&zl, locator);    
    
    if (err == _Z_RES_OK) {    
        _z_zbuf_t zbf = _z_zbuf_make(LWROS_SCOUT_MSG_DEFAULT_SIZE); // receive SCOUT(PDP) message
        z_clock_t start = z_clock_now();
        printf("timeout is %d \n", period);
        while (z_clock_elapsed_ms(&start) < period) {
            size_t len = _z_link_recv_zbuf(&zl, &zbf, NULL); // mowait            

            if (len ==SIZE_MAX) { // size max is -1: no data
                continue;
            }
            printf("RECEIVED len is %d .... \n", len);
            _rtps_scouting_message_t s_msg;
            err = _rtps_scouting_message_decode(&s_msg, &zbf);
            if (err != _Z_RES_OK) {
                ctrace("Scouting loop received malformed message");
                continue;
            }
        }               

        err = _z_link_send_wbuf(&zl, wbf);
        printf("ret %d Send len is %d \n..........", ret, _z_wbuf_len(wbf));
    } else {
            printf("link open failed : %d\n", err);
     }

    return ret;  
}

// 
// scout read with send
// 


void rtps_scout_inner() {  // pdp testing {
//      z_result_t ret = _Z_RES_OK;

    _z_string_t locator = _z_string_alias_str(SPDP_MCAST_DEFAULT_0);

    _z_hello_list_t *ret = NULL;

    z_what_t what = Z_WHAT_ROUTER_PEER;

    const uint32_t timeout = 2000; // 1;    

    const bool exit_on_first = true;

    // Create the buffer to serialize the scout message on
    // CA(Code Analysus): It declare MAX buffer size, but it does not allocate memory 
    _z_wbuf_t wbf; //  = _z_wbuf_make(LWROS_SCOUT_MSG_DEFAULT_SIZE, false);

#ifdef DEV_DEBUG
    ctrace("CHECK 1 wbf cap %d len %d ",wbf._ioss._capacity, wbf._ioss._len);
#endif    
    _rtps_scouting_message_t scout;
    _rtps_init_scout_msg_data(&scout);

    // when it writes contents to buffer, wbf allocate memory for a slice of contents.
    // wbf : linked list of written cotents.    

    _rtps_scouting_message_encode(&wbf, &scout); 

#ifdef DEV_DEBUG 
    ctrace("CHECK 2 wbf cap %d len %d ",wbf._ioss._capacity, wbf._ioss._len);
    ctrace("CHECK 2.1 wbf ridx %d widx %d ",wbf._r_idx, wbf._w_idx);
    ctrace("CHECK 2.2 wbf slice len %d  ", _z_iosli_readable(_z_wbuf_get_iosli(&wbf, 0)));
    ctrace("CHECK 2.3 wbf cap %d len %d ",_z_wbuf_capacity(&wbf), _z_wbuf_len(&wbf));
#endif    
    ctrace("############CHECK data#################");
#if 0
    _z_zbuf_t _outbuf = _z_wbuf_to_zbuf(&wbf);
    _rtps_scouting_message_t s_msg;
    ret = _rtps_scouting_message_decode(&s_msg, &_outbuf);
    if (ret != _Z_RES_OK) {
        ctrace("Scouting loop received malformed message");
    }    
    _z_wbuf_clear(&wbf);
    _z_zbuf_clear(&_outbuf);

    ctrace("HERE "); 
    _rtps_scouting_message_clear(&scout);
    
    ctrace("exit"); exit(1);
#endif    

    // Scout on multicast
     ret = rtps_scout_loop(&wbf, &locator, timeout, exit_on_first);       

    
    return;
}

int count = 1;
bool lwros_ok() {

    if (count > 5) {
        return false;
    }

    count = count + 1;

    return true;
}



void lwros_init() {
    count = 1;
    _rtps_init();
}

void lwros_spinOnce(){
    rtps_scout_inner("z_test_pub");
    //sleep(1);
}

int main()
{
    _rtps_time_t test_now = _rtps_time_now();

    printf("now --- %u %u \n", test_now._seconds, test_now._fraction);


    
    lwros_init();    

    //lwrosRate rate = lwros_create_rate(10);

    //while (lwros_ok()) {
        lwros_spinOnce();
        //  lwros_sleep(rate);
    //}  

    
/*
    //std::cout <<"Helo"<<std::endl;
    //my_tests();
    //printf("Helo\n");

    NodeHandle mynode = create_node("myNode");

    SubscriptionHandle mysub = create_subscription(mynode, "mytopic", "std::string", mycallback);

    wait_for_stop(mynode);
    */
}