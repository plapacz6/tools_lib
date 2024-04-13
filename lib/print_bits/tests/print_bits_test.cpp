#include <gtest/gtest.h>
#include <stdio.h>
#include <stdlib.h>
#include <stdint.h>
#include <assert.h>

#include "../print_bits.h"


TEST(print_bits_lib, test_00) {        
    uint32_t val1 = 0xC0300C03;
    enum {buff_size = 256};
    char buff[buff_size];
    memset(buff, 0, buff_size);
    print_bits(buff, buff_size, &val1, sizeof(val1), LE);
    ASSERT_STREQ(buff, "11000000 00110000 00001100 00000011");
    print_bits(buff, buff_size, &val1, sizeof(val1), BE);
    ASSERT_STREQ(buff, "00000011 00001100 00110000 11000000");    
}