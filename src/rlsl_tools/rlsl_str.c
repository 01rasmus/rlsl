#include <string.h>
#include "rlsl_str.h"

int32_t _rlsl_str_starts_with_any(const char* src, const char** substrings, int32_t substring_count) {
    for(int32_t i = 0; i < substring_count; i++) {
        const char* substring = substrings[i];
        size_t length = strlen(substring);
        if(strncmp(src, substring, length) == 0) {
            return i;
        }
    }
    return -1;
}

size_t rlsl_str_cat(char* dest, size_t dest_total_size, const char* src) {
    size_t dest_length = 0;
    size_t src_length = strlen(src);

    while(dest_length < dest_total_size && dest[dest_length] != 0) {
        dest_length++;
    }

    if(dest_length == (dest_total_size - 1)) {
        return dest_length + src_length;
    }

    size_t i = 0;
    for(; src[i] != 0 && (dest_length + i + 1) < dest_total_size; i++) {
        dest[dest_length + i] = src[i]; 
    }

    if((dest_length + i) < dest_total_size) {
        dest[dest_length + i] = '\0';
    } else {
        dest[dest_total_size] = '\0';
    }

    return dest_length + src_length;
}