#ifndef VAR_STR
#define VAR_STR

#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <stdint.h>


typedef struct variant_string
{
    char* data;
    uint16_t size;

    char* start_pointer;
    char* end_pointer;
};

char* init_vs(char* s);
uint8_t destroy_vs(variant_string* s);

int* get_numbers(variant_string* s);


#endif