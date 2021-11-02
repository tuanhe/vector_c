#include <stdio.h>
#include <stdint.h>

#include "vector.h"

typedef struct { 
    int a;
    int b;
    int c;
} my_struct;

typedef struct { 
    int a;
    int b;
    char* name ;
} str_struct;

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

void iterate_print_struct(vector* v)
{
    // Index style
    for (size_t i = 0; i < vector_size(v); i++){
        my_struct *p = (my_struct*)vector_at(v, i);
        printf("a:%d  b:%d  c:%d\n", p->a, p->b, p->c);
    }
    printf("vector size : %ld   capacity : %ld  element size : %ld \n", 
                        v->element_num, v->capacity, v->element_size);
}

void iterate_print_strstruct(vector* v)
{
    // Index style
    for (size_t i = 0; i < vector_size(v); i++){
        str_struct *p = (str_struct*)vector_at(v, i);
        printf("a:%d  b:%d  c:%s\n", p->a, p->b, p->name);
    }
    printf("vector size : %ld   capacity : %ld  element size : %ld \n", 
                        v->element_num, v->capacity, v->element_size);
}

int main(void)
{

    
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


    vector* v1 =  vector_create(sizeof(my_struct), NULL);
    printf("v1 num  %ld \n", v1->element_num );
    printf("v1 capa %ld \n", v1->capacity );
    printf("v1 size %ld \n", v1->element_size );

    my_struct test;
    test.a = 12;
    test.b = 81;
    test.c = 0x1c;
    vector_push_back(v1, &test);
    test.c = 0xc;
    vector_push_back(v1, &test);
    test.a = 0xac;
    vector_insert(v1, 0, &test);

    iterate_print_struct(v1);
    vector_destroy(v1);

    vector* v3 =  vector_create(sizeof(str_struct), NULL);
    printf("v3 num  %ld \n", v3->element_num );
    printf("v3 capa %ld \n", v3->capacity );
    printf("v3 size %ld \n", v3->element_size );

    str_struct st;
    for(uint32_t i = 0; i < 3; ++i)
    {
        char a[10];
        st.a = i +8;
        st.b = i*3+2;
        snprintf(a, sizeof(a), "loop_%d", i);
        st.name = a;   
        vector_push_back(v3, &st);
    }

    st.name = "checkit";
    vector_push_back(v3, &st);

    vector_erase(v3, 0);

    iterate_print_strstruct(v3);
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