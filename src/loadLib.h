#pragma once

#ifndef LOADLIB_H
#define LOADLIB_H

#include <node.h>
#include <v8.h>
#include <libNexusDb.h>
// #include <windows.h>
// #include <libloaderapi.h>

// extern HMODULE lib;

extern AddDatabasePtr lib_AddDatabase;
extern AddRemoteDatabasePtr lib_AddRemoteDatabase;
extern SetUsernamePtr lib_SetUsername;
extern SetPasswordPtr lib_SetPassword;
extern SetHostPtr lib_SetHost;
extern ConnectPtr lib_Connect;
extern CloseDatabasePtr lib_CloseDatabase;

/**
 * loads the dll and all functions
 * @argument {string} dllPath
 * @argument {boolean} ThrowErrorOnMultiLoad
 */
void node_LoadDll(const v8::FunctionCallbackInfo<v8::Value> &args);

/**
 * Unloads the dll
 * @argument {}
 */
void node_UnloadDll(const v8::FunctionCallbackInfo<v8::Value> &args);

#endif // LOADLIB_H
