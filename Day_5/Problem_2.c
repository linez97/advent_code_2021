#include <stdint.h>
#include <inttypes.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <math.h>

#define X0 0
#define Y0 1
#define X1 2
#define Y1 3

#define VENTS_NUMBER 500


typedef struct 
{
    int points[4];
    uint8_t is_orthogonal;
}Vent;

typedef struct 
{
    Vent** vents;
    uint16_t** field;
    uint32_t width;
    uint32_t height;

}Vent_Field;



Vent_Field* load_field_from_file(char* file_name);
Vent* create_vent_from_string(char* str);
uint64_t check_high_values(Vent_Field *fld, uint32_t value);
void apply_vents(Vent_Field* field, uint8_t include_diagonal);
void print_field(Vent_Field field);
void print_vent(Vent vent);

int main(){
    /*char str[20] = "299,462 -> 299,747\r\n";
    Vent* new_vent = (create_vent_from_string(str));
    print_vent(*new_vent);*/
    Vent_Field* field = load_field_from_file("input.txt");
    apply_vents(field, 1);
    //print_field(*field);
    printf("Dangerous zones: %" PRIu64 "\n", check_high_values(field, 2));
}


Vent_Field* load_field_from_file(char* file_name){
    Vent_Field* field = malloc(sizeof(Vent_Field));
    field->vents = malloc(sizeof(Vent*) * VENTS_NUMBER);

    FILE* f_ptr = fopen(file_name, "r");
    // Load Vents data
    uint32_t vent_counter = 0;
    char line[100];
    while (fgets(line, 100, f_ptr)){
        field->vents[vent_counter] = create_vent_from_string(line);
        vent_counter++;
    }
    fclose(f_ptr);
    //Search max height and width to initialize the field
    field->width = 0;
    field->height = 0;

    for(int i = 0; i < VENTS_NUMBER; i++){
        //Max Width looks for the X coords
        if (field->vents[i]->points[X0] > field->width) field->width = field->vents[i]->points[X0];
        if (field->vents[i]->points[X1] > field->width) field->width = field->vents[i]->points[X1];

        //Max Height looks for the X coords
        if (field->vents[i]->points[Y0] > field->height) field->height = field->vents[i]->points[Y0];
        if (field->vents[i]->points[X1] > field->height) field->height = field->vents[i]->points[Y1]; 
    }

    field->height++;
    field->width++;

    field->field = malloc(sizeof(uint16_t*) * field->height);
    //Initialize the array
    for(int i = 0; i < field->height; i++){
        field->field[i] = malloc(sizeof(uint16_t) * field->width);
        field->field[i] = memset(field->field[i], 0, sizeof(uint16_t) * field->width);
    }

    return field;

}

void apply_vents(Vent_Field* field, uint8_t include_diagonal){
    for(int i = 0; i < VENTS_NUMBER; i++){
        
        // Assign the lesser and major coordinate
        uint32_t major_x = field->vents[i]->points[X0] > field->vents[i]->points[X1] ? field->vents[i]->points[X0] : field->vents[i]->points[X1];
        uint32_t minor_x = field->vents[i]->points[X0] <= field->vents[i]->points[X1] ? field->vents[i]->points[X0] : field->vents[i]->points[X1];

        uint32_t major_y = field->vents[i]->points[Y0] > field->vents[i]->points[Y1] ? field->vents[i]->points[Y0] : field->vents[i]->points[Y1];
        uint32_t minor_y = field->vents[i]->points[Y0] <= field->vents[i]->points[Y1] ? field->vents[i]->points[Y0] : field->vents[i]->points[Y1];
        if(field->vents[i]->is_orthogonal){
            //Apply their effect on the field
            for (int j = minor_x; j <= major_x; j++) {
                for (int k = minor_y; k <= major_y; k++) {
                    field->field[j][k] += 1;
                }
            }
        } else if (include_diagonal){
            
            // X nd Y axis direction
            int is_x_positive = field->vents[i]->points[X0] > field->vents[i]->points[X1] ? -1 : 1;
            int is_y_positive = field->vents[i]->points[Y0] > field->vents[i]->points[Y1] ? -1 : 1;

            print_vent(*(field->vents[i]));
            int delta_x = major_x - minor_x;
            
            for(int k = 0; k <= delta_x; k++){
                uint16_t x_axis = field->vents[i]->points[X0] + (k * is_x_positive);
                uint16_t y_axis = field->vents[i]->points[Y0] + (k * is_y_positive);

                field->field[x_axis][y_axis] += 1;
            }
        }
    }
}

uint64_t check_high_values(Vent_Field* fld, uint32_t value){
   uint64_t count = 0;
   
   for (size_t i = 0; i < fld->height; i++)
   {
       for (size_t j = 0; j < fld->width; j++)
       {
           if(fld->field[i][j] >= value){
               count++;
           }
       }
       
   }

   return count;
}

Vent* create_vent_from_string(char* str){
    
    Vent* new_vent = malloc(sizeof(Vent));

    char* start_str;
    char* end_str;

    char* aux;

    start_str = str;
    start_str = strtok(str, " ");
    // Ignore the "->"
    strtok(NULL, " ");
    end_str = strtok(NULL, " ");

    aux = strtok(start_str, ",");
    new_vent->points[X0] = atoi(aux);
    new_vent->points[Y0] = atoi(strtok(NULL, ","));

    new_vent->points[X1] = atoi(strtok(end_str, ","));
    new_vent->points[Y1] = atoi(strtok(NULL, ","));

    new_vent->is_orthogonal = (new_vent->points[X0] == new_vent->points[X1]) |
                                (new_vent->points[Y0] == new_vent->points[Y1]);

    return new_vent;
}


void print_field(Vent_Field field){
    for (size_t i = 0; i < field.height; i++)
    {
        for (size_t j = 0; j < field.width; j++)
        {
            printf("%d", field.field[j][i]);
        }
        printf("\n");
    }
    
}

void print_vent(Vent vent){
    printf("%d,%d -> %d,%d orth:%d\r\n", vent.points[X0], vent.points[Y0], vent.points[X1], vent.points[Y1], vent.is_orthogonal);
}