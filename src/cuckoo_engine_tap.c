/*
 * Copyright 2013 Alex Reece (awreece@gmail.com).
 */

#include "config.h"

#include <stdlib.h>
#include <string.h>

#include <memcached/engine.h>

#include "cuckoo_engine.h"

ENGINE_ERROR_CODE engine_tap_notify(ENGINE_HANDLE* handle,
                                    const void *cookie,
                                    void *engine_specific,
                                    uint16_t nengine,
                                    uint8_t ttl,
                                    uint16_t tap_flags,
                                    tap_event_t tap_event,
                                    uint32_t tap_seqno,
                                    const void *key,
                                    size_t nkey,
                                    uint32_t flags,
                                    uint32_t exptime,
                                    uint64_t cas,
                                    const void *data,
                                    size_t ndata,
                                    uint16_t vbucket) {
  // TODO(awreece) Unimplemented.
  return ENGINE_ENOTSUP;
}
 
TAP_ITERATOR engine_get_tap_iterator(ENGINE_HANDLE* handle,
                                     const void* cookie,
                                     const void* client,
                                     size_t nclient,
                                     uint32_t flags,
                                     const void* userdata,
                                     size_t nuserdata) {
  // TODO(awreece) Unimplemented.
  // XXX(awreece) It is rather dangerous to return NULL here rather declaring
  // that this method is unsupported in create_instance.
  return NULL;
}
