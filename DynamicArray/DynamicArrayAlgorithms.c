#include "DynamicArray.h"
#include <stdlib.h>
#include <string.h>
#include <stdio.h>


void sort(DynamicArray* array) {
    if (array == NULL || array->size < 2 || array->type->element_compare == NULL) return;

    for (int i = 0; i < array->size - 1; i++) {
        for (int j = 0; j < array->size - 1 - i; j++) {
            void *current_element = (char*)array->data + j * array->type->element_size;
            void *next_element = (char*)array->data + (j + 1) * array->type->element_size;

            if (array->type->element_compare(current_element, next_element) > 0) {
                char *temp = malloc(array->type->element_size);
                if (temp == NULL) return;
                memcpy(temp, current_element, array->type->element_size);
                memcpy(current_element, next_element, array->type->element_size);
                memcpy(next_element, temp, array->type->element_size);
                free(temp);
            }
        }
    }
}

DynamicArray *copy(const DynamicArray *array) {
    if (array == NULL) return NULL;
    DynamicArray *copy_of_array = create(array->type);
    if (copy_of_array == NULL) return NULL;
    reserve(copy_of_array, array->size);
    for (int i = 0; i < array->size; i++) {
        void *current_of_array = (char*)array->data + i * array->type->element_size;
        void *copy_of_current = array->type->element_copy(current_of_array);
        if (copy_of_current == NULL) {
            destroy(copy_of_array);
            return NULL;
        }
        push(copy_of_array, copy_of_current);
    }

    return copy_of_array;
}

DynamicArray* map(const DynamicArray *array, void (*func)(void*)) {
    if (array == NULL || func == NULL) return NULL;
    DynamicArray *array_map = copy(array);
    if (array_map == NULL) return NULL;
    for (int i = 0; i < array_map->size; i++) {
        void *current = (char*)array_map->data + i * array_map->type->element_size;
        func(current);
    }

    return array_map;
}


DynamicArray* where(const DynamicArray* array, int (*predicate)(const void*)) {
    if (array == NULL || predicate == NULL) return NULL;
    DynamicArray* array_where = create(array->type);
    if (array_where == NULL) return NULL;

    for (int i = 0; i < array->size; i++) {
        void* el = (char*)array->data + i * array->type->element_size;
        if (predicate(el)) {
            void* copy = array->type->element_copy(el);
            if (copy == NULL) {
                destroy(array_where);
                return NULL;
            }
            push(array_where, copy);
        }
    }

    return array_where;
}

DynamicArray* concat(const DynamicArray* array1, const DynamicArray* array2) {
    if (array1 == NULL || array2 == NULL || array1->type != array2->type) return NULL;

    DynamicArray* concat_array = copy(array1);
    if (concat_array == NULL) return NULL;

    for (int i = 0; i < array2->size; i++) {
        void* current_array2 = (char*)array2->data + i * array2->type->element_size;
        void* copy_of_current = array2->type->element_copy(current_array2);
        if (copy_of_current == NULL) {
            destroy(concat_array);
            return NULL;
        }
        push(concat_array, copy_of_current);
    }

    return concat_array;
}
