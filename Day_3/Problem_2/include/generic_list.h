#ifndef GENERIC_LIST
#define GENERIC_LIST

#include <stdint.h>

typedef struct generic_list_node
{
    generic_list_node *next;
    void* data_p;
};

typedef generic_list_node* generic_list_node_p; 

typedef struct generic_list{
    generic_list_node* head;
    uint32_t size;
};

generic_list* create_list(generic_list_node_p *head);
generic_list* append_element(generic_list *list, void* data);


#endif 