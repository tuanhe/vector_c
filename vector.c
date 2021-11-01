#include "vector.h"
#include <stdlib.h>
#include <assert.h>
#include <string.h>

#define VECTOR_ELEMENT(v, i) ((void *) ((char *) (v)->mem + (i) * (v)->object_size))

struct _vector
{
    size_t element_num;
    size_t capacity;
    size_t object_size;
    void* mem;
    vector_deleter* deleter;
};

vector* vector_create(const size_t object_size, vector_deleter* deleter)
{
    vector* v = (vector*)malloc(sizeof(vector));

    if(!v) 
        return NULL;
    v->element_num = 0;
    v->object_size = object_size;
    v->capacity = sizeof(size_t);
    v->deleter = deleter;
    v->mem = malloc(v->capacity * object_size);
    if (v->mem == NULL)
    {
        free(v);
        return NULL;
    }
    
    return v;
}

void vector_release(vector* v)
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

bool vector_insert(vector* v, size_t idx, const void* data)
{
    assert(v != NULL);
        
    if(v->element_num == v->capacity && vector_resize(v, v->element_num + 1) == false)
        return false;

    if (!memmove(vector_at(v, idx + 1),
                 vector_at(v, idx),
                 v->object_size * (v->element_num - idx))) 
        return false;

    if (memcpy(vector_at(v, idx),
                      data,
                      v->object_size) == NULL) 
        return false;

    v->element_num++;

    return true;
}

bool vector_erase(vector* v, size_t idx)
{
    if (v->deleter) {
        v->deleter(vector_at(v, idx));
    }

    if (!memmove(vector_at(v, idx), vector_at(v, idx + 1),
                        v->object_size * (v->element_num - idx))) 
    return false;

    v->element_num--;
    return true;
}

bool vector_erase_range(vector* v, size_t first_idx, size_t last_idx)
{
    if (v->deleter != NULL) 
        for (size_t i = first_idx; i < last_idx; ++i)
            v->deleter(vector_at(v, i));

    if (!memmove(vector_at(v, first_idx),
                 vector_at(v, last_idx),
                 v->object_size * (v->element_num - last_idx))) 
        return false;

    v->element_num -= last_idx - first_idx;
    
    return true;

}

//Element access
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

void* get_vector_data(const vector* v, const size_t idx)
{
    assert(v != NULL);
    assert(v->mem != NULL);

    if (idx >= v->element_num) {
            return NULL;
    }

    return VECTOR_ELEMENT(v, idx);
}

void* vector_at(const vector* v, size_t idx)
{
    return get_vector_data(v, idx);
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


bool vector_empty(vector* v)
{
    assert(v != NULL);
	assert(v->mem != NULL);

	v->element_num == 0;

    return true;
}

bool vector_clear(vector* v)
{
    if (!v) 
        return false;
    if (v->deleter)
        for (size_t i = 0; i < v->element_num; v++)
            v->deleter(vector_at(v, i));
    v->element_num = 0;
    return true;
}