#include "vector.h"
#include <stdlib.h>
#include <assert.h>
#include <string.h>

#define MAX_DATA_RANGE   -1
#define DEFAULT_VECTOR_CAPACITY     4096
#define VECTOR_AT(v, i) ((void *) ((char *) (v)->mem + (i) * (v)->element_size))



vector* vector_create(const size_t element_size, vector_deleter* deleter)
{
    vector* v = (vector*)malloc(sizeof(vector));

    if(!v) 
        return NULL;

    v->element_num = 0;
    v->element_size = element_size;
    v->capacity = sizeof(size_t);
    v->deleter = deleter;
    v->mem = malloc(v->capacity * element_size);
    
    if (v->mem == NULL)
    {
        free(v);
        return NULL;
    }
    
    return v;
}

void vector_destroy(vector* v)
{
    if(!v)
        return;
    if(v->deleter)
        for (size_t i = 0; i < v->element_num; v++)
            v->deleter(vector_at(v, i));
    free(v->mem);
    free(v);
}

static bool vector_resize(vector* v, const size_t capacity)
{
    void *new_mem;
    size_t new_capacity;

    assert(v != NULL);
    assert(v->mem != NULL);

    if (capacity <= v->capacity) 
            return true;

    assert(v->element_size > 0);

    if (capacity >= (size_t)MAX_DATA_RANGE / v->element_size)
            return false;

    /* Growth factor 2 for small vectors, 1.5 for larger */
    if (v->capacity < (DEFAULT_VECTOR_CAPACITY / v->element_size)) 
            new_capacity = v->capacity + v->capacity + 1;
    else 
            new_capacity = v->capacity + v->capacity / 2 + 1;
    

    if (capacity > new_capacity || new_capacity >= (size_t) MAX_DATA_RANGE / v->element_size) {
            new_capacity = capacity;
    }

    new_mem = realloc(v->mem, new_capacity * v->element_size);

    if (new_mem == NULL) 
            return false;

    v->mem = new_mem;
    v->capacity = new_capacity;

    return true;
}

bool vector_push_back(vector* v, const void* element)
{
    assert(v != NULL);
    assert(element != NULL);
    
    if(v->element_num == v->capacity && vector_resize(v, v->element_num + 1) == false)
        return false;
    
    if(!memcpy(v->mem + v->element_num * v->element_size, element, v->element_size))
        return false;

    v->element_num++;
    return true;
}

bool vector_push_front(vector* v, const void* element)
{
    assert(v != NULL);
    assert(element != NULL);
    
    return vector_insert(v, 0, element);
}

bool vector_pop_back(vector* v)
{
    assert(v != NULL);
    assert(v->element_num >= 1);
    if(v->deleter)
        v->deleter(vector_back(v));
    v->element_num--;
    return true;
}

bool vector_pop_back_no_delete(vector* v)
{
    assert(v != NULL);
    assert(v->element_num >= 1);
    v->element_num--;
    return true;
}

bool vector_insert(vector* v, size_t idx, const void* element)
{
    assert(v != NULL);
        
    if(v->element_num == v->capacity && vector_resize(v, v->element_num + 1) == false)
        return false;

    if (!memmove(vector_at(v, idx + 1),
                 vector_at(v, idx),
                 v->element_size * (v->element_num - idx))) 
        return false;

    if (memcpy(vector_at(v, idx),
                      element,
                      v->element_size) == NULL) 
        return false;

    v->element_num++;

    return true;
}

bool vector_erase(vector* v, size_t idx)
{
    assert(v);
    assert(idx < v->element_num );

    if (v->deleter) {
        v->deleter(vector_at(v, idx));
    }

    if (!memmove(vector_at(v, idx), 
                 vector_at(v, idx + 1),
                 v->element_size * (v->element_num - idx))) 
        return false;

    v->element_num--;
    return true;
}

bool vector_erase_range(vector* v, size_t first_idx, size_t last_idx)
{
    assert(v);
    assert(first_idx < v->element_num );
    assert(last_idx < v->element_num );
    assert(first_idx <= last_idx );

    if (v->deleter != NULL) 
        for (size_t i = first_idx; i < last_idx; ++i)
            v->deleter(vector_at(v, i));

    if (!memmove(vector_at(v, first_idx),
                 vector_at(v, last_idx),
                 v->element_size * (v->element_num - last_idx))) 
        return false;

    v->element_num -= last_idx - first_idx;
    
    return true;

}

//Element access
void* vector_front(const vector* v)
{
    return vector_at(v, 0);
}

void* vector_back(const vector* v)
{
    return vector_at(v, (v->element_num - 1));
}

void* get_vector_element(const vector* v, const size_t idx)
{
    return vector_at(v, idx);
}

void* vector_at(const vector* v, size_t idx)
{
    assert(v != NULL);
    assert(v->mem != NULL);
    assert(idx < v->element_num);

    if(!v->element_size)
        return NULL;
    if(idx >= v->element_num)
        return NULL;

    return VECTOR_AT(v, idx);
}

//Information
size_t vector_size(const vector* v)
{
    assert(v != NULL);
    assert(v->mem != NULL);
    return v->element_num;
}

size_t vector_capacity(const vector* v)
{
    assert(v != NULL);
    assert(v->mem != NULL);
    return v->capacity;
}

bool vector_is_empty(const vector* v)
{
    return v->element_num == 0 ? true : false;
}

//iterator
void* vector_begin(const vector* v)
{
    return v->mem;
}

void* vector_end(const vector* v)
{
    return v->mem + v->element_num * v->element_size;
}

void* vector_iterator(const vector* v, const void* i)
{
    return (void*)((char*)i + v->element_size);
}

bool vector_clear(vector* v)
{
    if (!v) 
        return false;
    v->element_num = 0;
    return true;
}