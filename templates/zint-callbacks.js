mergeInto(LibraryManager.library, {
  js_get_barcode_text: function () { 
    var barcodeTextString = Module['barcodeText']
    var Pointer_generate = Module["stringToUTF8"];
    var buffer = Module._malloc(barcodeTextString.length + 1);//was not freed
    Pointer_generate(barcodeTextString, buffer, barcodeTextString.length*4+1)
    return buffer
    
  },
  js_get_barcode_type: function () { 
    return Module['barcodeType'];
  },
  js_output_result: function (bitmap, width, height, size, extra) {
    // var Pointer_stringify = Module["UTF8ToString"];
    var HEAPU8 = Module['HEAPU8'];
    const resultView = new Uint8Array(
      HEAP8.buffer,
      bitmap
      // ((width *height)*4)+1
  );
  // var offset = Module._malloc(size)
    const bitmap_pointer = new Uint8Array(resultView);
    
    Module['outputResult'](bitmap_pointer,width,height, size, extra);
  },


});
