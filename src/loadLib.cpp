#include <node.h>
#include <v8.h>
#include <libNexusDb.h>
#include <tchar.h>
#include <windows.h>
#include <libloaderapi.h>

#include <loadLib.h>

HMODULE lib = NULL;

AddDatabasePtr lib_AddDatabase = NULL;
AddRemoteDatabasePtr lib_AddRemoteDatabase = NULL;
SetUsernamePtr lib_SetUsername = NULL;
SetPasswordPtr lib_SetPassword = NULL;
SetHostPtr lib_SetHost = NULL;
ConnectPtr lib_Connect = NULL;
CloseDatabasePtr lib_CloseDatabase = NULL;

// load function that handles errors and throws node exceptions
FARPROC loadFunction(v8::Isolate *isolate, const char *functionName)
{
  FARPROC function = GetProcAddress(lib, functionName);
  if (function == NULL)
  {
    const char *message = "Could not load function " + *functionName;
    isolate->ThrowException(v8::Exception::Error(
        v8::String::NewFromUtf8(isolate, message).ToLocalChecked()));
    return NULL;
  }
  return function;
}

void node_LoadDll(const v8::FunctionCallbackInfo<v8::Value> &args)
{
  v8::Isolate *isolate = v8::Isolate::GetCurrent();
  v8::HandleScope scope(isolate);

  // check if arg0 exists
  if (args.Length() < 1)
  {
    isolate->ThrowException(v8::Exception::TypeError(
        v8::String::NewFromUtf8(isolate, "Wrong number of arguments").ToLocalChecked()));
    return;
  }

  // check if arg0 is a string
  if (!args[0]->IsString())
  {
    isolate->ThrowException(v8::Exception::TypeError(
        v8::String::NewFromUtf8(isolate, "Wrong arguments").ToLocalChecked()));
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
          v8::String::NewFromUtf8(isolate, "Wrong arguments").ToLocalChecked()));
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
          v8::String::NewFromUtf8(isolate, "Dll already loaded").ToLocalChecked()));
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
        v8::String::NewFromUtf8(isolate, "Could not load NexusDb.dll").ToLocalChecked()));
    return;
  }

  // load functions
  lib_AddDatabase = (AddDatabasePtr)loadFunction(isolate, "AddDatabase");
  lib_AddRemoteDatabase = (AddRemoteDatabasePtr)loadFunction(isolate, "AddRemoteDatabase");
  // lib_SetUsername = (SetUsernamePtr)loadFunction(isolate, "SetUsername");
  // lib_SetPassword = (SetPasswordPtr)loadFunction(isolate, "SetPassword");
  // lib_SetHost = (SetHostPtr)loadFunction(isolate, "SetHost");
  // lib_Connect = (ConnectPtr)loadFunction(isolate, "Connect");
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