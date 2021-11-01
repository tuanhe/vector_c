#include <stdio.h>
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


int main(void)
{
    #if 0
    // Define the vector object
    vector(int) my_vec = NULL;
    
    // Add an element
    vector_push_back(my_vec, 3);
    
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