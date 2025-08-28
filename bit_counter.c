#include <stdio.h>
#include <stdlib.h>
#include <time.h>

struct Node {
    int value;
    struct Node* next;
    struct Node* prev;
};

struct LinkedList {
    int size;
    struct Node *head;
    struct Node *tail;
};

void list_init(struct LinkedList* list, int n) {
    list->head = NULL;
    list->tail = NULL;
    list->size = n;
    for (int i = 0; i < n; i++) {
        struct Node* node = (struct Node*) malloc(sizeof(struct Node));
        node->value = rand();
        node->prev = list->tail;
        node->next = NULL;
        if(list->tail) {
            list->tail->next = node;
        }
        list->tail = node;
        if(!list->head) {
            list->head = node;
        }
    }
}

int main(int argc, char const *argv[])
{
    if(argc != 2) {
        printf("Необходимо указать количество элементов в списке");
        return 0;
    }
    int n = atoi(argv[1]);
    if (n <= 0) {
        printf("Количество элементов должно быть положительным");
        return 0;
    }
    srand(time(NULL));
    struct LinkedList list;
    list_init(&list, n);

    return 0;
}

