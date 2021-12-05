#include <stdio.h>
#include <stdlib.h>
#include <stdint.h>
#include <string.h>
#include <assert.h>

#define UP 0
#define DOWN 1
#define FORWARD 2

#define DEPTH 0
#define DISTANCE 1

int directions[2] = {0, 0};

void get_directions(char* file_name);
uint8_t get_number_value(char* line);

int main(){
    get_directions("input.txt");
    uint64_t depth = directions[DEPTH];
    uint64_t distance = directions[DISTANCE];
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
    int64_t aim = 0;
    uint64_t distance;
    // Read the file line by line
    while (fgets(line, sizeof(line), f_ptr))
    {
        // Selecft the array index
        switch (line[0])
        {
        case 'u':
            aim -= get_number_value(line); 
            break;
        case 'f': 
            distance = get_number_value(line);
            directions[DEPTH] += distance * aim;
            directions[DISTANCE] += distance;
            break;
        case 'd':
            aim += get_number_value(line);
            break;
        default:
            assert(0 && "Letter not found");
        }
    }
    fclose(f_ptr);
}

uint8_t get_number_value(char* line){
    char* tok = strtok(line, " ");
    tok = strtok(NULL, " ");
    return atoi(tok);
}