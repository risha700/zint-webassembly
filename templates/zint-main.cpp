#include <stdlib.h> 
#include <stdio.h>
#include <string.h>
#include <iostream>
#include "../zint-2.9.1-src/backend/zint.h"
#include <streambuf>
#include<sstream>
using namespace std;



#ifdef __cplusplus
extern "C" {
#endif /* __cplusplus */
// make it available for js

    extern void js_output_result(void *symbolName, uint8_t data);
    extern int js_get_barcode_type();
    extern char* js_get_barcode_text();
    extern void test_logger();


    int main(int argc, const char *argv[]) {
    test_logger();
    
    struct zint_symbol *my_symbol;


    // int  inputType=js_get_barcode_type();
    // char *inputText=js_get_barcode_text();

    // cout<<"inputText: "<<inputText[7]<<"\n";    
    
    
    // cout<<reinterpret_cast<unsigned char*>(my_symbol->vector)<<endl;

    // free(dataPtr);
    my_symbol = ZBarcode_Create();

    my_symbol->symbology = BARCODE_QRCODE;

    strcpy(my_symbol->outfile, "BarcodeTest.svg");
    
 

    string encode_data("BufferingSymbolsInMemory");

    int error_num = ZBarcode_Encode_and_Print(my_symbol, (unsigned char*)encode_data.c_str(), 0, 0);
    if(error_num != 0)
        {
        /* some error occurred */
        printf("%s\n", my_symbol->errtxt);
        }else{
            printf("%s\n",my_symbol->outfile);
        }
    // cout<<"bitmap content: "<<reinterpret_cast<inline char *>(my_symbol->vector)<<endl;
    // streambuf *s;
    
    // cout<<reinterpret_cast<streambuf *>(&my_symbol->vector)<<"\n";      
    // int r, g, b;
    // int i = 0;

    // char BMP_ARR[my_symbol->bitmap_height*my_symbol->bitmap_width];

    // for (int row = 0; row < my_symbol->bitmap_height; ++row)
    // {
    //     for (int col = 0; col < my_symbol->bitmap_width; ++col)
    //     {
    //         r = my_symbol->bitmap[i];
    //         g = my_symbol->bitmap[i + 1];
    //         b = my_symbol->bitmap[i + 2];
    //         i += 3;
    //         if (r == 0 && g == 0 & b == 0)
    //         {
    //             printf("■");

    //         }
    //         else
    //         {
    //             printf("□");
    //         }
    //     }

    //     printf("\n");
    // }

    // js_output_result(reinterpret_cast<streambuf *>(my_symbol->bitmap), 
    //                   int (my_symbol->bitmap_width* my_symbol->bitmap_height));
    
    
    ZBarcode_Delete(my_symbol);
    return 0;

}
#ifdef __cplusplus
}
#endif /* __cplusplus */