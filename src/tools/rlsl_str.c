#include <string.h>
#include <stdlib.h>
#include "rlsl_str.h"

int32_t _rlsl_str_starts_with_any_of(const char* src, const char** substrings, int32_t substring_count) {
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

char* rlsl_str_cpy(const char* string) {
    size_t length = strlen(string) + 1;
    char* new_string = (char*)malloc(length);
    if(new_string) {
        memcpy(new_string, string, length);
    }
    return new_string;
}

void rlsl_str_print_json_string(FILE* fd, const char* str) {
    for(; *str; str++) {
        switch(*str) {
            case '"': {
                fputs("\\\"", fd); break;
            }
            case '\\': {
                fputs("\\\\", fd); break;
            }
            case '\n': {
                fputs("\\n", fd); break;
            }
            case '\r': {
                fputs("\\r", fd); break;
            }
            case '\t': {
                fputs("\\t", fd); break;
            }
            case '\b': {
                fputs("\\b", fd); break;
            }
            case '\f': {
                fputs("\\f", fd); break;
            }
            
            default: {
                if ((unsigned char)*str < 0x20) {
                    fprintf(fd, "\\u%04x", (unsigned char)*str);
                } else {
                    fputc(*str, fd);
                }
            }
        }
    }
}