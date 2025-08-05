# CSE-220-Homework4
Name: Siddharth Korukonda
ID: 115607752

This is a program that encrypts/decrypts alphanumerical messages using the Ceasar Cipher Algorithm. You can skip over/ ignore non alphanumeric characters.

NOTE: All test cases are tested using Criterion. There is no main.c file. To test on your machine use:

    make 
    make test

# Guidelines:

1. The following content is a sample to follow. Describe the function in your own words. Design and describe your testcases under the student suite section.

2. Please use gcc compiler to compile the code. To ensure your code is compiled with the C99 standard, you should use the -std=c99 flag when compiling with GCC.

3. The submitted code shouldn't produce any errors or warning messages.

4. Write brief comments in the source file to explain your thinking and work. AI generated comments or content will lead to severe penalty. You may use AI to aid your learning.

# Notes to TA:
      1. Return values:
            - The return value is the number of successful encryptions/decryptions
            - Spaces are successfully passed from plaintext to ciphertext and vice versa but are not counted in the return value

      2. Priority of return values:
            - The priority for encrypt is -2, -1, 0
            - The priority for decrypt is -2, -1, 0

      3. Empty Plaintext/Ciphertext
            - "" encrypts to "undefined__EOM__"
            - "__EOM__" decrypts to ""

      4. Memory
            - The memory used for ciphertext in encrypt is the length of the preset string inside ciphertext
            - The memory used for plaintext in decrypt is the length of the preset string inside plaintext

# Information about encrypt()/decrypt()

// Give short description about the function you implemented

## int encrypt(const char *plaintext, char *ciphertext, int key)

    Purpose: 

            The encrypt function uses a Caesar cipher to change the plaintext by shifting letters and numbers by a key value, and adds "__EOM__" at the end of the result. If the input strings are NULL, the function returns -2. If the text needed to encrypt is beyond memory capacity, the function returns -1. If the input string is empty, it writes "undefined__EOM__" to the output and the function returns 0. For encryption, the key is applied to two cases: shifting letters (key % 26) and shifting numbers (key % 10). Both values are then made non-negative. Cycling between letters and numbers are done by using modular arithmetic and then finding how much the shift really is given the number of letters or numbers there are, respectively. Next, the loop goes over each character. There are three conditions: If the character is [a-z] or [A-Z] then, encrypt within a loop of [a-z] or [A-Z], respectively, not beyond. If it's [0-9] then encrypt within a loop of [0-9] and not beyond. If the plaintext contains any non-alphanumeric characters, the characters are copied directly to the ciphertext as they're outside the encryption requirements Such non-alphanumeric characters include spaces and punctuation etc. Note that every character is checked. To find the total length of the text that is encrypted, a counter is used to count everytime a letter or number is encrypted and skips every space and non-alphanumeric character. Finally, "__EOM__" is appended to signify the end of the encrypted text. This function finds the number of modified characters after correction, which is returned by the counter.

    Parameters:

            const char *plaintext:
                     This is a char pointer to the input string that is needed to encrypt. Note that the char pointer is a constant because this string is not meant to be changed, it's only meant to be used as a template to form the encrypted message

            char *ciphertext:
                     This is a char pointer to the output string which represents the encrypted Caeser cipher message. At the end of the encrypted text, a marker, "__EOM__" is used to mark the end of the string

            int key:
                     This is a integer value that represents the number of digits the characters in the plaintext are supposed to be shifted by. This value can be positive or negative and if the number exceeds the number of letters or numbers present, is wrapped around to make sure the encryption stays valid

    Return Value:
            - The return value is the number of successful encryptions
            - Spaces are successfully passed from plaintext to ciphertext but are not counted in the return value
            

## int decrypt(const char *ciphertext, char *plaintext, int key) 

    Purpose:
            The decrypt function does the reverse of the encrypt function, taking the encrypted ciphertext and decoding it back to plaintext. It starts by checking if the either the plaintext or the ciphertext inputs are NULL, and the function returns -2 if either is NULL. Then it searches for the "__EOM__" marker manually by checking each char and seeing if the exact 7 char sequence of "__EOM__" exists. If the "__EOM__" marker isn't present in the code, the function returns -1, signifying that the decrypted string is incomplete. If the "__EOM__" message is found, the index of the first "_" in the marker is noted to mark down the end of the decrypted message and the start of the marker. Once the marker's index is found, the key is then used to find out by how much the letters or the numbers are being shifted by. Same as the encryption function, the shifting key is applied to two cases: shifting letters (key % 26) and shifting numbers (key % 10). Both values are then made non-negative. Cycling between letters and numbers are done by using modular arithmetic and then finding how much the shift really is given the number of letters or numbers there are, respectively. A loop is used to identify the type of character the encrypted message is, and decrypts it by subtracting the shift by the ASCII offset and wrapping it around the alphabet or numbers to preserve validity. Any identified non-alphanumeric characters are passed to the decrypted plaintext without any modification. The qualifications for being a non-alphanumeric character in the decrypt function is the same as the qualification for being a non-alphanumeric character in the encrypt function. A counter is used to count the number of decrypted characters from the ciphertext string. Note that non-alphanumeric characters do not count as decrypted characters as they are just passed through to the plaintext without any modification. After decryption the function terminates the plaintext string and returns count which indicates how many characters were actually decoded. Essentially this ensures that even if ciphertext contains any form of padding, only meaningful decrypted characters are considered in terms of output and overall count. This ensures a consistency between the decrypt and encrypt functions.
     
    Parameters:

            const char *ciphertext:
                     This is a char pointer to the input string that represents the encrypted Caeser cipher message. At the end of the encrypted text, a marker, "__EOM__" is used to mark the end of the string. Note that the char pointer is a constant because this string is not meant to be changed, it's only meant to be used as a template to form the decrypted message

            char *plaintext:
                     This is a char pointer to the output string which represents the decrypted Caeser cipher message

            int key:
                     This is a integer value that represents the number of digits the characters in the ciphertext are supposed to be shifted by. This value can be positive or negative and if the number exceeds the number of letters or numbers present, is wrapped around to make sure the decryption stays valid
    
    Return Value:
            - The return value is the number of successful decryptions
            - Spaces are successfully passed from ciphertext to plaintext but are not counted in the return value

<<<<<<< HEAD
=======
 ## Your Helper function (arguments,...)

    Purpose:
  
    Parameters:
>>>>>>> upstream/main

# Test Cases

## Student Suite

Includes various test cases to validate the `encrypt` and `decrypt` functions under different scenarios.

### Encrypt Tests

1. **Test Case: encrypt_null_plaintext**
   - **Plaintext**: NULL
   - **Ciphertext**: "***I can store any message!***" (nothing is changed in ciphertext because plaintext is NULL)
   - **Description**: Tests that the function returns -2 when plaintext is NULL (Key: `34`)

2. **Test Case: encrypt_null_ciphertext**
   - **Plaintext**: "Ceasar Cipher"
   - **Ciphertext**: NULL
   - **Description**: Tests that the function returns -2 when ciphertext is NULL (Key: `99`)

3. **Test Case: encrypt_both_plaintext_and_ciphertext_null**
   - **Plaintext**: NULL
   - **Ciphertext**: NULL
   - **Description**: Tests that the function returns -2 when both the plaintext and ciphertext inputs are NULL (Key: `87`)

4. **Test Case: encrypt_empty_plaintext**
   - **Plaintext**: ""
   - **Ciphertext**: "undefined__EOM__"
   - **Description**: Tests that when plaintext is empty, the function returns 0 and writes "undefined__EOM__" into ciphertext (Key: `17`)

5. **Test Case: encrypt_ciphertext_buffer_too_short**
   - **Plaintext**: "LeBron James"
   - **Ciphertext**: "short" (nothing changes as ciphertext is shorter than plaintext, which is checked before the ciphertext is modifed)
   - **Description**: Tests that the function returns -1 if the ciphertext buffer is too small to hold the result

6. **Test Case: encrypt_with_nonalphanumeric_characters**
   - **Plaintext**: "Hello, World!"
   - **Ciphertext**: "Ifmmp Xpsme__EOM__"
   - **Description**: Ensures that non-alphanumeric characters are skipped, and only valid characters are encrypted (Key: `1`)

7. **Test Case: encrypt_wrap_digits_positive**
   - **Plaintext**: "siddio1234"
   - **Ciphertext**: "fvqqvb4567__EOM__"
   - **Description**: Tests digit encryption works correctly by forcing wrapping with a positive key greater than 10 (Key: `13`)

8. **Test Case: encrypt_wrap_letters_positive**
   - **Plaintext**: "siddio1234"
   - **Ciphertext**: "fvqqvb0123__EOM__"
   - **Description**: Tests letter encryption works correctly by forcing wrapping with a positive key greater than 26 (Key: `39`)

9. **Test Case: encrypt_with_key_zero**
   - **Plaintext**: "Water Bottle"
   - **Ciphertext**: "Water Bottle__EOM__"
   - **Description**: Tests that with a shift key of 0, the plaintext to ciphertext encryption is unchanged, and the EOM marker is added (Key: `0`)

10. **Test Case: encrypt_negative_key**
    - **Plaintext**: "Abid Malik"
    - **Ciphertext**: "Yzgb Kyjgi__EOM__"
    - **Description**: Tests that backward shift encryption works correctly with a negative shift value (Key: `-2`)

11. **Test Case: encrypt_wrap_digits_negative**
    - **Plaintext**: "4Joe Antony4"
    - **Ciphertext**: "1Wbr Nagbal1__EOM__"
    - **Description**: Tests if backward digit encryption works correctly by forcing wrapping with a negative key less than -10 (Key: `-13`)

12. **Test Case: encrypt_wrap_letters_negative**
    - **Plaintext**: "Stony Brook"
    - **Ciphertext**: "Nojit Wmjjf__EOM__"
    - **Description**: Tests if backward letter encryption works correctly by forcing wrapping with a negative key less than -26 (Key: `-31`)


 
### Decrypt Tests

1. **Test Case: decrypt_null_ciphertext**
   - **Ciphertext**: NULL
   - **Plaintext**: "***I can store any message!***" (nothing is changed in plaintext because ciphertext is NULL)
   - **Description**: Tests that the function returns -2 when ciphertext is NULL (Key: `6`)

2. **Test Case: decrypt_null_plaintext**
   - **Ciphertext**: "Abcd__EOM__"
   - **Plaintext**: NULL
   - **Description**: Tests that the function returns -2 when plaintext is NULL (Key: `7`)

3. **Test Case: decrypt_both_plaintext_and_ciphertext_null**
   - **Ciphertext**: NULL
   - **Plaintext**: NULL
   - **Description**: Tests that the function returns -2 when both the plaintext and ciphertext inputs are NULL (Key: `5`)

4. **Test Case: decrypt_incomplete_eom**
   - **Ciphertext**: "wpo Ofvnboo bsdijufduvsf"
   - **Plaintext**: "***I can store any message!***" (nothing changes in plaintext because the ciphertext is invalid)
   - **Description**: Tests that the function returns -1 if the EOM marker is not found, indicating an invalid input (Key: `1`)

5. **Test Case: decrypt_empty_ciphertext_with_eom**
   - **Ciphertext**: "__EOM__"
   - **Plaintext**: ""
   - **Description**: Tests that the function returns 0 and produces an empty string when ciphertext is only the EOM marker (Key: `3`)

6. **Test Case: decrypt_incomplete_eom_and_zero_plaintext**
   - **Ciphertext**: "cats__EOM"
   - **Plaintext**: ""
   - **Description**: Tests that a corrupt EOM marker with empty output buffer returns 0 (Key: `2`)

7. **Test Case: decrypt_ciphertext_longer_than_plaintext**
   - **Ciphertext**: "tvddftt__EOM__"
   - **Plaintext**: "succ"
   - **Description**: Tests whether decryption stops before overflow and all the ciphertext characters inside the buffer length have been decrypted (Key: `1`)

8. **Test Case: decrypt_wrap_digits_positive**
   - **Ciphertext**: "34567__EOM__"
   - **Plaintext**: "01234"
   - **Description**: Tests digit decryption works correctly by forcing wrapping with a positive key greater than 10 (Key: `13`)

9. **Test Case: decrypt_wrap_letters_positive**
   - **Ciphertext**: "bqqfoe__EOM__"
   - **Plaintext**: "append"
   - **Description**: Tests letter decryption works correctly by forcing wrapping with a positive key greater than 26 (Key: `53`)

10. **Test Case: decrypt_with_nonalphanumeric_characters**
    - **Ciphertext**: "Uftu!@#123__EOM__"
    - **Plaintext**: "Test012"
    - **Description**: Ensures that non-alphanumeric characters are skipped, and only valid characters are decrypted (Key: `1`)

11. **Test Case: decrypt_negative_key**
    - **Ciphertext**: "q__EOM__"
    - **Plaintext**: "s"
    - **Description**: Tests that backward shift decryption works correctly with a negative shift value (Key: `-2`)

12. **Test Case: decrypt_key_zero**
    - **Ciphertext**: "Chill on me__EOM__"
    - **Plaintext**: "Chill on me"
    - **Description**: Tests that with a shift key of 0, the ciphertext to plaintext decryption is unchanged, and the EOM marker is removed (Key: `0`)


13. **Test Case: decrypt_wrap_digits_negative**
    - **Ciphertext**: "Eketm 76898678__EOM__"
    - **Plaintext**: "Sysha 10232012"
    - **Description**: Tests if backward digit decryption works correctly by forcing wrapping with a negative key less than -10 (Key: `-14`)

14. **Test Case: decrypt_wrap_letters_negative**
    - **Ciphertext**: "Quxaqutjg lgsore__EOM__"
    - **Plaintext**: "Korukonda family"
    - **Description**: Tests if backward letter decryption works correctly by forcing wrapping with a negative key less than -26 (Key: `-46`)



## Base Suite

Includes baseline tests provided by TAs to validate the `encrypt` and `decrypt` functions.

### Encrypt Tests

1. **Test Case: "System Fundamentals"**
   - **Plaintext**: "System Fundamentals"
   - **Ciphertext**: "Tztufn Gvoebnfoubmt__EOM__"
   - **Description**: Tests if a full plaintext message can be encrypted with key `1`.

2. **Test Case: "Cse220"**
   - **Plaintext**: "Cse220"
   - **Ciphertext**: "Dtf331__EOM__"
   - **Description**: Tests if a full plaintext message with numbers can be encrypted with key `1`.

#### Decrypt Tests

1. **Test Case: "Tztufn Gvoebnfoubmt__EOM__"**
   - **Ciphertext**: "Tztufn Gvoebnfoubmt__EOM__"
   - **Plaintext**: "System Fundamentals"
   - **Description**: Tests if a full ciphertext message can be decrypted with key `1`.

2. **Test Case: "Dtf331__EOM__"**
   - **Ciphertext**: "Dtf331__EOM__"
   - **Plaintext**: "Cse220"
   - **Description**: Tests if a full ciphertext message with numbers can be decrypted with key `1`.
