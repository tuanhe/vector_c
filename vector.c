#include "vector.h"
#include <stdlib.h>
#include <assert.h>
#include <string.h>

#define VECTOR_ELEMENT(v, i) ((void *) ((char *) (v)->mem + (i) * (v)->object_size))

vector* vector_create(const size_t object_size)
{
    vector* v = (vector*)malloc(sizeof(vector));

    if(!v) 
        return NULL;
    v->element_num = 0;
    v->object_size = object_size;
    v->capacity = sizeof(size_t);
    v->mem = malloc(v->capacity * object_size);
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

        assert(v->object_size > 0);

        if (capacity >= (size_t)-1 / v->object_size)
                return false;

        /* Growth factor 2 for small vectors, 1.5 for larger */
        if (v->capacity < (4096 / v->object_size)) 
                new_capacity = v->capacity + v->capacity + 1;
        else 
                new_capacity = v->capacity + v->capacity / 2 + 1;
        

        if (capacity > new_capacity || new_capacity >= (size_t) -1 / v->object_size) {
                new_capacity = capacity;
        }

        new_mem = realloc(v->mem, new_capacity * v->object_size);

        if (new_mem == NULL) 
                return false;

        v->mem = new_mem;
        v->capacity = new_capacity;

    return true;
}

bool vector_push_back(vector* v, const void* data)
{
        assert(v != NULL);
        assert(data != NULL);
    
    if(v->element_num == v->capacity && vector_resize(v, v->element_num + 1) == false)
        return false;
    
    if(!memcpy(v->mem + v->element_num * v->object_size, data, v->capacity))
        return false;

    v->element_num++;
    return true;
}

bool vector_pop_back(vector* v)
{
    //if(v->deleter)
    //    v->deleter(vector_back(v));
    v->element_num--;
    return true;
}

void* get_vector_data(const vector* v, const size_t idx)
{
    assert(v != NULL);
    assert(v->mem != NULL);

    if (idx >= v->element_num) {
            return NULL;
    }

    return VECTOR_ELEMENT(v, idx);
}

void* vector_front(const vector* v)
{
    assert(v != NULL);
    assert(v->mem != NULL);

    if (v->element_num == 0)
        return NULL;
        
    return v->mem;
}

void* vector_back(const vector* v)
{
    assert(v != NULL);
    assert(v->mem != NULL);

    if (v->object_size == 0) {
            return NULL;
    }
    return (void *)((char *)(v->mem + (v->element_num - 1) * (v->object_size)));
}

size_t get_vector_size(const vector* v)
{
    assert(v != NULL);
    assert(v->mem != NULL);
    return v->element_num;
}

size_t get_vector_capacity(const vector* v)
{
    assert(v != NULL);
    assert(v->mem != NULL);
    return v->capacity;
}


//iterator
void* vector_begin(const vector* v)
{
    return v->mem;
}

void* vector_end(const vector* v)
{
    return v->mem + v->element_num * v->object_size;
}

void* vector_next(const vector* v, const void* i)
{
    return (char*)i + v->object_size;
}