#include <stdlib.h> 
#include <stdio.h>
// #include <string.h>
#include <iostream>
#include "zint.h"
#include <streambuf>
#include<sstream>
using namespace std;



#ifdef __cplusplus
extern "C" {
#endif /* __cplusplus */
// make it available for js

    int main(int argc, const char *argv[]) {

    
    struct zint_symbol *my_symbol;

    // free(dataPtr);
    my_symbol = ZBarcode_Create();

    my_symbol->symbology = BARCODE_QRCODE;

    strcpy(my_symbol->outfile, "BufferingSymbolsInMemory.svg");
    
 

    string encode_data("BufferingSymbolsInMemory");

    int error_num = ZBarcode_Encode_and_Buffer(my_symbol, (unsigned char*)encode_data.c_str(), 0, 0);
    // cout<<reinterpret_cast<unsigned char*>(my_symbol->vector)<<endl;
    // cout<<static_cast<string**>(&my_symbol)<<endl;
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