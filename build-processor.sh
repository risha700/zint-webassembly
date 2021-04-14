#/bin/bash
# # Any copyright is dedicated to the Public Domain.
# # http://creativecommons.org/publicdomain/zero/1.0/
#emcc fastcomp version
fastcomp_version="sdk-releases-fastcomp-edf24e7233e0def312a08cc8dcec63a461155da1-64bit"
emsdk_exist=`which emsdk`
if [ "$?" != "0" ]
then
  if [ ! -d "emsdk" ]
  then
  echo "Installing emsdk..."
  git clone git@github.com:emscripten-core/emsdk.git
  wait $!
  cd emsdk && ./emsdk install ${fastcomp_version} && ./emsdk activate ${fastcomp_version}  && source emsdk_env.sh && cd ..
  wait $!
  else
    source emsdk/emsdk_env.sh
  fi

fi

# make build
############
make_build(){
  cd  zint-2.9.1-src &&  mkdir -p build && cd build
  # emcmake cmake ..  -DZLIB_INCLUDE_DIR=/usr/local/include  -DPNG_INCLUDE_DIR=/usr/local/Cellar/libpng/1.6.37/include -DPNG_PNG_INCLUDE_DIR=/usr/local/Cellar/libpng/1.6.37/include  -DZLIB_LIBRARY=/System/Volumes/Data/usr/local/bin/zlib-flate -DPNG_LIBRARY=/usr/local/lib/libpng.a
  emcmake cmake ..  -DNO-PNG=0 -DNO-ZLIB=0 -DNO-Qt5=0

  #  -DEMSCRIPTEN_GENERATE_BITCODE_STATIC_LIBRARIES=1
}
# build 
#######
build(){
  emmake make zint-static -j -i
}

compile_processor(){
  emcc -O3 -o a.out.js \
    --js-library `pwd`/templates/zint-callbacks.js \
    -s WASM=0 \
    -s EXTRA_EXPORTED_RUNTIME_METHODS='["UTF8ToString","stringToUTF8"]' \
    -s SINGLE_FILE=1 -s SIDE_MODULE=0\
    -s ERROR_ON_UNDEFINED_SYMBOLS=0\
    -s EXPORTED_FUNCTIONS='["_main"]' -s ASSERTIONS=1\
    `pwd`/templates/zint-main.cpp `pwd`/zint-2.9.1-src/build/backend/libzint-static.a

    if [ "$?" == "0" ]
    then
    echo " ✅ Compiled Successfully"
    fi

    sed '/\/\* EMSCRIPTEN_CODE \*\//r ./a.out.js' ./templates/zint-process-wrapper.js > ./zint-processor.js
    rm a.out.js
}

if [ "$1" == "make_build" ]
then
  make_build
  build
  exit
  return 0
fi
# echo "$1"
# echo "$#"
# echo "$?"


if [ ! -d "zint-2.9.1-src" ]
then
  echo "Didn't find library src folder"
  if [ ! -f "zint-2.9.1-src.tar.gz"  ] 
    then
    echo "Didn't find library tar file, downloading..."
    wget https://sourceforge.net/projects/zint/files/zint/2.9.1/zint-2.9.1-src.tar.gz
    wait $!
    tar -xf zint-2.9.1-src.tar.gz 
    wait $!
    mv zint-2.9.1-src/backend/Makefile.mingw zint-2.9.1-src/backend/Makefile
    sed -i '' -e 's/set(ZINT_STATIC FALSE CACHE BOOL "Build static library")/set(ZINT_STATIC TRUE CACHE BOOL "Build static library")/g' zint-2.9.1-src/CMakeLists.txt 
    echo "Setup completed..."
    make_build
    wait $!
    build
    wait $!
    cd ../..
  fi
fi

if [ -d "zint-2.9.1-src"  ]
then
    echo "Compiling processor...."
    compile_processor
fi