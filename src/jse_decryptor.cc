#include <node.h>
#include "jse_decryptor.h"

using namespace v8;

const char* decryption_key = "secretphrase";

Persistent<Function> JSEDecryptor::constructor;

JSEDecryptor::JSEDecryptor(Handle<String> key) : key_(key) {
}

JSEDecryptor::~JSEDecryptor() {
}

void JSEDecryptor::Init(Handle<Object> exports,
    v8::Handle<v8::Object> module) {
  // Prepare constructor template
  Local<FunctionTemplate> tpl = FunctionTemplate::New(New);
  tpl->SetClassName(String::NewSymbol("JSEDecryptor"));
  tpl->InstanceTemplate()->SetInternalFieldCount(1);
  // Prototype
  tpl->PrototypeTemplate()->Set(String::NewSymbol("decrypt"),
      FunctionTemplate::New(Decrypt)->GetFunction());
  constructor = Persistent<Function>::New(tpl->GetFunction());
  exports->Set(String::NewSymbol("JSEDecryptor"), constructor);
}

Handle<Value> JSEDecryptor::New(const Arguments& args) {
  HandleScope scope;

  if (args.IsConstructCall()) {
    // Invoked as constructor: `new MyObject(...)`    
    Handle<String> key = String::New(decryption_key);
    JSEDecryptor* obj = new JSEDecryptor(key);
    obj->Wrap(args.This());
    return args.This();
  } else {
    // Invoked as plain function `MyObject(...)`, turn into construct call.
    const int argc = 1;
    Local<Value> argv[argc] = { args[0] };
    return scope.Close(constructor->NewInstance(argc, argv));
  }
}

Handle<Value> JSEDecryptor::Decrypt(const Arguments& args) {  
  HandleScope scope;

  Local<Object> module = args[0]->ToObject();

  Local<Context> context = Context::GetCurrent(); 
  Local<String> script_source = String::New(
    "(function (module, cryptKey) {"            
    "  var require = module.require;"

    "  var fs = require('fs');"
    "  var encryptedDataBuf = fs.readFileSync(module.filename);"    
    "  var encryptedData = encryptedDataBuf.toString();"    

    "  var crypto = require('crypto');"
    "  var decipher = crypto.createDecipher('aes-256-cbc', cryptKey);"  
    "  var decoded = decipher.update(encryptedData, 'base64', 'utf8');"
    "  decoded += decipher.final('utf8');"

    "  var m = new module.constructor();"
    "  m.paths = module.paths;"
    "  m.id = module.id;"
    "  m.filename = module.filename;"
    "  m.parent = module.parent;"
    "  m._compile(decoded);"
    "  return m.exports;"    
    "})"    
  ); 
  Local<Script> script = Script::New(script_source); 
  Local<Value> value = script->Run(); 
  
  Local<Function> fn = value.As<Function>(); 
  const int fn_argc = 2;
  Handle<Value> fn_argv[] = {
    module,  
    String::New(decryption_key)
  };
  Local<Value> decrypted_mod = fn->Call(context->Global(), fn_argc, fn_argv);

  return scope.Close(decrypted_mod);
}
