#include <stdio.h>
#include <stdlib.h>
#include <stdint.h>

#include "dynamic_array.h"

int main () {
    int array[2000];
    int counter = 0;
    FILE *f_ptr = fopen("input.txt", "r");
    char aux;
    char aux_str[10];
    char str_counter = 0;
    while((aux = fgetc(f_ptr)) != EOF){
        if (aux >= '0' && aux <= '9')
        {
            aux_str[str_counter] = aux;
            str_counter++; 
        } else if(aux == ',') {
            aux_str[str_counter] = 0;
            array[counter] = atoi(aux_str);
            counter++;
            str_counter = 0;
        }
    }   
    fclose(f_ptr);
}