#include "functionExample.h"

std::string functionExample::hello(){
    return "Hello World! from c++ to JS";
}

Napi::String functionExample::helloWrapped(const Napi::CallbackInfo& info){
    Napi::Env env = info.Env();
    Napi::String result = Napi::String::New(env, functionExample::hello());
    return result;
}

int functionExample::add(int a, int b){
    return a + b;    
}

Napi::Number functionExample::addWrapped(const Napi::CallbackInfo& info){
    auto env = info.Env();
    if(info.Length() < 2 || !info[0].IsNumber() || !info[1].IsNumber()){
        Napi::TypeError::New(env, "Number excpected").ThrowAsJavaScriptException();
    }
    Napi::Number fst = info[0].As<Napi::Number>();
    Napi::Number snd = info[1].As<Napi::Number>();
    int result = add(fst.Int32Value(), snd.Int32Value());
    return Napi::Number::New(env, result);
}

Napi::Object functionExample::Init(Napi::Env env, Napi::Object exports){
    exports.Set("hello", Napi::Function::New(env, functionExample::helloWrapped));
    exports.Set("add", Napi::Function::New(env, functionExample::addWrapped));
    return exports;
}