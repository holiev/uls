#include "../inc/libmx.h"

static int strlen(const char *s) {
    int i;
    for(i = 0; s[i] != '\0'; i++) {

    }
    return i;
}

void mx_printstr(const char *s) {
    write(1, s, strlen(s));
}

