#include <stdio.h>
#include <stdlib.h>

typedef struct Node {
    char *data;
    struct Node *prev;
    struct Node *next;
} LNode;

LNode *list_insert(LNode *list_head, char *string) {
    // If no string is provided, read one in on the fly.
    if (string == NULL) {
        string = (char *)malloc(100 * sizeof(char));
        printf("Enter new string data (max 100 char): ");
        scanf("%s", string);
    }
    // Navigate to the last non-null element.
    LNode *current = list_head;
    LNode *last = current;
    while (current != NULL) {
        last = current;
        current = current->next;
    }
    // Create the new node and update prev/next pointers.
    LNode *new_node = (LNode *)malloc(sizeof(LNode));
    new_node->data = string;
    if (last == NULL) {
        new_node->prev = NULL;
        new_node->next = NULL;
        list_head = new_node;
    } else {
        new_node->prev = last;
        last->next = new_node;
        new_node->next = current; // Note that current may be NULL.
        if (current != NULL) {
            current->prev = new_node;
        }
    }
    // Return the list head -- important in case the list was empty (i.e. NULL) and we
    // created it.
    return list_head;
}

void list_print(LNode *list_head) {
    LNode *current = list_head;
    while (current != NULL) {
        printf("%s\n", current->data);
        current = current->next;
    }
}

int main(int argc, char *argv[]) {
    LNode *list = NULL;
    list = list_insert(list, NULL);
    list = list_insert(list, NULL);
    list_print(list);
}
