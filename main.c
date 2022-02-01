#include <stdio.h>
#include <stdlib.h>
#include <string.h>

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

int list_find(LNode *list_head, char *string) {
    // Returns the first position where the element was found, else -1.
    int str_was_null = 0;
    if (string == NULL) {
        str_was_null = 1;
        string = (char *)malloc(100 * sizeof(char));
        printf("Enter string to find (max 100 char): ");
        scanf("%s", string);
    }
    int found = -1;
    int pos = 0;
    LNode *current = list_head;
    while (current != NULL) {
        if (strcmp(string, current->data) == 0) {
            found = pos;
            break;
        }
        current = current->next;
        pos++;
    }
    // Release the memory for the string if it was dynamically allocated.
    if (str_was_null == 1) {
        free(string);
        string = NULL;
    }
    return found;
}

LNode *list_remove(LNode *list_head, char *string) {
    int str_was_null = 0;
    if (string == NULL) {
        str_was_null = 1;
        string = (char *)malloc(100 * sizeof(char));
        printf("Enter string to remove (max 100 char): ");
        scanf("%s", string);
    }
    LNode* last = NULL;
    LNode* current = list_head;
    while (current != NULL) {
        if (strcmp(string, current->data) == 0) {
            if (last == NULL) {
                list_head = current->next;
            } else {
                last->next = current->next;
            }
            if (current->next != NULL) {
                current->next->prev = last;
            }
            free(current->data);
            free(current);
            break;
        }
        last = current;
        current = current->next;
    }

    if (str_was_null == 1) {
        free(string);
        string = NULL;
    }
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
    list = list_insert(list, NULL);

    list_print(list);
    int pos = list_find(list, NULL);
    printf("pos: %i\n", pos);

    list = list_remove(list, NULL);
    list_print(list);
}
