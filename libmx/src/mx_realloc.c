#include "../inc/libmx.h"

static void *memcpy(void *dst, const void *src, size_t len) {
    if (src) {
        for (size_t i = 0; i < len; i++) {
            ((unsigned char*)dst)[i] = ((unsigned char*)src)[i];
        }
    }
    return dst;
}

void *mx_realloc(void *ptr, size_t size) {
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

