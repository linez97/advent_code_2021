#include <stdlib.h>
#include <string.h>
#include <stdio.h>
#include <stdint.h>

#define BIT_PER_LINE 12
#define NEW_LINE_NUMBER_BIN BIT_PER_LINE


uint16_t* bynary_count;

uint16_t* get_ones_in_columns(char* file_name);
uint16_t g_rate = 0;
uint16_t e_rate = 0;


int main(){
    bynary_count = get_ones_in_columns("input.txt");
    for (int i = 0; i < BIT_PER_LINE; i++){
        //Clarity badness

        g_rate = (g_rate << 1) | (bynary_count[i] > (bynary_count[NEW_LINE_NUMBER_BIN]/2));
    }
    e_rate = ~g_rate;

    //Delete the first 4 bits 
    e_rate &= (0b0000111111111111);
    //e_rate &= (0b0000000000011111);

    uint64_t result = e_rate * g_rate;
    printf("The result is: %d", result);
}

uint16_t* get_ones_in_columns(char* file_name){
    // Initialize the array, this array contains the number of ones in each file
    uint16_t* array = malloc(sizeof(uint16_t) * (BIT_PER_LINE + 1));
    array = memset(array, 0, sizeof(uint16_t) * (BIT_PER_LINE + 1));

    // Counter to fill the bins of array
    uint8_t counter = 0;
    uint16_t new_line_counter = 0;
    // Open the input file
    FILE *f_ptr = fopen(file_name, "r");

    char aux_char;

    //Read the file char by char
    while ((aux_char = fgetc(f_ptr)) != EOF){
        if (aux_char != '\n' && aux_char != '\r'){
            array[counter] += (aux_char - 48);
            counter++;
        } else {
            if(aux_char == '\n'){
                new_line_counter++;
            }
            counter = 0;
        }
    }

    array[NEW_LINE_NUMBER_BIN] = new_line_counter;

    return array;
}