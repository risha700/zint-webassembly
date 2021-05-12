export default class BarcodeGenerator{
    constructor(processor_path='./zint-processor.js', wrapper_class){
        this.processor_path = processor_path
        this.wrapper = wrapper_class? document.getElementsByClassName(wrapper_class)[0]:document.body
        this.worker = null
        this.barcodeText = document.createElement('input')
        this.barcodeType = document.createElement('select')
        this.barcodeScale = document.createElement('input')
        this.button = document.createElement('button')
        this.errorText = document.createElement('p')
        this.init()
    }
    init(){
        this.buildUI()
        this.initWorker()
        this.button.addEventListener('click', (evt)=>{
            this.requestBarcode(evt, {
                'barcodeType':this.barcodeType.value,
                'barcodeText':this.barcodeText.value,
                'barcodeScale':this.barcodeScale.value
            })
        })

    }
    buildUI(){
        this.barcodeText.setAttribute('type', 'text')
        this.barcodeText.placeholder = 'Barcode data...'
        this.generateBarcodeTypes()
        //scale
        this.barcodeScale.setAttribute('type', 'range')
        this.barcodeScale.setAttribute('value', '2')
        this.barcodeScale.setAttribute('min', '2')
        this.barcodeScale.setAttribute('step', 0.25)
        this.barcodeScale.setAttribute('max', '6')
        // button
        this.button.innerHTML = "Generate Barcode"
        
        this.wrapper.appendChild(this.barcodeType)
        this.wrapper.appendChild(this.barcodeText)
        this.wrapper.appendChild(this.barcodeScale)
        this.wrapper.appendChild(this.button)
        this.errorText.setAttribute('style', 'color:red;')
    }
    initWorker(){
        if(this.worker === null) this.worker = new Worker(this.processor_path);
        this.worker.onmessage =(e)=> this.workerOnMessage(e)
    }
    workerOnMessage(e){
        this.handleCErrors(e.data)
        this.outputBMP(e.data)
    }
    requestBarcode(e, data){
        e.preventDefault();
        this.worker.postMessage(data);

    }
    outputBMP(data) {
        // console.log("Got C Data: ", data);
        var arr = new Uint8ClampedArray(data[0][0])
        this.drawBmpArr(arr, data);
    }
    drawBmpArr(arr, data){
        const header_size = 54;
        const width = data[0][1];
        const height = data[0][2];
        const byte_width = 4;
        const image_size = width * height * byte_width;
        // arr = new Uint8Array(header_size + image_size);
        const view = new DataView(arr.buffer);
        this.structBmpDataView(view, arr, header_size, width, height, image_size);
        const blob = new Blob([arr], { type: "image/png" });
        const url = window.URL.createObjectURL(blob);
        const img =document.getElementsByTagName('img')[0]|| new Image();
        img.src = url;
        this.wrapper.appendChild(img)   // needs a change 
    }
    structBmpDataView(view, arr, header_size, width, height, image_size){
        view.setUint16(0, 0x424D, false); // BM magic number.
        view.setUint32(2, arr.length+header_size, true);// File size.
        view.setUint32(10, header_size, true);// Offset to image data.
        view.setUint32(14, 40, true);// Size of BITMAPINFOHEADER
        view.setUint32(18, width, true);// Width
        view.setInt32(22, -height, true);// Height (signed because negative values flip the image vertically).
        view.setUint16(26, 1, true);// Number of colour planes (colours stored as separate images; must be 1).
        view.setUint16(28,24, true);// Bits per pixel.
        view.setUint32(30, 0, true); // Compression method, 0 = BI_RGB // no copression
        view.setUint32(34, image_size, true);// Image size in bytes.
        view.setUint32(38, 2835, true);// Horizontal resolution, pixels per metre.
        view.setUint32(42, 2835, true);// Vertical resolution, pixels per metre.
        view.setUint32(46, 0, true);// Number of colours. 0 = all            
        view.setUint32(50, 0, true);// Number of important colours. 0 = all
    }

    prepareCanvasImageData(bitmap, ctx) {
        var Width =bitmap.infoheader.biWidth;
        var Height =bitmap.infoheader.biHeight;
        var imageData = ctx.createImageData(Width, Height);
        var data = imageData.data;
        var bmpdata = bitmap.pixels;
        var stride = bitmap.stride;

        for (var y = 0; y < Height; ++y) {
            for (var x = 0; x < Width; ++x) {
                var index1 = (x+Width*(Height-y))*4;
                var index2 = x * 3 + stride * y;
                data[index1] = bmpdata[index2 + 2];
                data[index1 + 1] = bmpdata[index2 + 1];
                data[index1 + 2] = bmpdata[index2];
                data[index1 + 3] = 255;
            }
        }
        return imageData;
        }

        generateBarcodeTypes(){
            const BARCODE_TYPES = {1: 'BARCODE_CODE11 Code 1', 2: 'BARCODE_C25MATRIX Standard Code 2 of ', 3: 'BARCODE_C25INTER Interleaved 2 of ', 4: 'BARCODE_C25IATA Code 2 of 5 IAT', 6: 'BARCODE_C25LOGIC Code 2 of 5 Data Logi', 7: 'BARCODE_C25IND Code 2 of 5 Industria', 8: 'BARCODE_CODE39 Code 3 of 9 (Code 39', 9: 'BARCODE_EXCODE39 Extended Code 3 of 9 (Code 39+', 13: 'BARCODE_EANX EA', 16: 'BARCODE_EAN128 GS1-12', 18: 'BARCODE_CODABAR Codaba', 20: 'BARCODE_CODE128 Code 128 (automatic subset switching', 21: 'BARCODE_DPLEIT Deutshe Post Leitcod', 22: 'BARCODE_DPIDENT Deutshe Post Identcod', 23: 'BARCODE_CODE16K Code 16', 24: 'BARCODE_CODE49 Code 4', 25: 'BARCODE_CODE93 Code 9', 28: 'BARCODE_FLAT Flattermarke', 29: 'BARCODE_RSS14 GS1 DataBar-1', 30: 'BARCODE_RSS_LTD GS1 DataBar Limite', 31: 'BARCODE_RSS_EXP GS1 DataBar Expande', 32: 'BARCODE_TELEPEN Telepen Alph', 34: 'BARCODE_UPCA UPC ', 37: 'BARCODE_UPCE UPC ', 40: 'BARCODE_POSTNET PostNe', 47: 'BARCODE_MSI_PLESSEY MSI Plesse', 49: 'BARCODE_FIM FI', 50: 'BARCODE_LOGMARS LOGMAR', 51: 'BARCODE_PHARMA Pharmacode One-Trac', 52: 'BARCODE_PZN PZ', 53: 'BARCODE_PHARMA_TWO Pharmacode Two-Trac', 55: 'BARCODE_PDF417 PDF41', 56: 'BARCODE_PDF417TRUNC PDF417 Truncate', 57: 'BARCODE_MAXICODE Maxicod', 58: 'BARCODE_QRCODE QR Cod', 60: 'BARCODE_CODE128B Code 128 (Subset B', 63: 'BARCODE_AUSPOST Australia Post Standard Custome', 66: 'BARCODE_AUSREPLY Australia Post Reply Pai', 67: 'BARCODE_AUSROUTE Australia Post Routin', 68: 'BARCODE_AUSREDIRECT Australia Post Redirectio', 69: 'BARCODE_ISBNX ISBN (EAN-13 with verification stage', 70: 'BARCODE_RM4SCC Royal Mail 4 State (RM4SCC', 71: 'BARCODE_DATAMATRIX Data Matri', 72: 'BARCODE_EAN14 EAN-1', 75: 'BARCODE_NVE18 NVE-1', 76: 'BARCODE_JAPANPOST Japanese Pos', 77: 'BARCODE_KOREAPOST Korea Pos', 79: 'BARCODE_RSS14STACK GS1 DataBar-14 Stacke', 80: 'BARCODE_RSS14STACK_OMNI GS1 DataBar-14 Stacked Omnidirectiona', 81: 'BARCODE_RSS_EXPSTACK GS1 DataBar Expanded Stacke', 82: 'BARCODE_PLANET PLANE', 84: 'BARCODE_MICROPDF417 MicroPDF41', 85: 'BARCODE_ONECODE USPS OneCod', 86: 'BARCODE_PLESSEY Plessey Cod', 87: 'BARCODE_TELEPEN_NUM Telepen Numeri', 89: 'BARCODE_ITF14 ITF-1', 90: 'BARCODE_KIX Dutch Post KIX Cod', 92: 'BARCODE_AZTEC Aztec Cod', 93: 'BARCODE_DAFT DAFT Cod', 97: 'BARCODE_MICROQR Micro QR Cod', 98: 'BARCODE_HIBC_128 HIBC Code 12', 99: 'BARCODE_HIBC_39 HIBC Code 3', 102: 'BARCODE_HIBC_DM HIBC Data Matri', 104: 'BARCODE_HIBC_QR HIBC QR Cod', 106: 'BARCODE_HIBC_PDF HIBC PDF41', 108: 'BARCODE_HIBC_MICPDF HIBC MicroPDF41', 112: 'BARCODE_HIBC_AZTEC HIBC Aztec Cod', 128: 'BARCODE_AZRUNE Aztec Rune', 129: 'BARCODE_CODE32 Code 3', 130: 'BARCODE_EANX_CC Composite Symbol with EAN linear componen', 131: 'BARCODE_EAN128_CC Composite Symbol with GS1-128 linear componen', 132: 'BARCODE_RSS14_CC Composite Symbol with GS1 DataBar-14 linear componen', 133: 'BARCODE_RSS_LTD_CC Composite Symbol with GS1 DataBar Limited componen', 134: 'BARCODE_RSS_EXP_CC Composite Symbol with GS1 DataBar Extended componen', 135: 'BARCODE_UPCA_CC Composite Symbol with UPC A linear componen', 136: 'BARCODE_UPCE_CC Composite Symbol with UPC E linear componen', 137: 'BARCODE_RSS14STACK_CC Composite Symbol with GS1 DataBar-14 Stacked componen', 138: 'BARCODE_RSS14_OMNI_CC Composite Symbol with GS1 DataBar-14 Stacked Omnidirectional componen', 139: 'BARCODE_RSS_EXPSTACK_CC Composite Symbol with GS1 DataBar Expanded Stacked componen', 140: 'BARCODE_CHANNEL Channel Cod', 141: 'BARCODE_CODEONE Code On', 142: 'BARCODE_GRIDMATRIX Grid Matr'}
            Object.keys(BARCODE_TYPES).map((idx)=>{
                let opt = document.createElement('option')
                opt.value = idx
                opt.innerHTML = BARCODE_TYPES[idx]
                if(idx ==20)opt.setAttribute('selected','');
                this.barcodeType.appendChild(opt)
            })
        }
        handleCErrors(data){
            //* data = {[bitmap, bitmap_width, bitmap_height, bitmap_size, errors]} *// 
            try{this.wrapper.removeChild(this.errorText)}catch{}
            if(data[0][4].length){
                this.errorText.innerText = data[0][4];
                this.wrapper.appendChild(this.errorText)
            }
        }

}