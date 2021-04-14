self.onmessage = function(barcodeData) {
    postMessage(zintProcessBarcode(barcodeData.data));
  };
  
  function zintProcessBarcode(barcodeData) {
    var result = [];
    var Module = {};
    
    Module['barcodeText'] =barcodeData.barcodeText;
    Module['barcodeType'] = barcodeData.barcodeType;
    Module['barcodeScale'] = barcodeData.barcodeScale;
    
    Module['outputResult'] = function (...args) {
      
      result.push([...args]);
    };
    /* EMSCRIPTEN_CODE */
  
    return result;
  }
  
  