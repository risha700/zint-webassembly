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

template<typename T>
static std::string toBinaryString(const T& x)
{
    std::stringstream ss;
    ss << std::bitset<sizeof(T) * 8>(x);
    return ss.str();
}

#ifdef __cplusplus
extern "C" {
#endif /* __cplusplus */
// make it available for js

    extern void js_output_result(void* bitmap, int bitmap_width, int bitmap_height, int size);
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

    int bloblen = my_symbol->bitmap_height*my_symbol->bitmap_width;
    int r, g, b;
    int i = 0;
    unsigned int output_data[bloblen];

    for (int row = 0; row < my_symbol->bitmap_height; ++row)
    {
        for (int col = 0; col < my_symbol->bitmap_width; ++col)
        {
            r = my_symbol->bitmap[i];
            g = my_symbol->bitmap[i + 1];
            b = my_symbol->bitmap[i + 2];
            output_data[i] = static_cast<char>(r);
            output_data[i+1] = static_cast<char>(g);
            output_data[i+2] = static_cast<char>(b);
            // output_data[i+3] = static_cast<char>(255); //a

            i += 3;
            // if (r == 0 && g == 0 & b == 0)
            // {
            //     printf("■");
            
            // }
            // else
            // {
            //     printf("□");
            // }

        }

        // printf("\n");
    }
    cout<<reinterpret_cast<unsigned char *>(*my_symbol->bitmap)<<endl;
    js_output_result(reinterpret_cast<unsigned char *>(*my_symbol->bitmap), my_symbol->bitmap_width,
     my_symbol->bitmap_height, sizeof(my_symbol->bitmap_byte_length));
    
    
    ZBarcode_Delete(my_symbol);
    return 0;

}
#ifdef __cplusplus
}
#endif /* __cplusplus */

