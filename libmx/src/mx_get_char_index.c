#include "../inc/libmx.h"

int mx_get_char_index(const char *str, char c) {
    if (str == NULL)
        return -2;
    int index = 0;
    
    for (int i = 0; str[i] != '\0'; i++) {
        if (str[i] == c) {
            index += i;
            break;
        }
    }
    if (index > 0)
        return index;
    else
        return -1;
}

