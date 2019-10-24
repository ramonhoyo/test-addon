/* cppsrc/main.cpp */
#include <napi.h>
#include <string>
#include "samples/functionExample.h"
#include "samples/ActualClassWrapper.h"
#include "samples/DataProcessingAsyncWorker.h"

Napi::Object InitAll(Napi::Env env, Napi::Object exports) {
    ActualClassWrapper::Init(env, exports);
    functionExample::Init(env, exports);
    DataProcessingAsyncWorker::Init(env, exports);
    return exports;
}

NODE_API_MODULE(NODE_GYP_MODULE_NAME, InitAll)