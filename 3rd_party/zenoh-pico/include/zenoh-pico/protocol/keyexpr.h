//
// Copyright (c) 2022 ZettaScale Technology
//
// This program and the accompanying materials are made available under the
// terms of the Eclipse Public License 2.0 which is available at
// http://www.eclipse.org/legal/epl-2.0, or the Apache License, Version 2.0
// which is available at https://www.apache.org/licenses/LICENSE-2.0.
//
// SPDX-License-Identifier: EPL-2.0 OR Apache-2.0
//
// Contributors:
//   ZettaScale Zenoh Team, <zenoh@zettascale.tech>

#ifndef INCLUDE_ZENOH_PICO_PROTOCOL_KEYEXPR_H
#define INCLUDE_ZENOH_PICO_PROTOCOL_KEYEXPR_H

#include <stdbool.h>

#include "zenoh-pico/api/constants.h"
#include "zenoh-pico/protocol/core.h"

zp_keyexpr_canon_status_t _z_keyexpr_is_canon(const char *start, size_t len);
zp_keyexpr_canon_status_t _z_keyexpr_canonize(char *start, size_t *len);
bool _z_keyexpr_suffix_includes(const _z_keyexpr_t *left, const _z_keyexpr_t *right);
bool _z_keyexpr_suffix_intersects(const _z_keyexpr_t *left, const _z_keyexpr_t *right);
bool _z_keyexpr_suffix_equals(const _z_keyexpr_t *left, const _z_keyexpr_t *right);

/*------------------ clone/Copy/Free helpers ------------------*/
_z_keyexpr_t _z_keyexpr_from_string(uint16_t rid, _z_string_t *str);
_z_keyexpr_t _z_keyexpr_from_substr(uint16_t rid, const char *str, size_t len);
z_result_t _z_keyexpr_copy(_z_keyexpr_t *dst, const _z_keyexpr_t *src);
_z_keyexpr_t _z_keyexpr_duplicate(_z_keyexpr_t src);
_z_keyexpr_t _z_keyexpr_alias(_z_keyexpr_t src);
/// Returns either keyexpr defined by id + mapping with null suffix if try_declared is true and id is non-zero,
/// or keyexpr defined by its suffix only, with 0 id and no mapping. This is to be used only when forwarding
/// keyexpr in user api to properly separate declared keyexpr from its suffix.
_z_keyexpr_t _z_keyexpr_alias_from_user_defined(_z_keyexpr_t src, bool try_declared);
_z_keyexpr_t _z_keyexpr_steal(_Z_MOVE(_z_keyexpr_t) src);
static inline _z_keyexpr_t _z_keyexpr_null(void) {
    _z_keyexpr_t keyexpr = {0, {0}, _z_string_null()};
    return keyexpr;
}
bool _z_keyexpr_equals(const _z_keyexpr_t *left, const _z_keyexpr_t *right);
void _z_keyexpr_move(_z_keyexpr_t *dst, _z_keyexpr_t *src);
void _z_keyexpr_clear(_z_keyexpr_t *rk);
void _z_keyexpr_free(_z_keyexpr_t **rk);

#endif /* INCLUDE_ZENOH_PICO_PROTOCOL_KEYEXPR_H */