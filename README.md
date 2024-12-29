# CUT (Convenient Unit Tester)

CUT is a simple and convenient unit testing framework for C.

## How to Use

1. **Include `cut.h` in Your Test Files**

    In each of your test files, include the `cut.h` header to define your test cases.

    **test_file1.c**
    ```c
    #include "cut.h"

    CUT_TEST(pass)
    {
        CUT_TEST_PASS;
    }

    CUT_TEST(fail)
    {
        CUT_TEST_FAIL("This test will fail");
    }
    ```

    **test_file2.c**
    ```c
    #include "cut.h"

    CUT_TEST(assert)
    {
        CUT_ASSERT(1);
        CUT_TEST_PASS;
    }
    ```
2. **Compile Test Files with `cut.c`**

    To compile and run the tests, you need to link your test files with `cut.c`.
    ```
    gcc -o tests test_file1.c test_file2.c cut.c
    ./tests
    ```
You can find additional examples in the `tests` directory
