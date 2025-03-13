#include <stdio.h>
#include <stdlib.h>

typedef struct State State;
struct State 
{
    int x;
};


void * module_main(State *s)
{
    State * pState;
    if (s == NULL)
    {
        pState = malloc(sizeof(State));
        pState->x = 69;
    } else 
    {
        pState = s;
    };
        
    int run = 1;
    while (run)
    {
        printf("The number is: %d\n", pState->x);
        printf("q: quit, [0-9]: update num, h: reload, or anything to continue: ");
        char option;
        scanf(" %c", &option);
        if (option == 'q') return NULL;
        else if (option == 'h') return pState;
        else if ('0' <= option && option <= '9') pState->x = option - '0';
    }

    return pState;
};
