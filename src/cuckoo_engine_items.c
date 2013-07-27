/*
 * Copyright 2013 Alex Reece (awreece@gmail.com).
 */

#include "config.h"

#include <stdlib.h>
#include <string.h>

#include <memcached/engine.h>

#include "cuckoo_engine.h"

bool engine_get_item_info(ENGINE_HANDLE* handle, const void* cookie,
                          const void* item, item_info* item_info) {
  // TODO(awreece) Temporary stub.
  item_t* it = (item_t*) item;
  if (item_info->nvalue < 1) {
    return false;
  }

  item_info->cas = 0;  /* Not supported. */
  item_info->clsid = 0;  /* Not supported. */
  item_info->exptime = it->exptime;
  item_info->flags = it->flags;
  item_info->key = it->key;
  item_info->nkey = it->nkey;
  item_info->nbytes = it->ndata;  /* Total length of the items data. */
  item_info->nvalue = 1;  /* Number of fragments used. */
  item_info->value[0].iov_base = it->data;  /* Pointer to fragment 1. */
  item_info->value[0].iov_len = it->ndata;  /* Length of fragment 1. */

  return true;
}

ENGINE_ERROR_CODE engine_arithmetic(ENGINE_HANDLE* handle,
                                    const void* cookie,
                                    const void* key,
                                    const int nkey,
                                    const bool increment,
                                    const bool create,
                                    const uint64_t delta,
                                    const uint64_t initial,
                                    const rel_time_t exptime,
                                    uint64_t *cas,
                                    uint64_t *result,
                                    uint16_t vbucket) {
  // TODO(awreece) Unimplemented.
  return ENGINE_KEY_ENOENT;
}

void engine_item_set_cas(ENGINE_HANDLE *handle, const void *cookie,
                         item* item, uint64_t val) {
  // TODO(awreece) Unimplemented.
}
