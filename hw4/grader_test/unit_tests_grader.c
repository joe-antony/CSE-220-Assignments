/*
DO NOT CHANGE THE CONTENTS OF THIS FILE IN CASE A NEW VERSION IS DISTRIBUTED.
PUT YOUR OWN TEST CASES IN student_tests.c
*/

#include "unit_tests.h"

static char test_log_outfile[100];

int run_using_system(char *test_name) {
    char executable[100];
    sprintf(executable, "./bin/%s", test_name);
    assert(access(executable, F_OK) == 0);

    char cmd[500];
    sprintf(test_log_outfile, "%s/%s.log", TEST_OUTPUT_DIR, test_name);
#if defined(__linux__)
    sprintf(cmd, "valgrind -s --leak-check=full --show-leak-kinds=all --track-origins=yes --trace-children=yes --error-exitcode=37 ./bin/%s > %s 2>&1",
        test_name, test_log_outfile);
#else
    cr_log_warn("Skipping valgrind tests. Run tests on Linux or GitHub for full output.\n");
    sprintf(cmd, "./bin/%s > %s 2>&1", test_name, test_log_outfile);
#endif
    return system(cmd);
}

void assert_normal_exit(int status) {
    cr_expect_eq(status, 0, "The program did not exit normally (status = 0x%x).\n", status);
}

void assert_error_exit(int status) {
    cr_expect_eq(WEXITSTATUS(status), 0xff,
         "The program did not exit with status 0xff (status was 0x%x).\n", status);
}

void assert_no_valgrind_errors(int status) {
    cr_expect_neq(WEXITSTATUS(status), 37, "Valgrind reported errors -- see %s", test_log_outfile);
    if (WEXITSTATUS(status) == 37) {
        char cmd[200];
        sprintf(cmd, "cat %s", test_log_outfile);
        system(cmd);
    }
}

TestSuite(base_suite, .timeout=TEST_TIMEOUT);


// encrypt
Test(base_suite, encrypt_full_msg, .description="A full plaintext message can be encrypted.") {
    const char *plaintext = "System Fundamentals";
    char ciphertext_act[] = "***I can store any message!***";
    int count_act = encrypt(plaintext, ciphertext_act, 1);
    char *ciphertext_exp = "Tztufn Gvoebnfoubmt__EOM__";
    int count_exp = 18;
    cr_expect_str_eq(ciphertext_act, ciphertext_exp, "ciphertext was:          %s\nbut it should have been: %s", ciphertext_act, ciphertext_exp);
    cr_expect_eq(count_act, count_exp, "Return value was %d, but it should have been %d.\n", count_act, count_exp);
}

Test(base_suite, encrypt_full_msg_numbers, .description="A full plaintext message with numbers can be encrypted.") {
    const char *plaintext = "Cse220";
    char ciphertext_act[] = "***I can store any message!***";
    int count_act = encrypt(plaintext, ciphertext_act, 1);
    char *ciphertext_exp = "Dtf331__EOM__";
    int count_exp = 6;
    cr_expect_str_eq(ciphertext_act, ciphertext_exp, "ciphertext was:          %s\nbut it should have been: %s", ciphertext_act, ciphertext_exp);
    cr_expect_eq(count_act, count_exp, "Return value was %d, but it should have been %d.\n", count_act, count_exp);
}

// decrypt
Test(base_suite, decrypt_full_msg, .description="A full ciphertext message can be decrypted.") {
    const char *ciphertext = "Tztufn Gvoebnfoubmt__EOM__";
    char plaintext_act[] = "***I can store any message!***";
    int count_act = decrypt(ciphertext, plaintext_act, 1);
    char *plaintext_exp = "System Fundamentals";
    int count_exp = 18;
    cr_expect_str_eq(plaintext_act, plaintext_exp, "ciphertext was:          %s\nbut it should have been: %s", plaintext_act, plaintext_exp);
    cr_expect_eq(count_act, count_exp, "Return value was %d, but it should have been %d.\n", count_act, count_exp);
}

Test(base_suite, decrypt_full_msg_numbers, .description="A full ciphertext message with numbers can be decrypted.") {
    const char *ciphertext = "Dtf331__EOM__";
    char plaintext_act[] = "I can store any message!";
    int count_act = decrypt(ciphertext, plaintext_act, 1);
    char *plaintext_exp = "Cse220";
    int count_exp = 6;
    cr_expect_str_eq(plaintext_act, plaintext_exp, "ciphertext was:          %s\nbut it should have been: %s", plaintext_act, plaintext_exp);
    cr_expect_eq(count_act, count_exp, "Return value was %d, but it should have been %d.\n", count_act, count_exp);
}
#ifndef GRADER_TESTS
TestSuite(grader_suite, .timeout=TEST_TIMEOUT);
// Encrypt 
Test(grader_suite, encrypt_basic_lowercase, .description="Encrypt simple lowercase string.") {
    const char *plaintext = "abc";
    char ciphertext_act[50] = "anything!*";
    int count_act = encrypt(plaintext, ciphertext_act, 2);
    char *ciphertext_exp = "cde__EOM__";
    int count_exp = 3;
    cr_expect_str_eq(ciphertext_act, ciphertext_exp);
    cr_expect_eq(count_act, count_exp);
}

Test(grader_suite, encrypt_basic_uppercase, .description="Encrypt simple uppercase string.") {
    const char *plaintext = "Ayb";
    char ciphertext_act[50] = "hello**write";
    int count_act = encrypt(plaintext, ciphertext_act, 3);
    char *ciphertext_exp = "Dbe__EOM__";
    int count_exp = 3;
    cr_expect_str_eq(ciphertext_act, ciphertext_exp);
    cr_expect_eq(count_act, count_exp);
}

Test(grader_suite, encrypt_with_numbers, .description="Encrypt string with numbers.") {
    const char *plaintext = "Cse220";
    char ciphertext_act[50] = "msg";
    int count_act = encrypt(plaintext, ciphertext_act, 1);
    char *ciphertext_exp = "Dtf331__EOM__";
    int count_exp = -1;
    // cr_expect_str_eq(ciphertext_act, ciphertext_exp);
    cr_expect_eq(count_act, count_exp);
}

Test(grader_suite, encrypt_zero_key, .description="Encrypt with key=0 (should not shift).") {
    const char *plaintext = "CS";
    char ciphertext_act[50] = "**********";
    int count_act = encrypt(plaintext, ciphertext_act, 0);
    char *ciphertext_exp = "CS__EOM__";
    int count_exp = 2;
    cr_expect_str_eq(ciphertext_act, ciphertext_exp);
    cr_expect_eq(count_act, count_exp);
}

Test(grader_suite, encrypt_empty_str, .description="Encrypt empty string.") {
    const char *plaintext = "";
    char ciphertext_act[50] = "hello***hello***";
    int count_act = encrypt(plaintext, ciphertext_act, 5);
    char *ciphertext_exp = "__EOM__";
    char *ciphertext_exp2 ="undefined__EOM__";
    if (strcmp(ciphertext_act, ciphertext_exp2) == 0) {
        ciphertext_exp = ciphertext_exp2;
    }
    int count_exp = 0;
    cr_expect_str_eq(ciphertext_act, ciphertext_exp);
    cr_expect_eq(count_act, count_exp);
}

Test(grader_suite, encrypt_wraparound_lowercase, .description="Lowercase wraparound shift past 'z'.") {
    const char *plaintext = "xyz";
    char ciphertext_act[50] = "***********";
    int count_act = encrypt(plaintext, ciphertext_act, 3);
    char *ciphertext_exp = "abc__EOM__";
    int count_exp = 3;
    cr_expect_str_eq(ciphertext_act, ciphertext_exp);
    cr_expect_eq(count_act, count_exp);
}

Test(grader_suite, encrypt_wraparound_uppercase, .description="Uppercase wraparound shift past 'Z'.") {
    const char *plaintext = "XYZ";
    char ciphertext_act[50] = "***********";
    int count_act = encrypt(plaintext, ciphertext_act, 4);
    char *ciphertext_exp = "BCD__EOM__";
    int count_exp = 3;
    cr_expect_str_eq(ciphertext_act, ciphertext_exp);
    cr_expect_eq(count_act, count_exp);
}

Test(grader_suite, encrypt_wraparound_numbers, .description="Numbers wraparound past '9'.") {
    const char *plaintext = "789";
    char ciphertext_act[50] = "***********";
    int count_act = encrypt(plaintext, ciphertext_act, 4);
    char *ciphertext_exp = "123__EOM__";
    int count_exp = 3;
    cr_expect_str_eq(ciphertext_act, ciphertext_exp);
    cr_expect_eq(count_act, count_exp);
}

Test(grader_suite, encrypt_null_plaintext, .description="NULL plaintext pointer returns -2, unchanged ciphertext.") {
    char ciphertext_act[50] = "unchanged!";
    int count_act = encrypt(NULL, ciphertext_act, 3);
    cr_expect_str_eq(ciphertext_act, "unchanged!");
    cr_expect_eq(count_act, -2);
}

Test(grader_suite, encrypt_null_ciphertext, .description="NULL ciphertext pointer returns -2.") {
    const char *plaintext = "abc";
    int count_act = encrypt(plaintext, NULL, 2);
    cr_expect_eq(count_act, -2);
}

//Decrypt 
Test(grader_suite, decrypt_basic_lowercase, .description="Decrypt simple lowercase string.") {
    const char *ciphertext = "cde__EOM__";
    char plaintext_act[50] = "message!";
    int count_act = decrypt(ciphertext, plaintext_act, 2);
    char *plaintext_exp = "abc";
    int count_exp = 3;
    cr_expect_str_eq(plaintext_act, plaintext_exp);
    cr_expect_eq(count_act, count_exp);
}

Test(grader_suite, decrypt_basic_uppercase, .description="Decrypt simple uppercase string.") {
    const char *ciphertext = "Dbe__EOM__";
    char plaintext_act[50] = "something";
    int count_act = decrypt(ciphertext, plaintext_act, 3);
    char *plaintext_exp = "Ayb";
    int count_exp = 3;
    cr_expect_str_eq(plaintext_act, plaintext_exp);
    cr_expect_eq(count_act, count_exp);
}

Test(grader_suite, decrypt_with_numbers, .description="Decrypt with numbers in ciphertext.") {
    const char *ciphertext = "Dtf331__EOM__";
    char plaintext_act[50] = "before";
    int count_act = decrypt(ciphertext, plaintext_act, 1);
    char *plaintext_exp = "Cse220";
    int count_exp = 6;
    cr_expect_str_eq(plaintext_act, plaintext_exp);
    cr_expect_eq(count_act, count_exp);
}

Test(grader_suite, decrypt_zero_key, .description="Decrypt with key=0 should not shift.") {
    const char *ciphertext = "CS__EOM__";
    char plaintext_act[50] = "before";
    int count_act = decrypt(ciphertext, plaintext_act, 0);
    char *plaintext_exp = "CS";
    int count_exp = 2;
    cr_expect_str_eq(plaintext_act, plaintext_exp);
    cr_expect_eq(count_act, count_exp);
}

Test(grader_suite, decrypt_invalid_missing_eom, .description="Ciphertext missing EOM returns -1, plaintext unchanged.") {
    const char *ciphertext = "Dtf331";
    char plaintext_act[50] = "keepme";
    int count_act = decrypt(ciphertext, plaintext_act, 1);
    cr_expect_str_eq(plaintext_act, "keepme");
    cr_expect_eq(count_act, -1);
}

Test(grader_suite, decrypt_empty_eom, .description="Empty message (just __EOM__) returns 0.") {
    const char *ciphertext = "__EOM__";
    char plaintext_act[50] = "here******";
    int count_act = decrypt(ciphertext, plaintext_act, 42);
    char *plaintext_exp = "";
    char *plaintext_exp2 = "undefined";
    int count_exp = 0;
    if (strcmp(plaintext_act, plaintext_exp2) == 0) {
        plaintext_exp = plaintext_exp2;
    }
    cr_expect_str_eq(plaintext_act, plaintext_exp);
    cr_expect_eq(count_act, count_exp);
}

Test(grader_suite, decrypt_multiple_eom, .description="Decrypt only up to first EOM marker.") {
    const char *ciphertext = "XyZ__EOM__abc__EOM__";
    char plaintext_act[50] = "start";
    int count_act = decrypt(ciphertext, plaintext_act, 2);
    char *plaintext_exp = "VwX";
    int count_exp = 3;
    cr_expect_str_eq(plaintext_act, plaintext_exp);
    cr_expect_eq(count_act, count_exp);
}

Test(grader_suite, decrypt_small_plaintext_buffer, .description="Buffer too small: only decrypt partial text.") {
    const char *ciphertext = "abc__EOM__";
    char plaintext_act[10] = "z"; // Only 2 chars of storage
    int count_act = decrypt(ciphertext, plaintext_act, 0); // key=0
    // Only 'a' can fit (plus \0)
    char *plaintext_exp = "a";
    int count_exp = 1; // Only 1 character decrypted
    cr_expect_str_eq(plaintext_act, plaintext_exp);
    cr_expect_eq(count_act, count_exp);
}

Test(grader_suite, decrypt_null_ciphertext, .description="NULL ciphertext pointer returns -2, plaintext unchanged.") {
    char plaintext_act[50] = "before";
    int count_act = decrypt(NULL, plaintext_act, 5);
    cr_expect_str_eq(plaintext_act, "before");
    cr_expect_eq(count_act, -2);
}

Test(grader_suite, decrypt_null_plaintext, .description="NULL plaintext pointer returns -2.") {
    const char *ciphertext = "abc__EOM__";
    int count_act = decrypt(ciphertext, NULL, 3);
    cr_expect_eq(count_act, -2);
}
#endif