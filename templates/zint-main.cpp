#include <stdlib.h> 
#include <stdio.h>
#include <string.h>
#include <iostream>
#include <sstream> 
#include "/usr/local/include/zint.h"
#include <cstdlib>


using namespace std;


#ifdef __cplusplus
extern "C" {
#endif /* __cplusplus */
// make it available for js

    extern void js_output_result(void *(bitmap), int bitmap_width, int bitmap_height, int size, void* extra);
    extern void *js_get_barcode_type();
    extern char *js_get_barcode_text();
    // extern void test_logger();

    // std::cout << convert.to_bytes(s);

    int main(int argc, const char *argv[]) {

    struct zint_symbol *my_symbol;
    int js_bc_type =reinterpret_cast<int>(js_get_barcode_type());//this is ok

    // const char js_bc_text=reinterpret_cast<const char>(js_get_barcode_text());

    // char cp_str;
    // strcpy(&cp_str, js_get_barcode_text());
    // stringstream ss;
    // ss<<js_bc_text;
    // string str_bc_text = ss.str();

    // cout<<"textin c "<<js_bc_text<<endl;


    my_symbol = ZBarcode_Create();
    strcpy(my_symbol->outfile, "BarcodeTest.bmp");    
    // my_symbol->symbology = BARCODE_QRCODE;
    my_symbol->symbology =js_bc_type;
    my_symbol->input_mode = UNICODE_MODE;
    my_symbol->scale = 3;
    // my_symbol->option_3 = DM_DMRE;
    string js_bc_text =js_get_barcode_text();
    // cout<<" ptr: "<<ct<<"\n var: "<<ct<<"\n mem:"<<&ct<<"\n char from mem:"<<(uint8_t*)&ct<<endl;

    string encode_data(js_bc_text);

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

