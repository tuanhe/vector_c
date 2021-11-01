#ifndef _VECTOR_H
#define _VECTOR_H

#include <stddef.h>
#include <stdbool.h>

typedef void (vector_deleter)(void *);
typedef struct _vector vector;

//base
vector* vector_create(const size_t object_size, vector_deleter* deleter);
void vector_release(vector* vector);

//Element access
void* vector_front(const vector* vector);
void* vector_back(const vector* vector);
void* vector_at(const vector* vector, size_t idx);
void* get_vector_data(const vector* vector, const size_t idx);

size_t get_vector_size(const vector* vector);
size_t get_vector_capacity(const vector* vector);

//iterators
void* vector_begin(const vector* vector);
void* vector_end(const vector* vector);
void* vector_next(const vector* vector, const void* i);

//modifiers
bool vector_push_back(vector* vector, const void* data);
bool vector_pop_back(vector* vector);
bool vector_push_back_no_copy(const vector* vector, void* data);
bool vector_pop_back_no_delete(vector* vector);
bool vector_insert(vector* vector, size_t idx, const void* data);
bool vector_erase(vector* vector, size_t idx);
bool vector_erase_range(vector* vector, size_t first_idx, size_t last_idx);


/* Return `true` if `v` is empty; otherwise, return `false`. */
bool vector_empty(vector* v);
bool vector_clear(vector* v);

#endif