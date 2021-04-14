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
    // make API available for js
    extern void js_output_result(void *(bitmap), int bitmap_width, int bitmap_height, int size, void* errors);
    extern void *js_get_barcode_type();
    extern char *js_get_barcode_text();
    extern void *js_get_barcode_scale();
    // extern void *report_errors(void *(err));

    int main(int argc, const char *argv[]) {

    // check_endians();
    // https://archotag.files.wordpress.com/2017/10/zint_manual_242.pdf

    struct zint_symbol *my_symbol;
    
    // js inputs
    int js_bc_type =reinterpret_cast<int>(js_get_barcode_type());//this is ok
    string js_bc_text =js_get_barcode_text();
    int js_scale_value = reinterpret_cast<int>(js_get_barcode_scale());
    
    my_symbol = ZBarcode_Create();
    my_symbol->symbology =js_bc_type;
    string encode_data(js_bc_text);
    my_symbol->scale = js_scale_value;
    my_symbol->input_mode = UNICODE_MODE;
    my_symbol->whitespace_width = 8.0; 
    // my_symbol->option_3 += DM_DMRE+BARCODE_BIND+BARCODE_BOX+READER_INIT+GS1_GS_SEPARATOR;
    // my_symbol->option_1 = READER_INIT;
    // my_symbol->option_1 = 1;
    // my_symbol->option_2 = 2;
    // my_symbol->option_3 =DM_SQUARE;
    // my_symbol->border_width = 20;
    // strcpy(my_symbol->bgcolor, "00FFFFFF");

    if (my_symbol->symbology == BARCODE_QRCODE)
    {
        int even_ratio = js_scale_value%2==0? js_scale_value+2: js_scale_value+2+1;
        my_symbol->scale =even_ratio;
    }
    
    strcpy(my_symbol->outfile, "BarcodeTest.bmp");    
    int error_num = ZBarcode_Encode_and_Buffer(my_symbol, (unsigned char*)encode_data.c_str(), 0, 0);
    if(error_num != 0){
        printf("%s\n", my_symbol->errtxt);
        // report_errors(my_symbol->errtxt);
    }

    int bitmap_size = ((size_t*)my_symbol->bitmap)[-1] +1;
    js_output_result(my_symbol->bitmap, my_symbol->bitmap_width, 
                    my_symbol->bitmap_height, bitmap_size, my_symbol->errtxt);

    ZBarcode_Delete(my_symbol);
    return 0;

}
#ifdef __cplusplus
}
#endif /* __cplusplus */

