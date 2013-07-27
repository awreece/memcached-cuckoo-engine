/*
 * Copyright 2013 Alex Reece (awreece@gmail.com).
 */

#include "config.h"

#include <stdlib.h>
#include <string.h>

#include <memcached/engine.h>

#include "cuckoo_engine.h"

ENGINE_ERROR_CODE engine_get_stats(ENGINE_HANDLE* handle,
                                   const void* cookie,
                                   const char* stat_key,
                                   int nkey,
                                   ADD_STAT add_stat) {
  // TODO(awreece) Unimplemented.
  return ENGINE_SUCCESS;
}

void engine_reset_stats(ENGINE_HANDLE* handle, const void *cookie) {
  // TODO(awreece) Unimplemented.
}
