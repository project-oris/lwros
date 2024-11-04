#include "zenoh-pico/protocol/core.h"
#include "zenoh-pico/link/link.h"
#include "rtps/scout.h"

#define DEV_CHECK_STAGE1

//SPDP_MCAST_PORT = PB + DG * domainId + d0
// SPDP_UNICAST_PORT = PB + DG * domainId + d1 + PG * participantId
// user trafic = PB + DG * domainId + d2
// user unicast = PB + DG * domainId + d3 + PG * participantId
// PB = 7400
// DG = 250
// PG = 2
// d0 = 0, d1 = 10, d2 = 1, d3 = 11



_z_string_t _rtps_get_scout_addr(_rtps_what_t what, int domainId, int participantId )
{
    uint16_t port = 7400;
    char addr[30];

    if (what & RTPS_SPDP) {
        port = port + 250 * domainId;
    } else { // EPDP multicast
        port = port + 250 * domainId + 1;        
    }

    snprintf(addr, 30,"239.255.0.1:%d#iface=eth0", port);

    return _z_string_alias_str(addr);    
}

z_result_t _rtps_scout_link_init(_z_link_t *zl, _z_string_t *locator)
{
    z_result_t ret = _Z_RES_OK;  
    static _z_endpoint_t ep;       

    ret = _z_endpoint_from_string(&ep, locator);

#ifdef DEV_CHECK_STAGE1
    ctrace("locator: %s", _z_string_data(locator));        
#endif       

    _z_string_t cmp_str = _z_string_alias_str(UDPM_SCHEMA);
    if ((ret == _Z_RES_OK) && _z_string_equals(&ep._locator._protocol, &cmp_str)) {
        _z_endpoint_clear(&ep);
    } else if (ret == _Z_RES_OK) {
        _z_endpoint_clear(&ep);
        ret = _Z_ERR_TRANSPORT_NOT_AVAILABLE;        
    }

    if (ret == _Z_RES_OK) {
        memset(zl, 0, sizeof(_z_link_t));
        ret = _z_listen_link(zl, locator); // PDP
    }

    return ret;
}

void _rtps_scout_link_clear(_z_link_t *zl) {
    _z_link_clear(zl);
}
