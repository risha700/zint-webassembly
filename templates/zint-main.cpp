#include <stdlib.h> 
#include <stdio.h>
#include <string.h>
#include <iostream>
#include "/usr/local/include/zint.h"

using namespace std;

#ifdef __cplusplus
extern "C" {
#endif /* __cplusplus */
// make it available for js

    extern void js_output_result(void *(bitmap), int bitmap_width, int bitmap_height, int size, void* extra);
    extern void *js_get_barcode_type();
    extern void *js_get_barcode_text();
    // extern void test_logger();

    // std::cout << convert.to_bytes(s);

    int main(int argc, const char *argv[]) {

    struct zint_symbol *my_symbol;
    my_symbol = ZBarcode_Create();
    strcpy(my_symbol->outfile, "BarcodeTest.bmp");    
    // my_symbol->symbology = BARCODE_QRCODE;
    // my_symbol->input_mode = UNICODE_MODE;
    my_symbol->scale = 2;
    
    string encode_data("BufferingSymbolsInMemory");
    
    // unsigned char js_bc_text = js_get_barcode_text();

    cout<<" TEXTIN C " << atoi((const char *)js_get_barcode_text())<<endl;

    int js_bc_type =(int)js_get_barcode_type();


    cout<<" TYPEIN C " << static_cast<int>(js_bc_type)<<endl;
    // test printing
    // int print_err = ZBarcode_Encode_and_Print(my_symbol, (unsigned char*)encode_data.c_str(), 0, 0);
    // if(print_err!=0){printf("%s\n", my_symbol->errtxt);}


    int error_num = ZBarcode_Encode_and_Buffer(my_symbol, (unsigned char*)encode_data.c_str(), 0, 0);    
    if(error_num != 0){printf("%s\n", my_symbol->errtxt);}

    // unsigned char *a;
    // memcpy(&a, (unsigned char *)my_symbol->bitmap[56], 8);

    js_output_result((uint8_t *)&my_symbol->bitmap,my_symbol->bitmap_width,
                    my_symbol->bitmap_height,((size_t*)my_symbol->bitmap)[-1],
                    (int*)(&(my_symbol->bitmap)[55]));

                    // reinterpret_cast<stringstream *>(&((int*)my_symbol->bitmap)[18*4]));
    
    // wstring binStr = stringstream 

    ZBarcode_Delete(my_symbol);
    return 0;

}
#ifdef __cplusplus
}
#endif /* __cplusplus */

