#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include "linklist.h"

// this definition is in linklist.h
/*typedef struct __NODE__
{
    int x;
    int y;
    char type;
    struct __NODE__* next;
}node;*/

// start from 1 to end

node *head = NULL;

node *new_node(int x, int y, char type)
{
    node *output = (node *)malloc(sizeof(node));
    output->x = x;
    output->y = y;
    output->type = type;
    output->next = NULL;
    return output;
}

void add_end(node *new_node)
{
    if (head == NULL)
    {
        head = new_node;
        return;
    }
    node* current = head;
    while (current->next != NULL)
    {
        current = current->next;
    }
    current->next = new_node;
}

/*void print()
{
    int index = 1;
    node* curr = head;
    while(curr != NULL)
    {
        printf("value of node(%d) : %d %d %c\n", index , curr->x, curr->y, curr->type);
        index++;
        curr = curr->next;
    }
}*/

void add_first(node *new_node)
{
    new_node->next = head;
    head = new_node;
}

int len()
{
    int len = 0;
    node *temp = head;
    while (temp != NULL)
    {
        len++;
        temp = temp->next;
    }
    return len;
}

/*void insert(int index , node* new_node)
{
    node* curr;
    if (index == 1)
    {
        new_node->next = *head;
        *head = new_node;
        return;
    }
    if (index == len(*head) + 1)
    {

        for (curr = *head ; curr->next != NULL ; curr = curr->next)
        {
        }
        curr->next = new_node;
        return;
    }
    int i = 1;
    for ( curr = *head ; i < index - 1 ; i++ , curr = curr->next)
    {
    }
    new_node->next = curr->next;
    curr->next = new_node;
}

void write(node** head , int index , int x, int y, char type)
{
    node* curr = *head;
    int i = 0;
    while (i != index-1)
    {
        curr = curr->next;
        i++;
    }
    curr->x = x;
    curr->y = y;
    curr->type = type;
}

void read(node* head , int index)
{
    node* curr = head;
    int i = 1;
    while (i != index)
    {
        curr = curr->next;
        i++;
    }
    printf("%c\n", curr->type);

}*/

void replace(int index)
{
    int i = 1;
    node *ptr;
    for (ptr = head; i < index; i++, ptr = ptr->next)
    {
    }
    srand(time(NULL));
    if (rand() % 2)
        ptr->type = 'h';
    else
        ptr->type = 'd';
}

int delete_index(int index)
{
    if (index == -2)
        return 0;
    if (index == -1 || index > len() || (index < 1))
    {
        return 1;
    }
    node *curr = head;
    node *hold;
    if (index == 1)
    {
        hold = head;
        head = head->next;
        free(hold);
        return 0;
    }
    int i = 1;
    while (i != index - 1)
    {
        i++;
        curr = curr->next;
    }
    hold = curr->next;
    curr->next = curr->next->next;
    free(hold);
    return 0;
}

/*int delete_value(node** head , int x, int y, char type)
{
    if ((*head)->x && (*head)->y && (*head)->type)
    {
        delete_index(head , 1);
        return 0;
    }
    node* curr = *head;
    for (int i = 1; i <= len(*head); curr = curr->next , i++)
    {
        if (curr->x == x && curr->y == y && curr->type == type)
        {
            delete_index(head , i);
            return 0;
        }

    }
    return 1;
}*/

void free_list()
{
    while (head != NULL)
    {
        node* temp = head;
        head = head->next;
        free(temp);
    }
}

/*void replace_all(node* head , int find , int replace)
{
    node* curr = head;
    while (curr != NULL)
    {
        if (curr->value == find)
        {
            curr->value = replace;
        }
        curr = curr->next;
    }
    return;
}*/

int find(int x, int y, char type)
{
    node *curr = head;
    int i = 1;
    while (curr != NULL)
    {
        if ((curr->x == x || curr->x - x == 1 || curr->x - x == 2) && curr->y == y && (curr->type == type || type == '~'))
        {
            if (curr->type == 'e')
            {
                replace(i);
                return -2;
            }
            else
                return i;
        }
        i++;
        curr = curr->next;
    }
    return -1;
}
