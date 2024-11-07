#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/socket.h>
#include <netdb.h>
#include <arpa/inet.h>


#include "rtps/utils_net.h"

z_result_t _get_local_ip4_address(uint8_t *buf)
{
    uint8_t host[256];
    struct hostent *host_entry;
    char *ip_buffer;
    z_result_t ret  = _Z_RES_OK;   

    if (ret == _Z_RES_OK) {
        if (gethostname(host, sizeof(host)) == -1) {
            perror("gethostname");
            ret = _Z_ERR_SYSTEM_GENERIC;
        }
    }

    if (ret == _Z_RES_OK) {
        host_entry = gethostbyname(host);
        if (host_entry == NULL) {
            perror("gethostbyname");
            ret = _Z_ERR_SYSTEM_GENERIC;            
        }

        uint8_t *pod = host_entry->h_addr_list[0];
        buf[0] = pod[0];
        buf[1] = pod[1];
        buf[2] = pod[2];
        buf[3] = pod[3];        
    }

    return ret;
}

z_result_t _rtps_wbuf_add_wbuf(_z_wbuf_t *_dst, _z_wbuf_t *src)
{
    z_result_t ret = _Z_RES_OK;

    for (size_t i=0;i<_z_wbuf_len_iosli(src);i++){
        _z_iosli_t *t_ios = _z_wbuf_get_iosli(_dst, _dst->_w_idx);
        t_ios->_capacity = t_ios->_w_pos;
        _z_iosli_t *s_ios = _z_wbuf_get_iosli(src, i);
        _z_wbuf_add_iosli(_dst, s_ios);
    }

    return ret;
}


_z_wbuf_t _z_wbuf_compact(_z_wbuf_t *wbf, size_t sz)
{
    size_t len = _z_wbuf_len(wbf);

    if (sz > len) len = sz;

    _z_wbuf_t obf = _z_wbuf_make(len, true);

    for (size_t i = wbf->_r_idx; i<= wbf->_w_idx;i++) {
        _z_iosli_t *ios = _z_wbuf_get_iosli(wbf, i);
        _z_wbuf_write_bytes(&obf, ios->_buf, ios->_r_pos, _z_iosli_readable(ios));
    }

    return obf;
}
