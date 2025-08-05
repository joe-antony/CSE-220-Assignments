/* Siddharth Korukonda
   CSE 220.01
   115607752
*/

#include "unit_tests.h"

TestSuite(student_suite, .timeout=TEST_TIMEOUT);

/*
Test(student_suite, name_of_test, .description="description of test") {
    // Steps of unit test go here
}
*/

// Encrypt test cases
// Tests that the function returns -2 when plaintext is NULL
Test(base_suite, encrypt_null_plaintext, .description="Plaintext is NULL") {
    const char *plaintext = NULL;
    char ciphertext[] = "***I can store any message!***";
    int count_act = encrypt(plaintext, ciphertext, 34);
    int count_exp = -2;
    cr_expect_eq(count_act, count_exp, "Return value was %d, but it should have been %d.\n", count_act, count_exp);
}

// Tests that the function returns -2 when ciphertext is NULL
Test(base_suite, encrypt_null_ciphertext, .description="Ciphertext is NULL") {
    const char *plaintext = "Ceasar Cipher";
    char *ciphertext = NULL;
    int count_act = encrypt(plaintext, ciphertext, 99);
    int count_exp = -2;
    cr_expect_eq(count_act, count_exp, "Return value was %d, but it should have been %d.\n", count_act, count_exp);
}

// Tests that the function returns -2 when both the plaintext and ciphertext inputs are NULL
Test(base_suite, encrypt_both_plaintext_and_ciphertext_null, .description="Both plaintext and ciphertext are NULL") {
    const char *plaintext = NULL;
    char *ciphertext = NULL;
    int count_act = encrypt(plaintext, ciphertext, 87);
    int count_exp = -2;
    cr_expect_eq(count_act, count_exp, "Return value was %d, but it should have been %d.\n", count_act, count_exp);
}

// Tests that when plaintext is empty, the function returns 0 and writes "undefined__EOM__" into ciphertext
Test(base_suite, encrypt_empty_plaintext, .description="Plaintext is an empty string") {
    const char *plaintext = "";
    char ciphertext_act[] = "***I can store any message!***";
    int count_act = encrypt(plaintext, ciphertext_act, 17);
    char *ciphertext_exp = "undefined__EOM__";
    int count_exp = 0;
    cr_expect_str_eq(ciphertext_act, ciphertext_exp, "ciphertext was:          %s\nbut it should have been: %s", ciphertext_act, ciphertext_exp);
    cr_expect_eq(count_act, count_exp, "Return value was %d, but it should have been %d.\n", count_act, count_exp);
}

// Tests that the function returns -1 if the ciphertext buffer is too small to hold the result
Test(base_suite, encrypt_ciphertext_buffer_too_short, .description="Ciphertext buffer is too small") {
    const char *plaintext = "LeBron James";
    char ciphertext_act[] = "short";
    int count_act = encrypt(plaintext, ciphertext_act, 1);
    int count_exp = -1;
    cr_expect_eq(count_act, count_exp, "Return value was %d, but it should have been %d.\n", count_act, count_exp);
}

// Ensures that non-alphanumeric characters are skipped, and only valid characters are encrypted
Test(base_suite, encrypt_with_nonalphanumeric_characters, .description="Plaintext has nonalphanumeric characters") {
    const char *plaintext = "Hello, World!";
    char ciphertext_act[] = "***I can store any message!***";
    int count_act = encrypt(plaintext, ciphertext_act, 1);
    char *ciphertext_exp = "Ifmmp Xpsme__EOM__";
    int count_exp = 10;
    cr_expect_str_eq(ciphertext_act, ciphertext_exp, "ciphertext was:          %s\nbut it should have been: %s", ciphertext_act, ciphertext_exp);
    cr_expect_eq(count_act, count_exp, "Return value was %d, but it should have been %d.\n", count_act, count_exp);
}

// Tests digit encryption works correctly by forcing wrapping with a positive key greater than 10
Test(base_suite, encrypt_wrap_digits_positive, .description="Key > 10, digits wrap around properly") {
    const char *plaintext = "siddio1234";
    char ciphertext_act[] = "***I can store any message!***";
    int count_act = encrypt(plaintext, ciphertext_act, 13);
    char *ciphertext_exp = "fvqqvb4567__EOM__";
    int count_exp = 10;
    cr_expect_str_eq(ciphertext_act, ciphertext_exp, "ciphertext was:          %s\nbut it should have been: %s", ciphertext_act, ciphertext_exp);
    cr_expect_eq(count_act, count_exp, "Return value was %d, but it should have been %d.\n", count_act, count_exp);
}

// Tests letter encryption works correctly by forcing wrapping with a positive key greater than 26
Test(base_suite, encrypt_wrap_letters_positive, .description="Key > 26, letters wrap around properly") {
    const char *plaintext = "siddio1234";
    char ciphertext_act[] = "***I can store any message!***";
    int count_act = encrypt(plaintext, ciphertext_act, 39);
    char *ciphertext_exp = "fvqqvb0123__EOM__";
    int count_exp = 10;
    cr_expect_str_eq(ciphertext_act, ciphertext_exp, "ciphertext was:          %s\nbut it should have been: %s", ciphertext_act, ciphertext_exp);
    cr_expect_eq(count_act, count_exp, "Return value was %d, but it should have been %d.\n", count_act, count_exp);
}

// Tests that with a shift key of 0, the plaintext to ciphertext encryption is unchanged, and the EOM marker is added
Test(base_suite, encrypt_with_key_zero, .description="Encrypt with key 0 should leave text unchanged and then concatenate the EOM marker") {
    const char *plaintext = "Water Bottle";
    char ciphertext_act[] = "***I can store any message!***";
    int count_act = encrypt(plaintext, ciphertext_act, 0);
    char *ciphertext_exp = "Water Bottle__EOM__";
    int count_exp = 11;
    cr_expect_str_eq(ciphertext_act, ciphertext_exp, "ciphertext was:          %s\nbut it should have been: %s", ciphertext_act, ciphertext_exp);
    cr_expect_eq(count_act, count_exp, "Return value was %d, but it should have been %d.\n", count_act, count_exp);
}

// Tests that backward shift encryption works correctly with a negative shift value
Test(base_suite, encrypt_negative_key, .description="Encrypt message with negative key") {
    const char *plaintext = "Abid Malik";
    char ciphertext_act[] = "***I can store any message!***";
    int count_act = encrypt(plaintext, ciphertext_act, -2);
    char *ciphertext_exp = "Yzgb Kyjgi__EOM__";
    int count_exp = 9;
    cr_expect_str_eq(ciphertext_act, ciphertext_exp, "ciphertext was:          %s\nbut it should have been: %s", ciphertext_act, ciphertext_exp);
    cr_expect_eq(count_act, count_exp, "Return value was %d, but it should have been %d.\n", count_act, count_exp);
}

// Tests backward digit encryption works correctly by forcing wrapping with a negative key less than -10
Test(base_suite, encrypt_wrap_digits_negative, .description="Encrypt message with key < -10") {
    const char *plaintext = "4Joe Antony4";
    char ciphertext_act[] = "***I can store any message!***";
    int count_act = encrypt(plaintext, ciphertext_act, -13);
    char *ciphertext_exp = "1Wbr Nagbal1__EOM__";
    int count_exp = 11;
    cr_expect_str_eq(ciphertext_act, ciphertext_exp, "ciphertext was:          %s\nbut it should have been: %s", ciphertext_act, ciphertext_exp);
    cr_expect_eq(count_act, count_exp, "Return value was %d, but it should have been %d.\n", count_act, count_exp);
}

// Tests backward letter encryption works correctly by forcing wrapping with a negative key less than -26
Test(base_suite, encrypt_wrap_letters_negative, .description="Encrypt message with key < -26") {
    const char *plaintext = "Stony Brook";
    char ciphertext_act[] = "***I can store any message!***";
    int count_act = encrypt(plaintext, ciphertext_act, -31);
    char *ciphertext_exp = "Nojit Wmjjf__EOM__";
    int count_exp = 10;
    cr_expect_str_eq(ciphertext_act, ciphertext_exp, "ciphertext was:          %s\nbut it should have been: %s", ciphertext_act, ciphertext_exp);
    cr_expect_eq(count_act, count_exp, "Return value was %d, but it should have been %d.\n", count_act, count_exp);
}


// Decrypt test cases
// Tests that the function returns -2 when ciphertext is NULL
Test(base_suite, decrypt_null_ciphertext, .description="Ciphertext is NULL") {
    const char *ciphertext = NULL;
    char plaintext_act[] = "***I can store any message!***";
    int count_act = decrypt(ciphertext, plaintext_act, 6);
    int count_exp = -2;
    cr_expect_eq(count_act, count_exp, "Return value was %d, but it should have been %d.\n", count_act, count_exp);
}

// Tests that the function returns -2 when plaintext is NULL
Test(base_suite, decrypt_null_plaintext, .description="Plaintext is NULL") {
    const char *ciphertext = "Abcd__EOM__";
    char *plaintext_act = NULL;
    int count_act = decrypt(ciphertext, plaintext_act, 7);
    int count_exp = -2;
    cr_expect_eq(count_act, count_exp, "Return value was %d, but it should have been %d.\n", count_act, count_exp);
}

// Tests that the function returns -2 when both the plaintext and ciphertext inputs are NULL
Test(base_suite, decrypt_both_plaintext_and_ciphertext_null, .description="Both plaintext and ciphertext are NULL") {
    const char *ciphertext = NULL;
    char *plaintext_act = NULL;
    int count_act = decrypt(ciphertext, plaintext_act, 5);
    int count_exp = -2;
    cr_expect_eq(count_act, count_exp, "Return value was %d, but it should have been %d.\n", count_act, count_exp);
}

// Tests that the function returns -1 if __EOM__ is not found, indicating an invalid input
Test(base_suite, decrypt_incomplete_eom, .description="Ciphertext without EOM marker") {
    const char *ciphertext = "wpo Ofvnboo bsdijufduvsf";
    char plaintext_act[] = "***I can store any message!***";
    int count_act = decrypt(ciphertext, plaintext_act, 1);
    int count_exp = -1;
    cr_expect_eq(count_act, count_exp, "Return value was %d, but it should have been %d.\n", count_act, count_exp);
}

// Tests that the function returns 0 and produces an empty string when ciphertext is only the EOM marker
Test(base_suite, decrypt_empty_ciphertext_with_eom, .description="Empty ciphertext with only EOM marker") {
    const char *ciphertext = "__EOM__";
    char plaintext_act[] = "***I can store any message!***";
    int count_act = decrypt(ciphertext, plaintext_act, 3);
    char *plaintext_exp = "";
    int count_exp = 0;
    cr_expect_str_eq(plaintext_act, plaintext_exp, "Decrypted string was: %s, but expected: %s", plaintext_act, plaintext_exp);
    cr_expect_eq(count_act, count_exp, "Return value was %d, expected %d", count_act, count_exp);
}

// Tests that a corrupt EOM marker with empty output buffer returns 0
Test(base_suite, decrypt_incomplete_eom_and_zero_plaintext, .description="Incomplete EOM but buffer is 0, expect 0") {
    const char *ciphertext = "cats__EOM";
    char plaintext_act[] = "";
    int count_act = decrypt(ciphertext, plaintext_act, 2);
    int count_exp = 0;
    cr_expect_eq(count_act, count_exp, "Return value was %d, expected %d", count_act, count_exp);
}

// Tests whether decryption stops before overflow and all the ciphertext characters inside the buffer length have been decrypted
Test(base_suite, decrypt_ciphertext_longer_than_plaintext, .description="Ciphertext longer than buffer") {
    const char *ciphertext = "tvddftt__EOM__";
    char plaintext_act[] = "dogs";
    int count_act = decrypt(ciphertext, plaintext_act, 1);
    char *plaintext_exp = "succ";
    int count_exp = 4;
    cr_expect_str_eq(plaintext_act, plaintext_exp, "Decrypted string was: %s, expected: %s", plaintext_act, plaintext_exp);
    cr_expect_eq(count_act, count_exp, "Return value was %d, expected %d", count_act, count_exp);
}

// Tests digit decryption works correctly by forcing wrapping with a positive key greater than 10
Test(base_suite, decrypt_wrap_digits_positive, .description="Key > 10, digits wrap around properly") {
    const char *ciphertext = "34567__EOM__";
    char plaintext_act[] = "***I can store any message!***";
    int count_act = decrypt(ciphertext, plaintext_act, 13);
    char *plaintext_exp = "01234";
    int count_exp = 5;
    cr_expect_str_eq(plaintext_act, plaintext_exp, "Decrypted string was: %s, expected: %s", plaintext_act, plaintext_exp);
    cr_expect_eq(count_act, count_exp, "Return value was %d, expected %d", count_act, count_exp);
}

// Tests letter decryption works correctly by forcing wrapping with a positive key greater than 26
Test(base_suite, decrypt_wrap_letters_positive, .description="Key > 26, letters wrap around properly") {
    const char *ciphertext = "bqqfoe__EOM__";
    char plaintext_act[] = "***I can store any message!***";
    int count_act = decrypt(ciphertext, plaintext_act, 53);
    char *plaintext_exp = "append";
    int count_exp = 6;
    cr_expect_str_eq(plaintext_act, plaintext_exp, "Decrypted string was: %s, expected: %s", plaintext_act, plaintext_exp);
    cr_expect_eq(count_act, count_exp, "Return value was %d, expected %d", count_act, count_exp);
}

// Ensures that non-alphanumeric characters are skipped, and only valid characters are decrypted
Test(base_suite, decrypt_with_nonalphanumeric_characters, .description="Decrypt message with non-alphanumeric characters") {
    const char *ciphertext = "Uftu!@#123__EOM__";
    char plaintext_act[] = "***I can store any message!***";
    int count_act = decrypt(ciphertext, plaintext_act, 1);
    char *plaintext_exp = "Test012";
    int count_exp = 7;
    cr_expect_str_eq(plaintext_act, plaintext_exp, "Decrypted string was: %s, expected: %s", plaintext_act, plaintext_exp);
    cr_expect_eq(count_act, count_exp, "Return value was %d, expected %d", count_act, count_exp);
}

// Tests that backward shift decryption works correctly with a negative shift value
Test(base_suite, decrypt_negative_key, .description="Decrypt with negative key") {
    const char *ciphertext = "q__EOM__";
    char plaintext_act[] = "***I can store any message!***";
    int count_act = decrypt(ciphertext, plaintext_act, -2);
    char *plaintext_exp = "s";
    int count_exp = 1;
    cr_expect_str_eq(plaintext_act, plaintext_exp, "Decrypted string was: %s, expected: %s", plaintext_act, plaintext_exp);
    cr_expect_eq(count_act, count_exp, "Return value was %d, expected %d", count_act, count_exp);
}

// Tests that with a shift of 0, the ciphertext to plaintext decryption is unchanged, and the EOM marker is removed
Test(base_suite, decrypt_key_zero, .description="Decrypt with key 0 should leave text unchanged and then remove the EOM marker") {
    const char *ciphertext = "Chill on me__EOM__";
    char plaintext_act[] = "***I can store any message!***";
    int count_act = decrypt(ciphertext, plaintext_act, 0);
    char *plaintext_exp = "Chill on me";
    int count_exp = 9;
    cr_expect_str_eq(plaintext_act, plaintext_exp, "Decrypted string was: %s, expected: %s", plaintext_act, plaintext_exp);
    cr_expect_eq(count_act, count_exp, "Return value was %d, expected %d", count_act, count_exp);
}

// Tests backward digit decryption works correctly by forcing wrapping with a negative key less than -10
Test(base_suite, decrypt_wrap_digits_negative, .description="Decrypt with negative key < -10") {
    const char *ciphertext = "Eketm 76898678__EOM__";
    char plaintext_act[] = "***I can store any message!***";
    int count_act = decrypt(ciphertext, plaintext_act, -14);
    char *plaintext_exp = "Sysha 10232012";
    int count_exp = 13;
    cr_expect_str_eq(plaintext_act, plaintext_exp, "Decrypted string was: %s, expected: %s", plaintext_act, plaintext_exp);
    cr_expect_eq(count_act, count_exp, "Return value was %d, expected %d", count_act, count_exp);
}

// Tests backward letter encryption works correctly by forcing wrapping with a negative key less than -26
Test(base_suite, decrypt_wrap_letters_negative, .description="Decrypt with negative key < -26") {
    const char *ciphertext = "Quxaqutjg lgsore__EOM__";
    char plaintext_act[] = "***I can store any message!***";
    int count_act = decrypt(ciphertext, plaintext_act, -46);
    char *plaintext_exp = "Korukonda family";
    int count_exp = 15;
    cr_expect_str_eq(plaintext_act, plaintext_exp, "Decrypted string was: %s, expected: %s", plaintext_act, plaintext_exp);
    cr_expect_eq(count_act, count_exp, "Return value was %d, expected %d", count_act, count_exp);
}