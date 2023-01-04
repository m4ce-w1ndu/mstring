#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <check.h>

#include "../src/include/mstring.h"

START_TEST(mstring_construct_empty_string)
{
    mstring str = mstr_construct();

    // Assert that the str object ptr is not null
    ck_assert_ptr_nonnull(str);

    // Assert that the size is 0 and capacity is 1
    ck_assert_uint_eq(mstr_get_size(str), 0);
    ck_assert_uint_eq(mstr_get_capacity(str), 1);

    mstr_delete(str);
}
END_TEST

START_TEST(mstring_construct_init_string)
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

    mstr_delete(str);
}
END_TEST

// This really isn't a test. It's here because it's
// nice to look at.
START_TEST(mstring_delete_string)
{
    mstring str = mstr_construct();

    // Assert non null
    ck_assert_ptr_nonnull(str);

    // Free now
    mstr_delete(str);
}
END_TEST

START_TEST(mstring_compare_test)
{
    // To check for equality
    mstring strl = mstr_construct_init("Hello");
    mstring strr = mstr_construct_init("Hello");

    // Assert non null
    ck_assert_ptr_nonnull(strl);
    ck_assert_ptr_nonnull(strr);

    // Now compare the strings, we should expect a return
    // value of 0
    ck_assert_uint_eq(mstr_compare(strl, strr), 0);

    // Free those strings
    mstr_delete(strl);
    mstr_delete(strr);

    strl = mstr_construct_init("abcd");
    strr = mstr_construct_init("efgh");

    // Assert non null and check again
    ck_assert_ptr_nonnull(strl);
    ck_assert_ptr_nonnull(strr);

    int compare_result = mstr_compare(strl, strr);
    ck_assert_int_lt(compare_result, 0);

    compare_result = mstr_compare(strr, strl);
    ck_assert_int_gt(compare_result, 0);

    mstr_delete(strl);
    mstr_delete(strr);
}
END_TEST

START_TEST(mstring_size_checks)
{
    const char init[] = "Hello";

    // Init a string
    mstring str = mstr_construct_init(init);
    size_t len = strlen(init);

    // Check non null
    ck_assert_ptr_nonnull(str);

    // Size should be 4
    ck_assert_uint_eq(mstr_get_size(str), len);
    // Capacity should be size + 1 in init case
    ck_assert_uint_eq(mstr_get_capacity(str), strlen(init) + 1);

    mstr_delete(str);

    // Now test the same thing but with an empty string with appended chars
    str = mstr_construct();
    ck_assert_ptr_nonnull(str);

    // Append four characters
    mstr_append_char(str, 'a');
    mstr_append_char(str, 'b');
    mstr_append_char(str, 'c');
    mstr_append_char(str, 'd');

    // The string should be "abcd"
    ck_assert_str_eq(mstr_get(str), "abcd");

    // Delete
    mstr_delete(str);
}
END_TEST

Suite *mstring_tests_runner_0()
{
    TCase *test_0 = tcase_create("mstring_construct_destroy");
    tcase_add_test(test_0, mstring_construct_empty_string);
    tcase_add_test(test_0, mstring_construct_init_string);
    tcase_add_test(test_0, mstring_delete_string);

    TCase *test_1 = tcase_create("mstring_compare_check");
    tcase_add_test(test_1, mstring_compare_test);
    tcase_add_test(test_1, mstring_size_checks);

    Suite *suite = suite_create("mstring tests");
    suite_add_tcase(suite, test_0);
    suite_add_tcase(suite, test_1);

    return suite;
}

int main(void)
{
    int failed_0 = 0;
    int failed_1 = 0;

    Suite *suite_0 = mstring_tests_runner_0();
    SRunner *runner = srunner_create(suite_0);

    srunner_run_all(runner, CK_VERBOSE);
    failed_0 = srunner_ntests_failed(runner);

    srunner_free(runner);
    return (failed_0 == 0 ? EXIT_SUCCESS : EXIT_FAILURE);
}