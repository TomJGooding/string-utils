#include <string.h>

#include "ctest.h"
#include "string_utils.h"

int test_string_from_file() {
    char *actual = string_from_file("test_file.txt");
    char *expected =
        "This is the first line.\n"
        "This is the second line.\n"
        "This is the last line.\n";
    ctest_assert(!strcmp(actual, expected));
    return 0;
}

int test_strtok_to_array() {
    TokenArray *array = strtok_to_array(strdup("comma,separated,text"), ",");
    ctest_assert(array->length == 3);
    ctest_assert(!strcmp(array->elements[0], "comma"));
    ctest_assert(!strcmp(array->elements[1], "separated"));
    ctest_assert(!strcmp(array->elements[2], "text"));
    return 0;
}

ctest_test_suite(test_string_utils) {
    ctest_run_test(test_string_from_file);
    ctest_run_test(test_strtok_to_array);
}

int main() {
    ctest_run_suite(test_string_utils);
    ctest_report();

    return CTEST_EXIT_CODE;
}
