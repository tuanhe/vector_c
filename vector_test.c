#include <stdio.h>
#include <stdint.h>

#include "vector.h"

typedef struct { 
    int a;
    int b;
    int c;
} my_struct;

#if 0
void iterate(vector(my_struct*) v)
{
    // Index style
    for (size_t i = 0; i < vector_size(v); i++)
        printf("%d ", v[i]->a);
    printf("\n"); 
    // Iterator style
    vector_iterator(my_struct*) it;
    for (it = vector_begin(v); it != vector_end(v); ++it)
        printf("%d  ", (*it)->a);
    printf("\n"); 
}

#endif

void iterate_print(vector* v)
{
    // Index style
    for (size_t i = 0; i < vector_size(v); i++){
        int *p = vector_at(v, i);
        printf("%d  ", *p);
    }
    printf("\n"); 
    printf("vector size : %ld   capacity : %ld  element size : %ld \n", 
                        v->element_num, v->capacity, v->element_size);
    // Iterator style
    //vector_iterator(my_struct*) it;
    //for (it = vector_begin(v); it != vector_end(v); ++it)
    //    printf("%d  ", (*it)->a);
    //printf("\n"); 
}

int main(void)
{
    vector* v1 =  vector_create(sizeof(my_struct), NULL);
    printf("v1 num  %ld \n", v1->element_num );
    printf("v1 capa %ld \n", v1->capacity );
    printf("v1 size %ld \n", v1->element_size );
    
    vector* v2 =  vector_create(sizeof(int), NULL);
    printf("v2 num  %ld \n",  v2->element_num );
    printf("v2 capa %ld \n", v2->capacity );
    printf("v2 size %ld \n", v2->element_size );

    for(uint32_t i = 0; i < 8; i++) 
    {
        uint32_t data = i*2 + 7;
        vector_push_back(v2, &data);
    }

    iterate_print(v2);
        
    vector_pop_back(v2);
    iterate_print(v2);
    
    uint32_t element = 24;
    vector_insert(v2, 3, &element);
    iterate_print(v2);

    vector_push_front(v2, &element);
    iterate_print(v2);
    
    vector_erase(v2, 4);
    iterate_print(v2);
    
    vector_erase_range(v2, 4, 7);
    iterate_print(v2);

    vector_destroy(v2);

    #if 0
    // Access elements like normal arrays
    printf("%d\n", my_vec[0]);

    // Done with it, free memory
    vector_free(my_vec);
    
    vector(my_struct*) v = NULL;
    my_struct *obj = (my_struct*)malloc(sizeof(my_struct));
    obj->a = 6;
    obj->b = 7;
    obj->c = 8;
    vector_push_back(v, obj);
    my_struct *obj2 = (my_struct*)malloc(sizeof(my_struct));
    obj2->a = 87;
    obj2->b = 87;
    obj2->c = 87;
    vector_push_back(v, obj2);
    printf("%d\n", v[0]->a);
    printf("%d\n", v[0]->b);
    printf("%d\n", v[0]->c);

    iterate(v);
    vector_free(v);

    #endif
}