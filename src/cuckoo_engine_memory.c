/*
 * Copyright 2013 Alex Reece (awreece@gmail.com).
 */

#include "config.h"

#include <stdlib.h>
#include <string.h>

#include <memcached/engine.h>

#include "cuckoo_engine.h"

ENGINE_ERROR_CODE engine_allocate(ENGINE_HANDLE* handle,
                                  const void* cookie,
                                  item **item,
                                  const void* key,
                                  const size_t nkey,
                                  const size_t nbytes,
                                  const int flags,
                                  const rel_time_t exptime) {
  // TODO(awreece) Temporary stub.
  item_t* it = malloc(sizeof(item_t));
  if (it == NULL) {
    return ENGINE_ENOMEM;
  }

  it->flags = flags;
  it->exptime = exptime;
  it->nkey = nkey;
  it->ndata = nbytes;
  it->key = malloc(nkey);
  it->data = malloc(nbytes);

  if (it->key == NULL || it->data == NULL) {
    free(it->key);
    free(it->data);
    free(it);
    return ENGINE_ENOMEM;
  }

  memcpy(it->key, key, nkey);
  *item = it;
  return ENGINE_SUCCESS;
}

void engine_release(ENGINE_HANDLE* handle, const void *cookie, item* item) {
  // TODO(awreece) Temporary stub.
  item_t *it = item;
  free(it->key);
  free(it->data);
  free(it);
}
