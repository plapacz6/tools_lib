#ifndef PRINT_BITS_H
#define PRINT_BITS_H
#ifdef __cplusplus
extern "C"
{
#endif

#include <stdlib.h>
#include <stdint.h>

typedef enum Endian_TT {LE = 0, BE = 1} Endian_T;
/**
 * @brief print out binary representation of p_data
 * 
 * @param buff buffoer to store string of 0/1 represetnation of p_data
 * @param buff_size buffer size
 * @param p_data pointer to data to interpret and print as string of 0 and 1
 * @param bytes size of p_data in bytes (max size if hardcoded in function body)
 * @param endian if most significant bytes are on the beginning or on the end
 * @return if bytes are greater than max_bytes, or endian is wrong value, function ends with doing noting
 */
void print_bits(char* buff, size_t buff_size, void* p_data, size_t bytes, Endian_T endian);

#ifdef __cplusplus
}
#endif
#endif // PRINT_BITS_H