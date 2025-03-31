#ifndef CUT_H
#define CUT_H

#define CUT_STRINGIFY(_x) #_x
#define CUT_TO_STRING(_x) CUT_STRINGIFY(_x)

#define CUT_CONCAT(a, b) a ## b
#define CUT_EVAL_CONCAT(a, b) CUT_CONCAT(a, b)

#define CUT_TEST_SECTION_NAME cut_test_ptrs

#define CUT_TESTS_START CUT_EVAL_CONCAT(__start_, CUT_TEST_SECTION_NAME)
#define CUT_TESTS_STOP CUT_EVAL_CONCAT(__stop_,  CUT_TEST_SECTION_NAME)

enum test_return_code {
    TEST_PASS,
    TEST_FAIL,
    TEST_ASSERT_FAIL
};

struct test_result {
    char *msg;
};

typedef enum test_return_code (*test_fun_t)(struct test_result *__result);

struct test_entry {
    char *file_name;
    char *name;
    test_fun_t fun;
} __attribute__((aligned(32)));

extern const struct test_entry CUT_TESTS_START[];
extern const struct test_entry CUT_TESTS_STOP[];

#define CUT_LIKELY(x) __builtin_expect(!!(x), 1)
#define CUT_UNLIKELY(x) __builtin_expect(!!(x), 0)

#define CUT_LINE_FILE_STR CUT_TO_STRING(__LINE__)":" __FILE__": "

#define CUT_TEST(_name) \
    static enum test_return_code cut_test_##_name(struct test_result *__result); \
    static __attribute__((unused, section(CUT_TO_STRING(CUT_TEST_SECTION_NAME))))\
    const struct test_entry cut_test_entry_##_name = {.file_name = __FILE__,     \
        .name = #_name, .fun = &cut_test_##_name};\
    static enum test_return_code cut_test_##_name(struct test_result *__result)

#define CUT_TEST_PASS          \
    do {                       \
        __result->msg = "PASS";\
        return TEST_PASS;      \
    } while (0)

#define CUT_TEST_FAIL(_msg)                    \
    do {                                       \
        __result->msg = CUT_LINE_FILE_STR _msg;\
        return TEST_FAIL;                      \
    } while (0)

#define CUT_ASSERT(_cond)                                                   \
    do {                                                                    \
        if (CUT_UNLIKELY(!(_cond))) {                                       \
            __result->msg = CUT_LINE_FILE_STR "Assertion " #_cond " failed";\
            return TEST_ASSERT_FAIL;                                        \
        }                                                                   \
    } while (0)

#define CUT_ASSERT_WITH_MSG(_cond, _msg)                                           \
    do {                                                                           \
        if (CUT_UNLIKELY(!(_cond))) {                                              \
            __result->msg = CUT_LINE_FILE_STR "Assertion " #_cond " failed: " _msg;\
            return TEST_ASSERT_FAIL;                                               \
        }                                                                          \
    } while (0)

#endif
