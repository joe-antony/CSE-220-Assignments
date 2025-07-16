# CSE-220-Homework3
Name: {First Name, Last Name}
ID: 11#######

# Bit Manipulation
Files: BitManipulation.c, BitManipulation (executable)

## Functions:
1. int main(int argc, char* argv[])
2. int GetBit(int num, int pos);
3. int SetBit(int num, int pos);
4. int ClearBit(int num, int pos);
5. int Reversbit(int num);
6. int CountBit(int num);
7. int PowerofTwo(unsigned int num);

# Guidelines:

1. The folowing content is a sample to follow, please write your own test cases.

2. Please use gcc compiler to compile the code. To ensure your code is compiled with the C99 standard, you should use the -std=c99 flag when compiling with GCC.

3. The submitted code shouldn't produce any errors or warning messages.

4. Write brief comments to explain your thinking and work. AI generated comments or content will lead to severe penalty. You may use AI to aid your learning.

## Test Cases:
1. int GetBit(int num, int pos);

	//Testing regular number 12: 
	assert(GetBit(12, 0)==0); 

	//Testing 0 and -1 cases: 
	assert(GetBit(0, 0) == 0); 

	//Testing edge cases: 
	assert(GetBit(0xFFFFFFFF, 0) == 1)

	//Testing negative test cases: 
	assert(GetBit(-10, 0) == 0);   

	//Testing invalid positions: 
	assert(GetBit(10, 32)==-1); 

2. int SetBit(int num, int pos);



3. int ClearBit(int num, int pos);

	//Test Cases

4. int Reversbit(int num); // 

	//Test Cases

5. int CountBit(int num);

	//Test Cases 

6. int PowerofTwo(unsigned int num);

	//Test Cases

# IEEE 754 Float 
Files: float.c, float (executable)

## Functions:
1. int main(int argc, char* argv[])
2. float construct_float_sf(char sign_bit, char exponent, unsigned int fraction)

## Test Cases: 

    //Normal Test Cases:
    printf("f = %g\n", construct_float_sf(arg1,arg2,arg3));

    //Special/Edge Cases:
    printf("f = %g\n", construct_float_sf(arg1,arg2,arg3));
