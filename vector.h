#ifndef _VECTOR_H_
#define _VECTOR_H_

#include <stdlib.h>
#include <assert.h>

#define vector(type) type*

typedef struct _v_h
{
    size_t size; // Current stored elements
    size_t capacity;  // Current max capacity
} _v_h;

#define _vector_get_header(vec) (((_v_h*)vec) - 1)

#define _vector_capacity(vec) (vec ? _vector_get_header(vec)->capacity : 0)

#define _vector_set_capacity(vec, cp) _vector_get_header(vec)->capacity = cp

#define _vector_set_size(vec, sz) _vector_get_header(vec)->size = sz

#define vector_size(vec) (vec ? _vector_get_header(vec)->size : 0)

#define vector_back(vec) vec[vector_size(vec)]

#define vector_mid(vec) vec[vector_size(vec) / 2]

#define vector_front(vec) vec[0]

#define vector_is_emtpy(vec) !vector_size(vec)

#define vector_begin(vec) vec

#define vector_end(vec) (vec + vector_size(vec))

#define vector_iterator(type) type *

#define vector_pop_back(vec) vector_erase(vec, vec_size(vec))

#define _vector_create(vec, bytes)                                        \
    do {                                                                  \
        _v_h *h = (_v_h*)malloc(bytes * sizeof(*vec) + sizeof(_v_h));     \
        assert(h);                                                        \
        vec = (void*)&h[1];                                               \
        _vector_set_capacity(vec, 1);                                     \
        _vector_set_size(vec, 0);                                         \
    } while (0)

#define _vector_resize(vec, cap)                                          \
    do {                                                                  \
        _v_h *h = (_v_h*)realloc(_vector_get_header(vec),                 \
            cap * sizeof(*vec) + sizeof(_v_h));                           \
        assert(h);                                                        \
        vec = (void*)&h[1];                                               \
        _vector_set_capacity(vec, cap);                                   \
    } while (0)

#define vector_free(vec)                                                  \
    do {                                                                  \
        free(_vector_get_header(vec));                                    \
        vec = NULL;                                                       \
    } while (0)

#define vector_reserve(vec, bytes)                                        \
    do {                                                                  \
        assert(bytes >= 0);                                               \
        if (bytes != 0) {                                                 \
            if (!vec)                                                     \
                _vector_create(vec, bytes);                               \
            else                                                          \
                _vector_resize(vec, bytes);                               \
        }                                                                 \
    } while (0)

#define vector_push_back(vec, data)                                       \
    do {                                                                  \
        if (vector_size(vec) == _vector_capacity(vec)) {                  \
            if (!vec)                                                     \
                _vector_create(vec, 1);                                   \
            else                                                          \
                _vector_resize(vec, vector_size(vec) * 2);                \
        }                                                                 \
        vec[vector_size(vec)] = data;                                     \
        _vector_set_size(vec, vector_size(vec) + 1);                      \
    } while (0)

#define vector_erase(vec, idx)                                            \
    do {                                                                  \
        for (size_t i = idx; i < vector_size(vec) - 1; i++)               \
            vec[i] = vec[i + 1];                                          \
        _vector_set_size(vec, vector_size(vec) - 1);                      \
    } while (0)

#define vector_insert(vec, idx, data)                                     \
    do {                                                                  \
        assert(idx >= 0 && idx <= vector_size(vec));                      \
        if (!vec) {                                                       \
            vector_push_back(vec, data);                                  \
        } else {                                                          \
            if (vector_size(vec) == _vector_capacity(vec))                \
                _vector_resize(vec, vector_size(vec) * 2);                \
            for (size_t i = vector_size(vec); i > (size_t)idx; i--)       \
                vec[i] = vec[i - 1];                                      \
            vec[idx] = data;                                              \
            _vector_set_size(vec, vector_size(vec) + 1);                  \
        }                                                                 \
    } while (0)

#define vector_insert_many(dst, idx, src, src_len)                        \
    do {                                                                  \
        assert(idx >= 0 && idx <= vector_size(dst));                      \
        if (!dst) {                                                       \
            for (size_t i = 0; i < src_len; i++)                          \
                vector_push_back(dst, src[i]);                            \
        } else {                                                          \
            if (vector_size(dst) + src_len >= _vector_capacity(dst)) {    \
                size_t resize_by = _vector_capacity(dst) * 2;             \
                while (resize_by < vector_size(dst) + src_len)            \
                    resize_by *= 2;                                       \
                _vector_resize(dst, resize_by);                           \
            }                                                             \
            size_t i;                                                     \
            for (i = vector_size(dst) + src_len - 1; i > idx; i--)        \
                dst[i] = dst[i - src_len];                                \
            for (size_t j = idx, i = 0; j < src_len + idx; j++, i++)      \
                dst[j] = src[i];                                          \
            _vector_set_size(dst, vector_size(dst) + src_len);            \
        }                                                                 \
    } while (0)

#endif // VECTOR_H