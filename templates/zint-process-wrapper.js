self.onmessage = function(barcodeData) {
    console.log('called from wrapper onmsg', barcodeData)
    postMessage(zintProcessBarcode(barcodeData.data));
  };
  
  function zintProcessBarcode(barcodeData) {
    var result = [];
    var Module = {};
    
    Module['barcodeText'] =barcodeData.barcodeText;
    Module['barcodeType'] = barcodeData.barcodeType;

    Module['outputResult'] = function (...args) {
      
      result.push([...args]);
    };
    /* EMSCRIPTEN_CODE */
  
    return result;
  }
  
  