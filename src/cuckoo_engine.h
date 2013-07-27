/*
 * Copyright 2013 Alex Reece (awreece@gmail.com).
 */

#ifndef CUCKOO_ENGINE_H
#define CUCKOO_ENGINE_H

#include "config.h"

#include <memcached/engine.h>

typedef struct engine_engine_s {
  ENGINE_HANDLE_V1 engine;
} engine_t;

typedef struct item_s {
  void* key;
  size_t nkey;
  void* data;
  size_t ndata;
  int flags;
  rel_time_t exptime;
} item_t;

/**
 * Tear down this engine.
 *
 * @param handle the engine handle
 * @param force the flag indicating the force shutdown or not.
 */
void engine_destroy(ENGINE_HANDLE* handle, const bool force);

/**
 * Initialize an engine instance.
 * This is called *after* creation, but before the engine may be used.
 *
 * @param handle the engine handle
 * @param config_str configuration this engine needs to initialize itself.
 */
ENGINE_ERROR_CODE engine_initialize(ENGINE_HANDLE* handle,
                                    const char* config_str);

/**
 * Get a description of this engine.
 *
 * @param handle the engine handle
 * @return a string description of this engine
 */
const engine_info* engine_get_info(ENGINE_HANDLE* handle);

/**
 * Allocate an item.
 *
 * The item can later be loaded / inserted into the cache.
 *
 * @param handle the engine handle
 * @param cookie The cookie provided by the frontend
 * @param output variable that will receive the item
 * @param key the item's key
 * @param nkey the length of the key
 * @param nbytes the number of bytes that will make up the
 *        value of this item.
 * @param flags the item's flags
 * @param exptime the maximum lifetime of this item
 *
 * @return ENGINE_SUCCESS if all goes well
 */
ENGINE_ERROR_CODE engine_allocate(ENGINE_HANDLE* handle,
                                  const void* cookie,
                                  item **item,
                                  const void* key,
                                  const size_t nkey,
                                  const size_t nbytes,
                                  const int flags,
                                  const rel_time_t exptime);

/**
 * Indicate that a caller who received an item no longer needs
 * it.
 *
 * @param handle the engine handle
 * @param cookie The cookie provided by the frontend
 * @param item the item to be released
 */
void engine_release(ENGINE_HANDLE* handle, const void *cookie, item* item);

/**
 * Get information about an item.
 *
 * The loader of the module may need the pointers to the actual data within
 * an item. Instead of having to create multiple functions to get each
 * individual item, this function will get all of them.
 *
 * @param handle the engine that owns the object
 * @param cookie connection cookie for this item
 * @param item the item to request information about
 * @param item_info
 * @return true if successful
 */
bool engine_get_item_info(ENGINE_HANDLE* handle, const void* cookie,
                          const void* item, item_info* item_info);

/**
 * Store an item.
 *
 * @param handle the engine handle
 * @param cookie The cookie provided by the frontend
 * @param item the item to store
 * @param cas the CAS value for conditional sets
 * @param operation the type of store operation to perform.
 * @param vbucket the virtual bucket id
 *
 * @return ENGINE_SUCCESS if all goes well
 */
ENGINE_ERROR_CODE engine_store(ENGINE_HANDLE* handle,
                               const void* cookie,
                               item* item,
                               uint64_t *cas, 
                               ENGINE_STORE_OPERATION operation,
                               uint16_t vbucket);

/**
 * Retrieve an item.
 *
 * @param handle the engine handle
 * @param cookie The cookie provided by the frontend
 * @param item output variable that will receive the located item
 * @param key the key to look up
 * @param nkey the length of the key
 * @param vbucket the virtual bucket id
 *
 * @return ENGINE_SUCCESS if all goes well
 */
ENGINE_ERROR_CODE engine_get(ENGINE_HANDLE* handle,   
                             const void* cookie,
                             item** item,
                             const void* key,
                             const int nkey,
                             uint16_t vbucket);

/**
 * Remove an item from the cache.
 *
 * @param handle the engine handle
 * @param cookie The cookie provided by the frontend
 * @param key the key identifying the item to be removed
 * @param nkey the length of the key
 * @param vbucket the virtual bucket id
 *
 * @return ENGINE_SUCCESS if all goes well
 */
ENGINE_ERROR_CODE engine_remove(ENGINE_HANDLE* handle,
                                const void* cookie,
                                const void* key,
                                const size_t nkey,
                                uint64_t cas,
                                uint16_t vbucket);

/**
 * Flush the cache.
 *
 * @param handle the engine handle
 * @param cookie The cookie provided by the frontend
 * @param when time at which the flush should take effect
 *
 * @return ENGINE_SUCCESS if all goes well
 */
ENGINE_ERROR_CODE engine_flush(ENGINE_HANDLE* handle,
                               const void* cookie, time_t when);

/**
 * Perform an increment or decrement operation on an item.
 *
 * @param handle the engine handle
 * @param cookie The cookie provided by the frontend
 * @param key the key to look up
 * @param nkey the length of the key
 * @param increment if true, increment the value, else decrement
 * @param create if true, create the item if it's missing
 * @param delta the amount to increment or decrement.
 * @param initial when creating, specifies the initial value
 * @param exptime when creating, specifies the expiration time
 * @param cas output CAS value
 * @param result output arithmetic value
 * @param vbucket the virtual bucket id
 *
 * @return ENGINE_SUCCESS if all goes well
 */
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
                                    uint16_t vbucket);

/**
 * Get statistics from the engine.
 *
 * @param handle the engine handle
 * @param cookie The cookie provided by the frontend
 * @param stat_key optional argument to stats
 * @param nkey the length of the stat_key
 * @param add_stat callback to feed results to the output
 *
 * @return ENGINE_SUCCESS if all goes well
 */
ENGINE_ERROR_CODE engine_get_stats(ENGINE_HANDLE* handle,
                                   const void* cookie,
                                   const char* stat_key,
                                   int nkey,
                                   ADD_STAT add_stat);

/**
 * Reset the stats.
 *
 * @param handle the engine handle
 * @param cookie The cookie provided by the frontend
 */
void engine_reset_stats(ENGINE_HANDLE* handle, const void *cookie);

/**
 * Any unknown command will be considered engine specific.
 *
 * @param handle the engine handle
 * @param cookie The cookie provided by the frontend
 * @param request pointer to request header to be filled in
 * @param response function to transmit data
 *
 * @return ENGINE_SUCCESS if all goes well
 */
ENGINE_ERROR_CODE engine_unknown_command(ENGINE_HANDLE* handle,
                                         const void* cookie,
                                         protocol_binary_request_header *request,
                                         ADD_RESPONSE response);

/**
 * Set the CAS id on an item.
 */
void engine_item_set_cas(ENGINE_HANDLE *handle, const void *cookie,
                         item* item, uint64_t val);

/**
 * Callback for all incoming TAP messages. It is up to the engine
 * to determine what to do with the event. The core will create and send
 * a TAP_ACK message if the flag section contains TAP_FLAG_SEND_ACK with
 * the status byte mapped from the return code.
 *
 * @param handle the engine handle
 * @param cookie identification for the tap stream
 * @param engine_specific pointer to engine specific data (received)
 * @param nengine_specific number of bytes of engine specific data
 * @param ttl ttl for this item (Tap stream hops)
 * @param tap_flags tap flags for this object
 * @param tap_event the tap event from over the wire
 * @param tap_seqno sequence number for this item
 * @param key the key in the message
 * @param nkey the number of bytes in the key
 * @param flags the flags for the item
 * @param exptime the expiry time for the object
 * @param cas the cas for the item
 * @param data the data for the item
 * @param ndata the number of bytes in the object
 * @param vbucket the virtual bucket for the object
 * @return ENGINE_SUCCESS for success
 */
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
                                    uint16_t vbucket);
 

/**
 * Get (or create) a Tap iterator for this connection.
 * @param handle the engine handle
 * @param cookie The connection cookie
 * @param client The "name" of the client
 * @param nclient The number of bytes in the client name
 * @param flags Tap connection flags
 * @param userdata Specific userdata the engine may know how to use
 * @param nuserdata The size of the userdata
 * @return a tap iterator to iterate through the event stream
 */
TAP_ITERATOR engine_get_tap_iterator(ENGINE_HANDLE* handle,
                                     const void* cookie,
                                     const void* client,
                                     size_t nclient,
                                     uint32_t flags,
                                     const void* userdata,
                                     size_t nuserdata);


#endif
