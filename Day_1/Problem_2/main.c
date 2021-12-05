
//First challenge of the advent code 2021

#include <stdlib.h>
#include <stdio.h>
#include <stdint.h>

#define AVG_ELEMENTS 3
#define INPUT_FILE_LINE_CNT 2000


int* get_int_array(char *file_name);

int main(){
    // Import the file
    

    double last_val = 0xFFFFFFFF;
    uint32_t new_val = 0;

    uint16_t counter = 0;

    char* const file_name = "input.txt";


    // This variable keeps track of the element used to do the mean
    uint8_t mean_counter[AVG_ELEMENTS] = {0, 0, 0};

    // This is the variable that is used to accumulate the sums
    double accumulator[AVG_ELEMENTS] = {0, 0, 0};
    printf("start array creation\r\n");
    int* val_array = get_int_array(file_name);
    printf("array creation has ended\r\n");
    
    last_val = val_array[0] + val_array[1] + val_array[2];

    for (int i = 3; i < INPUT_FILE_LINE_CNT; i++){
        new_val = val_array[i] + val_array[i-1] + val_array[i-2]; 
        if (new_val > last_val) counter++;
        last_val = new_val;
    }

    printf("Descended %d times", counter);
    free(val_array);

}

int* get_int_array(char *file_name){
    int* array = malloc(INPUT_FILE_LINE_CNT * sizeof(uint32_t));

    char line[15];

    FILE *f_ptr = fopen(file_name, "r");

    for(int i = 0; i < INPUT_FILE_LINE_CNT; i++) {
        fgets(line, sizeof(line), f_ptr);
        array[i] = atoi(line);
    }

    fclose(f_ptr);
    return array;
}