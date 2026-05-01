#include "rlsl_cursor.h"

rlsl_cursor_t rlsl_cursor_create() {
    return (rlsl_cursor_t){
        .index = 0,
        .column = 1,
        .line = 1,
    };
}

size_t rlsl_cursor_advance(rlsl_cursor_t* rlsl_cursor, const char* string, size_t amount) {
    size_t destination_index = rlsl_cursor->index + amount;
    size_t start = rlsl_cursor->index;
    for(; rlsl_cursor->index < destination_index;) {
        const char current = string[rlsl_cursor->index];
        const char next = string[rlsl_cursor->index + 1];
        if(current == '\0') {
            break;
        }

        rlsl_cursor->index++;
        rlsl_cursor->column++;

        //if there is a double character newline
        //the index needs to be increased an extra time
        if(current == '\r' && next == '\n') {
            rlsl_cursor->index++;
        }
        if(current == '\r' || current == '\n') {
            rlsl_cursor->column = 1;
            rlsl_cursor->line++;
        }
    }
    return rlsl_cursor->index - start;
}