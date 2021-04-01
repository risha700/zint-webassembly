

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
    js_output_result: function (symbol, data) {
      
      var Pointer_stringify = Module["UTF8ToString"];
      console.log('sybmol unstrigified', symbol, data)
      // console.log('called on result', Pointer_stringify(symbol), Pointer_stringify(data));

      // console.log("sym", Pointer_stringify(symbol))
      // console.log("data",Pointer_stringify(data))
      var HEAPU32 = Module['HEAPU32'];
    //   const resultView = new Int32Array(
    //     HEAP32.buffer,
    //     polygon,
    //     polygon_size * 2
    // );
    // const coordinates = new Int32Array(resultView);
      Module['outputResult'](Pointer_stringify(symbol),
                             Pointer_stringify(data))
    //                          coordinates);
    }
  });
  