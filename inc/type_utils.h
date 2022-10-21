#ifndef _TYPE_UTILSH_
#define _TYPE_UTILSH_
#include <SDL2/SDL.h>

typedef struct rgba
{
    Uint8 r;
    Uint8 g;
    Uint8 b;
    Uint8 a;
} RGBA;

typedef struct state
{
    int id;
} State;

typedef struct tree
{
    State *states;
    int *adjacency_list;
    int num_states;
    int num_connections;
} Tree;
#endif