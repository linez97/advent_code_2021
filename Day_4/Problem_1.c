#include <stdint.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define MAX_EXTRACTIONS 100
#define TABLE_NUMBERS 100
#define TABLE_ROWS 5
#define TABLE_COLS 5

typedef struct{ 
    uint8_t** values; 
    uint8_t** extracted;
    uint8_t has_won;
}bingo_table;

//Constructors
int* get_extracted_numbers(char* file_name);
void print_tbl_value(bingo_table tbl);
bingo_table** get_tables(char* file_name);
bingo_table* get_table_from_string(char* string);

//Check Winners
uint8_t extract_number(uint8_t number, bingo_table** tables);
uint8_t check_number(uint8_t number, bingo_table* table);
uint8_t check_winners(bingo_table** tables); 
uint64_t calculate_points(bingo_table* table, uint8_t number);

int main() {
    //bingo_table* btbl = get_table_from_string(str);
    int* extracted = get_extracted_numbers("extracted_numbers.txt");
    bingo_table** tables = get_tables("bingo_tables.txt");

    for(int i = 0; i < MAX_EXTRACTIONS; i++){
        if(extract_number(extracted[i], tables)) break;
    }

}

uint8_t extract_number(uint8_t number, bingo_table** tables){
    uint8_t number_cnt = 0;
    uint8_t value = 0;
    for(uint8_t i = 0; i < TABLE_NUMBERS; i++){
        number_cnt += check_number(number, tables[i]);
    }
    printf("Extracted number: %d, found: %d times\r\n", number, number_cnt);
    if (check_winners(tables)) {  
        for (int i = 0; i < TABLE_NUMBERS; i++){
            if(tables[i]->has_won){
                print_tbl_value(*(tables[i]));
                printf("Points of table %d: %llu\r\n", i, calculate_points(tables[i], number));
                printf("\r\n");
                value = 1;
            }
        }
    }
    return value;
}

uint64_t calculate_points(bingo_table* table, uint8_t number){

    uint32_t selected_sum = 0;
    uint32_t unselected_sum = 0;

    for (size_t i = 0; i < TABLE_ROWS; i++)
    {
        for (size_t j = 0; j < TABLE_COLS; j++)
        {
            unselected_sum += (0 == table->extracted[i][j]) * table->values[i][j]; 
        }
        
    }
    
    return unselected_sum * number;
}

uint8_t check_number(uint8_t number, bingo_table* table){
    uint8_t returned_value = 0;
    for(int i = 0; i < TABLE_ROWS; i++){
        for(int j = 0; j < TABLE_COLS; j++){
            if(table->values[i][j] == number){
                table->extracted[i][j] = 1;
                returned_value++;
            }
        }
    }

    return returned_value;
}


uint8_t check_winners(bingo_table** tables){
    
    uint8_t return_value = 0;
    for(int i = 0; i < TABLE_NUMBERS; i++){
        // Iterate the rows
        uint8_t col_sums[TABLE_ROWS] = {0,0,0,0,0};
        uint8_t row_sum = 0;

        for(int j = 0; j < TABLE_ROWS; j++){
            //Iterate the columns
            row_sum = 0;
            for (int k = 0; k < TABLE_COLS; k++) {
                // Intercept the row win condition
                row_sum += tables[i]->extracted[j][k];
                // Intercept the column win condition
                col_sums[k] +=  tables[i]->extracted[j][k];
                if (row_sum == 5){
                    tables[i]->has_won = 1;
                    return_value++;
                    break;
                }
                if (col_sums[k] == 5){
                    tables[i]-> has_won = 1;
                    return_value++;
                    break;
                }
            }
        }
    }

    return return_value;

}

bingo_table** get_tables(char* file_name){
    //Line Buffer
    char line[100];
    char* aux = malloc(sizeof(char) * 100);
    bingo_table** tables = malloc(sizeof(bingo_table*) * TABLE_NUMBERS);

    uint8_t tables_counter = 0;

    FILE *f_ptr = fopen(file_name, "r");
    aux = memset(aux, 0, 100);
    while (fgets(line, 100, f_ptr)){
        if (!strcmp(line, "\n")){
            tables[tables_counter] = get_table_from_string(aux);
            tables_counter++;
            aux = memset(aux, 0, 100);
        }else{
            aux = strcat(aux, line);
        }
    }
    free(aux);
    fclose(f_ptr);

    return tables;
}

bingo_table* get_table_from_string(char* string){

    /*The string is composed by five rows and five columns separated by spaces*/
    bingo_table* tbl = malloc(sizeof(bingo_table));
    
    //Allocate the Rows
    tbl->values = malloc(sizeof(uint8_t*) * TABLE_ROWS);
    tbl->extracted = malloc(sizeof(uint8_t*) * TABLE_ROWS);
    
    // Allocate the cols
    for (int i = 0; i < TABLE_ROWS; i++){
        tbl->values[i] = malloc(sizeof(uint8_t) * TABLE_COLS);
        tbl->extracted[i] = malloc(sizeof(uint8_t) * TABLE_COLS);
        tbl->extracted[i] = memset(tbl->extracted[i], 0, sizeof(uint8_t) * TABLE_COLS); 
    }

    tbl->has_won = 0;

    uint8_t** dbg = tbl->values;

    char str_num[3] = {0, 0, 0};
    uint8_t char_index = 0;

    uint8_t col_index = 0;
    uint8_t row_index = 0;

    char* str_p = string;
    while(*str_p != NULL){
        if(*str_p >= '0' && *str_p <= '9'){
            str_num[char_index] = *str_p;
            char_index++;
        }

        if(*str_p == ' ' && str_num[0] != 0){
                tbl->values[row_index][col_index] = atoi(str_num);
                
                str_num[0] = 0;
                str_num[1] = 0;
                char_index = 0;
                
                col_index++;
        }

        if(*str_p == '\n'){
            tbl->values[row_index][col_index] = atoi(str_num);
            str_num[0] = 0;
            str_num[1] = 0;
            char_index = 0;
                
            col_index = 0;
            row_index++;
        }
        //Shift the pointer
        str_p += sizeof(char);
    } 

    //populate the array
    
    return tbl;

}

void print_tbl_value(bingo_table tbl){
    for(int i = 0; i < TABLE_ROWS; i++){
        for(int j = 0; j < TABLE_COLS; j++) {
            if(tbl.extracted[i][j] == 1){
                printf("|~%d", tbl.values[i][j]);
            } else {
                printf("| %d", tbl.values[i][j]);
            }
        }
        printf("\n");
    }
}

int* get_extracted_numbers(char* file_name) {
    
    int* array = malloc(sizeof(int)* MAX_EXTRACTIONS);

    FILE* f_ptr = fopen(file_name, "r");
    char num_str[3] = { 0, 0, 0 };
    char aux_char;

    uint8_t position_counter = 0;
    uint32_t index_counter = 0;

    while ((aux_char = fgetc(f_ptr)) != EOF){
        if(aux_char >= '0' && aux_char <= '9'){
            num_str[position_counter] = aux_char;
            position_counter++;
        } else if (aux_char == ',') {
            array[index_counter] = atoi(num_str);
            num_str[0] = 0;
            num_str[1] = 0;
            position_counter = 0;
            index_counter++;
        }
    }
    // Get the last conversion
    array[index_counter] = atoi(num_str);

    fclose(f_ptr);
    return array;
}

