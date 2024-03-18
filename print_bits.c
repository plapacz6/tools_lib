#include <stdio.h>
#include <stdlib.h>
#include <stdint.h>
#include <assert.h>
#include "print_bits.h"

// typedef enum Endian_TT {LE = 0, BE = 1} Endian_T;

void print_bits(char* buff, size_t buff_size,  void* p_data, size_t bytes, Endian_T endian) {
    // printf("\n----------------\nbytes: %zu\n", bytes);
    enum {max_bytes = 8};
    if(bytes > max_bytes) 
        return;
    size_t be[max_bytes];
    switch (endian)
    {
    case LE:        
        for(size_t i = 0; i < bytes; ++i){
            be[i] = ((bytes - 1) - i);
            // printf("%zu", be[i]);
        }
        // printf("%s\n", "");
        break;
    case BE:
        for(size_t i = 0; i < bytes; ++i){
            be[i] = (i);
            // printf("%zu", be[i]);
        }    
        // printf("%s\n", "");
        break;
    default:
        return;        
    }
    uint8_t *p = (uint8_t*)p_data;
    char *pbuff = buff;
    size_t mbuff_size = buff_size;
    for(size_t b = 0; b < bytes; ++b){        
        // printf("\nbe[%zu]:%zu:", b, be[b]);                
        for(size_t i = 8; i > 0; --i){
            snprintf(pbuff, mbuff_size, "%c", ((((*(p + be[b])) >> (i - 1)) & 1)) ? '1' : '0');
            mbuff_size--;
            pbuff++;
        }
        if(b >= bytes - 1) {
            break;
        }
        snprintf(pbuff, mbuff_size,"%c", ' ');                
        mbuff_size--;
        pbuff++;
    }
    // printf("%s\n", "");
}
