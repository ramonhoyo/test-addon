{
    "targets": [{
        "target_name": "testaddon",
        "cflags!": [ "-fno-exceptions" ],
        "cflags_cc!": [ "-fno-exceptions" ],
        "sources": [
            "cppsrc/main.cpp",
            "cppsrc/samples/functionExample.cpp",
            "cppsrc/samples/ActualClass.cpp",
            "cppsrc/samples/actualclasswrapper.cpp",
        ],
        'include_dirs': [
            "<!@(node -p \"require('node-addon-api').include\")"
        ],
        'libraries': [],
        'dependencies': [
            "<!(node -p \"require('node-addon-api').gyp\")",
            "<!@(node -p \"require('napi-thread-safe-callback').include\")"
        ],
        'defines': [ 'NAPI_DISABLE_CPP_EXCEPTIONS' ]
    }]
}