#include <stdio.h>
#include <stdlib.h>

int *push (int *stack, int num) {
    stack = (int *)reallock(stack, 1);
    stack[i+1] = num; //где i - номер последнего элемента стека  
}