/*
 * Copyright 2013 Alex Reece (awreece@gmail.com).
 */

#include "config.h"

#include <stdlib.h>
#include <string.h>

#include <memcached/engine.h>

#include "cuckoo_engine.h"

void engine_destroy(ENGINE_HANDLE* handle, const bool force) {
  // TODO(awreece) Temporary stub.
  free(handle);
}

ENGINE_ERROR_CODE engine_initialize(ENGINE_HANDLE* handle,
                                    const char* config_str) {
  // TODO(awreece) Temporary stub.
  return ENGINE_SUCCESS;
}

const engine_info* engine_get_info(ENGINE_HANDLE* handle)
{
  static engine_info info = {
    .description = "Cuckoo engine v0.1",
    .num_features = 0
  };

  return &info;
}

ENGINE_ERROR_CODE engine_unknown_command(ENGINE_HANDLE* handle,
                                         const void* cookie,
                                         protocol_binary_request_header *request,
                                         ADD_RESPONSE response) {
  // TODO(awreece) Unimplemented.
  return ENGINE_ENOTSUP;
}

MEMCACHED_PUBLIC_API
ENGINE_ERROR_CODE create_instance(uint64_t interface,
                                  GET_SERVER_API get_server_api,
                                  ENGINE_HANDLE **handle) {
  if (interface == 0) {
    return ENGINE_ENOTSUP;
  }

  engine_t* engine = (engine_t*) calloc(1, sizeof(engine_t));
  if (engine == NULL) {
    return ENGINE_ENOMEM;
  }

  engine_t engine_data = {
    .engine = {
      .interface = 1,

      .get_info = engine_get_info,
      .initialize = engine_initialize,
      .destroy = engine_destroy,

      .allocate = engine_allocate,
      .remove = engine_remove,
      .release = engine_release,

      .get = engine_get,
      .store = engine_store,

      .arithmetic = engine_arithmetic,

      .flush = engine_flush,

      .get_stats = engine_get_stats,
      .reset_stats = engine_reset_stats,

      .unknown_command = engine_unknown_command,

      .tap_notify = engine_tap_notify,
      .get_tap_iterator = engine_get_tap_iterator,

      .item_set_cas = engine_item_set_cas,
      .get_item_info = engine_get_item_info,

      /* The default engine doesn't support these either.
      .get_stats_struct = engine_get_stats_struct,
      .aggregate_stats = engine_aggregate_stats,
      .errinfo = engine_errinfo
      */

    },
  };

  *engine = engine_data;

  *handle = (ENGINE_HANDLE*) engine;

  return ENGINE_SUCCESS;
}
