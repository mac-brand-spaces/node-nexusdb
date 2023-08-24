#pragma once

#ifndef NODELIB_H
#define NODELIB_H

#include <node.h>
#include <v8.h>
#include <string.h>

/**
 * creates a connection to a remote database
 * @param string host
 * @param string alias name
 * @param string username
 * @param string password
 * @returns `string || undefined` DatabaseId or undefined if failed
 */
void node_AddRemoteDatabase(const v8::FunctionCallbackInfo<v8::Value> &args);

/**
 * creates a connection to a local database
 * @param string path
 * @param string alias name
 * @returns `string || undefined` DatabaseId or undefined if failed
 */
void node_AddDatabase(const v8::FunctionCallbackInfo<v8::Value> &args);

/**
 * Close a connection to a database
 * @param string DatabaseId
 * @returns boolean success
 */
void node_CloseDatabase(const v8::FunctionCallbackInfo<v8::Value> &args);

#endif // NODELIB_H