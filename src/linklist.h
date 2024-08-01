
#ifndef PROJECT_LINK_LIST_H
#define PROJECT_LINK_LIST_H

typedef struct __NODE__
{
    int x;
    int y;
    char type;
    struct __NODE__* next;
}node;

extern node* head;

node* new_node(int x, int y, char type);

void add_end(node* new_node);

void add_first(node* new_node);

int len();

int delete_index(int index);

void free_list();

void replace(int index);

int find(int x, int y, char type);

#endif //PROJECT_LINK_LIST_H
