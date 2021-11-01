#ifndef _VECTOR_H
#define _VECTOR_H

#include <stddef.h>
#include <stdbool.h>

typedef struct _vector
{
    size_t element_num;
    size_t capacity;
    size_t object_size;
    void* mem;
}vector;

vector* vector_create(const size_t object_size);
void vector_destroy(vector* vector);

bool vector_push_back(vector* vector, const void* data);
bool vector_pop_back(vector* vector);
bool vector_push_back_no_copy(const vector* vector, void* data);
bool vector_pop_back_no_delete(const vector* vector);

void* vector_front(const vector* vector);
void* vector_back(const vector* vector);

void* get_vector_data(const vector* vector, const size_t idx);
size_t get_vector_size(const vector* vector);
size_t get_vector_capacity(const vector* vector);

//iterators
void* vector_begin(const vector* vector);
void* vector_end(const vector* vector);
void* vector_next(const vector* vector, const void* i);

#endif