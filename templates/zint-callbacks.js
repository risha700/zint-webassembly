

mergeInto(LibraryManager.library, {
    js_get_barcode_text: function () { 
      // console.log(`Module['barcodeText'] ${Module['barcodeText']}`);
      // var binarien = Module['stringToUTF8']
      // var HEAPU8 = Module['HEAPU8'];
      // console.log('dataptr', dataPtr);
      // console.log( binarien(Module['barcodeText'], dataPtr, 100)); 
      // return binarien(Module['barcodeText'], HEAPU8.buffer, 100)
      return Module['barcodeText'];
      
    },
    js_get_barcode_type: function () { 
      // var binarien = Module['stringToUTF8']
      // var HEAPU8 = Module['HEAPU8'];
      // console.log(dataPtr)
      // return binarien(Module['barcodeType'], dataPtr, 100)
      return Module['barcodeType'];
    },
    test_logger:function(){console.log(Module)},
    // js_read_input: function (dataPtr, len) {
    //   var HEAPU8 = Module['HEAPU8'];
    //   var array = HEAPU8.subarray(dataPtr, dataPtr + len);
    //   Module['getImageData'](array);
    //   return array.length;
    // },
    js_output_result: function (bitmap, width, height, size, extra) {
      // var Pointer_stringify = Module["UTF32ToString"];
      var Pointer_stringify = Module["UTF8ToString"];

      
      console.log(Module);
      var HEAPU32 = Module['HEAPU32'];
      const resultView = new Uint32Array(
        HEAP32.buffer,
        bitmap,
        // size
        // (width *height)*4
    );
      const bitmap_pointer = new Uint32Array(resultView);
      // console.log('called from js_output_result',"bitmap pointer: ", bitmap_pointer,"bitmap plain", bitmap);
      Module['outputResult'](bitmap_pointer,width,height, size, extra);
    },
    
    iconv_open: function (toCode, fromCode) {
      var Pointer_stringify = Module["UTF8ToString"];
      var iconv = Module['iconvCache'] || (Module['iconvCache'] = {});
      var cd = Module['_malloc'](1);
      var descriptor = {
        toCode: Pointer_stringify(toCode),
        fromCode: Pointer_stringify(fromCode)
      };
      descriptor.decoder = new TextDecoder(descriptor.fromCode
                                                     .toLowerCase()
                                                     .replace(/\/\/.*$/, ''));
      descriptor.encoder = new TextEncoder(descriptor.toCode
                                                     .toLowerCase()
                                                     .replace(/\/\/.*$/, ''));
      iconv[cd] = descriptor;
      return cd;
    },
    iconv: function (cd, inbuf, inbytesleft, outbuf, outbytesleft) {
      var iconv = Module['iconvCache'];
      var descriptor = iconv[cd];
      var HEAPU8 = Module['HEAPU8'], HEAP32 = Module['HEAP32'];
      var offset = HEAP32[(inbuf >> 2)];
      var count = HEAP32[(inbytesleft >> 2)];
      var str = descriptor.decoder.decode(HEAPU8.subarray(offset, offset + count));
      HEAP32[(inbuf >> 2)] += count;
      HEAP32[(inbytesleft >> 2)] = 0;
      var bytes = descriptor.encoder.encode(str);
      var dest = HEAP32[(outbuf >> 2)];
      // HACK ignoring overflow for now
      HEAPU8.set(bytes, dest);
      HEAP32[(outbuf >> 2)] += bytes.length;
      HEAP32[(outbytesleft >> 2)] -= bytes.length;
      return str.length;
    },
    iconv_close: function (cd) {
      var iconv = Module['iconvCache'];
      delete iconv[cd];
      Module['_free'](cd);
    }

  
  });
  