#include <node.h>
#include <v8.h>
#include <string.h>
#include <stdlib.h>
#include <loadLib.h>
#include <helper.h>

#include <nodeLib.h>

void node_AddRemoteDatabase(const v8::FunctionCallbackInfo<v8::Value> &args)
{
  v8::Isolate *isolate = args.GetIsolate();

  if (!node_dllLoaded(isolate))
  {
    return;
  }

  if (args.Length() < 4)
  {
    isolate->ThrowException(v8::Exception::TypeError(
        v8::String::NewFromUtf8(isolate, "Wrong number of arguments").ToLocalChecked()));
    return;
  }

  if (!args[0]->IsString() || !args[1]->IsString() || !args[2]->IsString() || !args[3]->IsString())
  {
    isolate->ThrowException(v8::Exception::TypeError(
        v8::String::NewFromUtf8(isolate, "Wrong arguments").ToLocalChecked()));
    return;
  }

  v8::String::Utf8Value host(isolate, args[0]);
  v8::String::Utf8Value alias(isolate, args[1]);
  v8::String::Utf8Value username(isolate, args[2]);
  v8::String::Utf8Value password(isolate, args[3]);

  hNxStr16Ptr host16 = hNxStr16::fromString(*host);
  hNxStr16Ptr alias16 = hNxStr16::fromString(*alias);
  hNxStr16Ptr username16 = hNxStr16::fromString(*username);
  hNxStr16Ptr password16 = hNxStr16::fromString(*password);

  hNxStr16Ptr dbId = ((hNxStr16Ptr)lib_AddRemoteDatabase((NxStr16Ptr)host16, (NxStr16Ptr)alias16, (NxStr16Ptr)username16, (NxStr16Ptr)password16));
  const uint16_t *dbId_char16 = (uint16_t *)dbId->toChar16();
  args.GetReturnValue().Set(v8::String::NewFromTwoByte(
                                isolate, dbId_char16)
                                .ToLocalChecked());
  lib_FreeString((NxStr16Ptr)dbId);
  host16->destroy(host16);
  alias16->destroy(alias16);
  username16->destroy(username16);
  password16->destroy(password16);
}

void node_AddDatabase(const v8::FunctionCallbackInfo<v8::Value> &args)
{
  v8::Isolate *isolate = args.GetIsolate();

  if (!node_dllLoaded(isolate))
  {
    return;
  }

  if (args.Length() < 1)
  {
    isolate->ThrowException(v8::Exception::TypeError(
        v8::String::NewFromUtf8(isolate, "Wrong number of arguments").ToLocalChecked()));
    return;
  }

  if (!args[0]->IsString())
  {
    isolate->ThrowException(v8::Exception::TypeError(
        v8::String::NewFromUtf8(isolate, "Wrong arguments").ToLocalChecked()));
    return;
  }

  v8::String::Utf8Value path(isolate, args[0]);

  hNxStr16Ptr path16 = hNxStr16::fromString(*path);

  hNxStr16Ptr dbId = ((hNxStr16Ptr)lib_AddDatabase((NxStr16Ptr)path16));
  const uint16_t *dbId_char16 = (uint16_t *)dbId->toChar16();
  args.GetReturnValue().Set(v8::String::NewFromTwoByte(
                                isolate, dbId_char16)
                                .ToLocalChecked());
  lib_FreeString((NxStr16Ptr)dbId);
  path16->destroy(path16);
}

void node_CloseDatabase(const v8::FunctionCallbackInfo<v8::Value> &args)
{
  v8::Isolate *isolate = args.GetIsolate();

  if (!node_dllLoaded(isolate))
  {
    return;
  }

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

  v8::String::Utf8Value dbId(isolate, args[0]);
  hNxStr16Ptr dbId_char16 = hNxStr16::fromString(*dbId);
  bool success = lib_CloseDatabase((NxStr16Ptr)dbId_char16);

  args.GetReturnValue().Set(v8::Boolean::New(isolate, success));
}

void node_Execute(const v8::FunctionCallbackInfo<v8::Value> &args)
{
  v8::Isolate *isolate = args.GetIsolate();

  if (!node_dllLoaded(isolate))
  {
    return;
  }

  // check if arg0 exists
  if (args.Length() < 3)
  {
    isolate->ThrowException(v8::Exception::TypeError(
        v8::String::NewFromUtf8(isolate, "Wrong number of arguments").ToLocalChecked()));
    return;
  }

  // check if arg0 is a string
  if (!args[0]->IsString() || !args[1]->IsString() || !args[2]->IsString())
  {
    isolate->ThrowException(v8::Exception::TypeError(
        v8::String::NewFromUtf8(isolate, "Wrong arguments").ToLocalChecked()));
    return;
  }

  v8::String::Utf8Value dbId(isolate, args[0]);
  v8::String::Utf8Value query(isolate, args[1]);
  v8::String::Utf8Value params(isolate, args[2]);

  hNxStr16Ptr dbId_char16 = hNxStr16::fromString(*dbId);
  hNxStr16Ptr query_char16 = hNxStr16::fromString(*query);
  hNxStr16Ptr params_char16 = hNxStr16::fromString(*params);

  hNxStr16Ptr result = ((hNxStr16Ptr)lib_ExecuteSql((NxStr16Ptr)dbId_char16, (NxStr16Ptr)query_char16, (NxStr16Ptr)params_char16));

  const uint16_t *result_char16 = (uint16_t *)result->toChar16();
  args.GetReturnValue().Set(v8::String::NewFromTwoByte(
                                isolate, result_char16)
                                .ToLocalChecked());

  lib_FreeString((NxStr16Ptr)result);
  dbId_char16->destroy(dbId_char16);
  query_char16->destroy(query_char16);
  params_char16->destroy(params_char16);
}
