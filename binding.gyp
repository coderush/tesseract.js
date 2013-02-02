{
  "targets": [
    {
      'target_name': 'tesseractjsBindings',
      'dependencies': [
        'deps/tesseract/tesseract.gyp:libtesseract',
        'deps/leptonica/leptonica.gyp:liblept',
      ],
      'include_dirs': [
        'deps/leptonica/src',
        'deps/tesseract/api',
        'deps/tesseract/ccmain',
        'deps/tesseract/ccstruct',
        'deps/tesseract/ccutil',
        'deps/tesseract/classify',
        'deps/tesseract/cutil',
        'deps/tesseract/dict',
        'deps/tesseract/image',
        'deps/tesseract/textord',
        'deps/tesseract/viewer',
        'deps/tesseract/wordrec',
      ],
      'sources': [
        'src/TesseractBinding.cc',
        'src/module.cc',
        'src/TesseractBinding.h'
      ],
      'cflags!': ['-fno-exceptions'],
      'cflags_cc!': ['-fno-exceptions'],
      'conditions': [
        ['OS=="mac"',
          {
            'xcode_settings': {
              'GCC_ENABLE_CPP_EXCEPTIONS': 'YES'
            },
            'configurations': {
              'Debug': {
                'msvs_settings': {
                  'VCCLCompilerTool': {
                    'ExceptionHandling': '1',
                  },
                },
              },
              'Release': {
                'msvs_settings': {
                  'VCCLCompilerTool': {
                    'ExceptionHandling': '1',
                  },
                },
              },
            },
          }
        ],
      ],
    },
  ]
}