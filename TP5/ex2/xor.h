#ifndef _XOR_H
#define _XOR_H

#include <stdio.h>
#include <stdint.h>

void print_bits_of_char(const char c);
void print_dec_from_char(const char c);
void print_bits_of_int(const unsigned int my_int);
void encode(uint8_t key, FILE*in, FILE*out);
void optimized_encode(uint8_t key, FILE*in, FILE*out);
#endif