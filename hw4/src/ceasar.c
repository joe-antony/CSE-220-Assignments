/* Siddharth Korukonda
   CSE 220.01
   115607752
*/

#include "ceasar.h"

int encrypt(const char *plaintext, char *ciphertext, int key){
    // Edge case that returns a value of -2 if the plaintext or the ciphertext is null
    if (plaintext == NULL || ciphertext == NULL) {
        return -2;
    }

    /* eom_length captures the length of the EOM marker, which is important to know because the ciphertext might or might not have enough space for the
       marker, so finding the length of the marker makes it easier to find out if the marker can be placed or not
    */
    int eom_length = (int) strlen("__EOM__");

    /* Gets the size of the ciphertext, which is already preallocated by some dummy text, so finding the length of the ciphertext is important if we want 
       to know the buffer of the encryption and if the encryption can even happen or not
    */
    int buffer = (int) strlen(ciphertext);

    /* Edge cases to return the value of 0 if the plaintext is empty (first element of the plaintext array is the null terminator) */
    if (plaintext[0] == '\0') {
        /* The three lines below basically form the required ciphertext if the plaintext is empty
                - The first line attatches the null terminator to the ciphertext
                - The second line overwrites all the context in ciphertext with the "undefined" string. The null terminator is added to the end. The strcpy
                  string function ensures that there is a string that we can concatenate later on in the implementation without any segementation issues
                - The third line concatenates the ciphertext, which already has been overwritten by the strcpy function, with the EOM marker
        */
        ciphertext[0] = '\0';
        strcpy(ciphertext, "undefined");
        strcat(ciphertext, "__EOM__");

        return 0; // Returns 0 because 0 alphanumeric characters were successfully encrypted
    }
    
    /* Gets the length of the actual plaintext so that it can be added to the eom_length to see if the plaintext is larger than the ciphertext buffer, 
       which in that case should return a -1. This line of code makes the check easier, which is why it was included
    */
    int plaintext_length = (int) strlen(plaintext);
    
    /* A conditional to check if the plaintext length plus the EOM marker length is greater than the ciphertext buffer to see if the full plaintex can be
       encrypted or not
    */
    if (plaintext_length + eom_length > buffer) {
        return -1;
    }

    /* Replaces the ciphertext contents with an empty string with a null terminator, to ensure that the encryption goes smoothly and that the algorithm can
       implement string functions to make coding a lot easier
    */
    ciphertext[0] = '\0';

    /* Modular arithmetic is used to determine the effective shift for letters in the alphabet. Since there are 26 letters in the alphabet, we take 
       the key % 26 to ensure the shift wraps around correctly. This means that even if the key is larger than 26, the resulting shift stays within the 
       valid range of 0 to 25, effectively handling all wrap-around cases
    */
    int letter_shift = key % 26;
    /* A conditional is used to identify if the shift needed is negative, which happens if the key itself is negative. If the result of key % 26 is negative
       (which can happen when the key itself is negative), we add 26 to convert it into the equivalent positive shift within the alphabet. This ensures that
       the final letter_shift always falls within the valid range of 0 to 25, allowing proper wrap-around behavior when shifting characters
    */
    if (letter_shift < 0) {
        letter_shift += 26;
    }

    /* Modular arithmetic is used to determine the effective shift for digits in the numeric system. Since there are 10 numbers in the numeric system, we 
       take the key % 10 to ensure the shift wraps around correctly. This means that even if the key is larger than 10, the resulting shift stays within the 
       valid range of 0 to 9, effectively handling all wrap-around cases
    */
    int digit_shift = key % 10;
    /* A conditional is used to identify if the shift needed is negative, which happens if the key itself is negative. If the result of key % 10 is negative
       (which can happen when the key itself is negative), we add 10 to convert it into the equivalent positive shift within the numeric system. This 
       ensures that the final digit_shift always falls within the valid range of 0 to 9, allowing proper wrap-around behavior when shifting characters
    */
    if (digit_shift < 0) {
        digit_shift += 10;
    }

    // Two integer counters to track the position inside the ciphertext array and the number of alphanumeric characters encrypted
    int length = 0;
    int count = 0;

    // A for loop is used to traverse the plaintext and encrypt its alphanumeric values one by one
    for (int i=0; plaintext[i] != '\0'; i++) {
        // A conditional to see whether the current character in plaintext is an uppercase letter, which is a valid character to encrypt
        if (plaintext[i] >= 'A' && plaintext[i] <= 'Z') {
            /* Breakdown of the algorithm:
                  - plaintext[i] - 'A'
                        Converts the uppercase letter into a 0-based index
                  - + letter_shift
                        Adds the computed modulus Ceaser cipher shift for letters to the 0-based index value
                  - % 26
                        Additional wrapping just in case the 0-based index exceeds the number of valid alphabets, which is 26
                  - 'A' + 
                        Uses the calculated new character shifted index back into an uppercase letter
                  - ciphertext[length++] = 
                        Stores the calculated encrypted character to the next position in the ciphertext buffer
            */
            ciphertext[length++] = 'A' + (plaintext[i] - 'A' + letter_shift) % 26;
            count++; // Increment count to record the count of a successful encryption
        // A conditional to see whether the current character in plaintext is a lowercase letter, which is a valid character to encrypt
        } else if (plaintext[i] >= 'a' && plaintext[i] <= 'z') {
            /* Breakdown of the algorithm:
                  - plaintext[i] - 'a'
                        Converts the lowercase letter into a 0-based index
                  - + letter_shift
                        Adds the computed modulus Ceaser cipher shift for letters to the 0-based index value
                  - % 26
                        Additional wrapping just in case the 0-based index exceeds the number of valid alphabets, which is 26
                  - 'a' + 
                        Uses the calculated new character shifted index back into an lowercase letter
                  - ciphertext[length++] = 
                        Stores the calculated encrypted character to the next position in the ciphertext buffer
            */
            ciphertext[length++] = 'a' + (plaintext[i] - 'a' + letter_shift) % 26;
            count++; // Increment count to record the count of a successful encryption 
        // A conditional to see whether the current character in plaintext is a numeric digit, which is a valid character to encrypt
        } else if (plaintext[i] >= '0' && plaintext[i] <= '9') {
            /* Breakdown of the algorithm:
                  - plaintext[i] - '0'
                        Converts the numeric digit into a 0-based index
                  - + digit_shift
                        Adds the computed modulus Ceaser cipher shift for numeric digits to the 0-based index value
                  - % 10
                        Additional wrapping just in case the 0-based index exceeds the number of valid numeirc digits, which is 10
                  - '0' + 
                        Uses the calculated new character shifted index back into a numeric digit
                  - ciphertext[length++] = 
                        Stores the calculated encrypted character to the next position in the ciphertext buffer
            */
            ciphertext[length++] = '0' + (plaintext[i] - '0' + digit_shift) % 10;
            count++; // Increment count to record the count of a successful encryption
        // A conditional to see if the current character is a space, which needs to be added to the ciphertext as well but is not a valid encryption
        } else if (plaintext[i] == ' ') {
            /* Stores the space to the next position in the ciphertext

               No count because a space is not a valid encryption
            */
            ciphertext[length++] = ' ';
        }
    }

    /* Gives a pointer to the next available position in the ciphertext buffer. The strcpy string function is used to copy the string contents of the EOM 
       marker to the ciphertext
    */
    strcpy(&ciphertext[length], "__EOM__");

    // The number of successful encryptions is returned
    return count;
}

int decrypt(const char *ciphertext, char *plaintext, int key){
    // Edge case that returns a value of -2 if the plaintext or the ciphertext is null
    if (plaintext == NULL || ciphertext == NULL) {
        return -2;
    }

    /* Gets the size of the plaintext, which is already preallocated by some dummy text, so finding the length of the plaintext is important if we want 
       to know the buffer of the decryption and how many characters in the ciphertext needs decryption
    */
    int buffer = (int) strlen(plaintext);

    /* A conditional to check if the buffer size is 0, which means that there is 0 available space to store a decrypted character, and therefore there can't
       be a valid decryption, which means the return value should be 0
    */
    if (buffer == 0) {
        return 0;
    }

    /* An eom_index is declared and initialized to track the index of the start of the EOM marker.

       This value is set to -1 because any neutral (0) or positive number will be a valid index inside the ciphertext, which won't accurately capture the
       start of the EOM marker
    */
    int eom_index = -1;

    /* A for loop that increments through each character in the ciphertext to find the starting index of the EOM marker. The loop uses one character, and 
       looks at the next 6 indices to see if the characters at that index are the respective characters in the EOM marker. 

       This loop runs while the character isn't the null terminator and terminates when the character is a null terminator, signifying the end of the 
       ciphertext. At the end, if the starting index of the EOM marker is found, the eom_index is set to that index and is used later on
    */
    for (int i=0; ciphertext[i] != '\0'; i++) {
        if (ciphertext[i] == '_' &&
            ciphertext[i+1] == '_' &&
            ciphertext[i+2] == 'E' &&
            ciphertext[i+3] == 'O' &&
            ciphertext[i+4] == 'M' &&
            ciphertext[i+5] == '_' &&
            ciphertext[i+6] == '_') {
            eom_index = i;
            break;
        }
    }

    // If the eom_index is not found, this means that the ciphertext does not have a EOM marker and the ciphertext is incomplete. Therefore, we return -1
    if (eom_index == -1) {
        return -1;
    }

    /* Modular arithmetic is used to determine the effective shift for letters in the alphabet. Since there are 26 letters in the alphabet, we take 
       the key % 26 to ensure the shift wraps around correctly. This means that even if the key is larger than 26, the resulting shift stays within the 
       valid range of 0 to 25, effectively handling all wrap-around cases
    */
    int letter_shift = key % 26;
    /* A conditional is used to identify if the shift needed is negative, which happens if the key itself is negative. If the result of key % 26 is negative
       (which can happen when the key itself is negative), we add 26 to convert it into the equivalent positive shift within the alphabet. This ensures that
       the final letter_shift always falls within the valid range of 0 to 25, allowing proper wrap-around behavior when shifting characters
    */
    if (letter_shift < 0) {
        letter_shift += 26;
    }

    /* Modular arithmetic is used to determine the effective shift for digits in the numeric system. Since there are 10 numbers in the numeric system, we 
       take the key % 10 to ensure the shift wraps around correctly. This means that even if the key is larger than 10, the resulting shift stays within the 
       valid range of 0 to 9, effectively handling all wrap-around cases
    */
    int digit_shift = key % 10;
    /* A conditional is used to identify if the shift needed is negative, which happens if the key itself is negative. If the result of key % 10 is negative
       (which can happen when the key itself is negative), we add 10 to convert it into the equivalent positive shift within the numeric system. This 
       ensures that the final digit_shift always falls within the valid range of 0 to 9, allowing proper wrap-around behavior when shifting characters
    */
    if (digit_shift < 0) {
        digit_shift += 10;
    }

    // Two integer counters to track the position inside the plaintext array and the number of alphanumeric characters decrypted
    int length = 0;
    int count = 0;
    
    /* A for loop is used to traverse the ciphertext and decrypt its alphanumeric values one by one

       The loop condition is i<eom_index && length<buffer because there are two things that we are looking out for when we decrypt the ciphertext
            - If we have reached the EOM marker inside the ciphertext, which means no further decrypting needs to be done
            - The length of the decrypted portion of the ciphertext has reached its buffer, which means there is no more space left for decryption and
              therefore the decryption cannot continue further
    */
    for (int i=0; i<eom_index && length<buffer; i++) {
        // A conditional to see whether the current character in ciphertext is an uppercase letter, which is a valid character to decrypt
        if (ciphertext[i] >= 'A' && ciphertext[i] <= 'Z') {
            /* Breakdown of the algorithm:
                  - ciphertext[i] - 'A'
                        Converts the uppercase letter into a 0-based index
                  - - letter_shift
                        Subtracts the computed modulus Ceaser cipher shift for letters to the 0-based index value, essentially reverting the Ceaser cipher
                  - % 26
                        Additional wrapping just in case the 0-based index exceeds the number of valid alphabets, which is 26
                  - 'A' + 
                        Uses the calculated new character shifted index back into an uppercase letter
                  - plaintext[length++] = 
                        Stores the calculated decrypted character to the next position in the plaintext buffer
            */
            plaintext[length++] = 'A' + (ciphertext[i] - 'A' - letter_shift + 26) % 26;
            count++; // Increment count to record the count of a successful decryption
        // A conditional to see whether the current character in ciphertext is an lowercase letter, which is a valid character to decrypt
        } else if (ciphertext[i] >= 'a' && ciphertext[i] <= 'z') {
            /* Breakdown of the algorithm:
                  - ciphertext[i] - 'a'
                        Converts the lowercase letter into a 0-based index
                  - - letter_shift
                        Subtracts the computed modulus Ceaser cipher shift for letters to the 0-based index value, essentially reverting the Ceaser cipher
                  - % 26
                        Additional wrapping just in case the 0-based index exceeds the number of valid alphabets, which is 26
                  - 'a' + 
                        Uses the calculated new character shifted index back into an lowercase letter
                  - plaintext[length++] = 
                        Stores the calculated decrypted character to the next position in the plaintext buffer
            */
            plaintext[length++] = 'a' + (ciphertext[i] - 'a' - letter_shift + 26) % 26;
            count++; // Increment count to record the count of a successful decryption
        // A conditional to see whether the current character in ciphertext is an numeric digit, which is a valid character to decrypt
        } else if (ciphertext[i] >= '0' && ciphertext[i] <= '9') {
            /* Breakdown of the algorithm:
                  - ciphertext[i] - '0'
                        Converts the numeric digit into a 0-based index
                  - - digit_shift
                        Subtracts the computed modulus Ceaser cipher shift for numeric digits to the 0-based index value, essentially reverting the Ceaser 
                        cipher
                  - % 10
                        Additional wrapping just in case the 0-based index exceeds the number of valid numeirc digits, which is 10
                  - '0' + 
                        Uses the calculated new character shifted index back into a numeric digit
                  - plaintext[length++] = 
                        Stores the calculated decrypted character to the next position in the plaintext buffer
            */
            plaintext[length++] = '0' + (ciphertext[i] - '0' - digit_shift + 10) % 10;
            count++; // Increment count to record the count of a successful decryption
        // A conditional to see if the current character is a space, which needs to be added to the plaintext as well but is not a valid decryption
        } else if (ciphertext[i] == ' ') {
            /* Stores the space to the next position in the plaintext

               No count because a space is not a valid decryption
            */
            plaintext[length++] = ' ';
        }
    }

    // Attached a null terminator to the decrypted plaintext, completing the plaintext string
    plaintext[length] = '\0';

    // The number of successful decryptions is returned
    return count;
}