## zint barcode generator lib with emcc
--
1. setup for compilation with emsdk

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
emmake cmake ..
emmake make zint-static -i
```
