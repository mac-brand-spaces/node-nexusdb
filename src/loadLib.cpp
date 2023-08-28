#include <node.h>
#include <v8.h>
#include <libNexusDb.h>
#include <tchar.h>
#include <windows.h>
#include <libloaderapi.h>

#include <loadLib.h>
#include "messages.h"

HMODULE lib = NULL;

FreeStringPtr lib_FreeString = NULL;
AddDatabasePtr lib_AddDatabase = NULL;
AddRemoteDatabasePtr lib_AddRemoteDatabase = NULL;
ExecuteSqlPtr lib_ExecuteSql = NULL;
CloseDatabasePtr lib_CloseDatabase = NULL;

// load function that handles errors and throws node exceptions
FARPROC loadFunction(v8::Isolate *isolate, const char *functionName)
{
  FARPROC function = GetProcAddress(lib, functionName);
  if (function == NULL)
  {
    const char *message = Messages::ERR_FUNCTION_NOT_FOUND + *functionName;
    isolate->ThrowException(v8::Exception::Error(
        v8::String::NewFromUtf8(isolate, message).ToLocalChecked()));
    return NULL;
  }
  return function;
}

bool node_dllLoaded(v8::Isolate *isolate)
{
  if (lib == NULL)
  {
    isolate->ThrowException(v8::Exception::Error(
        v8::String::NewFromUtf8(isolate, Messages::ERR_DLL_NOT_LOADED).ToLocalChecked()));
    return false;
  }
  return true;
}

void node_LoadDll(const v8::FunctionCallbackInfo<v8::Value> &args)
{
  v8::Isolate *isolate = v8::Isolate::GetCurrent();
  v8::HandleScope scope(isolate);

  // check if arg0 exists
  if (args.Length() < 1)
  {
    isolate->ThrowException(v8::Exception::TypeError(
        v8::String::NewFromUtf8(isolate, Messages::ERR_WRONG_ARGUMENTS_COUNT).ToLocalChecked()));
    return;
  }

  // check if arg0 is a string
  if (!args[0]->IsString())
  {
    isolate->ThrowException(v8::Exception::TypeError(
        v8::String::NewFromUtf8(isolate, Messages::ERR_WRONG_ARGUMENTS).ToLocalChecked()));
    return;
  }

  bool ThrowErrorOnMultiLoad = false;
  // check if arg1 exists
  if (args.Length() > 1)
  {
    // check if arg1 is a boolean
    if (!args[1]->IsBoolean())
    {
      isolate->ThrowException(v8::Exception::TypeError(
          v8::String::NewFromUtf8(isolate, Messages::ERR_WRONG_ARGUMENTS).ToLocalChecked()));
      return;
    }
    ThrowErrorOnMultiLoad = args[1]->BooleanValue(isolate);
  }

  // check if dll is already loaded
  if (lib != NULL)
  {
    // throw error if ThrowErrorOnMultiLoad is true
    if (ThrowErrorOnMultiLoad)
    {
      isolate->ThrowException(v8::Exception::Error(
          v8::String::NewFromUtf8(isolate, Messages::ERR_DLL_ALREADY_LOADED).ToLocalChecked()));
      return;
    }
    else
    {
      return;
    }
  }

  v8::String::Utf8Value dllPathUtf8(isolate, args[0].As<v8::String>());

  lib = LoadLibraryA(*dllPathUtf8);

  if (lib == NULL)
  {
    isolate->ThrowException(v8::Exception::Error(
        v8::String::NewFromUtf8(isolate, Messages::ERR_DLL_NOT_FOUND).ToLocalChecked()));
    return;
  }
  // load functions
  lib_FreeString = (FreeStringPtr)loadFunction(isolate, "FreeString");
  lib_AddDatabase = (AddDatabasePtr)loadFunction(isolate, "AddDatabase");
  lib_AddRemoteDatabase = (AddRemoteDatabasePtr)loadFunction(isolate, "AddRemoteDatabase");
  lib_ExecuteSql = (ExecuteSqlPtr)loadFunction(isolate, "ExecuteSql");
  lib_CloseDatabase = (CloseDatabasePtr)loadFunction(isolate, "CloseDatabase");
}

void node_UnloadDll(const v8::FunctionCallbackInfo<v8::Value> &args)
{
  v8::Isolate *isolate = v8::Isolate::GetCurrent();
  v8::HandleScope scope(isolate);

  if (lib != NULL)
  {
    FreeLibrary(lib);
    lib = NULL;
  }
}