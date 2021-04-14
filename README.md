## zint barcode generator lib with emcc
-----------------
## Jump start with build script: 
```
./build-processor.sh
```
that basically does the following:

1. setup for compilation with emsdk  2.0.15 

fastcomp for build cmake build static

2. download & extract libs
```
wget https://sourceforge.net/projects/zint/files/zint/2.9.1/zint-2.9.1-src.tar.gz

tar -xf zint-2.9.1-src.tar.gz 
```
## some fixes to compile as static
```
mv zint-2.9.1-src/backend/Makefile.mglw zint-2.9.1-src/backend/Makefile

# build static only
--------
nano CMakeLists.txt
lineno:23 set(ZINT_STATIC TRUE CACHE BOOL "Build static library")
```

# build
```
mkdir build
cd build

#emcmake cmake ..  -DZLIB_INCLUDE_DIR=usr/local/include -DPNG_INCLUDE_DIR=/usr/local/Cellar/libpng/1.6.37/include 

#optional include bitcode
#-DEMSCRIPTEN_GENERATE_BITCODE_STATIC_LIBRARIES=1


emcmake cmake ..  -DZLIB_INCLUDE_DIR=/usr/local/include  -DPNG_INCLUDE_DIR=/usr/local/Cellar/libpng/1.6.37/include -DPNG_PNG_INCLUDE_DIR=/usr/local/Cellar/libpng/1.6.37/include  -DZLIB_LIBRARY=/System/Volumes/Data/usr/local/bin/zlib-flate -DPNG_LIBRARY=/usr/local/lib/libpng.a -DEMSCRIPTEN_GENERATE_BITCODE_STATIC_LIBRARIES=1

#if error png headers
emmake make -I/usr/local/Cellar/libpng/1.6.37/include -j

emmake make zint-static -j -i

```

