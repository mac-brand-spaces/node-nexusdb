#pragma once

#ifndef LOADLIB_H
#define LOADLIB_H

#include <node.h>
#include <v8.h>
#include <libNexusDb.h>

extern FreeStringPtr lib_FreeString;
extern AddDatabasePtr lib_AddDatabase;
extern AddRemoteDatabasePtr lib_AddRemoteDatabase;
extern ExecuteSqlPtr lib_ExecuteSql;
extern CloseDatabasePtr lib_CloseDatabase;

/**
 * checks if the dll is loaded
 * @param v8::Isolate *isolate
 * @returns bool
 */
bool node_dllLoaded(v8::Isolate *isolate);

/**
 * loads the dll and all functions
 * @param v8::FunctionCallbackInfo<v8::Value> &args
 * @nodeParam string dllPath
 * @nodeParam boolean ThrowErrorOnMultiLoad
 */
void node_LoadDll(const v8::FunctionCallbackInfo<v8::Value> &args);

/**
 * Unloads the dll
 * @param v8::FunctionCallbackInfo<v8::Value> &args
 */
void node_UnloadDll(const v8::FunctionCallbackInfo<v8::Value> &args);

#endif // LOADLIB_H
