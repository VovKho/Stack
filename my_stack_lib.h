#include <stdio.h>
#include <stdlib.h>
#include <assert.h>
#include <stdbool.h>

struct vs {
    int* data;
    int capacity;
    int size;
    int rsize;
    unsigned int hash;
};

//создаёт хеш стека         (stack)       (rsize + 1)
unsigned int MurmurHash2 (char * key, unsigned int len);

//создаёт стек с 8-ю (!!!) эл-тами
struct vs* stack_alloc (struct vs* stack);

//увеличивает вместимость стека на 5 эл-тов
struct vs* stack_increase (struct vs* stack);

//удаляет лишнюю длину из стека
struct vs* stack_decrease (struct vs* stack);

//кладёт эл-т в стек после последнего элемента
void push (int input, struct vs* stack);

//забирает последний эл-т из стека
int pop (int *output, struct vs* stack);

//проверяет, на месте ли канарейки
bool verify_canary (struct vs* stack);

//проверяет, в порядке ли стек
bool verify_hash (struct vs* stack);

//проверяет, в порядке ли стек, но лучше
bool verify_stack (struct vs* stack);

//записывает состояние стека (размер, вместимость, хеш и сами эл-ты) в файл
void dump (struct vs* stack);

