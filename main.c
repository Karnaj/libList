#include <stdio.h>
#include <stdlib.h>
#include "list.h"

void print_integer_list(s_list *list)
{
    if(list)
    {
        for(size_t i = 0; i < list->size; i++)
        {
            int *value = list_get(list, i);
            printf("list[i] = %d.\n", *value);
        }
    }
}

int main(void)
{
    int a = 3, b = 6;
    s_list *list = create_list();
    if(!list)
        return EXIT_FAILURE;
    /* Would check the return value of append and insert. */
    list_append(list, &a);
    list_append(list, &b);
    print_integer_list(list);
    list_insert(list, 1, NULL);
    list_pop(list);
    free_list(list);
    return EXIT_SUCCESS;
}
