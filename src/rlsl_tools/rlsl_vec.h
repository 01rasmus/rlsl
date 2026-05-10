#pragma once
#include <stdint.h>
#include <stddef.h>

#define RLSL_VEC_HEADER(VEC)            (rlsl_vec_header_t*)((uintptr_t)VEC - sizeof(rlsl_vec_header_t))
#define RLSL_VEC_INITIAL_CAPACITY       1

typedef struct rlsl_vec_header_t {
    size_t capacity;
    size_t size;
    size_t element_size;
} rlsl_vec_header_t;

#define rlsl_vec_push(VEC, ELEMENT) \
    _rlsl_vec_push((void**)&VEC, (void*)&ELEMENT, sizeof(ELEMENT))

int64_t rlsl_vec_size(void* vec);
void rlsl_vec_free(void* vec);

/*
    internal
*/
void _rlsl_vec_push(void** vec, const void* element, size_t element_size);