#include "rlsl_cursor.h"

rlsl_cursor_t rlsl_cursor_create() {
    return (rlsl_cursor_t){
        .offset = 0,
        .column = 1,
        .line = 1,
    };
}

rlsl_cursor_t rlsl_cursor_at_position(const char* source, size_t line, size_t column) {
    rlsl_cursor_t initial = rlsl_cursor_create();

    while(initial.line < line || (initial.line >= line && initial.column < column)) {
        if(rlsl_cursor_advance(&initial, source, 1) == 0) {
            break;
        }
    }
    return initial;
}

size_t rlsl_cursor_advance(rlsl_cursor_t* rlsl_cursor, const char* string, size_t amount) {
    size_t destination_index = rlsl_cursor->offset + amount;
    size_t start = rlsl_cursor->offset;
    for(; rlsl_cursor->offset < destination_index;) {
        const char current = string[rlsl_cursor->offset];
        const char next = string[rlsl_cursor->offset + 1];
        if(current == '\0') {
            break;
        }

        rlsl_cursor->offset++;
        rlsl_cursor->column++;

        //if there is a double character newline
        //the index needs to be increased an extra time
        if(current == '\r' && next == '\n') {
            rlsl_cursor->offset++;
        }
        if(current == '\r' || current == '\n') {
            rlsl_cursor->column = 1;
            rlsl_cursor->line++;
        }
    }
    return rlsl_cursor->offset - start;
}

int32_t rlsl_cursor_compare(const rlsl_cursor_t* a, const rlsl_cursor_t* b) {
    int32_t line_cmp = (a->line > b->line) - (a->line < b->line);
    if(line_cmp != 0) {
        return line_cmp;
    }

    int32_t column_cmp = (a->column > b->column) - (a->column < b->column);
    if(column_cmp != 0) {
        return column_cmp;
    }

    return (a->offset > b->offset) - (a->offset < b->offset);
}