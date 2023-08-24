#include <node.h>
#include <v8.h>
#include <string.h>
#include <loadLib.h>

#include <nodeLib.h>

void node_AddDatabase(const v8::FunctionCallbackInfo<v8::Value> &args)
{
  v8::Isolate *isolate = args.GetIsolate();

  char16_t *dbId = (lib_AddDatabase)();
  uint16_t *dbId_uint = reinterpret_cast<uint16_t *>(dbId);
  args.GetReturnValue().Set(v8::String::NewFromTwoByte(
                                isolate, dbId_uint)
                                .ToLocalChecked());
}

void node_AddRemoteDatabase(const v8::FunctionCallbackInfo<v8::Value> &args)
{
  v8::Isolate *isolate = args.GetIsolate();

  char16_t *dbId = (lib_AddRemoteDatabase)();
  uint16_t *dbId_uint = reinterpret_cast<uint16_t *>(dbId);
  args.GetReturnValue().Set(v8::String::NewFromTwoByte(
                                isolate, dbId_uint)
                                .ToLocalChecked());
}

void node_CloseDatabase(const v8::FunctionCallbackInfo<v8::Value> &args)
{
  v8::Isolate *isolate = args.GetIsolate();

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
  char16_t *dbId_char16 = reinterpret_cast<char16_t *>(*dbId);
  bool success = (lib_CloseDatabase)(dbId_char16);

  args.GetReturnValue().Set(v8::Boolean::New(isolate, success));
}
