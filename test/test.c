#include <stdlib.h>
#include <string.h>
#include <check.h>

#include "../src/include/mstring.h"

START_TEST(construct_empty_string)
{
    mstring str = mstr_construct();

    // Assert that the str object ptr is not null
    ck_assert_ptr_nonnull(str);

    // Assert that the size is 0 and capacity is 1
    ck_assert_uint_eq(mstr_get_size(str), 0);
    ck_assert_uint_eq(mstr_get_capacity(str), 1);
}
END_TEST

START_TEST(construct_init_string)
{
    mstring str = mstr_construct_init("Test Test");
    const char exp_value[] = "Test Test";

    // Assert non null
    ck_assert_ptr_nonnull(str);

    // Assert that size is strlen(exp_value)
    ck_assert_uint_eq(mstr_get_size(str), strlen(exp_value));
    // Assert that size is strlen(exp_value + 1)
    ck_assert_uint_eq(mstr_get_capacity(str), strlen(exp_value) + 1);

    // Assert that the content of the buffer and exp_value is the same
    ck_assert_str_eq(mstr_get(str), exp_value);
}
END_TEST

Suite *mstring_tests_runner()
{
    TCase *test_0 = tcase_create("mstring_construct");
    tcase_add_test(test_0, construct_empty_string);
    tcase_add_test(test_0, construct_init_string);

    Suite *suite = suite_create("mstring tests");
    suite_add_tcase(suite, test_0);

    return suite;
}

int main(void)
{
    int failed = 0;
    
    Suite *suite = mstring_tests_runner();
    SRunner *runner = srunner_create(suite);

    srunner_run_all(runner, CK_VERBOSE);
    failed = srunner_ntests_failed(runner);

    srunner_free(runner);
    return (failed == 0 ? EXIT_SUCCESS : EXIT_FAILURE);
}