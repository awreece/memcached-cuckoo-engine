/*
 * Copyright 2013 Alex Reece  (awreece@gmail.com).
 */

#include "config.h"

#include <stdlib.h>
#include <string.h>

#include <memcached/engine.h>

#include "cuckoo_engine.h"

ENGINE_ERROR_CODE engine_store(ENGINE_HANDLE* handle,
                               const void* cookie,
                               item* item,
                               uint64_t *cas, 
                               ENGINE_STORE_OPERATION operation,
                               uint16_t vbucket) {
  // TODO(awreece) Unimplemented.
  return ENGINE_NOT_STORED;
}

ENGINE_ERROR_CODE engine_get(ENGINE_HANDLE* handle,   
                             const void* cookie,
                             item** item,
                             const void* key,
                             const int nkey,
                             uint16_t vbucket) {
  // TODO(awreece) Unimplemented.
  return ENGINE_NOT_STORED;
}

ENGINE_ERROR_CODE engine_remove(ENGINE_HANDLE* handle,
                                const void* cookie,
                                const void* key,
                                const size_t nkey,
                                uint64_t cas,
                                uint16_t vbucket) {
  // TODO(awreece) Unimplemented.
  return ENGINE_KEY_ENOENT;
}

ENGINE_ERROR_CODE engine_flush(ENGINE_HANDLE* handle,
                               const void* cookie, time_t when) {
  // TODO(awreece) Unimplemented.
  return ENGINE_SUCCESS;
}
