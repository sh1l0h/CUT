#include <stdio.h>
#include "cut.h"

#define RED   "\x1B[31m"
#define GRN   "\x1B[32m"
#define RESET "\x1B[0m"

char *return_code_text[] = {
    [TEST_PASS]        = "["GRN"PASS"RESET"]       ",
    [TEST_FAIL]        = "["RED"FAIL"RESET"]       ",
    [TEST_ASSERT_FAIL] = "["RED"ASSERT FAIL"RESET"]"
};

int main()
{
    size_t test_count = CUT_TESTS_STOP - CUT_TESTS_START,
           failed_test_count = 0;

    for (size_t i = 0; i < test_count; i++) {
        const struct test_entry *entry = CUT_TESTS_START + i;
        struct test_result result = {};
        enum test_return_code code = entry->fun(&result);

        printf("%s%6lu/%lu: %s: %s\n", return_code_text[code], i + 1,
               test_count, entry->file_name, entry->name);

        if (code == TEST_PASS)
            continue;

        failed_test_count++;
        printf("\t%s\n", result.msg);
    }

    printf("\nResults: ["GRN"PASS"RESET"] %lu, ["RED"FAIL"RESET"] %lu\n",
           test_count - failed_test_count, failed_test_count);

    return 0;
}
