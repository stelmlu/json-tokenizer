json_tokenizer.h
================

This is a single-header-file [STB-style](https://github.com/nothings/stb/blob/master/docs/stb_howto.txt) library that tokenize json file for C (also works in C++)

The easiest way to install the library to your C/C++ project is to copy 'n' paste the *json_tokenizer.h* to your project and do this in *one* C or C++ file:

``` C
#define JSON_TOKENIZER_IMPLEMENTATION
#include "json_-_tokenizer.h"
```

Compile-time Options
--------------------

These defines only need to be set in the file containing XML_TOKENIZER_IMPLEMENTATION

``` C
#define JSON_REALLOC(context,ptr,size) better_realloc
#define JSON_FREE(context,ptr)         better_free
```

By default the stdlib realloc() and free() is used. You can defines your own by defining these symbols. You must either define both, or neither.

Note that at the moment, 'context' will always be NULL.

``` C
#define JSON_FOPEN(fp,filename,mode) better_fopen
#define JSON_FGETC(fp)               better_fgetc
#define JSON_FCLOSE(fp)              better_fclose
```

By default the stdlib fopen(), fgetc() and fclose() are used. You can defines you own by defining these symbols. You most either define all three, or neither.

Example
-------

You can find examples how to parser a sample.json file that contains a person data using C++ (C++11).

```
main.cpp
```

License
-------

See LICENSE.txt
