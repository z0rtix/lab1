#include "tests/tests_of_int.h"
#include "tests/tests_of_str.h"
#include "ui_menu/menu.h"
#include <stdio.h>

int main() {
    tests_of_int();
    tests_of_str();
    test_int_arrays();
    test_string_arrays();
    test_mix_arays();

    printf("\n============== Все тесты пройдены!✅ ==============\n");

    interactive_mode();
    
    return 0;
}
