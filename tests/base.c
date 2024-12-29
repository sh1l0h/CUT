#include "cut.h"

CUT_TEST(simple_pass)
{
    CUT_TEST_PASS;
}

CUT_TEST(simple_fail)
{
    CUT_TEST_FAIL("This test should fail");
}

CUT_TEST(simple_assert)
{
    CUT_ASSERT(0);

    CUT_TEST_FAIL("Assertion does not work");
}

CUT_TEST(simple_assert_msg)
{
    CUT_ASSERT_WITH_MSG(0, "This should fail");

    CUT_TEST_FAIL("Assertion does not work");
}
