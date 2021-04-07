#include <stdlib.h> 
#include <stdio.h>
#include <string.h>
#include <iostream>
#include "/usr/local/include/zint.h"
#include <streambuf>
#include<sstream>
#include <bitset>
#include <vector>
#include <algorithm>
#include <memory>

using namespace std;

#ifdef __cplusplus
extern "C" {
#endif /* __cplusplus */
// make it available for js

    extern void js_output_result(void *(bitmap), int bitmap_width, int bitmap_height, int size);
    extern int js_get_barcode_type();
    extern char* js_get_barcode_text();
    // extern void test_logger();




    int main(int argc, const char *argv[]) {
    struct zint_symbol *my_symbol;
    my_symbol = ZBarcode_Create();
    strcpy(my_symbol->outfile, "BarcodeTest.bmp");    
    // my_symbol->symbology = BARCODE_QRCODE;
    // my_symbol->input_mode = UNICODE_MODE;
    my_symbol->scale = 5;
    string encode_data("BufferingSymbolsInMemory");

    int error_num = ZBarcode_Encode_and_Buffer(my_symbol, (unsigned char*)encode_data.c_str(), 0, 0);    
    if(error_num != 0){printf("%s\n", my_symbol->errtxt);}

    js_output_result((uint8_t *)&my_symbol->bitmap,
     my_symbol->bitmap_width,
     my_symbol->bitmap_height, sizeof(my_symbol->bitmap_byte_length));
    
    
    ZBarcode_Delete(my_symbol);
    return 0;

}
#ifdef __cplusplus
}
#endif /* __cplusplus */

