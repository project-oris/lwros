#ifndef LWROS_RTPS_SCOUT_H
#define LWROS_RTPS_SCOUT_H

#include "zenoh-pico/protocol/core.h"

typedef enum {
    RTPS_SPDP = 0x01,  // Router
    RTPS_EPDP = 0x02,  // Router    
    RTPS_READER = 0x04,    // Peer
    RTPS_WRITER = 0x08,  // Client
    RTPS_SPDP_READER = (0x01 | 0x04),
    RTPS_SPDP_WRITER = (0x01 | 0x08),
    RTPS_EPDP_READER = (0x02 | 0x04),
    RTPS_EPDP_WRITER = (0x02 | 0x08),
} _rtps_what_t;

z_result_t _rtps_scout_link_init(_z_link_t *zl, _z_string_t *locator);
void _rtps_scout_link_clear(_z_link_t *zl);
_z_string_t _rtps_get_scout_addr(_rtps_what_t what, int domainId, int participantId );

#endif // LWROS_RTPS_SCOUT_H