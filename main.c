#include "my_stack_lib.h"

//stack == всё

int main () {
     // create a stack
    int input = 0, output = 0;
    struct vs* stack = (struct vs*) calloc (sizeof (struct vs), 1);

    stack = stack_alloc(stack);

    /*while (scanf("%d", &input) == 1) {    
        push (input, stack);
    }*/

    for (int i = 1; i < 65; i++)
    {
        push (i, stack);
    }

    dump (stack);

    for (int i = 0; i < 60; i++)
    {
        pop (&output, stack);
    }

    //assert (1 == pop (&output, stack));
    assert (1 == verify_hash (stack));

    dump (stack);

    free (stack);
    return 0;
}


