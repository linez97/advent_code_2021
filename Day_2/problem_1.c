#include <stdio.h>
#include <stdlib.h>
#include <stdint.h>
#include <string.h>
#include <assert.h>

#define UP 0
#define DOWN 1
#define FORWARD 2

int directions[3] = {0, 0, 0};

void get_directions(char* file_name);

int main(){
    get_directions("input.txt");
    uint64_t depth = directions[DOWN] - directions[UP];
    uint64_t distance = directions[FORWARD];
    uint64_t answer = (depth * distance);
    printf("The answer is %llu x %llu: %llu", depth, distance, answer);

    return 0;
}

void get_directions(char* file_name){
    FILE *f_ptr = fopen(file_name, "r");
    if (f_ptr == NULL){
        assert(0 && "File Not Found");
    }
    char line[15];

    uint8_t index = 0; 

    // Read the file line by line
    while (fgets(line, sizeof(line), f_ptr))
    {
        // Selecft the array index
        switch (line[0])
        {
        case 'u':
            index = UP;
            break;
        case 'f': 
            index = FORWARD;
            break;
        case 'd':
            index = DOWN;
            break;
        default:
            assert(0 && "Letter not found");
        }

        char* tok = strtok(line, " ");
        tok = strtok(NULL, " ");
        directions[index] += atoi(tok);
    }
    fclose(f_ptr);
}
