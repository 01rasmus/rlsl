#include <string.h>
#include <stdarg.h>
#include <stdlib.h>
#include "rlsl_str.h"

#define DEFAULT_CAPACITY 16

rlsl_str_stream_t rlsl_str_stream_create(uint8_t stream_type) {
    if(stream_type == RLSL_STR_STREAM_MEMORY) {
        return (rlsl_str_stream_t) {
            .type = RLSL_STR_STREAM_MEMORY,
            .capacity = DEFAULT_CAPACITY,
            .length = 0,
            .string = malloc(DEFAULT_CAPACITY)
        };
    }
    return (rlsl_str_stream_t) {
        .type = RLSL_STR_STREAM_STDOUT,
        .capacity = 0,
        .length = 0,
        .string = NULL
    };
}

void rlsl_str_stream_printf(rlsl_str_stream_t* sstr, const char* format, ...) {
    va_list args;
    va_start(args, format);

    if(sstr->type == RLSL_STR_STREAM_MEMORY) {

        //calculate how many bytes are needed
        va_list args_copy;
        va_copy(args_copy, args);
        int64_t needed = vsnprintf(NULL, 0, format, args_copy);
        va_end(args_copy);
        
        //reallocate if needed
        int64_t required = sstr->length + needed + 1;
        if(required > sstr->capacity) {
            int64_t new_capacity = sstr->capacity ? sstr->capacity : DEFAULT_CAPACITY;
            while(new_capacity < required) {
                new_capacity *= 2;
            }

            char* new_string = realloc(sstr->string, new_capacity);
            if(!new_string) {
                goto end;
            }

            sstr->string = new_string;
            sstr->capacity = new_capacity;
        }

        //write
        int64_t remaining = sstr->capacity - sstr->length;
        sstr->length += vsnprintf(sstr->string + sstr->length, remaining, format, args);
    } else {
        vprintf(format, args);
    }

end:
    va_end(args);
}

void rlsl_str_stream_print_json_string(rlsl_str_stream_t* sstr, const char* str) {
    for(; *str; str++) {
        switch(*str) {
            case '"': {
                rlsl_str_stream_printf(sstr, "\\\""); break;
            }
            case '\\': {
                rlsl_str_stream_printf(sstr, "\\\\"); break;
            }
            case '\n': {
                rlsl_str_stream_printf(sstr, "\\n"); break;
            }
            case '\r': {
                rlsl_str_stream_printf(sstr, "\\r"); break;
            }
            case '\t': {
                rlsl_str_stream_printf(sstr, "\\t"); break;
            }
            case '\b': {
                rlsl_str_stream_printf(sstr, "\\b"); break;
            }
            case '\f': {
                rlsl_str_stream_printf(sstr, "\\f"); break;
            }
            
            default: {
                if ((unsigned char)*str < 0x20) {
                    rlsl_str_stream_printf(sstr, "\\u%04x", (unsigned char)*str);
                } else {
                    rlsl_str_stream_printf(sstr, "%c", *str);
                }
            }
        }
    }
}

int64_t rlsl_str_stream_length(rlsl_str_stream_t* sstr) {
    return sstr->length;
}

/*
    make sure not to free this and the stream.
    only free this one or the stream
*/
char* rlsl_str_stream_raw(rlsl_str_stream_t* sstr) {
    return sstr->string;
}

void rlsl_str_stream_free(rlsl_str_stream_t* sstr) {
    if(!sstr) {
        return;
    }
    free(sstr->string);
}

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