#include <stdlib.h>
#include <string.h>
#include <stdio.h>
#include <stdint.h>

#define BIT_PER_LINE 12
#define NEW_LINE_NUMBER_BIN BIT_PER_LINE
#define FILE_SIZE 1000


uint16_t* bynary_count;

uint16_t* get_as_numbers(char* file_name);
uint16_t* prune(uint16_t* array, size_t size, uint8_t mode); 


int main(){
    bynary_count = get_as_numbers("input_2.txt");

    uint64_t result = 0;
    printf("The result is: %d", result);
}

uint16_t* prune(uint16_t* array, size_t size, uint8_t mode){
    // If the size is 1 return the value (end case)
    if(size = 1) {
        return array[0];
    }

    for(int i = 0; i < FILE_SIZE;){}
} 



uint16_t* get_as_numbers(char* file_name){
    // Initialize the array, this array contains the number of ones in each file
    uint16_t* array = malloc(sizeof(uint16_t)  * FILE_SIZE);
    array = memset(array, 0, sizeof(uint16_t)  * FILE_SIZE);

    uint8_t bit_size[12];
    // Counter to fill the bins of array
    uint8_t counter = 0;
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