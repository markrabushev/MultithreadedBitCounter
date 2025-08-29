#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <pthread.h>

pthread_mutex_t mutex;

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

int count_zero_bits(int value) {
    int n = 0;
    unsigned int u = (unsigned int)value;
    for (int i = 0; i < 32; i++, u >>= 1) {
        if (!(u & 1)) n++;
    }
    return n;
}

int count_one_bits(int value) {
    int n = 0;
    unsigned int u = (unsigned int)value;
    for (int i = 0; i < 32; i++, u >>= 1) {
        if (u & 1) n++;
    }
    return n;
}

struct thread_arg {
    struct LinkedList* list;
    int direction;
};

void* count_bits(void* arg) {
    struct thread_arg* targ = (struct thread_arg*)arg;
    struct LinkedList* list = targ->list;
    int direction = targ->direction;

    unsigned long long bit_count = 0;
    int elements = 0;

    while (1) {
        pthread_mutex_lock(&mutex);
        if (list->head == NULL) {
            pthread_mutex_unlock(&mutex);
            break;
        }

        struct Node* node = NULL;
        if (direction == 0) {
            node = list->head;
            if (list->head == list->tail) {
                list->head = NULL;
                list->tail = NULL;
            } else {
                list->head = list->head->next;
                list->head->prev = NULL;
            }
        } else {
            node = list->tail;
            if (list->head == list->tail) {
                list->head = NULL;
                list->tail = NULL;
            } else {
                list->tail = list->tail->prev;
                list->tail->next = NULL;
            }
        }
        pthread_mutex_unlock(&mutex);

        if (direction == 0) {
            bit_count += count_zero_bits(node->value);
        } else {
            bit_count += count_one_bits(node->value);
        }
        elements++;
        free(node);
    }

    printf("Количество %d-х битов, начиная с %s: %llu, Количество учтенных элементов %d\n",
           direction, direction == 0 ? "головы" : "хвоста", bit_count, elements);
    return NULL;
}

int main(int argc, char const *argv[])
{
    if(argc != 2) {
        printf("Необходимо указать количество элементов в списке");
        return 0;
    }
    int n = atoi(argv[1]);
    if (n <= 0) {
        printf("Количество элементов должно быть положительным числом");
        return 0;
    }
    srand(time(NULL));
    struct LinkedList list;
    list_init(&list, n);

    pthread_mutex_init(&mutex, NULL);
    pthread_t thread1, thread2;
    struct thread_arg arg1 = { &list, 0 };
    struct thread_arg arg2 = { &list, 1 };
    pthread_create(&thread1, NULL, count_bits, &arg1);
    pthread_create(&thread2, NULL, count_bits, &arg2);

    pthread_join(thread1, NULL);
    pthread_join(thread2, NULL);

    pthread_mutex_destroy(&mutex);

    return 0;
}

