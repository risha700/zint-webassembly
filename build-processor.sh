# #/bin/bash
# # Any copyright is dedicated to the Public Domain.
# # http://creativecommons.org/publicdomain/zero/1.0/
# #emcc fastcomp version
# cd zbar-0.10
# # unpacked from http://downloads.sourceforge.net/project/zbar/zbar/0.10/zbar-0.10.tar.bz2
# # no need in most of the features
# # CFLAGS=-I/usr/local/include -DCMAKE_OSX_ARCHITECTURES="armv7;armv7s;arm64" LDFLAGS=-Os
# # CMAKE_CXX_STANDARD=11  LDFLAGS=-Os CFLAGS=-I/Users/rs/code/zbarjs-master/emsdk/upstream/include  
# # export AR=emar export CFLAGS=-I/usr/local/include export CMAKE_CXX_STANDARD=11 export LDFLAGS=-Os 

# env emconfigure ./configure --without-PACKAGE --without-png
# emmake make
# AR=emar CFLAGS=-I/usr/local/include CMAKE_CXX_STANDARD=11 LDFLAGS=-Os 
# emmake cmake -S $SRC -B $OUT -DEMSCRIPTEN_GENERATE_BITCODE_STATIC_LIBRARIES=1
# emcc --bind `pwd`/zint-2.9.1-src/build/backend/libzint-static.a `pwd`/templates/zint-main.cpp  -o a.out.js \
#  --js-library `pwd`/templates/zint-callbacks.js \
#   -L/usr/local/Cellar/libpng/1.6.37/include   \
#   -s WASM=0 \
#   -s EXTRA_EXPORTED_RUNTIME_METHODS='["UTF8ToString","stringToUTF8"]' \
#   -s SINGLE_FILE=1 -s EXIT_RUNTIME=1 -s FORCE_FILESYSTEM=1\
#    -s ERROR_ON_UNDEFINED_SYMBOLS=0 -s DEMANGLE_SUPPORT=1 \
#   -s EXPORTED_FUNCTIONS='["_main"]' 

# export CFLAGS=$CFLAGS:/usr/local/opt/libpng
emcc -O0 -o a.out.js \
  --js-library `pwd`/templates/zint-callbacks.js \
  -I/usr/local/Cellar/libpng/1.6.37/include\
  -I/usr/local/Cellar/node/15.13.0/include/node\
  -L/usr/local/Cellar/libpng/1.6.37/lib/libpng16.a\
  -s WASM=0 -s USE_LIBPNG=1 \
  -s EXTRA_EXPORTED_RUNTIME_METHODS='["UTF8ToString","stringToUTF8","UTF8ArrayToString","UTF32ToString","writeStringToMemory","setValue" ]' \
  -s SINGLE_FILE=1 \
  -s ERROR_ON_UNDEFINED_SYMBOLS=0 -s EXPORT_ALL=1 -s ALLOW_MEMORY_GROWTH=1\
  -s EXPORTED_FUNCTIONS='["_main","_iconv","_iconv_open","_iconv_close","_js_get_barcode_text"]' -s ASSERTIONS=1\
  `pwd`/templates/zint-main.cpp `pwd`/zint-2.9.1-src/backend/*.c `pwd`/zint-2.9.1-src/build/backend/libzint.a

# -s EXIT_RUNTIME=1 -s FORCE_FILESYSTEM=1
# -s USE_ZLIB=1 -s USE_SDL=2
# -I/usr/local/include -L/usr/local/lib
#  /usr/local/Cellar/libpng/1.6.37/lib
  # -s RUNTIME_LINKED_LIBS='["`pwd`/zint-2.9.1-src/build/backend/libzint-static.a"]'\
# `pwd`/templates/zint-main.cpp `pwd`/zint-2.9.1-src/backend/*.c\
# 
  # -s FORCE_FILESYSTEM=1\

  # -s RUNTIME_LINKED_LIBS='["`pwd`/zint-2.9.1-src/build/backend/libzint.2.9.0.dylib"]'

  # -L `pwd`/zint-2.9.1-src/backend  `pwd`/zint-2.9.1-src/build/backend/libzint-static.a\

  # -s EXPORTED_FUNCTIONS='["_main"]' \

  # -s EXPORTED_FUNCTIONS='["_main"]' \
#  --llvm-opts='["allow-undefined","export-all"]'\
  
  #  -s RUNTIME_LINKED_LIBS='["/usr/local/opt/zint/lib/libzint.dylib"]'\
  #  -s ERROR_ON_UNDEFINED_SYMBOLS=0\
  # -DLLVM_ENABLE_PROJECTS='lld;clang,c++'\
  # -s LLD_REPORT_UNDEFINED -v
  # -s EXPORT_ALL=1 \
  # --ignore-dynamic-linking
  # -I /Applications/Xcode.app/Contents/Developer/Platforms/MacOSX.platform/Developer/SDKs/MacOSX11.1.sdk/usr/lib/libz.tbd\

  # -s RUNTIME_LINKED_LIBS='["`pwd`/zint-2.9.1-src/build/backend/libzint.2.9.0.dylib"]'\
#  -L /usr/local/bin/ /usr/local/lib/libzint.dylib `pwd`/templates/zint-main.cpp  `pwd`/zint-2.9.1-src/build/backend/libzint.2.9.0.dylib\
# 
  #  -s ERROR_ON_UNDEFINED_SYMBOLS=0
  # -s DEMANGLE_SUPPORT=1
  # -s ERROR_ON_UNDEFINED_SYMBOLS=0
  # -s USE_BOOST_HEADERS=1 -s PROXY_POSIX_SOCKETS=1 -s USE_PTHREADS=1 -s PROXY_TO_PTHREAD=1 -s USE_ZLIB=2
  # -I `pwd`/zint-2.9.1-src/build/backend/libzint.2.9.0.dylib \
  # -s EXPORTED_FUNCTIONS='["_main","_iconv","_iconv_open","_iconv_close"]' \

  
  # -s ERROR_ON_UNDEFINED_SYMBOLS=0\
  #  -I`pwd`/include  ../templates/zbar-main.c `pwd`/zbar/.libs/libzbar.a \
#
# unused options
# -s SIDE_MODULE=0 \
# -s LINKABLE=1 \
#   -s ALLOW_MEMORY_GROWTH=1 \
#   -s SAFE_HEAP=1 \
#   -s MALLOC=emmalloc \
#   -s FORCE_FILESYSTEM=1 \
#   -s ASSERTIONS=0 \
#   -s SINGLE_FILE=1 \
# -s BINARYEN=1 \
#   -s --save-bc 
sed '/\/\* EMSCRIPTEN_CODE \*\//r ./a.out.js' ./templates/zint-process-wrapper.js > ./zint-processor.js
cd ..