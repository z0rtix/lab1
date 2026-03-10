#include "tests_of_int.h"
#include "../DynamicArray/DynamicArray.h"
#include "../utils/utils.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <assert.h>
#include <time.h>

void test_create_destroy() {
    printf("Тест create/destroy -- ");
    DynamicArray *arr = create(&INT_TYPE);

    assert(arr != NULL);
    assert(size(arr) == 0);
    assert(empty(arr) == 1);

    destroy(arr);
    printf("✅\n");
}

void test_clear() {
    printf("Тест clear -- ");
    DynamicArray *arr = create(&INT_TYPE);
    int x = 42, y = 7, z = 99;
    push(arr, &x);
    push(arr, &y);
    push(arr, &z);
    
    assert(size(arr) == 3);
    
    clear(arr);
    
    assert(size(arr) == 0);
    assert(capacity(arr) == DEFAULT_CAPACITY);
    assert(arr->data != NULL);
    
    destroy(arr);
    printf("✅\n");
}

void test_push_get() {
    printf("Тест push/get -- ");
    DynamicArray *arr = create(&INT_TYPE);
    int a = 42, b = 7, c = 100;
    push(arr, &a);
    push(arr, &b);
    push(arr, &c);
    
    assert(size(arr) == 3);
    assert(*(int*)get(arr, 0) == 42);
    assert(*(int*)get(arr, 1) == 7);
    assert(*(int*)get(arr, 2) == 100);
    
    destroy(arr);
    printf("✅\n");
}

void test_pop() {
    printf("Тест pop -- ");
    DynamicArray *arr = create(&INT_TYPE);
    int x = 42, y = 7, z = 99;
    push(arr, &x);
    push(arr, &y);
    push(arr, &z);
    
    assert(size(arr) == 3);
    assert(*(int*)get(arr, 2) == 99);
    
    pop(arr);
    assert(size(arr) == 2);
    assert(*(int*)get(arr, 1) == 7);
    
    pop(arr);
    assert(size(arr) == 1);
    assert(*(int*)get(arr, 0) == 42);
    
    pop(arr);
    assert(size(arr) == 0);
    
    pop(arr);
    assert(size(arr) == 0);
    
    destroy(arr);
    printf("✅\n");
}

void test_remove_at() {
    printf("Тест remove_at -- ");
    DynamicArray *arr = create(&INT_TYPE);
    int vals[] = {10, 20, 30, 40, 50};
    for (int i = 0; i < 5; i++) push(arr, &vals[i]);
    assert(size(arr) == 5);

    remove_at(arr, 2);
    assert(size(arr) == 4);
    assert(*(int*)get(arr, 0) == 10);
    assert(*(int*)get(arr, 1) == 20);
    assert(*(int*)get(arr, 2) == 40);
    assert(*(int*)get(arr, 3) == 50);
    
    remove_at(arr, 0);
    assert(size(arr) == 3);
    assert(*(int*)get(arr, 0) == 20);
    assert(*(int*)get(arr, 1) == 40);
    assert(*(int*)get(arr, 2) == 50);
    
    remove_at(arr, 2);
    assert(size(arr) == 2);
    assert(*(int*)get(arr, 0) == 20);
    assert(*(int*)get(arr, 1) == 40);
    
    remove_at(arr, -1);
    remove_at(arr, 5);
    assert(size(arr) == 2);
    destroy(arr);
    printf("✅\n");
}

void test_set() {
    printf("Тест set -- ");
    DynamicArray *arr = create(&INT_TYPE);
    int a = 42, b = 7;
    push(arr, &a);
    push(arr, &b);
    int new_val = 99;
    set(arr, 0, &new_val);
    
    assert(*(int*)get(arr, 0) == 99);
    assert(*(int*)get(arr, 1) == 7);
    
    destroy(arr);
    printf("✅\n");
}

void test_reserve() {
    printf("Тест reserve -- ");
    DynamicArray *arr = create(&INT_TYPE);
    int initial_capacity = capacity(arr);

    reserve(arr, initial_capacity + 10);    
    assert(capacity(arr) >= initial_capacity + 10);
    assert(size(arr) == 0);
    
    int x = 42;
    push(arr, &x);
    assert(capacity(arr) >= initial_capacity + 10);
    assert(size(arr) == 1);
    
    reserve(arr, 1);
    assert(capacity(arr) >= initial_capacity + 10);
    
    destroy(arr);
    printf("✅\n");
}

void test_shrink_to_fit() {
    printf("Тест shrink_to_fit -- ");    
    DynamicArray *arr = create(&INT_TYPE);
    for (int i = 0; i < 20; i++) {
        push(arr, &i);
    }

    int before_capacity = capacity(arr);
    assert(before_capacity > 20);
    
    for (int i = 0; i < 10; i++) {
        pop(arr);
    }
    assert(size(arr) == 10);
    
    shrink_to_fit(arr);
    assert(capacity(arr) == 10);
    assert(*(int*)get(arr, 0) == 0);
    assert(*(int*)get(arr, 9) == 9);
    
    destroy(arr);
    printf("✅\n");
}

void test_sort() {
    printf("Тест sort -- ");
    DynamicArray *arr = create(&INT_TYPE);
    int vals[] = {42, 7, 100, 1};
    for (int i = 0; i < 4; i++) {
        push(arr, &vals[i]);
    }
    sort(arr);
    int prev = *(int*)get(arr, 0);
    for (int i = 1; i < size(arr); i++) {
        int curr = *(int*)get(arr, i);
        assert(prev <= curr);
        prev = curr;
    }
    destroy(arr);
    printf("✅\n");
}

void test_map() {
    printf("Тест map -- ");
    DynamicArray *arr = create(&INT_TYPE);
    int vals[] = {1, 2, 3, 4};
    for (int i = 0; i < 4; i++) {
        push(arr, &vals[i]);
    }
    DynamicArray *squared = map(arr, int_map_square);
    
    assert(size(squared) == 4);
    assert(*(int*)get(squared, 0) == 1);
    assert(*(int*)get(squared, 1) == 4);
    assert(*(int*)get(squared, 2) == 9);
    assert(*(int*)get(squared, 3) == 16);
    
    destroy(arr);
    destroy(squared);
    printf("✅\n");
}

void test_where() {
    printf("Тест where -- ");
    DynamicArray *arr = create(&INT_TYPE);
    int vals[] = {1, 2, 3, 4, 5, 6};
    for (int i = 0; i < 6; i++) {
        push(arr, &vals[i]);
    }
    DynamicArray *even = where(arr, int_is_even);
    
    assert(size(even) == 3);
    assert(*(int*)get(even, 0) == 2);
    assert(*(int*)get(even, 1) == 4);
    assert(*(int*)get(even, 2) == 6);
    
    destroy(arr);
    destroy(even);
    printf("✅\n");
}

void test_concat() {
    printf("Тест concat -- ");
    DynamicArray *arr1 = create(&INT_TYPE);
    DynamicArray *arr2 = create(&INT_TYPE);
    int a1[] = {1, 2, 3};
    int a2[] = {4, 5, 6};
    for (int i = 0; i < 3; i++) push(arr1, &a1[i]);
    for (int i = 0; i < 3; i++) push(arr2, &a2[i]);
    DynamicArray *arr3 = concat(arr1, arr2);
    
    assert(size(arr3) == 6);
    assert(*(int*)get(arr3, 0) == 1);
    assert(*(int*)get(arr3, 1) == 2);
    assert(*(int*)get(arr3, 2) == 3);
    assert(*(int*)get(arr3, 3) == 4);
    assert(*(int*)get(arr3, 4) == 5);
    assert(*(int*)get(arr3, 5) == 6);
    
    destroy(arr1);
    destroy(arr2);
    destroy(arr3);
    printf("✅\n");
}

void test_concat_type_mismatch() {
    printf("Тест concat type mismatch -- ");
    DynamicArray *int_arr = create(&INT_TYPE);
    DynamicArray *str_arr = create(&STRING_TYPE);
    
    int x = 42;
    push(int_arr, &x);
    
    char *s = strdup("test");
    push(str_arr, &s);
    
    DynamicArray *result = concat(int_arr, str_arr);
    assert(result == NULL);
    
    destroy(int_arr);
    destroy(str_arr);
    printf("✅\n");
}

void test_copy() {
    printf("Тест copy -- ");    
    DynamicArray *original = create(&INT_TYPE);
    int values[] = {10, 20, 30, 40, 50};
    for (int i = 0; i < 5; i++) {
        push(original, &values[i]);
    }
    
    DynamicArray *clone = copy(original);
    assert(size(original) == size(clone));
    assert(size(original) == capacity(clone));
    
    for (int i = 0; i < size(original); i++) {
        int orig_val = *(int*)get(original, i);
        int clone_val = *(int*)get(clone, i);
        assert(orig_val == clone_val);
    }
    assert(original->data != clone->data);
    
    int new_val = 999;
    set(original, 2, &new_val);
    assert(*(int*)get(original, 2) == 999);
    assert(*(int*)get(clone, 2) == 30);  
    
    int another_val = 777;
    set(clone, 4, &another_val);
    assert(*(int*)get(clone, 4) == 777);
    assert(*(int*)get(original, 4) == 50);
    
    destroy(original);
    destroy(clone);
    printf("✅\n");
}

void test_boundaries() {
    printf("Тест граничных случаев -- ");
    
    DynamicArray *arr = create(&INT_TYPE);
    assert(arr != NULL);
    assert(size(arr) == 0);
    assert(empty(arr) == 1);
    assert(capacity(arr) == DEFAULT_CAPACITY);
    assert(get(arr, 0) == NULL);
    assert(get(arr, -1) == NULL);
    assert(get(arr, 5) == NULL);
    
    pop(arr);
    assert(size(arr) == 0);
    
    remove_at(arr, 0);
    assert(size(arr) == 0);
    
    int x = 42;
    push(arr, &x);
    assert(size(arr) == 1);
    assert(empty(arr) == 0);
    assert(*(int*)get(arr, 0) == 42);
    assert(capacity(arr) >= 1);
    assert(get(arr, -1) == NULL);
    assert(get(arr, 1) == NULL);
    assert(get(arr, 100) == NULL);

    int new_val = 99;
    set(arr, -1, &new_val);
    assert(*(int*)get(arr, 0) == 42);
    
    set(arr, 1, &new_val);
    assert(*(int*)get(arr, 0) == 42);
    
    set(arr, 100, &new_val);
    assert(*(int*)get(arr, 0) == 42);
    
    int old_capacity = capacity(arr);
    reserve(arr, 1);
    assert(capacity(arr) == old_capacity);
    
    reserve(arr, old_capacity + 10);
    assert(capacity(arr) >= old_capacity + 10);
    assert(size(arr) == 1);
    assert(*(int*)get(arr, 0) == 42);
    
    int current_capacity = capacity(arr);
    for (int i = 1; i < current_capacity; i++) {
        push(arr, &i);
    }
    assert(size(arr) == current_capacity);
    assert(capacity(arr) == current_capacity);
    
    int last = 999;
    push(arr, &last);
    assert(size(arr) == current_capacity + 1);
    assert(capacity(arr) > current_capacity);
    assert(*(int*)get(arr, size(arr) - 1) == 999);
    
    int old_size = size(arr);
    pop(arr);
    assert(size(arr) == old_size - 1);
    assert(get(arr, old_size - 1) == NULL);
    
    int first_value = *(int*)get(arr, 0);
    remove_at(arr, 0);
    assert(size(arr) == old_size - 2);
    assert(*(int*)get(arr, 0) != first_value);
    
    int last_index = size(arr) - 1;
    remove_at(arr, last_index);
    assert(size(arr) == old_size - 3);
    assert(get(arr, last_index) == NULL);
    
    clear(arr);
    assert(size(arr) == 0);
    assert(capacity(arr) == DEFAULT_CAPACITY);
    assert(arr->data != NULL);
    
    for (int i = 0; i < 20; i++) push(arr, &i);
    int before_shrink_capacity = capacity(arr);
    assert(before_shrink_capacity > 20);
    
    for (int i = 0; i < 10; i++) pop(arr);
    assert(size(arr) == 10);
    
    shrink_to_fit(arr);
    assert(capacity(arr) == 10);
    assert(size(arr) == 10);
    
    for (int i = 0; i < 10; i++) {
        assert(*(int*)get(arr, i) == i);
    }

    destroy(arr);    
    printf("✅\n");
}

void test_10m_operations() {
    printf("Тест 10m operations -- ");
    clock_t start = clock();
    DynamicArray *arr = create(&INT_TYPE);

    int a[] = {1, 2, 3, 4, 5, 6, 7, 8, 9, 10};
    for (int i = 0; i < 10000000; i++) {
        push(arr, &a[i % 10]);
    }

    destroy(arr);
    clock_t end = clock();
    double time_spent = (double)(end - start) / CLOCKS_PER_SEC;
    printf("✅ (%.4f сек)\n", time_spent);
}

void test_int_arrays() {
    printf("Тест массива массивов int -- ");
    clock_t start = clock();
    DynamicArray *arr_of_arrs = create(&ARRAY_TYPE);
    assert(arr_of_arrs != NULL);
    assert(size(arr_of_arrs) == 0);

    DynamicArray *row1 = create(&INT_TYPE);
    push(row1, &(int){1});
    push(row1, &(int){2});
    push(row1, &(int){3});
    assert(size(row1) == 3);
    assert(*(int*)get(row1, 0) == 1);
    assert(*(int*)get(row1, 2) == 3);

    DynamicArray *row2 = create(&INT_TYPE);
    push(row2, &(int){4});
    push(row2, &(int){5});
    push(row2, &(int){6});
    assert(size(row2) == 3);

    DynamicArray *row3 = create(&INT_TYPE);
    push(row3, &(int){4});
    push(row3, &(int){5});
    push(row3, &(int){6});
    assert(size(row3) == 3);

    DynamicArray *row4 = create(&INT_TYPE);
    push(row4, &(int){7});
    push(row4, &(int){8});
    push(row4, &(int){9});
    assert(size(row4) == 3);

    DynamicArray *row5 = create(&INT_TYPE);
    push(row5, &(int){11});
    push(row5, &(int){12});
    push(row5, &(int){13});
    push(row5, &(int){133});
    assert(size(row5) == 4);
    assert(*(int*)get(row5, 3) == 133);

    push(arr_of_arrs, &row1);
    push(arr_of_arrs, &row2);
    push(arr_of_arrs, &row3);
    push(arr_of_arrs, &row4);
    push(arr_of_arrs, &row5);
    
    assert(size(arr_of_arrs) == 5);
    DynamicArray *first_row = *(DynamicArray**)get(arr_of_arrs, 0);
    assert(*(int*)get(first_row, 0) == 1);
    DynamicArray *last_row = *(DynamicArray**)get(arr_of_arrs, 4);
    assert(*(int*)get(last_row, 3) == 133);
    assert(*(int*)get(row5, 0) == 11);
    assert(*(int*)get(row5, 1) == 12);
    assert(*(int*)get(row5, 2) == 13);
    assert(*(int*)get(row5, 3) == 133);

    destroy(arr_of_arrs);
    clock_t end = clock();
    double time_spent = (double)(end - start) / CLOCKS_PER_SEC;
    printf("✅ (%.4f сек)\n", time_spent);
}

void tests_of_int() {
    printf("\n========== Тесты INT ==========\n\n");
    clock_t start = clock();

    test_create_destroy();
    test_clear();
    test_push_get();
    test_pop();
    test_remove_at();
    test_set();
    test_reserve();
    test_shrink_to_fit();
    test_sort();
    test_copy();
    test_map();
    test_where();
    test_concat();
    test_concat_type_mismatch();
    test_boundaries();
    test_10m_operations();
    
    printf("\n✅ ✅ ✅ ТЕСТЫ INT ПРОЙДЕНЫ ✅ ✅ ✅");
    clock_t end = clock();
    double time_spent = (double)(end - start) / CLOCKS_PER_SEC;
    printf("  (%.5f сек)\n\n", time_spent);
}