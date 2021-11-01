#ifndef _VECTOR_H
#define _VECTOR_H

#include <stddef.h>
#include <stdbool.h>

typedef void (vector_deleter)(void *);
//typedef struct _vector vector;
typedef struct _vector
{
    size_t element_num;
    size_t capacity;
    size_t element_size;
    void* mem;
    vector_deleter* deleter;
}vector;

//Base
vector* vector_create(const size_t object_size, vector_deleter* deleter);
void vector_destroy(vector* vector);

//Element access
void* vector_front(const vector* vector);
void* vector_back(const vector* vector);
void* vector_at(const vector* vector, size_t idx);
void* get_vector_element(const vector* vector, const size_t idx);

//Information
size_t vector_size(const vector* vector);
size_t vector_capacity(const vector* vector);
bool vector_is_empty(const vector* vector);

//Iterators
void* vector_begin(const vector* vector);
void* vector_end(const vector* vector);
void* vector_iterator(const vector* vector, const void* i);

// Insert
bool vector_push_back(vector* vector, const void* element);
bool vector_push_front(vector* vector, const void* element);
bool vector_insert(vector* vector, size_t idx, const void* element);
bool vector_push_back_no_copy(const vector* vector, void* element);

// Delete
bool vector_pop_back(vector* vector);
bool vector_pop_back_no_delete(vector* vector);
bool vector_erase_range(vector* vector, size_t first_idx, size_t last_idx);
bool vector_erase(vector* vector, size_t idx);
bool vector_clear(vector* v);

#endif