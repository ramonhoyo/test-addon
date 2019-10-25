{
    "targets": [{
        'cflags!': [ '-fno-exceptions' ],
        'cflags_cc!': [ '-fno-exceptions' ],
        'xcode_settings': {
            'GCC_ENABLE_CPP_EXCEPTIONS': 'YES',
            'CLANG_CXX_LIBRARY': 'libc++',
            'MACOSX_DEPLOYMENT_TARGET': '10.7',
        },
        'msvs_settings': {
            'VCCLCompilerTool': { 'ExceptionHandling': 1 },
        },
        'conditions': [
            ['OS=="win"', { 'defines': [ '_HAS_EXCEPTIONS=1' ] }]
        ],
        "target_name": "testaddon",
        "sources": [
            "cppsrc/main.cpp",
            "cppsrc/samples/functionExample.cpp",
            "cppsrc/samples/ActualClass.cpp",
            "cppsrc/samples/ActualClassWrapper.cpp",
            "cppsrc/samples/DataProcessingAsyncWorker.cpp"
        ],
        'include_dirs': [
            "<!@(node -p \"require('node-addon-api').include\")",
            "<!@(node -p \"require('napi-thread-safe-callback').include\")"
        ],
        'libraries': [],
        'dependencies': [
            "<!(node -p \"require('node-addon-api').gyp\")"
        ]
       
    }]
}