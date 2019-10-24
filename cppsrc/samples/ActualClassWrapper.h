#ifndef __ACTUAL_CLASS_WRAPPER__
#define __ACTUAL_CLASS_WRAPPER__

#include <napi.h>
#include "ActualClass.h"

class ActualClassWrapper: public Napi::ObjectWrap<ActualClassWrapper> {
private:
    static Napi::FunctionReference m_contructor;
    Napi::Value getValue(const Napi::CallbackInfo& info);
    Napi::Value add(const Napi::CallbackInfo& info);
    ActualClass* m_class;
public:
    static Napi::Object Init(Napi::Env env, Napi::Object exports);
    ActualClassWrapper(const Napi::CallbackInfo& info);
};

#endif
