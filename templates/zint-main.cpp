#include <stdlib.h> 
#include <stdio.h>
#include <string.h>
#include <iostream>
#include "/usr/local/include/zint.h"



using namespace std;
void check_endians(){
        int n = 1;
        // little endian if true
        if(*(char *)&n == 1) {
            printf("little endian structure detected");
        }else{
            printf("Big ass endian structure detected");
        }
    };


#ifdef __cplusplus
extern "C" {
#endif /* __cplusplus */
// make it available for js

    extern void js_output_result(void *(bitmap), int bitmap_width, int bitmap_height, int size, void* errors);
    extern void *js_get_barcode_type();
    extern char *js_get_barcode_text();
    // extern void *report_errors(void *(err));
    // extern void test_logger();

    // std::cout << convert.to_bytes(s);

    int main(int argc, const char *argv[]) {

    // check_endians();
    // https://archotag.files.wordpress.com/2017/10/zint_manual_242.pdf

    struct zint_symbol *my_symbol;
    int js_bc_type =reinterpret_cast<int>(js_get_barcode_type());//this is ok

    my_symbol = ZBarcode_Create();
    // my_symbol->symbology = BARCODE_QRCODE;
    my_symbol->symbology =js_bc_type;
    string js_bc_text =js_get_barcode_text();
    string encode_data(js_bc_text);
    my_symbol->scale = 2;
    my_symbol->input_mode = UNICODE_MODE;
    // my_symbol->option_3 += DM_DMRE+BARCODE_BIND+BARCODE_BOX+READER_INIT+GS1_GS_SEPARATOR;
    // my_symbol->option_1 = READER_INIT;
    // my_symbol->option_1 = 1;
    // my_symbol->option_2 = 2;
    // my_symbol->option_3 =DM_SQUARE;
    my_symbol->whitespace_width = 5;    
    // my_symbol->border_width = 20;
    // strcpy(my_symbol->bgcolor, "00FFFFFF");

    strcpy(my_symbol->outfile, "BarcodeTest.bmp");    
    int error_num = ZBarcode_Encode_and_Buffer(my_symbol, (unsigned char*)encode_data.c_str(), 0, 0);
    char err_str = *my_symbol->errtxt;

    if(error_num != 0){
        printf("%s\n", my_symbol->errtxt);
        // report_errors(my_symbol->errtxt);
    }

    // unsigned char *a;
    // memcpy(&a, (unsigned char *)my_symbol->bitmap[56], 8);

    js_output_result(my_symbol->bitmap, my_symbol->bitmap_width,
                    my_symbol->bitmap_height,((size_t*)my_symbol->bitmap)[-1], my_symbol->errtxt);
    ZBarcode_Delete(my_symbol);
    return 0;

}
#ifdef __cplusplus
}
#endif /* __cplusplus */

