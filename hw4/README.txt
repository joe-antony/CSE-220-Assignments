# CSE-220-Homework4
Name: ________
ID: ##########

This is a program that encrypts/decrypts alphanumerical messages using the Ceasar Cipher Algorithm.

NOTE: All test cases are tested using Criterion. There is no main.c file. To test on your machine use:

    make 
    make test


# Information about encrypt()/decrypt()

// Give short description about the function you implemented

## int encrypt(const char *plaintext, char *ciphertext, int key)

    Purpose:

    Parameters:

    Return Value:

## int decrypt(const char *ciphertext, char *plaintext, int key) 

    Purpose:
     
    Parameters:
    
    Return Value:

 ## void updateCharacterInformation(int a, int *start, int *range) 

    Purpose:
  
    Parameters:

# Test Cases

## Student Suite

Includes various test cases to validate the `encrypt` and `decrypt` functions under different scenarios.

### Encrypt Tests
### Decrypt Tests


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
