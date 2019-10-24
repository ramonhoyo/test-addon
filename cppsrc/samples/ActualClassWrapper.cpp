#include "ActualClassWrapper.h"

Napi::FunctionReference ActualClassWrapper::m_contructor;

Napi::Object ActualClassWrapper::Init(Napi::Env env, Napi::Object exports){
    Napi::HandleScope scope(env);

    Napi::Function func = DefineClass(env, "ActualClass", {
        InstanceMethod("add", &ActualClassWrapper::add),
        InstanceMethod("getValue", &ActualClassWrapper::getValue)
    });

    m_contructor = Napi::Persistent(func);
    m_contructor.SuppressDestruct();
    
    exports.Set("ActualClass", func);
    return exports;
}


ActualClassWrapper::ActualClassWrapper(const Napi::CallbackInfo& info)
    : Napi::ObjectWrap<ActualClassWrapper>(info) 
{
    Napi::Env env = info.Env(); 
    Napi::HandleScope scope(env);

    int len = info.Length();
    if(len != 1 || !info[0].IsNumber()){
        Napi::TypeError::New(env, "Expected number").ThrowAsJavaScriptException();
    }

    Napi::Number value = info[0].As<Napi::Number>();
    m_class = new ActualClass(value.DoubleValue());
}

Napi::Value ActualClassWrapper::getValue(const Napi::CallbackInfo& info){
    Napi::Env env = info.Env(); 
    Napi::HandleScope scope(env);
    return Napi::Number::New(env, m_class->getValue());
}

Napi::Value ActualClassWrapper::add(const Napi::CallbackInfo& info){
    Napi::Env env = info.Env(); 
    Napi::HandleScope scope(env);
    if(info.Length() != 1 || !info[0].IsNumber()){
        Napi::TypeError::New(env, "Expected Number").ThrowAsJavaScriptException();
    }
    Napi::Number value = info[0].As<Napi::Number>();
    return Napi::Number::New(env, m_class->addValue(value.DoubleValue()));
}
