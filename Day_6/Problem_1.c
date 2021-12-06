#include <stdio.h>
#include <stdlib.h>
#include <stdint.h>

typedef int lantern_fish;

lantern_fish* get_school_data;

//This problem requires the implementationm of a list
typedef struct{
    uint32_t value;
    struct lst_node* next_node;
} lst_node;

typedef struct{
    lst_node* head;
    uint64_t size;
} list;

list* initialize_lst();
lst_node* create_node(uint32_t value);
uint8_t append_node(list* lst, uint32_t value);
list* join_list(list* lst_1, list* lst_2);
void print_list(list lst, uint8_t one_line);
uint8_t free_node(lst_node* node);
uint8_t destroy_list(list* lst);



void init_school(char* file_name, list* lst); 

void advance_day(list* lst);

int main(){ 
    list* l = initialize_lst();
    //Load the initial status
    init_school("input.txt", l);

    for(int i = 0; i < 80; i++){
        printf("Iterating day: %d\n", i);
        advance_day(l);
        //print_list(*l, 1);
    }

    printf("Size of the school: %llu", l->size);

    return 0;

}

void advance_day(list* lst){
    list* aux = initialize_lst();

    lst_node* n = lst->head;

    while (n != NULL)
    {
        if(n->value == 0){
            n->value = 6;
            append_node(aux, 8);
        } else {
            n->value--;
        }

        n = n->next_node;
    }
    
    join_list(lst, aux);

}

void init_school(char* file_name, list* lst){
    FILE * f_ptr = fopen(file_name, "r");
    char aux;
    while((aux = fgetc(f_ptr)) != EOF){
        if (aux >= '0' && aux <= '9')
        {
            if(!append_node(lst, (aux-48))){
                printf("Error appending the node, quitting...");
                break;
            }
        }
        
    }   
    fclose(f_ptr);
}

/*LIST SUFF*/
#pragma region 

list* initialize_lst(){
    list* lst = malloc(sizeof(list));
    lst->head = NULL;
    lst->size = 0;

    return lst;
}

lst_node* create_node(uint32_t value){
    lst_node* node = malloc(sizeof(lst_node));
    if (node == NULL) return NULL;
    node->next_node = NULL;
    node->value = value;
    return node;
}

uint8_t append_node(list* lst, uint32_t value){
    lst_node* node = create_node(value);
    if(node == NULL) return 0;

    if(lst->head == NULL) {
        lst->head = node;
    } else {
        lst_node* p = lst->head;
        while(p->next_node != NULL){
            p = p->next_node;
        }
        p->next_node = node;
    }
    lst->size++;
    return 1;
}

uint8_t destroy_list(list* lst){
    lst_node* p = lst->head;
    lst_node* n = p;
    if(lst->head != NULL) {
        while(p != NULL){
            n = p;
            p = p->next_node;
            free(n);
        }
        free(p);
    }
    free(lst);    
}

void print_list(list lst, uint8_t one_line){
    lst_node* n = lst.head;
    while (n != NULL)
    {
        if (one_line){
            printf("%d,", n->value);
        }else{
            printf ("Memorized Value = %d, Next Element: %p\n", n->value, n->next_node);
        }   
        n = n -> next_node;
    }

    printf("List containing %llu elements\n", lst.size);
    
}

list* join_list(list* lst_1, list* lst_2){
    lst_node* aux = lst_1->head;

    while (aux->next_node != NULL)
    {
        aux = aux->next_node;
    }

    aux->next_node = lst_2->head;
    lst_1->size += lst_2->size;

    free(lst_2);
}
#pragma endregion