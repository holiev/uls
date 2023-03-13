#include "../inc/libmx.h"

static int strlen(const char *s) {
    int i;
    for(i = 0; s[i] != '\0'; i++) {

    }
    return i;
}

static void *memchr(const void *s, int c, size_t n) {
    unsigned char *ptr = (unsigned char*)s;
    
    while (n > 0) {
        if (*ptr == (unsigned char)c)
            return ptr;
        ptr++;
        n--;
    }
    return NULL;
}

static char *strcat(char *s1, const char *s2) {
    char *end = s1 + strlen(s1);
    
    while (*s2 != '\0') {
        *end = *s2;
        end++;
        s2++;
    }
    *end = '\0';
    return s1;
}

static void *memcpy(void *dst, const void *src, size_t len) {
    if (src) {
        for (size_t i = 0; i < len; i++) {
            ((unsigned char*)dst)[i] = ((unsigned char*)src)[i];
        }
    }
    return dst;
}

static void *f_realloc(void *ptr, size_t size) {
    if (ptr == NULL) {
        return malloc(size);
    }
    
    size_t new_size = malloc_size(ptr);
    if (size <= new_size)
        return ptr;
    
    void *new_ptr = malloc(size);
    memcpy(new_ptr, ptr, size);
    free(ptr);
    return new_ptr;
}

static char *strnew(const int size) {
    if (size <= 0)
        return NULL;
    char *str = (char *)malloc(size + 1);
    
    if (str == NULL)
        return NULL;
    for (int i = 0; i < size; i++) {
        str[i] = '\0';
    }
    str[size] = '\0';
    return str;
}

static char *strncpy(char *dst, const char *src, int len) {
    int i;
    for (i = 0; i < len && src[i] != '\0'; i++) {
        dst[i] = src[i];
    }
    for (int j = i; j < len; j++) {
        dst[j] = '\0';
    }
    return dst;
}

static char *strndup(const char *s1, size_t n) {
    int len = 0;
        
    if((int)n >= strlen(s1))
        len = strlen(s1);
    else
        len = (int)n;
        
    char *temp = strnew(len);
    if (temp == NULL)
        return NULL;
    return strncpy(temp, s1, len);
}

static void strdel(char **str) {
    if (str != NULL) {
        free(*str);
        *str = NULL;
    }
    else
        return;
}

int mx_read_line(char **lineptr, size_t buf_size, char delim, const int fd) {
    static char *remainder = NULL;
    char *str = NULL;
    int total = 0;
    char *buf = (char *)malloc(buf_size + 1);
    ssize_t result = -1;

    if (remainder != NULL) {
        str = remainder;
        remainder = NULL;
        total = strlen(str);
    }

    while (fd >= 0 && (result = read(fd, buf, buf_size)) > 0) {
        char *ptr = (char *)memchr(buf, delim, result);
        ssize_t count = result;

        if (ptr != NULL) {
            count = ptr - buf;
        }

        buf[count] = '\0';
        str = (char *)f_realloc(str, total + count + 1);
        strcat(str, buf);
        total += count;

        if (ptr != NULL) {
            ssize_t remaining = result - count;

            if (remaining > 0) {
                remainder = strndup(buf + count + 1, remaining);
            }
            break;
        }
    }

    free(buf);

    if (result == -1) {
        strdel(&str);
        strdel(&remainder);
        return -2;
    }

    if (str == NULL) {
        return -1;
    }

    *lineptr = str;
    return total;
}

