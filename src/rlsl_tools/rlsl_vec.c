#include <stdlib.h>
#include <string.h>
#include "rlsl_vec.h"

int64_t rlsl_vec_size(void* vec) {
    if(!vec) {
        return 0;
    }

    rlsl_vec_header_t* header = RLSL_VEC_HEADER(vec);
    return header->size;
}

void rlsl_vec_free(void* vec) {
    rlsl_vec_header_t* header = RLSL_VEC_HEADER(vec);
    free(header);
}

static void* _rlsl_vec_init(size_t element_size) {
    void* mem = malloc(sizeof(rlsl_vec_header_t) + (element_size * RLSL_VEC_INITIAL_CAPACITY));
    rlsl_vec_header_t* header = (rlsl_vec_header_t*)mem;
    header->capacity = RLSL_VEC_INITIAL_CAPACITY;
    header->size = 0;
    header->element_size = element_size;
    return RLSL_VEC_POINTER_ADD(mem, sizeof(rlsl_vec_header_t));
}

static void* _rlsl_vec_realloc(void* vec, size_t needed_size) {
    rlsl_vec_header_t* header = RLSL_VEC_HEADER(vec);
    size_t desired_size = header->size + needed_size;
    if(header->capacity >= desired_size) {
        return vec;
    }

    size_t new_cap = header->capacity;
    while(new_cap < desired_size) {
        new_cap *= 2;
    }

    void* new_mem = realloc(header, sizeof(rlsl_vec_header_t) + (new_cap * header->element_size));
    if(!new_mem) {
        return NULL;
    }
    header = (rlsl_vec_header_t*)new_mem;
    header->capacity = new_cap;

    return RLSL_VEC_POINTER_ADD(new_mem, sizeof(rlsl_vec_header_t));
}

void _rlsl_vec_push(void** vec, const void* element, size_t element_size) {
    void* v = *vec;

    if(!v) {
        v = _rlsl_vec_init(element_size);
    }
    
    v = _rlsl_vec_realloc(v, 1);
    rlsl_vec_header_t* header = RLSL_VEC_HEADER(v);

    size_t offset = header->size * element_size;
    memcpy(RLSL_VEC_POINTER_ADD(v, offset), element, element_size);
    header->size++;
    (*vec) = v;
}