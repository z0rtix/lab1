#include "menu.h"
#include "../utils/utils.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <math.h>

DynamicArray* choose_type() {
    printf("\n=== ВЫБОР ТИПА ===\n");
    printf("1 - int\n");
    printf("2 - double\n");
    printf("3 - string\n");
    printf("0 - выход\n");
    printf("> ");
    
    int choice;
    scanf("%d", &choice);
    getchar();
    
    switch(choice) {
        case 1: return create(&INT_TYPE);
        case 2: return create(&DOUBLE_TYPE);
        case 3: return create(&STRING_TYPE);
        case 0: return NULL;
        default: 
            printf("Неверный выбор, создаю int\n");
            return create(&INT_TYPE);
    }
}

void add_element(DynamicArray *arr) {
    if (arr->type == &INT_TYPE) {
        int val;
        printf("Введите int: ");
        scanf("%d", &val);
        getchar();
        push(arr, &val);
    }
    else if (arr->type == &STRING_TYPE) {
        char buffer[256];
        printf("Введите string: ");
        fgets(buffer, 256, stdin);
        buffer[strcspn(buffer, "\n")] = 0;
        if (strlen(buffer) > 0) {
            char *new_str = strdup(buffer);
            push(arr, &new_str);
        }
    }
    else if (arr->type == &DOUBLE_TYPE) {
        double val;
        printf("Введите double: ");
        scanf("%lf", &val);
        getchar();
        push(arr, &val);
    }
}

DynamicArray* map_with_choice(DynamicArray *arr) {
    if (arr->type == &INT_TYPE) {
        printf("\n=== MAP для int ===\n");
        printf("1 - возвести в квадрат\n");
        printf("2 - возвести в куб\n");
        printf("3 - прибавить 10\n");
        printf("> ");
        
        int choice;
        scanf("%d", &choice);
        getchar();
        
        switch(choice) {
            case 1: return map(arr, int_map_square);
            case 2: return map(arr, int_map_cube);
            case 3: return map(arr, int_map_add10);
            default: return map(arr, int_map_square);
        }
    }
    else if (arr->type == &DOUBLE_TYPE) {
        printf("\n=== MAP для double ===\n");
        printf("1 - возвести в квадрат\n");
        printf("2 - квадратный корень\n");
        printf("3 - умножить на 2\n");
        printf("> ");
        
        int choice;
        scanf("%d", &choice);
        getchar();
        
        switch(choice) {
            case 1: return map(arr, double_map_square);
            case 2: return map(arr, double_map_sqrt);
            case 3: return map(arr, double_map_mul2);
            default: return map(arr, double_map_square);
        }
    }
    else if (arr->type == &STRING_TYPE) {
        printf("\n=== MAP для string ===\n");
        printf("1 - to UPPER CASE\n");
        printf("2 - добавить !!!\n");
        printf("3 - реверс\n");
        printf("> ");
        
        int choice;
        scanf("%d", &choice);
        getchar();
        
        switch(choice) {
            case 1: return map(arr, string_map_upper);
            case 2: return map(arr, string_map_exclaim);
            case 3: return map(arr, string_map_reverse);
            default: return map(arr, string_map_upper);
        }
    }
    return NULL;
}

DynamicArray* where_with_choice(DynamicArray *arr) {
    if (arr->type == &INT_TYPE) {
        printf("\n=== WHERE для int ===\n");
        printf("1 - четные\n");
        printf("2 - нечетные\n");
        printf("3 - больше 5\n");
        printf("> ");
        
        int choice;
        scanf("%d", &choice);
        getchar();
        
        switch(choice) {
            case 1: return where(arr, int_is_even);
            case 2: return where(arr, int_is_odd);
            case 3: return where(arr, int_gt_5);
            default: return where(arr, int_is_even);
        }
    }
    else if (arr->type == &DOUBLE_TYPE) {
        printf("\n=== WHERE для double ===\n");
        printf("1 - положительные\n");
        printf("2 - больше 1\n");
        printf("> ");
        
        int choice;
        scanf("%d", &choice);
        getchar();
        
        switch(choice) {
            case 1: return where(arr, double_is_positive);
            case 2: return where(arr, double_gt_1);
            default: return where(arr, double_is_positive);
        }
    }
    else if (arr->type == &STRING_TYPE) {
        printf("\n=== WHERE для string ===\n");
        printf("1 - длина > 3\n");
        printf("2 - начинается с A/a\n");
        printf("3 - содержит 'e'\n");
        printf("> ");
        
        int choice;
        scanf("%d", &choice);
        getchar();
        
        switch(choice) {
            case 1: return where(arr, string_length_gt_3);
            case 2: return where(arr, string_starts_with_a);
            case 3: return where(arr, string_contains_e);
            default: return where(arr, string_length_gt_3);
        }
    }
    return NULL;
}

void interactive_mode() {
    int program_running = 1;
    
    while (program_running) {
        DynamicArray *arr = choose_type();
        if (arr == NULL) {
            program_running = 0;
            break;
        }
        
        int array_running = 1;
        
        while (array_running) {
            printf("\nТекущий массив: ");
            print_array(arr);
            printf("Размер: %d\n", size(arr));
            
            printf("\n=== МЕНЮ ===\n");
            printf("1 - Добавить элемент (push)\n");
            printf("2 - Удалить последний элемент (pop)\n");
            printf("3 - Вывести элемент по номеру (get)\n");
            printf("4 - Изменить элемент по номеру (set)\n");
            printf("5 - Удалить элемент по номеру (remove_at)\n");
            printf("6 - Сортировать (sort)\n");
            printf("7 - Применить функцию (map)\n");
            printf("8 - Фильтр (where)\n");
            printf("9 - Новый массив (сменить тип) (create)\n");
            printf("0 - Выход\n");
            printf("> ");
            
            int choice;
            scanf("%d", &choice);
            getchar();
            
            switch(choice) {
                case 1: {
                    add_element(arr);
                    break;
                }

                case 2: {
                    pop(arr);
                    break;
                }

                case 3: {
                    int s = size(arr);
                    if (s == 0) {
                        printf("❌ Массив пустой\n");
                        break;
                    }

                    printf("Размер массива: %d. Введите индекс (0-%d): ", s, s-1);
                    int index;
                    scanf("%d", &index);
                    getchar();
                    
                    if (index < 0 || index >= s) {
                        printf("❌ Неверный индекс. Будет выведен элемент 0.\n");
                        index = 0;
                    }
                    
                    printf("Элемент под номером %d: ", index);
                    void *element = get(arr, index);
                    arr->type->element_print(element);
                    printf("\n");
                    break;
                }
                
                case 4: {
                    if (size(arr) == 0) {
                        printf("❌ Массив пустой\n");
                        break;
                    }

                    printf("Размер массива: %d. Введите номер элемента(при неверном вводе - 0): ", size(arr));
                    int index;
                    scanf("%d", &index);
                    getchar();
                    if (index >= size(arr) || index < 0) {
                        printf("❌ Неверный индекс. Будет изменен элемент под номером 0.\n");
                        index = 0;
                    }

                    printf("Введите значение: ");
                    if (arr->type == &INT_TYPE) {
                        int val;
                        scanf("%d", &val);
                        getchar();
                        set(arr, index, &val);
                    }
                    else if (arr->type == &STRING_TYPE) {
                        char buffer[256];
                        printf("Введите строку: ");
                        fgets(buffer, 256, stdin);
                        buffer[strcspn(buffer, "\n")] = 0;
                        
                        if (strlen(buffer) > 0) {
                            char *val = strdup(buffer);
                            set(arr, index, &val);
                        } else {
                            printf("❌ Пустая строка, элемент не изменен\n");
                        }
                    }
                    else if (arr->type == &DOUBLE_TYPE) {
                        double val;
                        scanf("%lf", &val);
                        getchar();
                        set(arr, index, &val);
                    }

                    break;
                }

                case 5: {
                    int s = size(arr);
                    if (s == 0) {
                        printf("❌ Массив пустой\n");
                        break;
                    }

                    printf("Размер массива: %d. Введите индекс для удаления (0-%d): ", s, s-1);
                    int index;
                    scanf("%d", &index);
                    getchar();
                    
                    if (index < 0 || index >= s) {
                        printf("❌ Неверный индекс\n");
                        break;
                    }

                    printf("Удаляемый элемент: ");
                    void *element = get(arr, index);
                    arr->type->element_print(element);
                    printf("\n");

                    printf("Подтвердите удаление (y/n): ");
                    char confirm;
                    scanf("%c", &confirm);
                    getchar();
                    
                    if (confirm == 'y' || confirm == 'Y') {
                        remove_at(arr, index);
                        printf("✅ Элемент удален\n");
                    } else {
                        printf("❌ Удаление отменено\n");
                    }
                    break;
                }
                
                case 6: {
                    sort(arr);
                    printf("✓ Массив отсортирован\n");
                    break;
                }
                    
                case 7: {
                    DynamicArray *new_arr = map_with_choice(arr);
                    if (new_arr != NULL) {
                        destroy(arr);
                        arr = new_arr;
                        printf("✓ Map применен, текущий массив заменен\n");
                    }
                    break;
                }
                
                case 8: {
                    DynamicArray *new_arr = where_with_choice(arr);
                    if (new_arr != NULL) {
                        destroy(arr);
                        arr = new_arr;
                        printf("✓ Where применен, текущий массив заменен\n");
                    }
                    break;
                }
                
                case 9: {
                    destroy(arr);
                    array_running = 0; 
                    break;
                }

                case 0: {
                    destroy(arr);
                    program_running = 0;
                    array_running = 0;
                    break;
                }
                    
                default:
                    printf("❌ Неверный выбор\n");
            }
        }
    }
    
    printf("\nПрограмма завершена\n");
}