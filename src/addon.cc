#include <node.h>
#include "jse_decryptor.h"

using namespace v8;

void InitAll(Handle<Object> exports, Handle<Object> module) {
  JSEDecryptor::Init(exports, module);
}

NODE_MODULE(addon, InitAll)
