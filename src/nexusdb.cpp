#include <node.h>
#include <v8.h>
// #include <string.h>
#include <stdbool.h>
#include <loadLib.h>
#include <nodeLib.h>

// function that returns a string

void Method(const v8::FunctionCallbackInfo<v8::Value> &args)
{
  v8::Isolate *isolate = args.GetIsolate();
  args.GetReturnValue().Set(v8::String::NewFromUtf8(
                                isolate, "world")
                                .ToLocalChecked());
}

void init(v8::Local<v8::Object> exports, v8::Local<v8::Object> module)
{
  NODE_SET_METHOD(exports, "hello", Method);
  NODE_SET_METHOD(exports, "loadDll", node_LoadDll);
  NODE_SET_METHOD(exports, "unloadDll", node_UnloadDll);
  NODE_SET_METHOD(exports, "addDatabase", node_AddDatabase);
  NODE_SET_METHOD(exports, "addRemoteDatabase", node_AddRemoteDatabase);
  NODE_SET_METHOD(exports, "closeDatabase", node_CloseDatabase);
}

NODE_MODULE(NODE_GYP_MODULE_NAME, init)