#include <stdio.h>


float construct_float_sf(char sign_bit, char exponent, unsigned int fraction) {
    /* DO NOT CHANGE THE DECLARATION OF "f" (This will be converted to float later) */
    unsigned int f = 0; // DO NOT CHANGE
    /*------------------------------------------------------------------------------*/
    
    /* Start Coding Here */
    
    
    
    
    
    
    
    /*-------------------*/
    
    /* DO NOT CHANGE THE RETURN VALUE (This returns the binary representation of "f" as float) */
    return *((float*)&f); // DO NOT CHANGE
    /* ----------------------------------------------------------------------------------------*/
}

#ifndef STUDENT_MAIN /* Do not remove this line*/
int main(int argc, char* argv[])
{
    (void) argc; // to supress compiler warning
    (void)argv;  // to supress compiler warning   
    printf("f = %g\n", construct_float_sf(0x00, 0x00, 0x000000));

    return 0;
}
#endif /* Do not remove this line*/

