#ifndef __DATA_PROCESSING_ASYNC__
#define __DATA_PROCESSING_ASYNC__

#include <napi.h>

class DataProcessingAsyncWorker : public Napi::AsyncWorker {
public:
    static Napi::Object Init(Napi::Env env, Napi::Object exports);
    static Napi::Value ProcessData(const Napi::CallbackInfo& info);
    DataProcessingAsyncWorker(Napi::Buffer<uint8_t> &data, Napi::Function &callback);
    void Execute() override;
    void OnOK() override;
 private:
    Napi::ObjectReference dataRef;
    uint8_t *dataPtr;
    size_t dataLength;
    Napi::Env __env;
};

#endif