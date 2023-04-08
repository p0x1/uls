#include "../inc/libmx.h"

void mx_pop_front(t_list **list){
    if (list == NULL || *list == NULL)
        return;
    t_list *temp_node = *list;
    *list = temp_node->next;
    free(temp_node);
    temp_node = NULL;
}
