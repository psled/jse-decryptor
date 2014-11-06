#ifndef JSE_DECRYPTOR_H
#define JSE_DECRYPTOR_H

#include <node.h>

class JSEDecryptor : public node::ObjectWrap {
 public:
  static void Init(v8::Handle<v8::Object> exports,
    v8::Handle<v8::Object> module);

 private:
  explicit JSEDecryptor(v8::Handle<v8::String> key = v8::Undefined());
  ~JSEDecryptor();

  static v8::Handle<v8::Value> New(const v8::Arguments& args);  
  static v8::Handle<v8::Value> Decrypt(const v8::Arguments& args);
  static v8::Persistent<v8::Function> constructor;

  v8::Handle<v8::String> key_;
};

#endif
