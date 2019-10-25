#include "DataProcessingAsyncWorker.h"
#include <iostream>


Napi::Object DataProcessingAsyncWorker::Init(Napi::Env env, Napi::Object exports){
    Napi::HandleScope scope(env);
    exports.Set("ProcessData", Napi::Function::New(env, DataProcessingAsyncWorker::ProcessData));
    return exports;
}

Napi::Value DataProcessingAsyncWorker::ProcessData(const Napi::CallbackInfo& info){
    Napi::Env env = info.Env();
    if(info.Length() != 2 || !info[0].IsBuffer() || !info[1].IsFunction()){
        Napi::TypeError::New(env, "Expected buffer array and callback").ThrowAsJavaScriptException();
    }    
    Napi::Buffer<uint8_t> buffer = info[0].As<Napi::Buffer<uint8_t>>();
    Napi::Function callback = info[1].As<Napi::Function>();
    (new DataProcessingAsyncWorker(buffer, callback))->Queue();
    return Napi::Number::New(env, 0);
}


DataProcessingAsyncWorker::DataProcessingAsyncWorker(
    Napi::Buffer<uint8_t> &data,
    Napi::Function &callback
) : 
    AsyncWorker(callback),
    dataRef(Napi::ObjectReference::New(data, 1)),
    dataPtr(data.Data()),
    dataLength(data.Length()),
    __env(data.Env())
{
    callbackShared = std::make_shared<ThreadSafeCallback>(callback);
}

void DataProcessingAsyncWorker::Execute() {
    size_t percentStep = dataLength/100;
    for (size_t i = 0; i < dataLength; i++) {
        uint8_t value = *(dataPtr + i);
        *(dataPtr + i) = value * 2;
        if(!((i+1)%percentStep)){
            int currentProgress =  ((i+1)*100)/dataLength;
            callbackShared->call([currentProgress](Napi::Env env, std::vector<napi_value>& args){
                args = { Napi::Number::New(env, currentProgress) };
            });
        }
    }
    callbackShared->call([](Napi::Env env, std::vector<napi_value>& args){
        args = { Napi::Number::New(env, 100) };
    });
}

void DataProcessingAsyncWorker::OnOK() {
    Callback().Call({});
    dataRef.Unref();
}