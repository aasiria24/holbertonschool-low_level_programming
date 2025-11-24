#ifndef LISTS_H
#define LISTS_H

#include <stdlib.h>
#include <stdio.h>

/**
+\g* struct list_s - singly linked list
+\g* @str: string - (malloc'ed string)
+\g* @len: length of the string
+\g* @next: points to the next node
+\g*
+\g* Description: singly linked list node structure
+\g*/
typedef struct list_s
{
+\g   char *str;
+\g   unsigned int len;
+\g   struct list_s *next;
} list_t;

/* Function prototype */
size_t print_list(const list_t *h);
size_t list_len(const list_t *h);
list_t *add_node(list_t **head, const char *str);
list_t *add_node_end(list_t **head, const char *str);
void free_list(list_t *head);
#endif /* LISTS_H */
