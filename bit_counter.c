#include <stdio.h>
#include <stdlib.h>

struct Node {
    int value;
    struct Node* next;
    struct Node* prev;
};

struct LinkedList {
    struct Node *head;
    struct Node *tail;
};

void list_init(struct LinkedList* list, int n) {
    list->head = NULL;
    list->tail = NULL;
    for (int i = 0; i < n; i++) {
        
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

    return 0;
}

