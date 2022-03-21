#include "my_stack_lib.h"

int main () {
    
    int *stack = (int *) calloc (sizeof(int), 1); // create a stack


    
    int num = 0; 
    scanf ("%d", &num); // read number

    stack [0] = num;

    printf("%d", stack[0]);

    return 0;

}



/*
    
int *stack = calloc (sizeof(int), 128); // create a stack
    
int number = 0; 
scanf ("%d", number); // read number

push (stack, number):

    stack = (int*) realloc (stack, sizeof (number)) //добавляем память под число

    
    //вписываем число



*/