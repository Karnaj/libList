#include <stdio.h>
#include <stdlib.h>
#include "list.h"

int list_is_empty(s_list *list)
{
    return list->size == 0;
}

s_list *create_list(void)
{
    s_list *list = malloc(sizeof(s_list));
    if(NULL == list)
    {
        perror("Error creating a new list : ");
        return NULL;
    }
    list->first = NULL;
    list->last = NULL;
    list->size = 0;
    return list;
}

void free_list(s_list *list)
{
    if(list)
    {
        s_node *node = list->first;
        while(node)
        {
            s_node *next = node->next;
            free(node);
            node = next;
        }
        free(list);
    }
}

s_node *list_get_element(s_list const * const list, size_t i)
{
    s_node *node = list->first;
    if(i == 0)
        return list->first;
    else if(i == list->size - 1)
        return list->last;
    else if(i > list->size - 1)
    {
        fprintf(stderr, "Error getting an element to a list : list index out of range.");
        return NULL;
    }
    for(; i ; i--)
        node = node->next;
    return node;
}

void *list_get(s_list const * const list, const size_t i)
{
    return list_get_element(list, i)->data;
}

void *list_pop_index(s_list * const list, const size_t i)
{
    if(i == 0)
        return list_pop_first(list);
    else if(i == list->size - 1)
        return list_pop(list);
    else if(i > list->size - 1)
    {
        fprintf(stderr, "Error pop an index element from a list : list index out of range.");
        return NULL;
    }
    s_node *node = list_get_element(list, i);
    s_node *previous = node->previous, *next = node->next;
    void *data = node->data;
    list->size--;
    node->next = next;
    next->previous = previous;
    free(node);
    return data;
}

void *list_pop(s_list * const list)
{
    if(list_is_empty(list))
    {
        fprintf(stderr, "Error pop an element from a list : empty list.");
        return NULL;
    }
    s_node *last = list->last;
    void *data = last->data;
    list->size--;
    list->last = last->previous;
    list->last->next = NULL;
    free(last);
    return data;
}

void *list_pop_first(s_list * const list)
{
    if(list_is_empty(list))
    {
        fprintf(stderr, "Error pop an element from a list : empty list.");
        return NULL;
    }
    s_node *first = list->first;
    void *data = first->data;
    list->size--;
    list->first = first->next;
    free(first);
    return data;
}

int list_append(s_list *list, void *data)
{
    s_node *node = malloc(sizeof(s_node));
    if(NULL == node)
    {
        perror("Error appending an element to a list : ");
        return -1;
    }
    node->list = list;
    node->data = data;
    node->next = NULL;
    node->previous = list->last;
    if(list_is_empty(list))
        list->first = node;
    else
        list->last->next = node;
    list->last = node;
    list->size++;
    return 0;
}

int list_append_first(s_list *list, void *data)
{
    s_node *node = malloc(sizeof(s_node));
    if(NULL == node)
    {
        perror("Error appending an element to a list : ");
        return -1;
    }
    node->list = list;
    node->data = data;
    node->previous = NULL;
    node->next = list->first;
    if(list_is_empty(list))
        list->last = node;
    else
        list->first->previous = node;
    list->first = node;
    list->size++;
    return 0;
}

int list_insert(s_list *list, size_t i, void *data)
{
    if(i == 0)
        return list_append_first(list, data);
    else if(i == list->size)
        return list_append(list, data);
    else if(i > list->size)
    {
        fprintf(stderr, "Error inserting an element to a list : list index out of range.");
        return -1;
    }
    s_node *node = malloc(sizeof(s_node));
    if(NULL == node)
    {
        perror("Error inserting an element to a list : ");
        return -1;
    }
    s_node *tmp = list_get_element(list, i - 1);
    node->list = list;
    node->data = data;
    list->size++;
    node->previous = tmp;
    node->next = tmp->next;
    tmp->next->previous = node;
    tmp->next = node;
    return 0;
}

void free_node(s_node *node)
{
    s_list *list = node->list;
    s_node *previous = node->previous, *next = node->next;
    list->size--;
    if(previous)
        previous->next = next;
    else
        list->first = next;
    if(next)
        next->previous = previous;
    else
        list->last = previous;
    free(node);
}
