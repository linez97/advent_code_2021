#include <stdlib.h>
#include <string.h>
#include <stdio.h>
#include <stdint.h>
#include <assert.h>

#define BIT_PER_LINE 12
#define NEW_LINE_NUMBER_BIN BIT_PER_LINE
#define ARRAY_END 0
#define FILE_SIZE 1000

typedef struct {
    uint16_t* array;
    uint16_t size;
}indexed_array;

uint16_t* get_as_numbers(char* file_name);
void free_array(indexed_array* array);
indexed_array* create_array_cpy(indexed_array src);
uint8_t append_to_i_array(indexed_array*, uint16_t value);
uint16_t prune(indexed_array* src, indexed_array* ones, indexed_array* zeros, uint8_t bit_to_check, uint8_t most_common);

indexed_array* create_array_cpy(indexed_array src);

int main(){
    indexed_array binary_count;
    binary_count.array = get_as_numbers("input.txt");
    binary_count.size = FILE_SIZE;

    indexed_array ones;
    ones.array = malloc(sizeof(uint16_t) * FILE_SIZE);
    ones.size = 0;
    assert(ones.array);

    indexed_array zeroes;
    zeroes.array = malloc(sizeof(uint16_t) * FILE_SIZE);
    zeroes.size = 0;
    assert(ones.array);

    uint16_t bit_index = BIT_PER_LINE - 1;

    uint16_t array_index = FILE_SIZE;

    //Oxigen rate MOST COMMON BIT
    uint16_t OGR = prune(&binary_count, &ones, &zeroes, BIT_PER_LINE-1, 1);
    uint16_t CSR = prune(&binary_count, &ones, &zeroes, BIT_PER_LINE-1, 0);
    uint64_t result = OGR * CSR;
    printf("The result is: %d", result);
}

uint16_t prune(indexed_array* src, indexed_array* ones, indexed_array* zeros, uint8_t bit_to_check, uint8_t most_common){
    
    if(src->size == 1 || bit_to_check == 255){
        return src->array[0];
    }
    
    indexed_array* aux = create_array_cpy(*src);
    ones->size = 0;
    zeros->size = 0;
    for(int i = 0; i < aux->size; i++){
        if(1 & (aux->array[i] >> bit_to_check)){
            ones->array[ones->size] = aux->array[i];
            ones->size++;
        } else {
            zeros->array[zeros->size] = aux->array[i];
            zeros->size++;
        }
    }
    free_array(aux);
    indexed_array* most_cm;
    indexed_array* least_cmn;
    if(zeros->size > ones->size){
        most_cm = zeros;
        least_cmn = ones;
    } else {
        most_cm = ones;
        least_cmn = zeros;
    }

    if(most_common){
        return prune(most_cm, ones, zeros, bit_to_check-1, most_common);
    } else {
        return prune(least_cmn, ones, zeros, bit_to_check-1, most_common);
    }
} 

uint8_t append_to_i_array(indexed_array* array, uint16_t value){
    array->array[array->size] = value;
    array->size++;
    return (array->size <= FILE_SIZE);
}

indexed_array* create_array_cpy(indexed_array src){

    indexed_array* ptr = malloc(sizeof(indexed_array)); 
    assert(ptr);
    ptr -> array = malloc(sizeof(uint16_t) * src.size);
    assert(ptr->array);
    for(int i  = 0; i < src.size; i++){
        ptr->array[i] = src.array[i];
    }
    ptr->size = src.size; 

    return ptr;
}

void free_array(indexed_array* array){
    free(array->array);
    free(array);
}

uint16_t* get_as_numbers(char* file_name){
    // Initialize the array, this array contains the number of ones in each file
    uint16_t* array = malloc(sizeof(uint16_t)  * FILE_SIZE);
    array = memset(array, 0, sizeof(uint16_t)  * FILE_SIZE);

    uint32_t counter = 0;
    // Open the input file
    FILE *f_ptr = fopen(file_name, "r");

    char aux_char;

    //Read the file char by char
    while ((aux_char = fgetc(f_ptr)) != EOF){
        if (aux_char != '\n' && aux_char != '\r'){
            array[counter] = (aux_char - 48) | (array[counter] << 1);
        } else {
            if(aux_char == '\n'){
                counter++;
            }
        }
    }

    return array;
}