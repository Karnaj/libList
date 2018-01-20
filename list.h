#ifndef LIST_H
#define LIST_H


typedef struct s_node s_node;
typedef struct s_list s_list;


struct s_node
{
    void *data;
    s_node *next;
    s_node *previous;
    s_list *list;
};

struct s_list
{
    size_t size;
    s_node *first;
    s_node *last;
};


int list_is_empty(s_list *list);
s_list *create_list(void);
void free_list(s_list *list);
s_node *list_get_element(s_list const * const list, size_t i);
void *list_get(s_list const * const list, const size_t i);
void *list_pop_index(s_list * const list, const size_t i);
void *list_pop(s_list * const list);
void *list_pop_first(s_list * const list);
int list_append(s_list *list, void *data);
int list_append_first(s_list *list, void *data);
int list_insert(s_list *list, size_t i, void *data);
void free_node(s_node *node);


#endif
