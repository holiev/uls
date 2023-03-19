#include "../inc/uls.h"

bool flag(char **argv)
{
    if (mx_strcmp("-l", argv[1]) == 0)
    {
        return true;
    }
    else
        return false;
}
