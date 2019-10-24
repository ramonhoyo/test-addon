#include <napi.h>

namespace functionExample {
    std::string hello();
    Napi::String helloWrapped(const Napi::CallbackInfo& info);
    
    int add(int a, int b);
    Napi::Number addWrapped(const Napi::CallbackInfo& info);
    
    Napi::Object Init(Napi::Env env, Napi::Object exports);
}