# CSE-220-Homework5
Name: Siddharth Korukonda
ID: 115607752

# Submission folder structure:


CSE220_{SBU ID#}_HW5
|
|__matrix.c
|__student_tests.c
|__README.md

## Functions:
1. int SparseMatrix(int row, int col, int** M, int** S)
2. int Addition(int RM, int CM, int RN, int CN, int RA, int CA, int** M, int** N, int** A)
3. int Multiplication(int RM, int CM, int RN, int CN, int RA, int CA, int** M, int** N, int** A)
4. int Transpose(int RA, int RC, int RAT, int CAT, int** A, int** AT)


## Notes:
1. int SparseMatrix returns -2 if there is a structural error with the matrices. Structural errors include:
        - row and col are less than or equal to 0
        - the entire matrices M or/and N or a part of matrices M or/and N are NULL
        - the order of priority for return values is decreasing order (the lower return value is returned)

2. int Addition returns -4 if there is a structural error with the matrices. Structural errors include:
        - RM, CM, RN, CN, RA, CA are less than or equal to 0
        - the entire matrices M, N, or/and A or a part of matrices M, N, or/and A are NULL
        - the order of priority for return values is decreasing order (the lower return value is returned)

3. int Multiplication returns -4 if there is a structural error with the matrices. Structural errors include:
        - RM, CM, RN, CN, RA, CA are less than or equal to 0
        - the entire matrices M, N, or/and A or a part of matrices M, N, or/and A are NULL
        - the order of priority for return values is decreasing order (the lower return value is returned)

4. int SparseMatrix returns -2 if there is a structural error with the matrices. Structural errors include:
        - RA, CA, RAT, CAT are less than or equal to 0
        - the entire matrices A or/and AT or a part of matrices A or/and AT are NULL
        - the order of priority for return values is decreasing order (the lower return value is returned)



# Guidelines:

1. Please use gcc compiler to compile the code. To ensure your code is compiled with the C99 standard, you should use the -std=c99 flag when compiling with GCC.

2. The submitted code shouldn't produce any errors or warning messages.

3. Write brief comments to explain your thinking and work. AI generated comments or content will lead to severe penalty. You may use AI to aid your learning.

