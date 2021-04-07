## zint barcode generator lib with emcc
--
1. setup for compilation with emsdk
fastcomp for build cmake

2. download lib
```
wget https://sourceforge.net/projects/zint/files/zint/2.9.1/zint-2.9.1-src.tar.gz

tar -xf zint-2.9.1-src.tar.gz 

mv zint-2.9.1-src/backend/Makefile.mglw zint-2.9.1-src/backend/Makefile

# build static only
--------
nano CMakeLists.txt
lineno:23 set(ZINT_STATIC TRUE CACHE BOOL "Build static library")

# build
--------
mkdir build
cd build

emcmake cmake ..  -DZLIB_INCLUDE_DIR=usr/local/include -DPNG_INCLUDE_DIR=/usr/local/Cellar/libpng/1.6.37/include -DEMSCRIPTEN_GENERATE_BITCODE_STATIC_LIBRARIES=1

emmake make zint-static -j -i
```
