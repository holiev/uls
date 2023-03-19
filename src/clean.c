#include "../inc/uls.h"

void clean_array(char **names, int size)
{
    for (int i = 0; i < size; i++)
    {
        free(names[i]);
    }
    free(names);
}
