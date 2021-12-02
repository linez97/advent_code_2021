
//First challenge of the advent code 2021

#include <stdlib.h>
#include <stdio.h>
#include <stdint.h>

int main(){
    // Import the file
    char* const file_name = "input.txt";

    uint32_t last_val = 0xFFFFFFFF;
    uint32_t new_val = 0;

    uint16_t counter = 0;

    FILE *f_ptr = fopen(file_name, "r");
    char line[15];

    // Read the file line by line
    while (fgets(line, sizeof(line), f_ptr))
    {
        new_val = atoi(line);
        if (new_val > last_val) counter++;
        last_val = new_val;
    }
    
    printf("Descended %d times", counter);

}