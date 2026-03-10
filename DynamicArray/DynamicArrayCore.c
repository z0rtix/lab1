#include "DynamicArray.h"
#include <stdlib.h>
#include <string.h>
#include <stdio.h>

DynamicArray *create(const TypeInfo *type) {
    DynamicArray *array = malloc(sizeof(DynamicArray));
    if (array == NULL) return NULL;

    array->data = malloc(type->element_size * DEFAULT_CAPACITY);
    if (array->data == NULL) {
        free(array);
        return NULL;
    }

    array->size = 0;
    array->capacity = DEFAULT_CAPACITY;
    array->type = type;

    return array;
}

void destroy(DynamicArray *array) {
    if (array == NULL) return;

    if (array->type->element_free != NULL) {
        for (int i = 0; i < array->size; i++) {
            void *element = (char*)array->data + i * array->type->element_size;
            array->type->element_free(element);
        }
    }

    free(array->data);
    free(array);
}

void clear(DynamicArray *array) {
    if (array == NULL) return;

    if (array->type->element_free != NULL) {
        for (int i = 0; i < array->size; i++) {
            void *element = (char*)array->data + i * array->type->element_size;
            array->type->element_free(element);
        }
    }

    void *new_data = malloc(array->type->element_size * DEFAULT_CAPACITY);
    if (new_data == NULL) return;
    free(array->data);
    array->size = 0;
    array->capacity = DEFAULT_CAPACITY;
    array->data = new_data;
}

void push(DynamicArray *array, const void *element) {
    if (array == NULL || element == NULL) return;

    if (array->size >= array->capacity) {
        int new_capacity = array->capacity * 2;
        void *new_data = malloc(new_capacity * array->type->element_size);
        
        if (new_data == NULL) return;

        memcpy(new_data, array->data , array->size * array->type->element_size);
        free(array->data);
        array->data = new_data;
        array->capacity = new_capacity;
    }

    void *last_element = (char*)array->data + array->size * array->type->element_size;
    memcpy(last_element, element, array->type->element_size);
    array->size++;
}

void pop(DynamicArray *array) {
    if (array == NULL || array->size == 0) return;

    void *last_element = (char*)array->data + (array->size - 1) * array->type->element_size;
    if (array->type->element_free != NULL) {
        array->type->element_free(last_element);
    }
    array->size--;
}

void remove_at(DynamicArray *array, int index) {
    if (array == NULL || index < 0 || index >= array->size) return;

    char *element_to_remove = (char*)array->data + index * array->type->element_size;
    if (array->type->element_free != NULL) {
        array->type->element_free(element_to_remove);
    }
    int elements_after = array->size - index - 1;
    int bytes_per_element = array->type->element_size;

    for (int move_index = 0; move_index < elements_after; move_index++) {
        char *source = (char*)array->data + (index + 1 + move_index) * bytes_per_element;
        char *destination = (char*)array->data + (index + move_index) * bytes_per_element;
        for (int byte = 0; byte < bytes_per_element; byte++) {
            destination[byte] = source[byte];
        }
    }
    array->size--;
}

void *get(const DynamicArray *array, int index) {
    if (array == NULL || index < 0 || index >= array->size) return NULL;

    return (char*)array->data + index * array->type->element_size;
}

void set(DynamicArray *array, int index, const void *element) {
    if (array == NULL || index < 0 || index >= array->size || element == NULL) return;

    void *el = (char*)array->data + index * array->type->element_size;
    if (array->type->element_free != NULL) {
        array->type->element_free(el);
    }

    memcpy(el, element, array->type->element_size);
}

int size(const DynamicArray *array) {
    if (array == NULL) return 0;
    return array->size;
}

int empty(const DynamicArray *array) {
    if (array == NULL) return 0;
    return array->size == 0;
}

int capacity(const DynamicArray *array) {
    if (array == NULL) return 0;
    return array->capacity;
}

void reserve(DynamicArray *array, int new_capacity) {
    if (array == NULL || new_capacity <= array->capacity) return;

    void *new_data = realloc(array->data, new_capacity * array->type->element_size);
    if (new_data == NULL) return;
    array->data = new_data;
    array->capacity = new_capacity;
}

void shrink_to_fit(DynamicArray *array) {
    if (array == NULL || array->data == NULL || array->size == array->capacity) return;

    void *new_data = realloc(array->data, array->size * array->type->element_size);
    if (new_data == NULL) return;
    array->data = new_data;
    array->capacity = array->size;
}

void print_array(const DynamicArray *array) {
    if (array == NULL || array->type->element_print == NULL) {
        printf("[]\n");
        return;
    }
    
    printf("[");
    for (int i = 0; i < size(array); i++) {
        void *element = (char*)array->data + i * array->type->element_size;
        array->type->element_print(element);
        if (i < size(array) - 1) {
            printf(", ");
        }
    }
    printf("]\n");
}