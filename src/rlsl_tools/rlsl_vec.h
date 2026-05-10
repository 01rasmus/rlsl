#pragma once
#include <stdlib.h>
#include <stdint.h>
#include <stddef.h>

#define RLSL_VEC_HEADER(VEC)                (VEC ? (((uintptr_t)VEC) - sizeof(rlsl_vec_header_t)) : NULL)
#define RLSL_VEC_ARRAY_PTR(HEADER)          (HEADER ? (void*)(((uintptr_t)HEADER) + sizeof(rlsl_vec_header_t)) : NULL)
#define RLSL_VEC_INITIAL_CAPACITY           16

typedef struct rlsl_vec_header_t {
    size_t capacity;
    size_t size;
    size_t element_size;
} rlsl_vec_header_t;

#define rlsl_vec_push(VEC, ELEMENT) \
    _rlsl_vec_push((void**)&VEC, (const void*)&ELEMENT, sizeof(ELEMENT))

int64_t rlsl_vec_size(void* vec);
void rlsl_vec_free(void* vec);

/*
    internal
*/
void _rlsl_vec_push(void** vec, const void* element, size_t element_size);