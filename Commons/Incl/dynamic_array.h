#ifndef STATIC_ARRAY_H
#define STATIC_ARRAY_H

#include <stdlib.h>
#include <stdint.h>

#define DYN_ARRAY_DEF 0

typedef struct {
    void **items;
    uint64_t size;
    uint64_t capacity;
}dynamic_array;

dynamic_array* init_array(uint32_t size);
dynamic_array* extend_array(uint32_t extension_size);
uint8_t dyn_array_append(dynamic_array* array, void* value);
uint8_t free_array(dynamic_array* array);

#endif