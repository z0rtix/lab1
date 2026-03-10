#ifndef DYNAMICARRAY_H
#define DYNAMICARRAY_H

#define DEFAULT_CAPACITY 4

typedef struct TypeInfo {
    int element_size;
    
    void (*element_free)(void*);
    int (*element_compare)(const void*, const void*);
    void (*element_print)(const void*);
    void *(*element_copy)(const void*);
} TypeInfo;

typedef struct DynamicArray {
    void *data;
    int size;
    int capacity;

    const TypeInfo *type;
} DynamicArray;

// Core
DynamicArray *create(const TypeInfo *type);

void destroy(DynamicArray *array);
void clear(DynamicArray *array);

void push(DynamicArray *array, const void *element);
void pop(DynamicArray *array);
void remove_at(DynamicArray *array, int index);

void *get(const DynamicArray *array, int index);
void set(DynamicArray *array, int index, const void *element);

int size(const DynamicArray *array);
int empty(const DynamicArray *array);
int capacity(const DynamicArray *array);

void reserve(DynamicArray *array, int new_capacity);
void shrink_to_fit(DynamicArray *array);

void print_array(const DynamicArray *array);

// Algorithms
void sort(DynamicArray* arr);

DynamicArray *copy(const DynamicArray *array);
DynamicArray *map(const DynamicArray *array, void (*func)(void*));
DynamicArray *where(const DynamicArray *array, int (*predicate)(const void*));
DynamicArray *concat(const DynamicArray *array1, const DynamicArray *array2);

#endif