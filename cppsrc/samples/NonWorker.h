#ifndef __NON_WORKER__
#define __NON_WORKER__

#include <napi.h>
#include <thread>
#include <iostream>
namespace NON_WORKER {
    void execAsyn(const Napi::CallbackInfo& info);

}
void NON_WORKER::execAsyn(const Napi::CallbackInfo& info){
    auto callback = info[1].As<Napi::Function>();
    auto buffer =  info[0].As<Napi::Buffer<uint8_t>>();
    auto lenght = buffer.Length();
    auto data = Napi::ObjectReference::New(buffer, 1);
    auto dataPtr = buffer.Data();
    std::thread([dataPtr, lenght, callback, &data]{
        try{
            for (size_t i = 0; i < lenght; i++) {
                uint8_t value = *(dataPtr + i);
                *(dataPtr + i) = value * 2;
                if(!(i % 10)){
                    std::cout << "processing " << ((i+1)*100)/lenght << " %\n";
                }
            }
        } catch(std::exception& e){
            std::cerr << e.what();
        }
        data.Unref();
    }).detach();
}
#endif