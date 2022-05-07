#include "my_stack_lib.h"

int canary = 1101001; //канарейка

//создаёт хеш стека     ((char*) stack)  (rsize + 1)
unsigned int MurmurHash2 (char * key, unsigned int len)
{
  const unsigned int m = 0x5bd1e995;
  const unsigned int seed = 0;
  const int r = 24;

  unsigned int h = seed ^ len;

  const unsigned char * data = (const unsigned char *)key;
  unsigned int k = 0;

  while (len >= 4)
  {
      k  = data[0];
      k |= data[1] << 8;
      k |= data[2] << 16;
      k |= data[3] << 24;

      k *= m;
      k ^= k >> r;
      k *= m;

      h *= m;
      h ^= k;

      data += 4;
      len -= 4;
  }

  switch (len)
  {
    case 3:
      h ^= data[2] << 16;
    case 2:
      h ^= data[1] << 8;
    case 1:
      h ^= data[0];
      h *= m;
  };

  h ^= h >> 13;
  h *= m;
  h ^= h >> 15;

  return h;
}


//создаёт стек с 8-ю (!!!) эл-тами
struct vs* stack_alloc (struct vs* stack) {
    int *a = (int*) calloc (sizeof(int), 8);
    stack -> data = a; // сам массив
    stack -> capacity = 8; // вместимость
    stack -> size = 0; // кол-во элементов без канареек
    stack -> rsize = 1; // кол-во элементов c первой канарейкой
    stack -> data[0] = canary;
    stack -> data[1] = canary;
    return stack;
}

//увеличивает вместимость стека на 5 эл-тов
struct vs* stack_increase (struct vs* stack) {
    stack -> data = (int*) realloc (stack -> data, sizeof(int) * stack -> capacity * 2);
    stack -> capacity *= 2;
    return stack;
}
//удаляет лишнюю длину из стека
struct vs* stack_decrease (struct vs* stack) {
    stack -> data = (int*) realloc (stack -> data, sizeof(int)* stack -> capacity / 4);
    stack -> capacity /= 4;
}

//кладёт эл-т в стек после последнего элемента
void push (int input, struct vs* stack) {
    if (stack -> capacity == stack -> rsize + 1) {
        stack_increase (stack);
    }
    stack -> data[stack -> rsize] = input;
    stack -> size++;
    stack -> rsize++;
    stack -> data[stack -> rsize] = canary;  //добавляем канарейку
    stack -> hash = MurmurHash2 ((char*)stack -> data, stack -> rsize + 1);
}

//забирает последний эл-т из стека
int pop (int *output, struct vs* stack) {
    if (0 == stack -> size) {
        return 0;
    } else {
        stack -> rsize--;
        *output = stack -> data[stack -> rsize];
        stack -> size--;
        stack -> data[stack -> rsize] = canary;  //добавляем канарейку
        
        if (stack -> capacity > stack -> rsize * 16) {  //удаляем лишнее, если надо
            stack_decrease (stack);
        }

        stack -> hash = MurmurHash2 ((char*)stack -> data, stack -> rsize + 1);
        
        return 1;
    }
}

//проверяет, на месте ли канарейки
bool verify_canary (struct vs* stack) {
    if (stack -> data[0] == canary && stack -> data[stack -> rsize] == canary) {
        return 1;
    } else {
        return 0;
    }
}

//проверяет, в порядке ли стек
bool verify_hash (struct vs* stack) {
    if (MurmurHash2 ((char*)stack -> data, stack -> rsize + 1) != stack -> hash) {
        return 0;
    } else {
        return 1;
    }
}

//проверяет, в порядке ли стек, но лучше
bool verify_stack (struct vs* stack) {
    if (verify_canary (stack) && verify_hash (stack)) {
        return 1;
    } else {
        return 0;
    }
}

//записывает состояние стека (размер, вместимость и сами эл-ты) в файл
void dump (struct vs* stack) {
    FILE* s = fopen ("stack.txt", "a");
    fprintf(s, "=============================================\n");
    fprintf(s, "size = %d, rsize = %d, cap = %d\n\nhash = %u\n\n", stack -> size, stack -> rsize, stack->capacity, stack -> hash);
    
    for (int i = 0; i < stack -> rsize + 1; i++)
    {
        fprintf (s, "stack[%d] = %d\n", i, stack -> data[i]);
    }    
    fprintf(s, "=============================================\n\n\n");
    fclose (s);
}
